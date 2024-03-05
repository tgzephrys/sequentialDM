#ifndef SEQUENTIALDM_NODE_H
#define SEQUENTIALDM_NODE_H


#include "seqJob.h"
#include <vector>
using namespace std;

class Node {
public:
    vector<seqJob> aTransactions;
};


#endif //SEQUENTIALDM_NODE_H
