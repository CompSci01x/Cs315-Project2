

#ifndef FCFS_QUEUE_FCFSQUEUENODE_HPP
#define FCFS_QUEUE_FCFSQUEUENODE_HPP


#include "Request.hpp"

class QueueNode
{
public:
    QueueNode(Request *req, QueueNode *nextPtr);
    QueueNode(Request *req);
    QueueNode *next();
    void next(QueueNode *node);
    Request *request();

private:
    QueueNode *_next;
    Request *_request;
};


#endif //FCFS_QUEUE_FCFSQUEUENODE_HPP
