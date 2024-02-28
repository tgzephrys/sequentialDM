#ifndef SEQUENTIALDM_NODE_H
#define SEQUENTIALDM_NODE_H


#include "seqJob.h"

class Node {
public:
    int relation = 0;
    seqJob* aTransaction[100] = {};
    int num = 0;
};


#endif //SEQUENTIALDM_NODE_H
