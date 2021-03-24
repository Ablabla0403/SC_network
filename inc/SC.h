/****************************************************************************
  FileName     [ SC.h ]
  Author       [ YEN-JU (Andrew) LEE ]
  Copyright    [ Copyleft(c) 2021-present ALcom(III), EE, NTU, Taiwan ]
****************************************************************************/
#ifndef SC_H
#define SC_H

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <time.h>

using namespace std;

struct ESL{  //數字struct，一個存分子一個存分母
    bool *h;
    bool *l;
};

class SC
{
public:
    SC() {}
    double to_bipolar(int);
    double print(ESL);
    double print(bool*);
    bool* bit_gen(double);
    ESL number_gen(double);
    bool* XNOR(bool*, bool*);
    ESL APC(ESL, ESL);
    bool* APC(bool*, bool*);
    bool* MUX(bool*, bool*);
    ESL ESL_Multiplier(ESL, ESL);
    ESL ESL_Adder(ESL, ESL);
    bool* ReLU(bool*);
    ESL ReLU_grad(ESL);
    bool* ReLU_grad(bool*);
    ESL ToESL(bool*);
    ESL ReLU(ESL);
    ESL NEW_APC(bool*, bool*);
    ESL NEW_APC(ESL, ESL);
    bool* NEW_APC_B(bool*, bool*);
};


#endif