/* */

#include <esphomelib/controller.h>
#include <esphomelib/log.h>
#include <esphomelib/light/light_state.h>
#include <esphomelib/mqtt/mqtt_component.h>
#include <ArduinoJson.h>

#include <string>

#include "printer_controller.h"

using esphomelib::light::LightState;
using esphomelib::mqtt::MQTTComponent;


MQTTPrinterController::MQTTPrinterController(
            const std::string &event_topic,
            const std::string &progress_topic,
            const std::string &temperature_topic) :
        MQTTComponent(),
        event_topic_(event_topic),
        progress_topic_(progress_topic),
        temperature_topic_(temperature_topic) {
}


void MQTTPrinterController::setup() {
    ESP_LOGCONFIG(TAG, "Setting up MQTT Printer Controller...");

    this->subscribe_json(this->event_topic_ + "PrinterStateChanged",
                         [&](JsonObject &root) {
        this->parse_state_change(root);
    });
}


void MQTTPrinterController::add_state_color(const std::string &state,
                                            float r,
                                            float g,
                                            float b,
                                            float w,
                                            float bright,
                                            float light_state) {
    this->state_map_[state] = { r, g, b, w, bright, light_state};
}


void MQTTPrinterController::parse_state_change(const JsonObject &root) {
    const char* state_id = root["state_id"];
    auto state_color_it = this->state_map_.find(state_id);

    if (state_color_it == this->state_map_.end()) {
        return;
    }

    auto color = state_color_it->second;

    for (LightState *ls: this->lights_) {
        auto v = ls->get_remote_values();

        if (color.state > 0.0f) {
            v.set_brightness(color.bright);
            v.set_red(color.r / 255.0f);
            v.set_green(color.g / 255.0f);
            v.set_blue(color.b / 255.0f);
            v.set_white(color.w / 255.0f);
            v.normalize_color(ls->get_traits());
        }

        v.set_state(color.state);
        ls->start_default_transition(v);
    }
}


bool MQTTPrinterController::is_internal() {
    return false;
}


std::string MQTTPrinterController::friendly_name() const {
    return "octoprint";
}


std::string MQTTPrinterController::component_type() const {
    return "octoprint";
}
