import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import esp32_ble_tracker
from esphome.const import CONF_ID, CONF_ESP32_BLE_ID, CONF_RSSI_THRESHOLD

DEPENDENCIES = ["esp32_ble_tracker"]

custom_ble_scanner_ns = cg.esphome_ns.namespace("custom_ble_scanner")
CustomBLEScanner = custom_ble_scanner_ns.class_(
    "CustomBLEScanner", cg.Component, esp32_ble_tracker.ESPBTDeviceListener
)

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(CustomBLEScanner),
        cv.Required(CONF_ESP32_BLE_ID): cv.use_id(esp32_ble_tracker.ESP32BLETracker),
        cv.Optional(CONF_RSSI_THRESHOLD, default=-100): cv.int_,
    }
).extend(cv.COMPONENT_SCHEMA)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    cg.add(var.set_rssi_threshold(config[CONF_RSSI_THRESHOLD]))
    parent = await cg.get_variable(config[CONF_ESP32_BLE_ID])
    cg.add(parent.register_listener(var))