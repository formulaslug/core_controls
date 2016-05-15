#include "CANopen.h"
#include <kinetis_flexcan.h>

CANopen::CANopen(uint32_t id, uint32_t baud) : FlexCAN(baud) {
  CAN_filter_t mask;
  mask.rtr = 0;
  mask.ext = 0;
  mask.id = id;
  begin(mask);

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWriteFast(LED_BUILTIN, 0);

  setFilters({0x620, 0x002});
}

CANopen::~CANopen() {
  end();
}

void CANopen::setFilters(std::initializer_list<uint32_t> filters) {
  CAN_filter_t filter;
  filter.rtr = 0;
  filter.ext = 0;

  uint32_t i = 0;
  for (auto id : filters) {
    // Set remaining filters to last entry if the provided list is too short
    if (i < filters.size()) {
      filter.id = id;
      i++;
    }
    setFilter(filter, i);
  }
}

bool CANopen::sendMessage(const CAN_message_t& msg) {
  if (write(msg)) {
    digitalWriteFast(LED_BUILTIN, 1);
    return true;
  } else {
    digitalWriteFast(LED_BUILTIN, 0);
    return false;
  }
}

bool CANopen::recvMessage(CAN_message_t& msg) {
  return read(msg);
}

void CANopen::printTx(const CAN_message_t& msg) const {
  Serial.print("[EVENT]: CAN message TX >> [ id: 0x");

  // Print the node's ID
  Serial.print(msg.id, HEX);

  Serial.print(", value: 0x");
  for (uint32_t i = 0; i < msg.len; ++i) {
    // Print message contents
    Serial.print(msg.buf[i], HEX);
  }

  Serial.println(" ]");
}

void CANopen::printRx(const CAN_message_t& msg) const {
  Serial.print("[EVENT]: CAN message RX << [ id: 0x");

  // Print the node's ID
  Serial.print(msg.id, HEX);

  Serial.print(", value: 0x");
  for (uint32_t i = 0; i < msg.len; ++i) {
    // Print message contents
    Serial.print(msg.buf[i], HEX);
  }

  Serial.println(" ]");
}
