#include "global.h"
#include "../Model/Complete.h"

int TRANSACTION_NUM = 0;
map<char, int> singleItem;
map<char, int> addValid;
vector<char> freq1tem;
Node *all[5000] = {};
Complete *rulesHead = nullptr;
Complete *rulesTail = nullptr;

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