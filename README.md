# ESPHome BLE Decoder for BTHome v2 Devices

This ESPHome project provides a BLE-to-MQTT gateway for decoding and forwarding data from BTHome v2 sensors. Designed for integration with Home Assistant.

## Features

- BLE decoding of BTHome v2 format (temperature, humidity, voltage)
- MQTT publishing with Home Assistant Discovery support
- Compatible with BT2BEE-BTH01, TH05 and similar BLE sensors
- ESP32-based setup with HTTP-based IP check and LED heartbeat

## Setup

1. Add your Wi-Fi and MQTT credentials to `secrets.yaml`:
```yaml
wifi_ssid: "your_wifi_ssid"
wifi_password: "your_wifi_password"
mqtt_broker: "192.168.1.100"
mqtt_user: "mqtt_username"
mqtt_password: "mqtt_password"
```

2. Flash `bthome_decoder.yaml` to your ESP32.

3. Home Assistant will auto-discover the MQTT sensors.

## License

MIT License