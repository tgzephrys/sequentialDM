#ifndef SEQUENTIALDM_MAIN_H
#define SEQUENTIALDM_MAIN_H

void doDM(string name);
void findFirstNode(DataHead* mining, string name);
Connect *wantCandiItem(DataHead *mining);
void chooseNext(Connect *head, DataHead *mining);
void addNewRule (DataHead *mining);

#endif //SEQUENTIALDM_MAIN_H
