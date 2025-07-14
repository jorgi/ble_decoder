#include "ble_scanner.h"
#include "esphome/core/log.h"

namespace esphome {
namespace ble_scanner {

static const char *const TAG = "BLEScanner";

void BLEScanner::setup() {
  ESP_LOGD(TAG, "✅ BLE Scanner Initialized!");
}

void BLEScanner::loop() {
  unsigned long current_time = millis();

  // ✅ Log scan activity every 60 seconds to confirm it's running
  if (current_time - last_log_time_ > 60000) {
    ESP_LOGD(TAG, "BLE scanner is active...");
    last_log_time_ = current_time;
  }
}

// ✅ Log all detected BLE devices (MAC & RSSI)
void BLEScanner::on_ble_advertise(const esphome::esp32_ble_tracker::ESPBTDevice &device) {
  ESP_LOGD(TAG, "🔎 BLE Device Found! MAC: %s, RSSI: %d",
           device.address_str().c_str(), device.get_rssi());
}

}  // namespace ble_scanner
}  // namespace esphome