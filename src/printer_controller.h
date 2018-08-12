/* */

#ifndef PRINTER_CONTROLLER_H_
#define PRINTER_CONTROLLER_H_

#include <esphomelib/mqtt/mqtt_component.h>
#include <esphomelib/controller.h>
#include <ArduinoJson.h>

#include <map>
#include <string>


using esphomelib::StoringController;
using esphomelib::mqtt::MQTTComponent;
using esphomelib::mqtt::SendDiscoveryConfig;


struct color {
    float r;
    float g;
    float b;
    float w;
    float state;
};


class MQTTPrinterController : public StoringController, public MQTTComponent {
 public:
     MQTTPrinterController(const std::string &event_topic,
                           const std::string &progress_topic,
                           const std::string &temperature_topic);
     void setup() override;
     void add_state_color(const std::string &state,
                          float r = 0,
                          float g = 0,
                          float b = 0,
                          float w = 0,
                          float light_state = 1.0f);

     bool is_internal() override;
     void send_initial_state() {}
     void send_discovery(JsonBuffer &buffer,
                         JsonObject &root,
                         SendDiscoveryConfig &config) {}

 protected:
     std::string event_topic_;
     std::string progress_topic_;
     std::string temperature_topic_;

     std::map<std::string, struct color> state_map_{};

     void parse_state_change(const JsonObject &root);

     std::string friendly_name() const override;
     std::string component_type() const override;
};


#endif  /* PRINTER_CONTROLLER_H_ */
