
#include "TimerEvent.hpp"

void TimerEvent::processTimerEvent(Queue *queue[5] , EventQueue *eventQueue)
{
    std::ofstream outStream("timer_output.txt" , std::ios_base::app);
    static int header = 0;
    
    if (header == 0)
    {
        outStream << "Timer Report\n"
        << "Time" << "\t\t"
        << "FCFS" << "\t\t"
        << "SameTrack" << "\t"
        << "PickUp" << "\t\t"
        << "CLook" << "\t\t"
        << "Look" << "\n";
        
        header++;
    }
    
    outStream << getTime() << "\t\t";
    
    for (int x = 0 ; x < 5 ; x++)
    {
        QueueNode *currentPtr = queue[x]->getHead();
        int lengthOfQueue = 0;
        
        while (currentPtr != nullptr)
        {
            lengthOfQueue++;
            currentPtr = currentPtr->next();
        }
       
        outStream << lengthOfQueue << "\t\t";
        
       if ( queue[x]->getmaxNumInQue() < lengthOfQueue)
       {
           queue[x]->setmaxNumInQue(lengthOfQueue);
       }
        
        queue[x]->setsumNumInQue(lengthOfQueue);
        
    }
    
    outStream << "\n";
    outStream.close();
    
}
