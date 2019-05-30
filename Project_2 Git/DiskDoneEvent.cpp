

#include "DiskDoneEvent.hpp"

void DiskDoneEvent::processDiskDone(EventQueue *eventQueue)
{

        
    queue->getRequest();
    
        if (queue->isEmpty())
        {
            // set the state to idle
            queue->setIdleToTrue();
            
          
        }
        else
        {
            // Get request from disk's queue
          Request *request = queue->getHead()->request();
            
            // This is "serving the request"
            // It'll calculate service time and create a diskdone event and set state to busy.
            queue->doThisWhenIdle(eventQueue, request );
        }
    
    
}

void DiskDoneEvent::processFirstDDone(EventQueue *eventQueue)
{
    queue->moveHead();
    
}


