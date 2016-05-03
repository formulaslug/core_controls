#ifndef CAN_OPEN_H
#define CAN_OPEN_H

#include <initializer_list>
#include <FlexCAN.h>

constexpr uint32_t k_statusHeartbeat = 3000;

class CANopen : public FlexCAN {
 public:
  CANopen(uint32_t id, uint32_t baud);
  virtual ~CANopen();

  void setFilters(std::initializer_list<uint32_t> filters);
  bool sendMessage(const CAN_message_t& msg);
  bool recvMessage(CAN_message_t& msg);
};

#endif // CAN_OPEN_H
