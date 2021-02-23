/****************************************************************************
  FileName     [ SC.h ]
  Author       [ YEN-JU (Andrew) LEE ]
  Copyright    [ Copyleft(c) 2021-present ALcom(III), EE, NTU, Taiwan ]
****************************************************************************/
#ifndef SC_H
#define SC_H

#include <cstring>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
using namespace std;
const int bit_len = 1000000;

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
    bool* bit_gen(double);
    ESL number_gen(double , bool*);
    bool* XNOR(bool*, bool*);
    ESL APC(ESL, ESL);
    bool* MUX(bool*, bool*);
    ESL ESL_Multiplier(ESL, ESL);
    ESL ESL_Adder(ESL, ESL);
};

#endif