#ifndef SEQUENTIALDM_GLOBAL_H
#define SEQUENTIALDM_GLOBAL_H

#include <string>
#include <map>
#include "../Model/seqJob.h"
#include "../Model/node.h"
#include "../Model/Complete.h"
#include <vector>

using namespace std;

#define FOLLOW 1
#define MEET 2
#define OVER_LAP 3
#define CONTAIN 4
#define MATCH 5
#define LINE 0.5
#define CONF_LINE 0.5
#define SUP_LINE 0.5

extern int TRANSACTION_NUM;
extern map<char, int> singleItem;
extern map<char, int> addValid;
extern vector<char> freq1tem;
extern Node *all[5000];
extern Complete *rulesHead;   //找到的规则是全局的
extern Complete *rulesTail;   //找到的规则是全局的

int calcRelation(seqJob* oJob, seqJob* nJob);

#endif //SEQUENTIALDM_GLOBAL_H