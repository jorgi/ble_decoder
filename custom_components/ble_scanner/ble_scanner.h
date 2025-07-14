#pragma once

#include "esphome/core/component.h"
#include "esphome/components/esp32_ble_tracker/esp32_ble_tracker.h"

namespace esphome {
namespace ble_scanner {

class BLEScanner : public Component, public esp32_ble_tracker::ESPBTDeviceListener {
 public:
  void setup() override;
  void loop() override;
  void on_ble_advertise(const esphome::esp32_ble_tracker::ESPBTDevice &device);

 protected:
  unsigned long last_log_time_ = 0;
};

}  // namespace ble_scanner
}  // namespace esphome