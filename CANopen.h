// Copyright (c) Formula Slug 2016. All Rights Reserved.

#ifndef CAN_OPEN_H
#define CAN_OPEN_H

#include <initializer_list>

#include <FlexCAN.h>
#include "CircularBuffer.h"

// COB-IDs: MAX LENGTH of 12 bits, only the LSB 12 should be used
constexpr uint32_t cobid_TPDO5 = 0x241;  // including throttle voltage payload
constexpr uint32_t cobid_node3Heartbeat = 0x003;
constexpr uint32_t cobid_node4Heartbeat = 0x004;
constexpr uint32_t cobid_p2s = 0x013;
constexpr uint32_t cobid_s2p = 0x014;

// Payload constants
constexpr uint32_t payload_heartbeat = 0x1;

class CANopen : public FlexCAN {
 public:
  CANopen(uint32_t id, uint32_t baud);
  virtual ~CANopen();

  void setFilters(std::initializer_list<uint32_t> filters);
  bool sendMessage(const CAN_message_t& msg);
  bool recvMessage(CAN_message_t& msg);

  // queues a message to be transmitted
  void queueTxMessage(CAN_message_t msg);
  uint8_t txQueueSize();
  // dequeues a message received
  CAN_message_t dequeueRxMessage();
  uint8_t rxQueueSize();

  // listen to CAN bus and Enqueue/Dequeue messages accordingly
  void processTxMessages();
  void processRxMessages();

  // print out all messages currently in txLogsQueue and rxLogsQueue, dequeueing
  // them from each
  void printTxAll();
  void printRxAll();

 private:
  // circular buffers to hold CAN_message_t instances
  CircularBuffer<CAN_message_t> txQueue{10};
  CircularBuffer<CAN_message_t> txLogsQueue{10};
  CircularBuffer<CAN_message_t> rxQueue{10};
  CircularBuffer<CAN_message_t> rxLogsQueue{10};

  // print CAN message to serial console
  void printTxMessage(const CAN_message_t& msg) const;
  void printRxMessage(const CAN_message_t& msg) const;
};

#endif  // CAN_OPEN_H
