#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include "../inc/SC.h"
#include "../inc/definition.h"

using namespace std;

int main(int argc,char** argv){
    SC sc;
    srand(time(NULL));
    cout<<"program in"<<endl;
    vector<bool*> sum;
    
    bool**** test_in;//channel|size+2*padding|size+2*padding|bit_len
    bool**** filter; //in_channel|out_channel|kernal|kernal
    bool**** test_out;//channel|size+2*padding|size+2*padding|bit_len
    // bool* test_in[3][7][7];
    // bool filter[3][5][3][3];
    // bool* test_out[5][7][7];
    test_in = new bool***[3];
    filter = new bool***[3];
    test_out = new bool***[5];

    for(unsigned i = 0; i < 3; i++){
        test_in[i] = new bool**[7];
        for(unsigned j = 0; j < 7; j++){
            test_in[i][j] = new bool*[7];
            for(unsigned k = 0; k < 7;k++){
                test_in[i][j][k] = new bool[bit_len];
                test_in[i][j][k] = sc.bit_gen(1);
            }
        }
    }

    for(unsigned i = 0; i < 5; i++){
        test_out[i] = new bool**[7];
        for(unsigned j = 0; j < 7; j++){
            test_out[i][j] = new bool*[7];
            for(unsigned k = 0; k < 7;k++){
                test_out[i][j][k] = new bool[bit_len];
                test_out[i][j][k] = sc.bit_gen(0);
            }
        }
    }

    for(unsigned i = 0; i < 3; i++){
        filter[i] = new bool**[5];
        for(unsigned j = 0; j <5; j++){
            filter[i][j] = new bool*[3];
            for(unsigned k = 0; k < 3;k++){
                filter[i][j][k] = new bool[3];
                for(unsigned l = 0; l < 3; l++){
                    filter[i][j][k][l] = 1;
                }
            }
        }
    }
    cout<<test_out[4][6][6][7]<<endl;

    test_out = sc.conv2d(test_in, filter, sum, 5, 3, 5, 3, 1, 1);

    cout<<test_out[4][6][6][7]<<endl;
    

    
    return 0;
}

