#ifndef SEQUENTIALDM_SEQJOB_H
#define SEQUENTIALDM_SEQJOB_H

#include "connect.h"
#include <string>
#include <vector>

using namespace std;

class seqJob{
public:
    string name1;
    int startTime = -1;
    int endTime = -1;
    Connect *cp = nullptr;
    vector<int> nextSpecItems;
    seqJob() {
        nextSpecItems = vector<int>(5, -1);
    };
};


#endif //SEQUENTIALDM_SEQJOB_H
