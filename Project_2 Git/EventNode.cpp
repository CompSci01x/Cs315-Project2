

#include "EventNode.hpp"

void EventNode::addTimer(TimerEvent *timer)
{
    timerEvent = timer;
    isTimer = true;
    time = timerEvent->getTime();
}

void EventNode::addRequest(RequestEvent *request)
{
    requestEvent = request;
    isRequest = true;
    
    // if there are more requests then get the time of the req
    if ( ! requestEvent->isNoMoreRequests() )
    {
         time = request->seeTheReq()->time();
    }
   
}

void EventNode::addDiskDone(DiskDoneEvent *dDone)
{
    ddoneEvent = dDone;
    isDDone = true;
    time = ddoneEvent->getCompTime();
}
