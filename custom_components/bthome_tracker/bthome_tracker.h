#pragma once

#include "esphome/core/component.h"
#include "esphome/components/esp32_ble_tracker/esp32_ble_tracker.h"
#include "esphome/components/mqtt/mqtt_client.h"
#include <vector>

namespace esphome {
namespace bthome_tracker {

struct BTHomeDevice {
  std::string mac;
  int rssi;
  float temperature;
  float humidity;
  float voltage;
  bool valid = false;
};

class BTHomeTracker : public Component, public esp32_ble_tracker::ESPBTDeviceListener {
 public:
  void setup() override;
  void loop() override;
  void on_ble_advertise(const esphome::esp32_ble_tracker::ESPBTDevice &device);  // ✅ Removed `override`
  bool parse_device(const esphome::esp32_ble_tracker::ESPBTDevice &device) override;
  void set_mqtt_client(mqtt::MQTTClientComponent *mqtt_client) { mqtt_client_ = mqtt_client; }

 protected:
  mqtt::MQTTClientComponent *mqtt_client_;
  std::vector<BTHomeDevice> devices_;  // ✅ Stores discovered BLE devices
  unsigned long last_publish_time_ = 0;

  void publish_device_list();  // ✅ Function to publish device list every 60s
  void clean_old_devices();  // ✅ Function to manage memory and remove outdated devices
};
}  // namespace bthome_tracker
}  // namespace esphome