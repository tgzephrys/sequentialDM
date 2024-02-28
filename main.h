#ifndef SEQUENTIALDM_MAIN_H
#define SEQUENTIALDM_MAIN_H

void doDM(char c);
void findFirstNode(DataHead* mining, char c);
Connect *wantCandiItem(DataHead *mining);
void chooseNext(Connect *head, DataHead *mining);
void addNewRule (DataHead *mining);

#endif //SEQUENTIALDM_MAIN_H
