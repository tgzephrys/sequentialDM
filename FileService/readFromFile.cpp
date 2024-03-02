#include "readFromFile.h"
#include "../Model/seqJob.h"
#include "../ToolKit/global.h"

void addItemOccNum(char name) {
    if (!addValid.count(name)) {
        addValid[name] = true;
    }

    if (addValid[name] == true) {

        if (!singleItem.count(name)) {
            singleItem[name] = 1;
        } else
            singleItem[name]++;
    }

    addValid[name] = false;
}

void fill() {
    FILE *fp;
    if ((fp = fopen("../seqActivities.txt", "r")) == nullptr) {
        fp = fopen("../seqActivities", "w");
    }

    int index = 0;
    int innerI = 0;
    singleItem.clear();
    addValid.clear();

    ifstream fileStream;

    fileStream.open("../tb_battle_info.txt", ios::in);
//    fileStream.open("../seqActivities.txt", ios::in);

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

    all2 = vector<Node> (TRANSACTION_NUM);

    fileStream.clear();
    fileStream.seekg(fileStream.beg);

    string line;
    while (getline(fileStream, line) && !line.empty()) {

    }

    char ch = 0;
    while (true) {


        ch = fgetc(fp); //新一行

        while (true) {  //结束一行

            seqJob *job = new seqJob;

            while (ch != ')') {

                while (ch == '(' || ch == ',') {
                    ch = fgetc(fp);
                }

                job->name = ch;

                fgetc(fp);
                fscanf(fp, "%d", &job->startTime);

                fgetc(fp);
                fscanf(fp, "%d", &job->endTime);


                ch = fgetc(fp);
            }

            if (innerI == 0) {
                Node* node = new Node;
                all[index] = node;
                TRANSACTION_NUM++;
            }

            if (innerI < 100) {
                seqJob* jobP = job;
                all[index]->aTransaction[innerI] = jobP;
                all[index]->num ++;
                addItemOccNum(job->name);
            }
            innerI++;

            ch = fgetc(fp);
            if (ch == '\n' || ch == EOF)
                break;
        }

        for (int i = 0; i < innerI; ++i) {
            Connect *p = all[index]->aTransaction[i]->cp;

            for (int j = i + 1; j < innerI; ++j) {
                Connect *c = new Connect;
                c->relation = calcRelation(all[index]->aTransaction[i], all[index]->aTransaction[j]);
                c->i = j;
                c->name = all[index]->aTransaction[j]->name;
                if (p == nullptr) {
                    all[index]->aTransaction[i]->cp = c;
                    p = all[index]->aTransaction[i]->cp;
                } else {
                    p->next = c;
                    p = p->next;
                }
            }
        }
        if (ch == EOF)break;
        index++;
        innerI = 0;

        map<char, int>::iterator iterator;
        for (iterator = addValid.begin(); iterator != addValid.end(); iterator++) {
            iterator->second = true;
        }
    }
    int i = 0;
    map<char, int>::iterator iterator;
    for (iterator = singleItem.begin(); iterator != singleItem.end(); iterator++) {
        if ((iterator->second / (float) TRANSACTION_NUM) >= LINE)
            freq1tem.push_back(iterator->first);
    }
}
