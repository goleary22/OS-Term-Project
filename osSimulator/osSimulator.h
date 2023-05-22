/*
osSimulator.h
*/
#ifndef OSSIMULATOR_H
#define OSSIMULATOR_H
#include "processHandler.h"
#include "readyQueueHandler.h"
#include "jobHandler.h"
#include "deviceHandler.h"
#include "displayHandler.h"
#include <vector>
#include <string>


// The following constants are used to define the different types of events.
const char EVENT_TYPE_SYSTEM_CONFIGURATION = 'C';
const char EVENT_TYPE_JOB_ARRIVAL = 'A';
const char EVENT_TYPE_DEVICE_REQUEST = 'Q';
const char EVENT_TYPE_DEVICE_RELEASE = 'L';
const char EVENT_TYPE_DISPLAY = 'D';

extern int start_time;
extern int current_time;
extern int system_memory;
extern int available_memory;
extern int system_devices;
extern int available_devices;
extern int time_quantum;

extern SortedLinkedList HoldQueue1;
extern SortedLinkedList HoldQueue2;
extern Process CPU;
extern std::vector<Process> ReadyQueue;
extern std::vector<Process> CompleteQueue;
extern std::vector<Process> WaitQueue;

extern std::vector<Job> jobs;
extern std::vector<Device> devices;


void processInstruction(std::string instruction);
void processQueues();
void handle_job_arrival_event(
    int job_id, 
    int priority, 
    int memory, 
    int device, 
    int run_time
);
Process createProcessFromJob(const Job job, int available_memory);

int getTotalDevices();

#endif /* OSSIMULATOR_H */