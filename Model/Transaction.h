#ifndef SEQUENTIALDM_TRANSACTION_H
#define SEQUENTIALDM_TRANSACTION_H


#include "seqJob.h"
#include <vector>
using namespace std;

class Transaction {
public:
    vector<seqJob> seqJobs;
};


#endif //SEQUENTIALDM_TRANSACTION_H
