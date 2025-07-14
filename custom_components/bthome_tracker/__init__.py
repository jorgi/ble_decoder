import esphome.codegen as cg
import esphome.config_validation as cv

bthome_tracker_ns = cg.esphome_ns.namespace("bthome_tracker")
BTHomeTracker = bthome_tracker_ns.class_("BTHomeTracker", cg.Component)

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(BTHomeTracker),
})

def to_code(config):
    var = cg.new_Pvariable(config[cv.GenerateID()])
    yield cg.register_component(var, config)