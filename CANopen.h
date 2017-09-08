// Copyright (c) 2016-2017 Formula Slug. All Rights Reserved.

#ifndef CAN_OPEN_H
#define CAN_OPEN_H

#include <initializer_list>

#include <FlexCAN.h>

#include "CircularBuffer.h"

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
