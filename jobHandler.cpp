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

Job SortedLinkedList::removeFirst(){
    Node* temp = head;
    head = head->next;
    Job data = temp->data;
    delete temp;
    return data;
}

bool SortedLinkedList::isEmpty(){
    return head == nullptr;
}


void SortedLinkedList::print(){
    Node* current = head;
    while (current != nullptr){
        std::cout << current->data.job_id << " ";
        current = current->next;
    }
    std::cout << std::endl;
}
