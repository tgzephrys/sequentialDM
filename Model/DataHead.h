#ifndef SEQUENTIALDM_DATAHEAD_H
#define SEQUENTIALDM_DATAHEAD_H
#include <vector>
#include "CompleteNode.h"
#include "connect.h"

using namespace std;

class DataHead {
public:
    vector<Connect> miningList;
    int isValid = true;
};

#endif //SEQUENTIALDM_DATAHEAD_H
