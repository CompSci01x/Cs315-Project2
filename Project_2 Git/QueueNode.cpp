
#include "QueueNode.hpp"



QueueNode::QueueNode(Request *req, QueueNode *nextPtr) : _request(req), _next(nextPtr) {}

QueueNode::QueueNode(Request *req) : _request(req), _next(nullptr) {}


QueueNode *QueueNode::next()
{
    return _next;
}


void QueueNode::next(QueueNode *node)
{
    _next = node;
}


Request *QueueNode::request()
{
    return _request;
}
