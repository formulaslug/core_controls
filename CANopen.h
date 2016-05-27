#ifndef CAN_OPEN_H
#define CAN_OPEN_H

#include <initializer_list>
#include <FlexCAN.h>

// Primary Teesy <-> Secondary Teensy: status, warning, and error codes
// MAX LENGTH of 12 bits, only the LSB 12 are used
constexpr uint16_t cobid_statusHeartbeat = 0x01;
constexpr uint16_t cobid_TPDO5 = 0x241; // including throttle voltage payload

class CANopen : public FlexCAN {
 public:
  CANopen(uint32_t id, uint32_t baud);
  virtual ~CANopen();

  void setFilters(std::initializer_list<uint32_t> filters);
  bool sendMessage(const CAN_message_t& msg);
  bool recvMessage(CAN_message_t& msg);

  // Print CAN message to serial console
  void printTx(const CAN_message_t& msg) const;
  void printRx(const CAN_message_t& msg) const;
};

#endif // CAN_OPEN_H
