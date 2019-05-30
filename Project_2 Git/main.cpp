#include <iostream>
#include <fstream>
#include "Request.hpp"
#include "FCFSQueue.hpp"
#include "SameTrackQueue.hpp"
#include "PickUpQueue.hpp"
#include "LookUpQueue.hpp"
#include "CLookQueue.hpp"
#include "EventNode.hpp"
#include "EventQueue.hpp"
#include "RequestEvent.hpp"

//Function Prototype
void process_event(EventNode* , EventQueue* , std::ifstream& , Queue*[5]);
void createDiskOutputFiles(EventNode *);
void print_summary(Queue*[5]);


//Global variable
int totalNumOfReq = 0;
int totalNumOfTmEvents = 0;


int main(int argc, char *argv[])
{

    if( argc != 2)
    {
        std::cout << "usage: " << argv[0] << " nameOfAnInputFile\n";
        exit(1);
    }

    std::ifstream inputStream;

    inputStream.open(argv[1], std::ios::in);
    if( ! inputStream.is_open())
    {
        std::cout << "Unable top open " << argv[1] << ". Terminating...";
        perror("Error when attempting to open the input file.");
        exit(1);
    }
    
    FCFSQueue *fqueue = new FCFSQueue();
     SameTrackQueue *squeue = new SameTrackQueue();
     PickUpQueue *pqueue = new PickUpQueue();
     LookUpQueue *lqueue = new LookUpQueue();
     CLookUpQueue *cqueue = new CLookUpQueue();
    
     Queue *queue[5];
    queue[0] = fqueue;
    fqueue->setQueue(queue[0]);
    
    queue[1] = squeue;
    squeue->setQueue(queue[1]);
    
    queue[2] = pqueue;
    pqueue->setQueue(queue[2]);
    
    queue[3] = lqueue;
    lqueue->setQueue(queue[3]);
    
    queue[4] = cqueue;
    cqueue->setQueue(queue[4]);
    
    EventQueue *eventQueue = new EventQueue();
    
    
        EventNode *eNode = new EventNode();
    RequestEvent *diskRequest = new RequestEvent();
    diskRequest->getRequest(inputStream);
    eNode->addRequest(diskRequest);
    
    eventQueue->addEvent(eNode);
    
    EventNode *node = new EventNode();
    TimerEvent *timeEvent = new TimerEvent();
    timeEvent->setTime(50);
    
    node->addTimer(timeEvent);
    eventQueue->addEvent(node);
    
    
    while ( !eventQueue->isEmpty() )
    {
        EventNode *eventNode = eventQueue->getEvent();
        
        process_event (eventNode , eventQueue , inputStream , queue);
        
    }

       inputStream.close();
    
    print_summary(queue);


    std::cout << "Program has run successfully.\n";
    
    return 0;
}


void process_event( EventNode *eNode , EventQueue *eventQueue , std::ifstream& inputStream , Queue*queue[5] )
{
    
    if (eNode->isRequestEvent())
    {
        totalNumOfReq++;
        eNode->getRequest()->scheduleRequest(queue , eventQueue , inputStream);
        
    }
    else if (eNode->isDiskDoneEvent())
    {
        
        createDiskOutputFiles(eNode);
        
        eNode->getDiskDone()->processDiskDone(eventQueue);
        
    }
    else if (eNode->isTimerEvent())
    {
        totalNumOfTmEvents++;
        
        static int _time = 50;
        
        eNode->getTimer()->processTimerEvent(queue , eventQueue);
        
        if (!eventQueue->isEmpty())
        {
            _time = _time + 50;
            EventNode *node = new EventNode();
            TimerEvent *timeEvent = new TimerEvent();
            timeEvent->setTime(_time);
            
            node->addTimer(timeEvent);
            eventQueue->addEvent(node);
            
        }
        
    }
    else
    {
        std:: cout << "Unknown Event. Terminating\n\n";
        exit(1);
    }
    
    
}


void createDiskOutputFiles(EventNode *eNode)
{
    
    std::ofstream outStream;
    
    if (eNode->getDiskDone()->getQueue()->nameOfQueue() == ("FCFSQueue"))
    {
        outStream.open("fcfs_output.txt" , std::ios_base::app);
        
    }
    else if (eNode->getDiskDone()->getQueue()->nameOfQueue() == ("SameTrackQueue"))
    {
        outStream.open("strack_output.txt", std::ios_base::app);
        
    }
    else if (eNode->getDiskDone()->getQueue()->nameOfQueue() == ("PickUpQueue"))
    {
        outStream.open("pickup_output.txt", std::ios_base::app);
        
    }
    else if (eNode->getDiskDone()->getQueue()->nameOfQueue() == ("LookUpQueue"))
    {
        outStream.open("lookup_output.txt", std::ios_base::app);
        
    }
    else if (eNode->getDiskDone()->getQueue()->nameOfQueue() == ("CLookQueue"))
    {
        outStream.open("clook_output.txt", std::ios_base::app);
        
    }
    
    static int header = 0;
    // this is to create the headers in the file
    if (header != 5)
    {
        outStream << "#Trac     Sec     Entr    Init    Comp    Wait    Serv    TmInSys\n";
        header++;
    }
    
    
    outStream << eNode->getDiskDone()->getQueue()->getTrack() << "\t"
    << eNode->getDiskDone()->getQueue()->getSector() << "\t"
    << eNode->getDiskDone()->getQueue()->getEntr() << "\t"
    <<  eNode->getDiskDone()->getQueue()->getInit() << "\t"
    << eNode->getDiskDone()->getQueue()->getComp() << "\t"
    << eNode->getDiskDone()->getQueue()->getWait() << "\t"
    << eNode->getDiskDone()->getQueue()->getServ() << "\t"
    << eNode->getDiskDone()->getQueue()->getTmInSys() << " \n ";
    
    outStream.close();
}

void print_summary(Queue *queue[5])
{
    std::ofstream outStream("summary_output.txt");
    
    outStream << "Name" << "\t\t"
            << "TmInSys" << "\t\t\t"
            << "WaitTime" << "\t\t"
            << "ServiceTime" << "\t\t"
    << "NumInQue" << "\n";
    
    outStream << "\t\t" << "Min" << "\t" << "Max" << "\t" << "Avg"
                << "\t" << "Min" << "\t" << "Max" << "\t" << "Avg"
                << "\t" << "Min" << "\t" << "Max" << "\t" << "Avg"
    << "\t" << "Max" << "\t" << "Avg" << "\n";
    
    for (int x = 0; x < 5 ; x ++)
    {
       outStream << queue[x]->nameOfQueue() << "\t"
                << queue[x]->getminTmInSys() << "\t"
                << queue[x]->getmaxTmInSys() << "\t"
                << (queue[x]->getsumTmInSys() / totalNumOfReq) << "\t"
        
                << queue[x]->getminWaitTm() << "\t"
                << queue[x]->getmaxWaitTm() << "\t"
                << (queue[x]->getsumWaitTm() / totalNumOfReq) << "\t"
        
                << queue[x]->getminServTm() << "\t"
                << queue[x]->getmaxServTm() << "\t"
                << (queue[x]->getsumServTm() / totalNumOfReq) << "\t"
        
                << queue[x]->getmaxNumInQue() << "\t"
        << (queue[x]->getsumNumInQue() / totalNumOfTmEvents ) << "\n";
    }
    
    outStream.close();
    
}

