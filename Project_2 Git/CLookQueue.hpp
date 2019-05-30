
#ifndef CLookQueue_hpp
#define CLookQueue_hpp


#include <stdio.h>
#include<iostream>
#include "Queue.hpp"
#include "QueueNode.hpp"

class Request;

class CLookUpQueue: public Queue
{
    
public:
    CLookUpQueue(): head(nullptr), tail(nullptr), _isIdle(true), curr_track(0), curr_sector(0), _init(0) , _comp(0) , _wait(0) , _serv(0) ,_tminsys(0) , _track(0) , _sector(0) , _entr(0), _queue(nullptr),  _maxTmInSys (0), _minTmInSys (0), _sumTmInSys(0), _maxWaitTm(0), _minWaitTm(0), _sumWaitTm(0), _maxServTm(0), _minServTm(0), _sumServTm(0), _maxNumInQue(0),  _sumNumInQue(0) {}
    
    virtual void addRequest(Request *request);
    
    virtual Request *getRequest();
    virtual bool isEmpty();
    virtual void print();
    virtual ~CLookUpQueue();
    
  virtual  bool isIdle() {return _isIdle;}
    virtual void setIdleToTrue() { _isIdle = true;}
        virtual void doThisWhenIdle(EventQueue* , Request *);
       virtual void processSingleQueue(Request *);
    
    int dist(int , int);
    int Rotdist(int , int);
    
    virtual QueueNode* getHead() {return head;}
    virtual void moveHead() {head = head->next();}
    
       virtual void createCompletionStats(Request *);
    
    virtual int getTrack() {return _track;}
    virtual int getSector() {return _sector;}
    virtual int getEntr() {return _entr;}
    virtual double getInit() {return _init;}
    virtual double getComp() {return _comp;}
    virtual double getWait() {return _wait;}
    virtual double getServ() {return _serv;}
    virtual double getTmInSys() {return _tminsys;}
    
    virtual void setQueue(Queue *q) {_queue = q;}
    virtual Queue* getQueue() {return _queue;}
    
      virtual std::string nameOfQueue() {return "CLookQueue";}
    
    virtual double getmaxTmInSys() {return _maxTmInSys;}
    virtual double getminTmInSys() {return _minTmInSys;}
    virtual double getsumTmInSys() {return _sumTmInSys;}
    virtual double getmaxWaitTm() {return _maxWaitTm;}
    virtual double getminWaitTm() {return _minWaitTm;}
    virtual double getsumWaitTm() {return _sumWaitTm;}
    virtual double getmaxServTm() {return _maxServTm;}
    virtual double getminServTm() {return _minServTm;}
    virtual double getsumServTm() {return _sumServTm;}
    virtual double getmaxNumInQue() {return _maxNumInQue;}
    virtual double getsumNumInQue() {return _sumNumInQue;}
    
      virtual void setsumNumInQue(int numInQ) {_sumNumInQue += numInQ;}
     virtual void setmaxNumInQue(int maxNumInQ) {_maxNumInQue = maxNumInQ;}
    
private:
    QueueNode *head, *tail;
    bool _isIdle;
     int curr_track , curr_sector;
    double _init , _comp , _wait , _serv , _tminsys;
    int _track , _sector , _entr;
     Queue * _queue;
    double _maxTmInSys, _minTmInSys, _sumTmInSys;
    double _maxWaitTm, _minWaitTm, _sumWaitTm;
    double _maxServTm, _minServTm, _sumServTm;
    double _maxNumInQue, _sumNumInQue;
};


#endif /* CLookQueue_hpp */
