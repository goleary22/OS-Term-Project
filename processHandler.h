/*
processHandler.h
Manages process conversion
*/
#ifndef PROCESS_HANDLER_H
#define PROCESS_HANDLER_H

#include "jobHandler.h"

struct Process {
    int pid; /* process identifier */ 
    int state; /* state of the process */ 
    int time_slice; /* scheduling information */
    int run_time;
    int memory_requirement;
    int device_requirement;
    int finished;
    int start_time;
    int turnaround_time;
    int waiting_time;
    int finished_time;
};


#endif /* PROCESS_HANDLER_H */