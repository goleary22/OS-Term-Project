/*
deviceHandler.h
manages device queue
*/

#ifndef DEVICEHANDLER_H
#define DEVICEHANDLER_H

#include <vector>

struct Device {
  int device_id;
  int number_of_available_devices;
};

// The following function is used to handle device request events.
void handle_device_request_event(int time, int job_id, int device);

// The following function is used to handle device release events.
void handle_device_release_event(int time, int job_id, int device);



#endif /* DEVICEHANDLER_H */