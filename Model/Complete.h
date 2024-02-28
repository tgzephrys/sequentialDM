#ifndef SEQUENTIALDM_COMPLETE_H
#define SEQUENTIALDM_COMPLETE_H


#include "CompleteHead.h"

class Complete {   //挖完一次之后  保存所有的事务集信息
public:
    CompleteHead *head = nullptr;
    Complete *next = nullptr;
    double conf = 0;
};


#endif //SEQUENTIALDM_COMPLETE_H
