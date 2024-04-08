//Created by Zephrys
// Time sequential data mining project
// Tel:13671092791
//

#include <iostream>
#include "ToolKit/global.h"
#include "FileService/readFromFile.h"
#include "Model/DataHead.h"
#include "main.h"
#include "Model/Complete.h"
#include "FileService/saveToFile.h"

void doDM(string name) {

    DataHead mining[TRANSACTION_NUM];  //记录正在查找的情况的数组
    findFirstNode(mining, name);

    Connect *newHead = nullptr;
    Connect *pHead = nullptr;

//    map<Connect, bool> confirm;
//    map<Connect, double> candiItems;

    map<string, bool> confirm;
    map<string, int> candiItems;

    for (int i = 0; i < TRANSACTION_NUM; ++i) {
        //vector<Connect> *v = &mining[i].miningList;
        //int index = mining[i].miningList[0].i;

        for (int j = 0; j < all2[i].seqJobs.size(); ++j) {
            if (all2[i].seqJobs[j].name1 == mining[i].miningList[0].name1) {
                Connect *p = all2[i].seqJobs[j].cp;
                while (p != nullptr) {
//                Connect connect;
//                connect.name = p->name;
//                connect.relation = p->relation;

                    string connect = to_string(p->relation) + p->name1;

                    if (confirm.count(connect) == 0) {
                        confirm[connect] = true;
                    }
                    if (confirm[connect]) {
                        if (!candiItems.count(connect))
                            candiItems[connect] = 1;
                        else
                            candiItems[connect]++;
                    }

                    confirm[connect] = false;
                    p = p->next;
                    cout << 54 << endl;
                }
            }
        }
        for (auto &iterator: confirm) {
            iterator.second = true;
        }
    }

    for (auto &iterator: candiItems) {
        if ((iterator.second / TRANSACTION_NUM) >= SUP_LINE) {
            Connect *newC = new Connect;
            //newC->relation = iterator.first.relation;
            char re = *(iterator.first.data());
            newC->relation = atoi(&re);

            //newC->name = iterator.first.name;

            newC->name1 = iterator.first.substr(1);
            newC->sup = iterator.second / TRANSACTION_NUM;
            if (newHead == nullptr) {
                newHead = newC;
                pHead = newHead;
            } else {
                pHead->next = newC;
                pHead = pHead->next;
            }
        }
    }

    chooseNext(newHead, mining);
}

void findFirstNode(DataHead *mining, string name) {
    for (int i = 0; i < TRANSACTION_NUM; ++i) {
        int num = all2[i].seqJobs.size();    //每行事务集的项集数量

        for (int j = 0; j < num; ++j) {
            if (all2[i].seqJobs[j].name1 == name) {
                Connect cNode;
                cNode.i = j;
                cNode.sup = 0;
                cNode.name1 = name;
                mining[i].miningList.push_back(cNode);
                break;
            }
        }
    }
}

Connect *wantCandiItem(DataHead *mining) {
    Connect *newHead = nullptr;
    Connect *pHead = nullptr;

//    map<Connect, bool> confirm;
//    map<Connect, double> candiItems;

    map<string, bool> confirm;
    map<string, double> candiItems;

    for (int i = 0; i < TRANSACTION_NUM; ++i) {
        if (mining[i].isValid) {
            vector<Connect> *v = &mining[i].miningList;
            int index = (*v)[(*v).size() - 1].i;

            Connect *p = all2[i].seqJobs[index].cp;
            while (p != nullptr) {
                cout << 132 << endl;
//                Connect c;
//                c.name = p->name;
//                c.relation = p->relation;

                string c = to_string(p->relation) + p->name1;

                if (confirm.count(c) == 0) {
                    confirm[c] = true;
                }
                if (confirm[c]) {
                    if (!candiItems.count(c))
                        candiItems[c] = 1;
                    else
                        candiItems[c]++;
                }

                confirm[c] = false;
                p = p->next;
            }
            for (auto &iterator: confirm) {
                iterator.second = true;
            }
        }
    }

    for (auto &iterator: candiItems) {
        if ((iterator.second / TRANSACTION_NUM) >= SUP_LINE) {
            Connect *newC = new Connect;
            //newC->relation = iterator.first.relation;
            char re = *(iterator.first.data());
            newC->relation = atoi(&re);

            //newC->name = iterator.first.name;

            newC->name1 =iterator.first.substr(1);
            newC->sup = iterator.second / TRANSACTION_NUM;
            if (newHead == nullptr) {
                newHead = newC;
                pHead = newHead;
            } else {
                pHead->next = newC;
                pHead = pHead->next;
            }
        }
    }
    return newHead;
}


int findSpecItem(Connect &connect, DataHead *mining, int i) {
    vector<Connect> *v = &mining[i].miningList;
    int index = (*v)[(*v).size() - 1].i;
    Connect *p = all2[i].seqJobs[index].cp;
    while (p != nullptr) {
        cout << 187 << endl;
        if (p->relation == connect.relation && p->name1 == connect.name1) {
            return p->i;
        }
        p = p->next;
    }
    return -1;
}

int findSpecItem(int relation, string name, Transaction &transaction, int x) {
    int next = transaction.seqJobs[x].nextSpecItems[relation];
    while (next != -1) {
        if (transaction.seqJobs[next].name1 == name)
            return next;
        next = transaction.seqJobs[next].nextSpecItems[relation];
    }
    return -1;
}

bool cmpTransaction(int i, DataHead *mining, int index) {
    Complete *p = rulesHead;
    CompleteHead *pH = nullptr;
    while (p != nullptr) {
        cout << 200 << endl;
        pH = p->head;
        while (pH != nullptr) {
            cout << 203 << endl;

            if (pH->index == i) {
                int j = 0;
                double maxSupComplete = 0;
                double maxSupMining = 0;
                bool same = true;
                for (; j < mining[i].miningList.size(); ++j) {
                    if (pH->oneRule[j].sup > maxSupComplete)
                        maxSupComplete = pH->oneRule[j].sup;
                    if (mining[i].miningList[j].sup > maxSupMining)
                        maxSupMining = mining[i].miningList[j].sup;

                    if (pH->oneRule[j].i != mining[i].miningList[j].i) {
                        same = false;
                        break;
                    }
                }

                if (same) {
                    for (; j < pH->oneRule.size()-1; ++j) {
                        if (pH->oneRule[j].sup > maxSupComplete)
                            maxSupComplete = pH->oneRule[j].sup;
                        if (pH->oneRule[j+1].i == index && maxSupComplete >= maxSupMining)
                            return true;
                    }
                }

            }
            pH = pH->next;
        }
        p = p->next;
    }
    return false;
}

void chooseNext(Connect *head, DataHead *mining) {

    Connect *p = head;   //关系
    CompleteNode *changeValid = nullptr; //记录这一次挖掘把哪些行的可挖掘属性置为false
    CompleteNode *pValid = nullptr;
    bool hasCandiValid = false;   //记录节点的候选集添加后置信度是否都不够，true表示有一条够，否则就当前作为规则
    while (p != nullptr) {
        cout << 246 << endl;

        double conf = 0; //记录这一条线的置信度

        for (int i = 0; i < TRANSACTION_NUM; ++i) {
            if (mining[i].isValid) {

                if (mining[i].miningList.size() == 1) {   //单个job的时候，找下一个关系
                    int origin = mining[i].miningList[0].i;
                    for (int j = mining[i].miningList[0].i; j < all2[i].seqJobs.size(); ++j) {
                        if (all2[i].seqJobs[j].name1 == mining[i].miningList[0].name1) {
                            mining[i].miningList[0].i = j;
                        }
                        if (findSpecItem(*p, mining, i) != -1)
                            break;
                        else
                            mining[i].miningList[0].i = origin; //mining[i].miningList[0].i = origin
                    }
                }

                int nextP = findSpecItem(*p, mining, i);
                if (nextP == -1) {
                    mining[i].isValid = false;

                    CompleteNode *node = new CompleteNode;
                    node->i = i;
                    if (changeValid == nullptr) {
                        changeValid = node;
                        pValid = node;
                    } else {
                        pValid->next = node;
                        pValid = pValid->next;
                    }
                }
            }
        }

        bool shouldBan = true;
        for (int i = 0; i < TRANSACTION_NUM; ++i) {
            if (mining[i].isValid) {
                int nextP = findSpecItem(*p, mining, i);
                shouldBan = cmpTransaction(i, mining, nextP);
                if (!shouldBan)
                    break;
            }
        }


        if (shouldBan) {  //前面挖过的是这个的超集，直接不挖了
            pValid = changeValid;
            CompleteNode *pFree = pValid;
            while (true) {
                cout << 298 << endl;
                if (pValid != nullptr) {
                    mining[pValid->i].isValid = true;
                    pValid = pValid->next;
                    delete pFree;
                    pFree = pValid;
                } else {
                    changeValid = nullptr;
                    break;
                }
            }
            p = p->next;
            continue;
        } else {

            //计算置信度，判断是否继续挖掘
            int idx = 0;
            while (!mining[idx].isValid) {
                cout << 316 << endl;
                idx ++;
            }
            double maxSup = 0;
            for (Connect& connect : mining[idx].miningList) {
                if (connect.sup > maxSup)
                    maxSup = connect.sup;
            }
            conf = p->sup / maxSup;
            if (conf >= LINE) { //置信度够，先添加新的候选集，然后判断是否继续挖掘
                hasCandiValid = true;
                for (int i = 0; i < TRANSACTION_NUM; ++i) {
                    if (mining[i].isValid) {
                        int nextP = findSpecItem(*p, mining, i);
                        Connect connect;
                        connect.sup = p->sup;
                        connect.i = nextP;
                        connect.name1 = p->name1;
                        connect.relation = p->relation;
                        mining[i].miningList.push_back(connect);
                    }
                }
                Connect *newHead = wantCandiItem(mining);

                if (newHead == nullptr) { //没有候选集了
                    addNewRule(mining);
                } else {
                    chooseNext(newHead, mining);
                }

            }
        }

        if (conf >= LINE) {  //代表添加了新节点，换候选集挖掘时要把新添加的节点退掉，如果false就是置信度不够没有添加
            for (int i = 0; i < TRANSACTION_NUM; ++i) {
                if (mining[i].isValid) {
                    mining[i].miningList.pop_back();
                }
            }
        }

        pValid = changeValid;
        CompleteNode *pFree = pValid;
        while (true) {
            cout << 360 << endl;
            if (pValid != nullptr) {
                mining[pValid->i].isValid = true;
                pValid = pValid->next;
                delete pFree;
                pFree = pValid;
            } else {
                changeValid = nullptr;
                break;
            }
        }
        p = p->next;
    }

    if (!hasCandiValid)  //所有候选集置信度都不够，把当前加进去
        addNewRule(mining);
}

void addNewRule(DataHead *mining) {
    int idx = 0;
    for (; idx < TRANSACTION_NUM; ++idx) {
        if (mining[idx].isValid)
            break;
    }

    if (mining[idx].miningList.size() > 2) {
        Complete *complete = new Complete;
        if (rulesHead == nullptr) {
            rulesHead = complete;
            rulesTail = rulesHead;
        } else {
            rulesTail->next = complete;
            rulesTail = rulesTail->next;
        }
        CompleteHead *pH = complete->head;

        for (int i = 0; i < TRANSACTION_NUM; ++i) {
            if (mining[i].isValid) {
                CompleteHead *cHead = new CompleteHead;
                cHead->index = i;
                for (auto &j: mining[i].miningList) {
                    Connect connect;
                    connect.sup = j.sup;
                    connect.i = j.i;
                    connect.name1 = j.name1;
                    connect.relation = j.relation;
                    cHead->oneRule.push_back(connect);
                }
                if (pH == nullptr) {
                    complete->head = cHead;
                    pH = complete->head;
                } else {
                    pH->next = cHead;
                    pH = pH->next;
                }
            }
        }
    }
}

int main() {
    fill();

    for (string name: freqItems) {
        doDM(name);
    }

    saveRules();

    return 0;
}
