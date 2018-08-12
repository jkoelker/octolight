/* */

#ifndef CONFIG_H_
#define CONFIG_H_


#if __has_include("config.user..h") || defined(CONFIG_USER)
    #include "config.user.h"
#endif


#ifndef APP_NAME
    #define APP_NAME "octolight"
#endif


#ifndef SSID
    #warning "SSID not defined."
    #error "Did you forget to copy config.user.h.sample to config.user.h?"
#endif


#ifndef SSID_PASSWORD
    #define SSID_PASSWORD ""
#endif


#ifndef ENABLE_OTA
    #define ENABLE_OTA 1
#endif


#if ENABLE_OTA
#ifndef OTA_PASSPHRASE
    #warning "OTA_PASSPHRASE not defined. OTA server will accept any firmware."
#endif
#endif


#ifndef ENABLE_WEB_SERVER
    #define ENABLE_WEB_SERVER 1
#endif


#ifndef MQTT_HOST
    #define MQTT_HOST "mqtt"
#endif


#ifndef MQTT_PORT
    #define MQTT_PORT 1883
#endif


#ifndef MQTT_USERNAME
    #define MQTT_USERNAME ""
#endif


#ifndef MQTT_PASSWORD
    #define MQTT_PASSWORD ""
#endif

#ifndef NUM_LEDS
    #define NUM_LEDS 1
#endif

#ifndef DATA_PIN
    #define DATA_PIN 13
#endif

#ifndef CLK_PIN
    #define CLK_PIN 14
#endif

#ifndef LED_TYPE
    #define LED_TYPE APA102
#endif

#ifndef COLOR_ORDER
    #define COLOR_ORDER BGR
#endif

#ifndef OCTOPRINT_BASE_TOPIC
    #define OCTOPRINT_BASE_TOPIC "octoprint/"
#endif

#ifndef OCTOPRINT_EVENT_TOPIC
    #define OCTOPRINT_EVENT_TOPIC OCTOPRINT_BASE_TOPIC "event/"
#endif

#ifndef OCTOPRINT_PROGRESS_TOPIC
    #define OCTOPRINT_PROGRESS_TOPIC OCTOPRINT_BASE_TOPIC "progress/"
#endif

#ifndef OCTOPRINT_TEMPERATURE_TOPIC
    #define OCTOPRINT_TEMPERATURE_TOPIC OCTOPRINT_BASE_TOPIC "temperature/"
#endif

#endif  /* CONFIG_H_ */
