#ifndef SEQUENTIALDM_COMPLETEHEAD_H
#define SEQUENTIALDM_COMPLETEHEAD_H


#include "CompleteNode.h"
#include "connect.h"
#include <vector>

using namespace std;

class CompleteHead {
public:
    int index = 0; //在哪个事务集里
    vector<Connect> oneRule;  //一条成型的规则
    CompleteHead* next = nullptr;
};


#endif //SEQUENTIALDM_COMPLETEHEAD_H
