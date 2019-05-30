

#ifndef EventNode_hpp
#define EventNode_hpp

#include "TimerEvent.hpp"
#include "RequestEvent.hpp"
#include "DiskDoneEvent.hpp"

class TimerEvent;
class RequestEvent;
class DiskDoneEvent;
class Event;

class EventNode
{
    
public:
    EventNode(): timerEvent(nullptr), requestEvent(nullptr), ddoneEvent(nullptr),isTimer(false), isRequest(false), isDDone(false), _next(nullptr), time(0) {}
    
    
    void addTimer(TimerEvent *timer);
    
    void addRequest(RequestEvent *request);
    
    void addDiskDone(DiskDoneEvent *dDone);

    
    TimerEvent *getTimer() { return timerEvent; }
    RequestEvent *getRequest() { return requestEvent; }
    DiskDoneEvent *getDiskDone() { return ddoneEvent; }
    
    
    bool isTimerEvent()    { return isTimer; }
    bool isRequestEvent()  { return isRequest; }
    bool isDiskDoneEvent() { return isDDone; }
  
    
    EventNode *next() { return _next; }
    void next(EventNode *node) { _next = node ; }
    
    double getNodeTime() {return time;}
    
    
private:
    TimerEvent *timerEvent;
    RequestEvent *requestEvent;
    DiskDoneEvent *ddoneEvent;
    bool isTimer, isRequest, isDDone;
    double time;
    
    EventNode *_next;
    
    
};

#endif /* EventNode_hpp */
