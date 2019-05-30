

#include "RequestEvent.hpp"
#include "FCFSQueue.hpp"
#include "SameTrackQueue.hpp"
#include "PickUpQueue.hpp"
#include "LookUpQueue.hpp"
#include "CLookQueue.hpp"




void RequestEvent::scheduleRequest( Queue *queue[5] , EventQueue *eventQueue, std::ifstream &inputStream )
{
    
    Request *request = _req;
    
    
    for (int x = 0 ; x < 5 ; x++)
    {
          queue[x]->addRequest(request);
        
            if (queue[x]->isIdle())
            {
                queue[x]->doThisWhenIdle(eventQueue, request);
                
            }
    
        
        
    }
    
    // Add a Disk Request Event to the event queue
    EventNode *node = new EventNode();
    RequestEvent *diskRequest = new RequestEvent();
    diskRequest->getRequest(inputStream);
    
    node->addRequest(diskRequest);
    eventQueue->addEvent(node);
    
}


Request* RequestEvent:: getRequest(std::ifstream &inputStream)
{
    
    Request *request = nullptr;
    
    double time;
    int track, sector;
    if (inputStream >> time && inputStream >> track && inputStream >> sector )
    {
         request = new Request(time, track, sector);
    }
    else
    {
        _noMoreRequests = true;
    }
    
    _req = request;
    
    return request;
}

