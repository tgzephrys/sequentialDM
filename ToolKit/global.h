#ifndef SEQUENTIALDM_GLOBAL_H
#define SEQUENTIALDM_GLOBAL_H

#include <string>
#include <map>
#include "../Model/seqJob.h"
#include "../Model/Transaction.h"
#include "../Model/Complete.h"
#include <vector>
#include "iostream"
#include "sstream"

using namespace std;

#define FOLLOW 0
#define MEET 1
#define OVER_LAP 2
#define CONTAIN 3
#define MATCH 4
#define LINE 0.5  //置信度
#define SUP_LINE 0.5  //支持度
#define CONF_LINE 0.5

extern int TRANSACTION_NUM;
extern vector<string> freqItems;
extern vector<Transaction> all2;
extern Complete *rulesHead;   //找到的规则是全局的
extern Complete *rulesTail;   //找到的规则是全局的

int calcRelation(seqJob & oJob, seqJob & nJob);
int calcRelation(seqJob * oJob, seqJob * nJob);

vector<string> split(string&, char);

#endif //SEQUENTIALDM_GLOBAL_H