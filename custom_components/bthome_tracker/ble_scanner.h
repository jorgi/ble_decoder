#pragma once

#include "esphome/core/component.h"
#include "esphome/components/esp32_ble_tracker/esp32_ble_tracker.h"

namespace esphome {
namespace custom_ble_scanner {

class CustomBLEScanner : public Component, public esp32_ble_tracker::ESPBTDeviceListener {
 public:
  void setup() override;
  void loop() override;
  void on_ble_advertisement(esp32_ble_tracker::ESPBTAdvertisedDevice &device) override;
  bool parse_device(const esp32_ble_tracker::ESPBTDevice &device) override;

  void set_rssi_threshold(int rssi);

 protected:
  unsigned long last_log_time_ = 0;
  int rssi_threshold_ = -100;
};

}  // namespace custom_ble_scanner
}  // namespace esphome