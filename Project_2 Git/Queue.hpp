
#ifndef QUEUE_HPP
#define QUEUE_HPP
class Request;
class EventQueue;
class QueueNode;

#include <string>

class Queue {

public:
    virtual void addRequest(Request *request) = 0;
    virtual Request *getRequest() = 0;
    virtual bool isEmpty() = 0;
    virtual void print() = 0;
    virtual ~Queue() {}

    virtual bool isIdle() = 0;
    virtual void setIdleToTrue() = 0;
    virtual void doThisWhenIdle(EventQueue * , Request *) = 0;
    virtual void createCompletionStats(Request *) = 0;
    virtual QueueNode* getHead() = 0;
    virtual void moveHead() = 0;
    
    virtual int getTrack() = 0;
    virtual int getSector() = 0;
    virtual int getEntr() = 0;
    virtual double getInit() = 0;
    virtual double getComp() = 0;
    virtual double getWait() = 0;
    virtual double getServ() = 0;
    virtual double getTmInSys() = 0;
    
    virtual void setQueue(Queue *q) = 0;
    virtual Queue* getQueue() = 0;
    virtual std::string nameOfQueue() = 0;
    
    virtual void processSingleQueue(Request *) = 0;
    
    
    virtual double getmaxTmInSys() = 0;
    virtual double getminTmInSys() = 0;
    virtual double getsumTmInSys() = 0;
    virtual double getmaxWaitTm() = 0;
    virtual double getminWaitTm() = 0;
    virtual double getsumWaitTm() = 0;
    virtual double getmaxServTm() = 0;
    virtual double getminServTm() = 0;
    virtual double getsumServTm() = 0;
    virtual double getmaxNumInQue() = 0;

    virtual double getsumNumInQue() = 0;
    
    virtual void setsumNumInQue(int) = 0;
    
    virtual void setmaxNumInQue(int) = 0;
    
};

#endif // QUEUE_HPP
