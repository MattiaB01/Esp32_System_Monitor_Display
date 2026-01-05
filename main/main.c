/*
 * main.c
 *
 *  Created on: 31 lug 2023
 *      Author: Mattia
 */

#include "esp_log.h"

#include <string.h>

#include "WiFi.h"

#include "ssd1306.h"

#include "mqtt_client.h"

SSD1306_t oled_dev;

#define MQTT_URI "mqtt://192.168.1.183:1883"
#define MQTT_TOPIC1 "system/cpu"
#define MQTT_TOPIC2 "system/ram"
#define MQTT_TOPIC3 "system/disk"

#define DEBUG 1

static const char *TAG = "MAIN";

static void mqtt_start();

void app_main(void) {

#ifdef DEBUG
#endif

  // Start Wifi
  startWifi();

  ESP_LOGE(TAG, "This is error log");
  ESP_LOGW(TAG, "This is warning log");
  ESP_LOGI(TAG, "This is info log");
  ESP_LOGD(TAG, "This is debug log");
  ESP_LOGV(TAG, "This is verbos log");
  i2c_master_init(&oled_dev, 17, 18, 21); // SDA=17, SCL=18, RESET=16

  ESP_LOGI(TAG, "info");
  ESP_LOGD(TAG, "debug");
  // Inizializza display SSD1306
  ssd1306_init(&oled_dev, 128, 64); // se il tuo display è 128x64

  // Pulisce il display
  ssd1306_clear_screen(&oled_dev, false);

  char *text = "Dashboard";

  int len = (int)strlen(text);
  // Scrive una stringa di prova
  ssd1306_display_text(&oled_dev, 0, text, len, false);
  // WiFi icon 16x16, 1bpp
  // 1 = pixel acceso
 

  mqtt_start();
}
static void mqtt_event_handler(void *arg, esp_event_base_t base,
                               int32_t event_id, void *event_data) {
  esp_mqtt_event_handle_t event = event_data;

  switch (event_id) {

  case MQTT_EVENT_CONNECTED:
    ESP_LOGI(TAG, "MQTT connected");
    esp_mqtt_client_subscribe(event->client, MQTT_TOPIC1, 0);
    esp_mqtt_client_subscribe(event->client, MQTT_TOPIC2, 0);
    esp_mqtt_client_subscribe(event->client, MQTT_TOPIC3, 0);
    break;

  case MQTT_EVENT_DATA: {
    char topic_buf[32];

    memcpy(topic_buf, event->topic, event->topic_len);
    topic_buf[event->topic_len] = '\0';
    ESP_LOGI(TAG, "%s", topic_buf);

    char data[32] = {0};
    snprintf(data, event->data_len + 1, "%.*s", event->data_len, event->data);

    float cpu = atof(data);
    ESP_LOGI(TAG, "CPU usage: %.1f %%", cpu);
    
    char buf[32];

    if (strcmp(topic_buf, MQTT_TOPIC1) == 0)

    {

      snprintf(buf, sizeof(buf), "Cpu:  %.*s %%  ", event->data_len,
               event->data);

      ssd1306_display_text(&oled_dev, 2, buf, strlen(buf), false);
      break;
    } else if (strcmp(topic_buf, MQTT_TOPIC2) == 0) {
      snprintf(buf, sizeof(buf), "Ram:  %.*s %%  ", event->data_len,
               event->data);

      ssd1306_display_text(&oled_dev, 4, buf, strlen(buf), false);
      break;
    } else if (strcmp(topic_buf, MQTT_TOPIC3) == 0){
      snprintf(buf, sizeof(buf), "Disk: %.*s %%  ", event->data_len,
               event->data);

      ssd1306_display_text(&oled_dev, 6, buf, strlen(buf), false);
      break;
    }
  }

  default:
    break;
  }
}

static void mqtt_start(void) {
  esp_mqtt_client_config_t mqtt_cfg = {.broker.address.uri = MQTT_URI};

  esp_mqtt_client_handle_t client = esp_mqtt_client_init(&mqtt_cfg);
  esp_mqtt_client_register_event(client, ESP_EVENT_ANY_ID, mqtt_event_handler,
                                 NULL);
  esp_mqtt_client_start(client);
}
