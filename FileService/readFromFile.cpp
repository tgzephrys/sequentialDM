#include "readFromFile.h"
#include "../Model/seqJob.h"
#include "../ToolKit/global.h"
#include "set"

void fill() {
//    FILE *fp;
//    if ((fp = fopen("../seqActivities.txt", "r")) == nullptr) {
//        fp = fopen("../seqActivities", "w");
//    }

//    int index = 0;
//    int innerI = 0;
//    singleItem.clear();
//    addValid.clear();

    ifstream fileStream;

//    fileStream.open("../tb_battle_info.txt", ios::in);
    fileStream.open("../test_data.txt", ios::in);

    //现在开始取最后一行看有多少个事务
    fileStream.seekg(-1, fileStream.end);
    while(fileStream.peek() == '\n') {  //规避结尾空行
        fileStream.seekg(-1, fileStream.cur);
    }

    while(fileStream.peek() != '\n') {
        fileStream.seekg(-1, fileStream.cur);
    }

    fileStream.seekg(1, fileStream.cur);
    string lastLine;
    getline(fileStream, lastLine);

    vector<string> vec = split(lastLine, ',');
    TRANSACTION_NUM = stoi(vec[1]);

    all2 = vector<Transaction> (TRANSACTION_NUM);

    fileStream.clear();
    fileStream.seekg(fileStream.beg);

    string line;
    getline(fileStream, line);
    vector<Transaction>::iterator transactionsItr = all2.begin();

    set<string> rowItems;
    map<string, int> allItems;

    while (getline(fileStream, line) && !line.empty()) {
        if (line.substr(0, 7) == "lq_name") {

            for (vector<seqJob>::iterator itr1 = transactionsItr->seqJobs.begin(); itr1 != transactionsItr->seqJobs.end(); itr1++ ) {
                Connect *p = itr1 -> cp;

                for (vector<seqJob>::iterator itr2 = itr1 + 1; itr2 != transactionsItr->seqJobs.end(); itr2++) {
//                    Connect *c = new Connect;
//                    c->relation = calcRelation(*itr1, *itr2);
//                    c->i = itr2 - transactionsItr->seqJobs.begin();
//                    c->name1 = itr2->name1;
//                    if (p == nullptr) {
//                        itr1->cp = c;
//                        p = itr1->cp;
//                    } else {
//                        p->next = c;
//                        p = p->next;
//                    }
                    bool allHasNext = true;
                    for (int idx: itr1->nextSpecItems) {
                        if (idx == -1)
                            allHasNext = false;
                    }
                    if (allHasNext) break;

                    int relation = calcRelation(*itr1, *itr2);
                    if (itr1->nextSpecItems[relation] == -1) {
                        itr1->nextSpecItems[relation] = itr2 - transactionsItr->seqJobs.begin();
                    }
                }
            }

            for (string name : rowItems) {
                allItems[name] ++;
            }

            rowItems.clear();
            transactionsItr++;
            continue;
        }

        vector<string> jobVec = split(line, ',');
        seqJob job = seqJob();
        job.name1 = jobVec[4];
        rowItems.insert(job.name1);
        try {
            job.startTime = stoi(jobVec[5]);
        } catch (const std::invalid_argument& e) {
            cout << jobVec[5] << endl;
        }
        if (jobVec[6].empty()) { job.endTime = INT_MAX; }
        else { job.endTime = stoi(jobVec[6]); }

        transactionsItr->seqJobs.push_back(job);
    }
    for (map<string, int>::iterator itr = allItems.begin(); itr != allItems.end(); itr++) {
        if (((float )itr->second / (float)TRANSACTION_NUM) >= LINE)
            freqItems.push_back(itr->first);
    }

//    char ch = 0;
//    while (true) {
//
//
//        ch = fgetc(fp); //新一行
//
//        while (true) {  //结束一行
//
//            seqJob *job = new seqJob;
//
//            while (ch != ')') {
//
//                while (ch == '(' || ch == ',') {
//                    ch = fgetc(fp);
//                }
//
//                job->name = ch;
//
//                fgetc(fp);
//                fscanf(fp, "%d", &job->startTime);
//
//                fgetc(fp);
//                fscanf(fp, "%d", &job->endTime);
//
//
//                ch = fgetc(fp);
//            }
//
//            if (innerI == 0) {
//                Transaction* node = new Transaction;
//                all[index] = node;
//                TRANSACTION_NUM++;
//            }
//
//            if (innerI < 100) {
//                seqJob* jobP = job;
//                all[index]->aTransaction[innerI] = jobP;
//                all[index]->num ++;
//                addItemOccNum(job->name);
//            }
//            innerI++;
//
//            ch = fgetc(fp);
//            if (ch == '\n' || ch == EOF)
//                break;
//        }
//
//        for (int i = 0; i < innerI; ++i) {
//            Connect *p = all[index]->aTransaction[i]->cp;
//
//            for (int j = i + 1; j < innerI; ++j) {
//                Connect *c = new Connect;
//                c->relation = calcRelation(all[index]->aTransaction[i], all[index]->aTransaction[j]);
//                c->i = j;
//                c->name = all[index]->aTransaction[j]->name;
//                if (p == nullptr) {
//                    all[index]->aTransaction[i]->cp = c;
//                    p = all[index]->aTransaction[i]->cp;
//                } else {
//                    p->next = c;
//                    p = p->next;
//                }
//            }
//        }
//        if (ch == EOF)break;
//        index++;
//        innerI = 0;
//
//        map<char, int>::iterator iterator;
//        for (iterator = addValid.begin(); iterator != addValid.end(); iterator++) {
//            iterator->second = true;
//        }
//    }
//
//    map<char, int>::iterator iterator;
//    for (iterator = singleItem.begin(); iterator != singleItem.end(); iterator++) {
//        if ((iterator->second / (float) TRANSACTION_NUM) >= LINE)
//            freq1tem.push_back(iterator->first);
//    }
}
