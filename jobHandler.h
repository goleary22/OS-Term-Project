/*
jobhandler.h
handle jobs as they arrive
*/
#ifndef JOBHANDLER_H
#define JOBHANDLER_H

#include <vector>
#include "processHandler.h"


// The following structs are used to represent jobs and devices.
struct Job {
  int job_id;
  int arrival_time;
  int priority;
  int memory_requirement;
  int device_requirement;
  int run_time;
  int turnaround_time;
  int waiting_time;
  bool finished_time;
  bool finished;
};

struct Node {
    Job data;
    int attribute;
    Node* next;
};


class SortedLinkedList {
  public:
    // default constructor
    SortedLinkedList() : head(nullptr) {}
    void add(Job data);
    void addSorted(Job data, int attribute);
    Job removeFirst();
    bool isEmpty();
    void print();
  private:
    Node* head;
};


#endif /* JOBHANDLER_H */