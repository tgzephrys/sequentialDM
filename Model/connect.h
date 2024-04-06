#ifndef SEQUENTIALDM_CONNECT_H
#define SEQUENTIALDM_CONNECT_H

#include "string"
using namespace std;

class Connect {
public:
    int i = -1;
    Connect *next = nullptr;
    int relation = 0;
    string name1;
    double sup = 0;

    Connect() {}

    Connect(Connect const &connect) {
        this->i = connect.i;
        this->next = nullptr;
        this->relation = connect.relation;
        this->name1 = connect.name1;
        this->sup = connect.sup;
    }
    int operator<(const Connect &connect) const {
        if(this->name1 < connect.name1 || this->relation < connect.relation)
            return true;
        else
            return false;
    }
};


#endif //SEQUENTIALDM_CONNECT_H
