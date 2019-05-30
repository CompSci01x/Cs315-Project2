

#ifndef TimerEvent_hpp
#define TimerEvent_hpp

#include <stdio.h>
#include <fstream>
#include "Queue.hpp"
#include "EventQueue.hpp"


class TimerEvent
{
    
public:
    TimerEvent() {}
 
    int getTime() { return _time; }
    void setTime(int _t) { _time = _t ;}
    
    void processTimerEvent(Queue*[5] , EventQueue*);
   
    
private:
    int _time;
};
#endif /* TimerEvent_hpp */
