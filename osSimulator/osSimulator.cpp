/*
osSimulator.cpp
Acts like a CPU scheduler
*/

#include "osSimulator.h"
#include "jobHandler.h"
#include "processHandler.h"
#include "readyQueueHandler.h"
#include "displayHandler.h"
#include "deviceHandler.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <list>
#include <algorithm>
#include <iterator>
#include <iomanip>

int start_time;
int current_time;
int system_memory;
int available_memory;
int system_devices;
int available_devices;
int time_quantum;

SortedLinkedList HoldQueue1;
SortedLinkedList HoldQueue2;
Process CPU;
std::vector<Process> ReadyQueue;
std::vector<Process> CompleteQueue;
std::vector<Process> WaitQueue;

std::vector<Job> jobs;
std::vector<Device> devices;

std::vector<std::string> split(std::string input_string, char delimiter) {
    std::vector<std::string> output_vector;
    std::string current_string = "";
    for (int i = 0; i < input_string.length(); i++) {
        if (input_string[i] == delimiter) {
            output_vector.push_back(current_string);
            current_string = "";
        } else {
            current_string += input_string[i];
        }
    }
    output_vector.push_back(current_string);
    return output_vector;
}

void processInstruction(std::string instruction) {
    // each line in the file starts with a letter that indicates the type of event
    // C - system configuration
    // A - job arrival
    // Q - device request
    // L - device release
    // D - display
    // split instruction into a vector of strings delimited by ' '
    // the first string in the vector is the event type
    std::vector<std::string> line_data = split(instruction, ' ');
    char event_type = line_data[0][0];

    if (event_type == EVENT_TYPE_SYSTEM_CONFIGURATION) {
        // line C 9 M=45 S=12 Q=1
        start_time = stoi(line_data[1]);
        for (int i = 2; i < line_data.size(); i++) {
            std::vector<std::string> system_configuration_data = split(line_data[i], '=');
            if (system_configuration_data[0] == "M") {
                system_memory = stoi(system_configuration_data[1]);
                available_memory = stoi(system_configuration_data[1]);
            } else if (system_configuration_data[0] == "S") {
                system_devices = stoi(system_configuration_data[1]);
                available_devices = stoi(system_configuration_data[1]);
            } else if (system_configuration_data[0] == "Q") {
                time_quantum = stoi(system_configuration_data[1]);
            }
        }

        for (int i = 0; i < system_devices; i++) {
            Device device;
            device.device_id = i;
            device.number_of_available_devices = 1;
            devices.push_back(device);
        }
    }

    else if (event_type == EVENT_TYPE_JOB_ARRIVAL) {
        // A 10 J=1 M=5 S=4 R=3 P=1 
        current_time = stoi(line_data[1]);
        int job_id, priority, memory, serial_devices, run_time;
        for (int i = 2; i < line_data.size(); i++) {
            std::vector<std::string> system_configuration_data = split(line_data[i], '=');
            if (system_configuration_data[0] == "J") {
                job_id = stoi(system_configuration_data[1]);
            } else if (system_configuration_data[0] == "M") {
                memory = stoi(system_configuration_data[1]);
            } else if (system_configuration_data[0] == "S") {
                serial_devices = stoi(system_configuration_data[1]);
            } else if (system_configuration_data[0]=="R") {
                run_time = stoi(system_configuration_data[1]);
            } else if (system_configuration_data[0]=="P") {
                priority = stoi(system_configuration_data[1]);
            }
        }
        
        handle_job_arrival_event(
            job_id, 
            priority, 
            memory, 
            serial_devices, 
            run_time
        );
    } 

    else if (event_type == EVENT_TYPE_DEVICE_REQUEST) {
        // Q 10 J=3 D=4 
        current_time = stoi(line_data[1]);
        int job_id, device;

        for (int i = 2; i < line_data.size(); i++) {
            std::vector<std::string> system_configuration_data = split(line_data[i], '=');
            if (system_configuration_data[0] == "J") {
                job_id = stoi(system_configuration_data[1]);
            } else if (system_configuration_data[0] == "D") {
                device = stoi(system_configuration_data[1]);
            }
        }

        handle_device_request_event(current_time, job_id, device);
    }

    else if (event_type == EVENT_TYPE_DEVICE_RELEASE) {
        current_time = stoi(line_data[1]);
        int job_id, device;

        for (int i = 2; i < line_data.size(); i++) {
            std::vector<std::string> system_configuration_data = split(line_data[i], '=');
            if (system_configuration_data[0] == "J") {
                job_id = stoi(system_configuration_data[1]);
            } else if (system_configuration_data[0] == "D") {
                device = stoi(system_configuration_data[1]);
            }
        }

        handle_device_release_event(current_time, job_id, device);
    }

    else if (event_type == EVENT_TYPE_DISPLAY) {
        current_time = stoi(line_data[1]);

        // call handleDisplayEvent with all the data
        handle_display_event(current_time, CPU, HoldQueue1, HoldQueue2, ReadyQueue, jobs, CompleteQueue);
    }
    // increment the current time
    current_time++;

}
//Round Robin
void processQueues() {
    bool system_active = true;
    while (system_active){
        CPU.pid = -1;
        // if the CPU is not busy
        if (CPU.pid == -1) {
            // if there are jobs in the ready queue
            if (ReadyQueue.size() > 0) {
                // set the CPU to the first job in the ready queue
                CPU = ReadyQueue[0];
                current_time++;
                CPU.start_time = current_time;
                ReadyQueue.erase(ReadyQueue.begin());
            }
        }
        // if the CPU is busy
        if (CPU.pid != -1) {
            // decrement the job's run time by the time quantum
            CPU.run_time -= time_quantum;
            

            // if the job's run time is less than or equal to 0
            if (CPU.run_time <= 0) {
                // set the job's finished to true
                CPU.finished = true;
                // set the job's turnaround time to the current time minus the job's start time
                current_time++;
                CPU.turnaround_time = current_time - CPU.start_time;
                // set the job's waiting time to the job's turnaround time minus the job's run time
                CPU.waiting_time = CPU.turnaround_time - CPU.run_time;
                // add the job to the finished queue
                CPU.finished_time = current_time;
                CPU.run_time = CPU.finished_time - CPU.start_time;
                CompleteQueue.push_back(CPU);
                available_memory += CPU.memory_requirement;
                available_devices += CPU.device_requirement;
                // set the CPU to the next job in the ready queue
                if (ReadyQueue.size() > 0) {
                    CPU = ReadyQueue[0];
                    ReadyQueue.erase(ReadyQueue.begin());
                } else {
                    CPU.pid = -1;
                }   
            }
            
            if (CPU.run_time > 0){
                // move this job to the wait queue
                WaitQueue.push_back(CPU);
                // set the CPU to the next job in the ready queue
                if (ReadyQueue.size() > 0) {
                    CPU = ReadyQueue[0];
                    ReadyQueue.erase(ReadyQueue.begin());
                } else {
                    CPU.pid = -1;
                }   
            }
        }

        // if the wait queue is not empty
        // Loop through the wait queue and find the first job that can be allocated a device
        if (WaitQueue.size() > 0) {
            for (int i = 0; i < WaitQueue.size(); i++) {
                Process process = WaitQueue[i];
                // if the job has not requested a device yet
                if (process.device_requirement == 0) {
                    // find the device in the devices vector
                    Device device;
                    for (int i = 0; i < devices.size(); i++) {
                        if (devices[i].device_id == process.device_requirement) {
                            device = devices[i];
                            break;
                        }
                    }
                    // if the device is available
                    if (device.number_of_available_devices > 0) {
                        // decrement the number of available devices
                        device.number_of_available_devices--;
                        // set the job's device requirement to the device
                        process.device_requirement = device.device_id;
                        // remove the job from the wait queue
                        WaitQueue.erase(WaitQueue.begin() + i);
                        // put the job in the ready queue
                        ReadyQueue.push_back(process);
                        break;
                    }
                }
            }
        }


        if (! HoldQueue1.isEmpty()){
            std::vector<int> job_ids;
            Job current;
            current.job_id = -1;

            while (std::find(job_ids.begin(), job_ids.end(), current.job_id) != job_ids.end()) {
                Job current = HoldQueue1.removeFirst();
                job_ids.push_back(current.job_id);
                if (current.memory_requirement <= available_memory){ current = HoldQueue1.removeFirst();
                    Process process = createProcessFromJob(current, available_memory);
                    
                    // put the process in the Ready Queue
                    ReadyQueue.push_back(process);
                } 
                else {
                    // put the job back in the hold queue
                    HoldQueue1.add(current);
                }
            }
        }
        
        if (! HoldQueue2.isEmpty()){
            std::vector<int> job_ids;
            Job current;
            current.job_id = -1;

            while (std::find(job_ids.begin(), job_ids.end(), current.job_id) != job_ids.end()) {
                Job current = HoldQueue2.removeFirst();
                job_ids.push_back(current.job_id);
                if (current.memory_requirement <= available_memory){ current = HoldQueue2.removeFirst();
                    Process process = createProcessFromJob(current, available_memory);
                    
                    // put the process in the Ready Queue
                    ReadyQueue.push_back(process);
                } 
                else {
                    // put the job back in the hold queue
                    HoldQueue2.add(current);
                }
            }
        }

        // This doesn't seem to work
        if (ReadyQueue.size() == 0 && HoldQueue1.isEmpty() && HoldQueue2.isEmpty() && WaitQueue.size() == 0 && CPU.pid == -1) {
            // call handleDisplayEvent with all the data
            handle_display_event(current_time, CPU, HoldQueue1, HoldQueue2, ReadyQueue, jobs, CompleteQueue);
            system_active = false;
        }
    }
}

// The following function is used to handle job arrival events.
void handle_job_arrival_event(
    int job_id, 
    int priority, 
    int memory, 
    int device, 
    int run_time
){
    // create a new job
    Job job;
    job.job_id = job_id;
    job.priority = priority;
    job.arrival_time = current_time;
    job.memory_requirement = memory;
    job.device_requirement = device;
    job.run_time = run_time;
    job.turnaround_time = 0;
    job.waiting_time = 0;
    job.finished = false;
    job.finished_time = 0;
    
    /*
        When a job arrives, one of three things may happen:  
        1. If there is not enough total main memory or total number of devices in the system for the job, the job is rejected never gets to one of the Hold Queues. 
        2. If there is not enough available main memory for the job, the job is put in one of the Hold Queues, based on its priority, to wait for enough available main memory. 
        3. If there is enough main memory for the job, then a process is created for the job, the required main memory is allocated to the process, and the process is put in the Ready Queue.
        1  
        Pre-allocation of memory is required, but device allocation is dynamic. Banker’s algorithm is used  for device allocation.  
        When a job terminates, the job releases any main memory and devices(s) that it held. The  release of main memory may cause one or more jobs to leave one of the Hold Queues and  move to the Ready Queue. The implicit release of devices may cause one or more jobs to move  from the Wait Queue to the Ready Queue.  
        Assume that the two Hold Queues are based on priority. There are two priorities: 1 and 2, with 1  being the highest priority. Priority is only used for the job scheduler.  
        ∙ Job scheduling for Hold Queue 1 is Shortest Job First (SJF).  
        ∙ Job scheduling for Hold Queues 2 is First In First Out (FIFO).  
        ∙ Process scheduling will be Round Robin (with a quantum).  
        
        Jobs may acquire and release devices during execution. A device can only be used by one process  at a time, because it is a serial (not a random access) device (tapes, printers, etc.)  
    */
    // if there is not enough total main memory or total number of devices in the system for the job, the job is rejected never gets to one of the Hold Queues.
    if (job.memory_requirement > system_memory || job.device_requirement > system_devices) {
        // reject the job
        return;
    }
    // if there is not enough available main memory for the job, the job is put in one of the Hold Queues, based on its priority, to wait for enough available main memory.
    if (job.memory_requirement  > available_memory) {

        if (job.priority == 1) {
            // use addSorted to put the job_node in HoldQueue1
            HoldQueue1.add(job);
        }
        // if the job's priority is 2
        if (job.priority == 2) {
            // put the job in Hold Queue 2
            HoldQueue2.add(job);
        }
    }
    // if there is enough main memory for the job, then a process is created for the job, the required main memory is allocated to the process, and the process is put in the Ready Queue.
    if (job.memory_requirement <= available_memory) {
        Process process = createProcessFromJob(job, available_memory);
        // allocate the required main memory to the process
        available_memory -= job.memory_requirement;
        // put the process in the Ready Queue
        addProcessToReadyQueue(process, ReadyQueue);
    }
}

Process createProcessFromJob(const Job job, int available_memory){
    available_memory -= job.memory_requirement;
    Process process;
    process.pid = job.job_id;
    process.state = 0;
    process.time_slice = 0;
    process.run_time = job.run_time;
    process.memory_requirement = job.memory_requirement;
    process.device_requirement = job.device_requirement;
    process.finished = job.finished;
    process.start_time = job.arrival_time;
    process.turnaround_time = job.turnaround_time;
    process.waiting_time = job.waiting_time;
    process.finished_time = job.finished_time;
    return process;
}
