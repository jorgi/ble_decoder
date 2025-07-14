#ifndef CUSTOM_BTHOME_H
#define CUSTOM_BTHOME_H
#include <string>
struct BTHomeDevice {
  std::string mac;
  std::string name;
  int rssi;
  float temperature;
  float humidity;
  float voltage;
  bool valid;
  bool discovered;
};
static BTHomeDevice device_data[10];
#endif