#include "saveToFile.h"
#include "../Model/Complete.h"

void saveRules() {
    fstream file = nullptr;
//    file.open("../all_rules.txt", ios::out | ios::trunc);
    file.open("../all_rules1.txt", ios::out | ios::trunc);

    Complete *p = rulesHead;
    while (p != nullptr) {

        vector<Connect> *oneRule = &p->head->oneRule;

        double maxSup = 0;

        for (int i = 0; i < (*oneRule).size(); ++i) {
            if (i != (*oneRule).size() - 1)
                if ((*oneRule)[i].sup > maxSup)
                    maxSup = (*oneRule)[i].sup;

            if (i == 0) {
                file << (*oneRule)[i].name1;
            } else {
                file << transRelation((*oneRule)[i].relation) << (*oneRule)[i].name1;
            }
        }
        double conf = 0;
        conf = (*oneRule)[(*oneRule).size()-1].sup / maxSup;

        file << "   " << "conf: " << conf;

        file << "\n";

        p = p->next;
    }

    file.close();
}

string transRelation(int relation) {
    switch (relation) {
        case 1:
            return "follows";
        case 2:
            return "meets";
        case 3:
            return "overlaps";
        case 4:
            return "contains";
        default:
            return "matches";
    }
}
