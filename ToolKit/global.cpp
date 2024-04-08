#include <cstring>
#include "global.h"
#include "../Model/Complete.h"

int TRANSACTION_NUM = 0;
vector<string> freqItems;
vector<Transaction> all2;
Complete *rulesHead = nullptr;
Complete *rulesTail = nullptr;

int calcRelation(seqJob &o, seqJob &n) {
    if (n.startTime == o.startTime || n.endTime == o.endTime) {
        return MATCH;
    } else if (n.startTime < o.endTime) {
        if (n.endTime > o.endTime)
            return OVER_LAP;
        else return CONTAIN;
    } else if (n.startTime == o.endTime)
        return MEET;
    else return FOLLOW;
}

int calcRelation(seqJob *o, seqJob *n) {
    if (n->startTime == o->startTime || n->endTime == o->endTime) {
        return MATCH;
    } else if (n->startTime < o->endTime) {
        if (n->endTime > o->endTime)
            return OVER_LAP;
        else return CONTAIN;
    } else if (n->startTime == o->endTime)
        return MEET;
    else return FOLLOW;
}

vector<string> split(string& str, char delim) {
    vector<string> vec;
    string result;
    stringstream origin(str);
    while(getline(origin, result, delim))
        vec.push_back(result);
    return vec;
}