/* */

#include <esphomelib.h>
#include <esphomelib/esppreferences.h>
#include <esphomelib/log.h>
#include <esphomelib/light/light_effect.h>

#include <FastLED.h>

#include "config.h"
#include "printer_controller.h"


using esphomelib::App;
using esphomelib::light::light_effect_entries;


void setup() {
    App.set_name(APP_NAME);
    App.init_log();

    App.init_wifi(SSID, SSID_PASSWORD);

#ifdef ENABLE_OTA
#ifdef OTA_PASSPHRASE
    auto *ota = App.init_ota();
    ota->set_auth_plaintext_password(OTA_PASSPHRASE);
#else
    App.init_ota();
#endif  /* OTA_PASSPHRASE */
#endif  /* ENABLE_OTA */


    App.init_mqtt(MQTT_HOST,
                  MQTT_USERNAME,
                  MQTT_PASSWORD);


#ifdef ENABLE_WEB_SERVER
    App.init_web_server();
#endif  /* ENABLE_WEB_SERVER */

    App.make_status_led(LED_BUILTIN);

    auto printer = new MQTTPrinterController(OCTOPRINT_EVENT_TOPIC,
                                             OCTOPRINT_PROGRESS_TOPIC,
                                             OCTOPRINT_TEMPERATURE_TOPIC);
    printer->add_state_color("OPERATIONAL", 255, 255, 255, 255, 0.5f, 1.0f);
    printer->add_state_color("OFFLINE", 0, 0, 0, 0, 0.0f, 0.0f);

    App.register_component(printer);
    App.register_controller(printer);

    auto fast_led = App.make_fast_led_light("printer_light");
    fast_led.fast_led->add_leds<LED_TYPE,
                                DATA_PIN,
                                CLK_PIN,
                                COLOR_ORDER>(NUM_LEDS);
    fast_led.fast_led->get_controller()->setCorrection(TypicalSMD5050);

    light_effect_entries.empty();

    App.setup();
}


void loop() {
    App.loop();
}
