
#ifndef EventQueue_hpp
#define EventQueue_hpp

#include <stdio.h>
#include<iostream>
#include "Queue.hpp"
#include "QueueNode.hpp"
#include "EventNode.hpp"
#include <fstream>

class EventNode;

class EventQueue
{
    
public:
    EventQueue(): head(nullptr), tail(nullptr) {}
    
    void addEvent(EventNode * );
    
    EventNode *getEvent();
   bool isEmpty();

     ~EventQueue();
    
private:
    EventNode *head , *tail;
};


#endif /* EventQueue_hpp */
