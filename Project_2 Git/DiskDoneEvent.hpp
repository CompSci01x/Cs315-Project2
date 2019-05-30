

#ifndef DiskDoneEvent_hpp
#define DiskDoneEvent_hpp

#include <stdio.h>
#include "EventNode.hpp"
#include "EventQueue.hpp"
#include "Queue.hpp"


class DiskDoneEvent
{
public:
    DiskDoneEvent(): comp_time(0) , queue(nullptr) {}
    
    void processDiskDone(EventQueue* );
    
    void setDiskDoneCompTime(double ct) {comp_time = ct;}
    void setDiskDoneQueue(Queue *q) {queue = q;}
    
    Queue* getQueue() {return queue;}
    
    double getCompTime() {return comp_time;}
    
    void processFirstDDone(EventQueue *eventQueue);
    
    void writeToOutputFile();
    
    
    
private:
    double comp_time;
    Queue *queue;
};

#endif /* DiskDoneEvent_hpp */
