#ifndef SEQUENTIALDM_SEQJOB_H
#define SEQUENTIALDM_SEQJOB_H

#include "connect.h"

class seqJob{
public:
    char name = 0;
    int startTime = -1;
    int endTime = -1;
    Connect *cp = nullptr;
};


#endif //SEQUENTIALDM_SEQJOB_H
