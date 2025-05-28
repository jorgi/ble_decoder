# ESPHome BLE Decoder for BTHome v2 Devices

This ESPHome project provides a ready-to-use configuration to decode data from BTHome v2 BLE (Bluetooth Low Energy) devices and publish it to Home Assistant via MQTT or native ESPHome API.

## 📦 Features

- 📡 BLE decoding of temperature, humidity, voltage from BTHome v2 sensors
- ✅ Compatible with `BT2BEE-BTH01`, `TH05`, and similar devices
- 🔁 Data filtering, smoothing (median), and validation
- 🧠 Optional integration with Victron SmartSolar devices via BLE
- 🌐 Auto-discovers in Home Assistant via ESPHome
- 🧾 Captures public IP via HTTP request (useful for diagnostics)
- 📊 BLE RSSI signal strength sensors included
- 🧩 Modular YAML structure for clean reuse and expansion

---

## 🛠 Project Structure

```bash
esphome_ble_package/
├── bthome_decoder.yaml              # Main ESPHome config
└── packages/
    └── ble_sensor/
        ├── bt2bee_bth01.yaml        # BT2BEE-BTH01 BLE decoder
        ├── th05.yaml                # TH05 BLE decoder
        └── victron_ble.yaml         # Optional Victron MPPT support
