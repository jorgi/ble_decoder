#include "ble_scanner.h"
#include "esphome/core/log.h"

namespace esphome {
namespace custom_ble_scanner {

static const char *TAG = "custom_ble_scanner";

void CustomBLEScanner::setup() {
  ESP_LOGD(TAG, "Setting up Custom BLE Scanner, RSSI threshold: %d dBm", rssi_threshold_);
}

void CustomBLEScanner::loop() {}

void CustomBLEScanner::on_ble_advertisement(esp32_ble_tracker::ESPBTAdvertisedDevice &device) {
  if (millis() - last_log_time_ >= 1000) {
    ESP_LOGD(TAG, "BLE Advertisement - MAC: %s, RSSI: %d dBm", device.get_address_str().c_str(), device.get_rssi());
    last_log_time_ = millis();
  }
  parse_device(device);
}

bool CustomBLEScanner::parse_device(const esp32_ble_tracker::ESPBTDevice &device) {
  if (device.get_rssi() < rssi_threshold_) {
    ESP_LOGV(TAG, "Device %s skipped due to low RSSI: %d dBm", device.address_str().c_str(), device.get_rssi());
    return false;
  }
  ESP_LOGD(TAG, "Processing device %s, RSSI: %d dBm", device.address_str().c_str(), device.get_rssi());
  return true;
}

void CustomBLEScanner::set_rssi_threshold(int rssi) {
  rssi_threshold_ = rssi;
  ESP_LOGD(TAG, "RSSI threshold set to %d dBm", rssi_threshold_);
}

}  // namespace custom_ble_scanner
}  // namespace esphome