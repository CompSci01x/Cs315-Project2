

#include "EventQueue.hpp"

void EventQueue::addEvent( EventNode *eNode )
{
    
    
    if (eNode->isRequestEvent())
    {
        // check if there are not more requests in the inputFile
        if (eNode->getRequest()->isNoMoreRequests())
        {
            // If no more requests in the input file stop, dont add a request event to the event queue
            return;
        }
        
    }
    
    
    if( isEmpty() )
    {
        head = tail = eNode;
        return;
    }
    
    if (eNode->getNodeTime() < head->getNodeTime())
    {
        eNode->next(head);
        head = eNode;
        return;
    }
    else
    {
        EventNode *currentPtr = head->next();
        EventNode *prevPtr = head;
        
        while (currentPtr != nullptr)
        {
            if (eNode->getNodeTime() < currentPtr->getNodeTime())
            {
                eNode->next(prevPtr->next());
                prevPtr->next(eNode);
                return;
            }
            
            prevPtr = currentPtr;
            currentPtr = currentPtr->next();
            
        }
        
        tail = prevPtr;
        tail->next(eNode);
        tail = eNode;
        
    }
    
    return;
}



EventNode *EventQueue::getEvent()
{
    if( isEmpty() )
    {
        std::cout << "Calling FCFSQueueNode::getRequest() on empty queue. Terminating...\n";
        exit(1);
    }
    EventNode *eNode = head;

    
    head = head->next();
    if( head == nullptr )
        tail = nullptr;
  
    return eNode;
}



bool EventQueue::isEmpty()
{
    return head == nullptr;
}


EventQueue::~EventQueue()
{
    while( head != nullptr )
    {
        EventNode *node = head;
        head = node->next();
        delete node;
    }
}
