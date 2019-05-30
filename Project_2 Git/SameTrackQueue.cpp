

#include "SameTrackQueue.hpp"
#include "Request.hpp"
#include "EventNode.hpp"
#include "EventQueue.hpp"


void SameTrackQueue::createCompletionStats(Request *req)
{
    _track = req->track();
    _sector = req->sector();
    _entr = req->time();
    
    double seekTime = dist(curr_track , req->track() ) * 3;
    double rotationalDelay = Rotdist(curr_sector , req->sector()) * 0.1;
    double transferTime = 0.1;
    _serv = seekTime + rotationalDelay + transferTime;
    
    if (_init == 0)
    {
        _init = req->time();
    }
    else
    {
        _init = _comp;
        _wait = _comp - req->time();
    }
    
    _comp = _serv + _init;
    
    _tminsys = _wait + _serv;
    
    static int firstCall = 0;

    
    _sumTmInSys += _tminsys;
    _sumWaitTm += _wait;
    _sumServTm += _serv;
    
    // set max, min , sum
    if ( _maxTmInSys <= _tminsys)
    {
        _maxTmInSys = _tminsys;
    }
    
    if (firstCall == 0)
    {
        _minTmInSys = _tminsys;
        // _minWaitTm = _wait;
        _minServTm = _serv;
        
        firstCall++;
        
    }
    if (_minTmInSys > _tminsys)
    {
        _minTmInSys = _tminsys;
    }
    
    if (_maxWaitTm <= _wait)
    {
        _maxWaitTm = _wait;
    }
    
    if (_minWaitTm > _wait)
    {
        _minWaitTm = _wait;
    }
    
    if (_maxServTm <= _serv)
    {
        _maxServTm = _serv;
    }
    
    if (_minServTm > _serv)
    {
        _minServTm = _serv;
    }
    
    
}

void SameTrackQueue::doThisWhenIdle(EventQueue* eventQueue , Request* req )
{
    // Calculate serivce time AKA access time
    createCompletionStats(req);
    
    // Create a diskDone event and add it to the event Queue
    EventNode *eNode = new EventNode();
    DiskDoneEvent *dDone = new DiskDoneEvent();
    dDone->setDiskDoneCompTime(getComp());
      dDone->setDiskDoneQueue(getQueue());
    
    eNode->addDiskDone(dDone);
    eventQueue->addEvent(eNode);
    
    // Change state of disk (queue) to busy AKA not_Idle
    _isIdle = false;
    
    
}

void SameTrackQueue::processSingleQueue(Request *req)
{
    createCompletionStats(req);
}




int SameTrackQueue::dist(int current_track, int dest_track)
{
    int distance =  abs(current_track - dest_track);
    curr_track = dest_track;
    
    return distance;
    
}


int SameTrackQueue::Rotdist(int current_sector, int dest_sector)
{
    int rotationDistance = 0;
    
    if (current_sector > dest_sector)
    {
        int getTo29 = 0;
        while (current_sector != 29)
        {
            getTo29++;
            current_sector++;
        }
        
        current_sector = 0;
        getTo29++;
        
        rotationDistance = (dest_sector - current_sector) + getTo29;
        
    }
    else
    {
        rotationDistance = abs(dest_sector - current_sector);
        
    }
    
    
    // Remember when the disk drive completes the access the curr-sector is ++
    curr_sector = dest_sector + 1;
    
    if (curr_sector > 29)
    {
        curr_sector = 0;
    }
    
    
    return rotationDistance;
}



void SameTrackQueue::addRequest(Request *request)
{
    QueueNode *rNode = new QueueNode(request);
    
    if( isEmpty() )
    {
        head = tail = rNode;
        return;
    }
    
     QueueNode *currentPtr = head;
    
    while (currentPtr != nullptr)
    {
        if ( currentPtr->request()->track() == request->track() )
        {
            rNode->next(currentPtr->next());
            currentPtr->next(rNode);
            
            if (rNode->next() == nullptr)
            {
                tail = rNode;
            }
            
            return;
        }
        
        currentPtr = currentPtr->next();
       
    }

    if (currentPtr == nullptr)
    {
        tail->next(rNode);
        tail = rNode;
    }
    
    
    
}



Request *SameTrackQueue::getRequest()
{
    if( isEmpty() )
    {
        std::cout << "Calling FCFSQueueNode::getRequest() on empty queue. Terminating...\n";
        exit(1);
    }
    QueueNode *fcfsNode = head;
    Request *request = fcfsNode->request();
    head = head->next();
    if( head == nullptr )
        tail = nullptr;
    delete fcfsNode;
    return request;
}


bool SameTrackQueue::isEmpty()
{
    return head == nullptr;
}


void SameTrackQueue::print()
{
    for(auto cur = head; cur; cur = cur->next() )
        cur->request()->print();
}


SameTrackQueue::~SameTrackQueue()
{
    while( head != nullptr )
    {
        QueueNode *node = head;
        head = node->next();
        delete node;
    }
}
