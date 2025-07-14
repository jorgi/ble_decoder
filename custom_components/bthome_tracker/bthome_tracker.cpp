#include "bthome_tracker.h"
#include "esphome/core/log.h"
#include "esphome/components/esp32_ble_tracker/esp32_ble_tracker.h"

namespace esphome {
namespace bthome_tracker {

static const char *const TAG = "bthome_tracker";

void BTHomeTracker::setup() {
  ESP_LOGD(TAG, "✅ BTHomeTracker Component Initialized!");
}

void BTHomeTracker::loop() {
  unsigned long current_time = millis();

  // ✅ Publish full device list every 60 seconds
  if (current_time - last_publish_time_ > 60000) {
    publish_device_list();
    clean_old_devices();  // ✅ Remove outdated devices to optimize memory
    last_publish_time_ = current_time;
  }
}

// ✅ Log all BLE advertisements to verify scanning is active
void BTHomeTracker::on_ble_advertise(const esphome::esp32_ble_tracker::ESPBTDevice &device) {
  ESP_LOGD(TAG, "🔎 BLE Advertisement Seen! MAC: %s, RSSI: %d",
           device.address_str().c_str(), device.get_rssi());

  auto mac = device.address_str();
  mac.erase(std::remove(mac.begin(), mac.end(), ':'), mac.end());

  auto service_datas = device.get_service_datas();
  const std::vector<uint8_t> *service_data = nullptr;

  for (const auto &data : service_datas) {
    if (data.uuid == esphome::esp32_ble_tracker::ESPBTUUID::from_uint16(0xFCD2)) {
      service_data = &data.data;
      break;
    }
  }

  if (service_data == nullptr || service_data->size() < 14) {
    ESP_LOGD(TAG, "No valid BTHome service data found.");
    return;
  }

  float temp = ((*service_data)[6] | ((*service_data)[7] << 8)) / 100.0;
  float hum = ((*service_data)[9] | ((*service_data)[10] << 8)) / 100.0;
  float volt = ((*service_data)[12] | ((*service_data)[13] << 8)) / 1000.0;
  int rssi = device.get_rssi();

  if ((*service_data)[5] != 0x02 || (*service_data)[8] != 0x03 || (*service_data)[11] != 0x0C ||
      temp <= -40 || temp >= 100 || hum < 0 || hum > 100 || volt <= 0 || volt >= 4) {
    ESP_LOGD(TAG, "Invalid BTHome data detected, ignoring...");
    return;
  }

  ESP_LOGD(TAG, "✅ BTHome Device Found! MAC: %s, Temp: %.2f°C, Hum: %.2f%%, Volt: %.3fV, RSSI: %d",
           mac.c_str(), temp, hum, volt, rssi);

  // ✅ Check if device already exists in list
  for (auto &stored_device : devices_) {
    if (stored_device.mac == mac) {
      stored_device.rssi = rssi;
      stored_device.temperature = temp;
      stored_device.humidity = hum;
      stored_device.voltage = volt;
      stored_device.valid = true;
      return;  // ✅ Update existing entry, no duplicate added
    }
  }

  // ✅ Store new device if not found in list
  devices_.push_back({mac, rssi, temp, hum, volt, true});
}

// ✅ Publish stored device list to MQTT every 60s
void BTHomeTracker::publish_device_list() {
  if (!mqtt_client_ || devices_.empty()) return;

  ESP_LOGD(TAG, "Publishing %d BLE devices to MQTT", devices_.size());

  std::string payload = "[";
  for (size_t i = 0; i < devices_.size(); i++) {
    payload += "{";
    payload += "\"mac\":\"" + devices_[i].mac + "\",";
    payload += "\"rssi\":" + std::to_string(devices_[i].rssi) + ",";
    payload += "\"temperature\":" + std::to_string(devices_[i].temperature) + ",";
    payload += "\"humidity\":" + std::to_string(devices_[i].humidity) + ",";
    payload += "\"voltage\":" + std::to_string(devices_[i].voltage);
    payload += "}";
    if (i < devices_.size() - 1) payload += ",";
  }
  payload += "]";

  mqtt_client_->publish("homeassistant/sensor/bthome_device_list/state", payload);
}

// ✅ Remove old devices from list periodically to manage memory usage
void BTHomeTracker::clean_old_devices() {
  if (devices_.size() > 100) {  // ✅ Trim list if too large
    ESP_LOGD(TAG, "Trimming BLE device list, removing oldest entries...");
    devices_.erase(devices_.begin(), devices_.begin() + 50);
  }
}

bool BTHomeTracker::parse_device(const esphome::esp32_ble_tracker::ESPBTDevice &device) {
  ESP_LOGD(TAG, "Parsing BLE device: %s", device.address_str().c_str());
  return true;
}

}  // namespace bthome_tracker
}  // namespace esphome