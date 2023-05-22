/*
displayHandler.cpp
handles printing information to the console
*/

#include "displayHandler.h"
#include "processHandler.h"
#include "jobHandler.h"
#include "deviceHandler.h"
#include "osSimulator.h"
#include <iostream>
#include <vector>


// The following function is used to handle display events.
void handle_display_event(
    int time, 
    Process CPU, 
    SortedLinkedList HoldQueue1, 
    SortedLinkedList HoldQueue2,
    std::vector<Process> ReadyQueue, 
    std::vector<Job> jobs, 
    std::vector<Process> CompleteQueue
    ){
    /*
        the following should  be printed:  
        a) A list of each job that has entered the system; for each job, print the state of the job (e.g.,  running on the CPU, in the Hold Queue, or finished at time 11), the remaining service time  for unfinished jobs, and the turnaround time and waiting time for finished jobs.  
        b) The contents of each queue.  
        c) The system turnaround time only at the last display. Assume that the input file has a "D  9999" command at the end, so that you present the final state of the system.  
    */
    // print the current time
    std::cout << "Current Time: " << time << std::endl;
    std::cout << "Available Main Memory: " << available_memory << std::endl;
    //std::cout << "Current Devices: " << device.number_of_available_devices << std::endl;

    // print a table header with all the fields in CPU with a line of dashes and a line of equal signs
   std::cout<< "Process running on CPU:" <<std::endl;
   std::cout<< "PID\tFinished Time\tTime Left" << std::endl;
   std::cout<< "---\t-------------\t-------------\t---------------" << std::endl;
    // print the pid, state, time slice, run time, memory requirement, device requirement, finished, start time, turnaround time, and waiting time for the CPU
   std::cout<< CPU.pid << "\t" << CPU.finished_time<< "\t\t" << CPU.finished_time << std::endl;

   std::cout<< "Hold Queue 1:" <<std::endl;
    // print a table header with all the fields in the HoldQueue1 with a line of dashes and a line of equal signs
   std::cout<< "Job ID\tRun Time" <<std::endl;
   std::cout<< "------\t--------" <<std::endl;
    // print all the items in HoldQueue1
    HoldQueue1.print();

    std::cout<< "Hold Queue 2:" <<std::endl;
    // print a table header with all the fields in Hold2Queue with a line of dashes and a line of equal signs
   std::cout<< "Job ID\tRun Time" <<std::endl;
   std::cout<< "------\t--------" <<std::endl;
    // print all the items in HoldQueue2
    HoldQueue2.print();

   std::cout<< "Ready Queue:" <<std::endl;
    // print a table header with all the fields in the Ready Queue with a line of dashes and a line of equal signs
   std::cout<< "PID\tRun Time\tTime Finished" <<std::endl;
   std::cout<< "---\t--------\t-------------" <<std::endl;
    // print the pid, state, time slice, run time, memory requirement, device requirement, finished, start time, turnaround time, and waiting time for each process
    for (int i = 0; i < ReadyQueue.size(); i++) {
        Process process = ReadyQueue[i];
       std::cout<< process.pid << "\t" << process.run_time << "\t\t" << process.finished_time <<std::endl;
    }

   std::cout<< "Wait Queue:" <<std::endl;
    // print a table header with all the fields in the WaitQueue with a line of dashes and a line of equal signs
   std::cout<< "Job ID\tRun Time\tFinished Time" <<std::endl;
   std::cout<< "------\t---------\t------------" <<std::endl;
    // print the job id, priority, memory requirement, device requirement, run time, turnaround time, waiting time, and finished for each job
    for (int i = 0; i < WaitQueue.size(); i++){
        Process process = WaitQueue[i];
        std::cout<< process.pid << "\t" << process.run_time << "\t" << process.finished_time << std::endl;
    }

   std::cout<< "Finished Queue:" <<std::endl;
    // print a table header with all the fields in the Finished Queue with a line of dashes and a line of equal signs
   std::cout<< "PID\tFinished\tStart Time\tTurnaround Time" <<std::endl;
   std::cout<< "---\t--------\t-----------\t---------------" <<std::endl;
    // print the pid, state, time slice, run time, memory requirement, device requirement, finished, start time, turnaround time, and waiting time for each process
    for (int i = 0; i < CompleteQueue.size(); i++) {
        Process process = CompleteQueue[i];
       std::cout<< process.pid << "\t" << process.finished_time << "\t" << process.start_time << "\t\t" << process.turnaround_time << "\t\t" << process.memory_requirement << "\t\t\t" << process.device_requirement << "\t\t\t" << process.finished << "\t\t" << process.start_time << "\t\t" << process.turnaround_time << "\t\t" << process.waiting_time <<std::endl;
    }

   std::cout<< "Submitted Jobs:" <<std::endl;
    // print a table header with all the fields in a Job with a line of dashes and a line of equal signs
   std::cout<< "Job ID\tRun Time\tTurnaround Time\tWaiting Time" <<std::endl;
   std::cout<< "------\t--------\t---------------\t------------" <<std::endl;
    // print the job id, run time, turnaround time, and waiting time for each job
    for (int i = 0; i < jobs.size(); i++) {
        Job job = jobs[i];
       std::cout<< job.job_id << "\t" << job.run_time << "\t\t" << job.turnaround_time << "\t\t" << job.waiting_time <<std::endl;
    }

   std::cout<< "System Turnaround Time: " <<std::endl;

}