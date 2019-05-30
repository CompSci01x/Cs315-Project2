

#ifndef RequestEvent_hpp
#define RequestEvent_hpp

#include <stdio.h>
#include <iostream>
#include "Request.hpp"
#include "Queue.hpp"
#include <fstream>
#include "EventQueue.hpp"





class RequestEvent
{
public:
    RequestEvent(): _noMoreRequests(false) , _req(nullptr) {}
    
    void scheduleRequest(Queue*[5] , EventQueue* , std::ifstream&);
    Request *getRequest(std::ifstream &);
    
    bool isNoMoreRequests() {return _noMoreRequests;}
    Request *seeTheReq() {return _req;}
    
    
private:
    bool _noMoreRequests;
    Request *_req;
    
};
#endif /* RequestEvent_hpp */
