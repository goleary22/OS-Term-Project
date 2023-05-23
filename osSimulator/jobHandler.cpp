/*
jobHandler.cpp
Handle jobs as they arrive
*/

#include "jobHandler.h" 
#include "readyQueueHandler.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <list>
#include <algorithm>
#include <iterator>
#include <iomanip>

//Sorts the hold queue 1 by SJF job scheduling: The job with the shortest run time is at the head, longest at the end.
void SortedLinkedList::addSorted(Job data, int attribute){
    Node* newNode = new Node;
    newNode->data = data;
    newNode->attribute = attribute;
    newNode->next = nullptr;
    if (head == nullptr){
        head = newNode;
    } else {
        Node* current = head;
        Node* previous = nullptr;
        while (current != nullptr && current->attribute < attribute){
            previous = current;
            current = current->next;
        }
        if (previous == nullptr){
            newNode->next = head;
            head = newNode;
        } else {
            previous->next = newNode;
            newNode->next = current;
        }
    }
}

//Sorts the hold queue 2 by FIFO job scheduling: the jobs just take their place in the queue as they arrive 
void SortedLinkedList::add(Job data){
    Node* newNode = new Node;
    newNode->data = data;
    newNode->next = nullptr;
    if (head == nullptr){
        head = newNode;
    } else {
        Node* current = head;
        Node* previous = nullptr;
        while (current != nullptr){
            previous = current;
            current = current->next;
        }
        previous->next = newNode;
    }
}

//helper function removes the head of the queue
Job SortedLinkedList::removeFirst(){
    Node* temp = head;
    head = head->next;
    Job data = temp->data;
    delete temp;
    return data;
}
//helper function handles empty case
bool SortedLinkedList::isEmpty(){
    return head == nullptr;
}

//helper function prints information 
void SortedLinkedList::print(){
    Node* current = head;
    while (current != nullptr){
        std::cout << current->data.job_id << " ";
        current = current->next;
    }
    std::cout << std::endl;
}
