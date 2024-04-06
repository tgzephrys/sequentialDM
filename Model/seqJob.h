#ifndef SEQUENTIALDM_SEQJOB_H
#define SEQUENTIALDM_SEQJOB_H

#include "connect.h"
#include <string>
using namespace std;

class seqJob{
public:
    string name1;
    int startTime = -1;
    int endTime = -1;
    Connect *cp = nullptr;
};


#endif //SEQUENTIALDM_SEQJOB_H
