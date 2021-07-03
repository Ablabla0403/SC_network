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
    
    // bool**** test_in;//channel|size+2*padding|size+2*padding|bit_len
    // bool**** filter; //in_channel|out_channel|kernal|kernal
    // bool**** test_out;//channel|size+2*padding|size+2*padding|bit_len
    // // bool* test_in[3][7][7];
    // // bool filter[3][5][3][3];
    // // bool* test_out[5][7][7];
    // test_in = new bool***[3];
    // filter = new bool***[3];
    // test_out = new bool***[5];

    // for(unsigned i = 0; i < 3; i++){
    //     test_in[i] = new bool**[7];
    //     for(unsigned j = 0; j < 7; j++){
    //         test_in[i][j] = new bool*[7];
    //         for(unsigned k = 0; k < 7;k++){
    //             test_in[i][j][k] = new bool[bit_len];
    //             test_in[i][j][k] = sc.bit_gen(1);
    //         }
    //     }
    // }

    // for(unsigned i = 0; i < 5; i++){
    //     test_out[i] = new bool**[7];
    //     for(unsigned j = 0; j < 7; j++){
    //         test_out[i][j] = new bool*[7];
    //         for(unsigned k = 0; k < 7;k++){
    //             test_out[i][j][k] = new bool[bit_len];
    //             test_out[i][j][k] = sc.bit_gen(0);
    //         }
    //     }
    // }

    // for(unsigned i = 0; i < 3; i++){
    //     filter[i] = new bool**[5];
    //     for(unsigned j = 0; j <5; j++){
    //         filter[i][j] = new bool*[3];
    //         for(unsigned k = 0; k < 3;k++){
    //             filter[i][j][k] = new bool[3];
    //             for(unsigned l = 0; l < 3; l++){
    //                 filter[i][j][k][l] = 1;
    //             }
    //         }
    //     }
    // }
    // cout<<test_out[4][6][6][7]<<endl;

    // test_out = sc.conv2d(test_in, filter, sum, 5, 3, 5, 3, 1, 1);

    // cout<<test_out[4][6][6][7]<<endl;
    bool***** chart;
    chart = new bool****[8];
    chart[0] = new bool***[3];
    for(unsigned i = 0; i < 3; i++){
        chart[0][i] = new bool**[128];
        for(unsigned j = 0; j < 128; j++){
            chart[0][i][j] = new bool*[3];
            for(unsigned k = 0; k < 3; k++){
                chart[0][i][j][k] = new bool[3];
                for(unsigned l = 0; l < 3; l++){
                    chart[0][i][j][k][l] = 0;
                }
            }
        }
    }

    for(unsigned m = 1; m < 8; m++){
        chart[m] = new bool***[128];
        for(unsigned i = 0; i < 128; i++){
            chart[m][i] = new bool**[128];
            for(unsigned j = 0; j < 128; j++){
                chart[m][i][j] = new bool*[3];
                for(unsigned k = 0; k < 3; k++){
                    chart[m][i][j][k] = new bool[3];
                    for(unsigned l = 0; l < 3; l++){
                        chart[m][i][j][k][l] = 0;
                    }
                }
            }
        }
    }
    fstream fin("output-7.txt");
    if (!fin){
        cout<<"error"<<endl;
    }
    char buf;
    // vector<int> C;
    // C.reserve(size);
    // while (fin>>buffer){
    //     cout<<buffer<<endl;
    // }
    bool flag = 1;
    unsigned a = 0;
    short rank = 0, in_channel = -1,conv = -1, out_channel = -1, kernal_1 = -1, kernal_2 = -1;

    while(flag){
        fin>>buf;
        a++;
        if(buf == 'c')
            conv++;
        if(buf == '['){
            rank++;
            if(rank == 2)
                in_channel++;
            if(rank == 3)
                out_channel++;
            if(rank == 4)
                kernal_1++;
        }
        if(buf == ']'){
            rank--;
            if(rank == 0)
                in_channel = -1;
            if(rank == 1)
                out_channel = -1;
            if(rank == 2)
                kernal_1 = -1;
            if(rank == 3)
                kernal_2 = -1;
        }
        if(rank == 4){
            if(buf == '0'){
                kernal_2++;
                // cout<<conv <<" "<<in_channel<<" "<<out_channel<<" "<<kernal_1<<" "<<kernal_2<<endl;
                chart[conv][in_channel][out_channel][kernal_1][kernal_2] = 0;
            }
            if(buf == '1'){
                kernal_2++;
                // cout<<conv<<" "<<in_channel<<" "<<out_channel<<" "<<kernal_1<<" "<<kernal_2<<endl;
                chart[conv][in_channel][out_channel][kernal_1][kernal_2] = 1;
            }
        }
        if(buf == '?')
            flag = 0;
    }
    cout<<"complete"<<endl;
    fin.close();
    fstream fin_1("fc-6.txt");
    if (!fin_1){
        cout<<"error"<<endl;
    }
    flag = 1;
    short fc = -1, weight_1 = -1, weight_2 = -1;
    rank = 0;
    bool*** chart_1;
    chart_1 = new bool**[5];
    chart_1[0] = new bool*[512];
    chart_1[4] = new bool*[128];

    for(unsigned i = 0; i < 512; i++){
        chart_1[0][i] = new bool[128];
        for(unsigned j = 0; j < 128; j++){
            chart_1[0][i][j] = 0;
        }
    }

    for(unsigned i = 0; i < 128; i++){
        chart_1[4][i] = new bool[10];
        for(unsigned j = 0; j < 10; j++){
            chart_1[4][i][j] = 0;
        }
    }

    for(unsigned i = 1; i < 4; i++){
        chart_1[i] = new bool*[128];
        for(unsigned j = 0; j < 128; j++){
            chart_1[i][j] = new bool[128];
            for(unsigned k = 0; k < 128; k++){
                chart_1[i][j][k] = 0;
            }
        }
    }

    while(flag){
        fin_1>>buf;
        if(buf == 'f')
            fc++;
        if(buf == '['){
            rank++;
            if(rank == 2)
                weight_1++;
        }
        if(buf == ']'){
            rank--;
            if(rank == 0)
                weight_1 = -1;
            if(rank == 1)
                weight_2 = -1;
        }
        if(rank == 2){
            if(buf == '0'){
                weight_2++;
                // cout<<fc <<" "<<weight_1<<" "<<weight_2<<" "<<buf<<" "<<endl;
                chart_1[fc][weight_1][weight_2] = 0; 
            }
            if(buf == '1'){
                weight_2++;
                // cout<<fc <<" "<<weight_1<<" "<<weight_2<<" "<<buf<<" "<<endl;
                chart_1[fc][weight_1][weight_2] = 1; 
            }
        }
        if(buf == '?')
            flag = 0;
    }
    fin_1.close();
    // a=  0;
    // for(unsigned i = 0; i < 512; i++){
    //     for(unsigned j = 0; j < 128; j++){
    //         cout<<chart_1[0][i][j]<<" ";
    //         a++;
    //     }
    // }
    // cout<<"\n";
    // cout<<chart_1[0][0][127]<<endl;
    // cout<<128*512<<" "<<a<<endl;
    cout<<"1=========="<<endl;
    bool***** conv_neurons;
    conv_neurons = new bool****[10];
    conv_neurons[0] = new bool***[3];
    for(unsigned j = 0; j < 3; ++j){
        conv_neurons[0][j] = new bool**[34];
        for(unsigned k = 0; k < 34; ++k){
            conv_neurons[0][j][k] = new bool*[34];
            for(unsigned l = 0; l < 34; ++l){
                // cout<<l<<endl;
                conv_neurons[0][j][k][l] = new bool[bit_len];
                // cout<<l<<endl;
                for(unsigned m = 0; m < bit_len; ++m){
                    // cout<<l<<" "<<m<<endl;
                    conv_neurons[0][j][k][l][m] = 0;
                    // cout<<l<<" "<<m<<endl;
                }
            }
        }
    }
    cout<<"2========="<<endl;
    conv_neurons[1] = new bool***[128];
    for(unsigned j = 0; j < 128; ++j){
        conv_neurons[1][j] = new bool**[34];
        for(unsigned k = 0; k < 34; ++k){
            conv_neurons[1][j][k] = new bool*[34];
            for(unsigned l = 0; l < 34; ++l){
                conv_neurons[1][j][k][l] = new bool[bit_len];
                for(unsigned m = 0; m < bit_len; ++m){
                    conv_neurons[1][j][k][l][m] = 0;
                }
            }
        }
    }
    cout<<"3"<<endl;
    conv_neurons[1] = sc.conv2d(conv_neurons[0], chart[0], sum, 32, 3,128,3,1,1);
    
    for(unsigned i = 2; i < 4; ++i){
        conv_neurons[i] = new bool***[128];
        for(unsigned j = 0; j < 128; ++j){
            conv_neurons[i][j] = new bool**[18];
            for(unsigned k = 0; k < 18; ++k){
                conv_neurons[i][j][k] = new bool*[18];
                for(unsigned l = 0; l < 18; ++l){
                    conv_neurons[i][j][k][l] = new bool[bit_len];
                    for(unsigned m = 0; m < bit_len; ++m){
                        conv_neurons[i][j][k][l][m] = 0;
                    }
                }
            }
        }
    }
    cout << "4" <<endl;
    conv_neurons[1] = sc.conv2d(conv_neurons[1], chart[1], sum, 32, 128,128,3,1,1);
    cout<<"4.1"<<endl;
    conv_neurons[2] = sc.maxpool2d(conv_neurons[1], 32, 128, 2, 2);
    cout<<"5"<<endl;
    conv_neurons[2] = sc.conv2d(conv_neurons[2], chart[2], sum, 16, 128,128,3,1,1);
    conv_neurons[2] = sc.conv2d(conv_neurons[2], chart[3], sum, 16, 128,128,3,1,1);
    
    for(unsigned i = 4; i < 6; ++i){
        conv_neurons[i] = new bool***[128];
        for(unsigned j = 0; j < 128; ++j){
            conv_neurons[i][j] = new bool**[10];
            for(unsigned k = 0; k < 10; ++k){
                conv_neurons[i][j][k] = new bool*[10];
                for(unsigned l = 0; l < 10; ++l){
                    conv_neurons[i][j][k][l] = new bool[bit_len];
                    for(unsigned m = 0; m < bit_len; ++m){
                        conv_neurons[i][j][k][l][m] = 0;
                    }
                }
            }
        }
    }
    conv_neurons[4] = sc.maxpool2d(conv_neurons[2], 16, 128, 2, 2);
    conv_neurons[4] = sc.conv2d(conv_neurons[4], chart[4], sum, 8, 128,128,3,1,1);
    conv_neurons[4] = sc.conv2d(conv_neurons[4], chart[5], sum, 8, 128,128,3,1,1);
    for(unsigned i = 6; i < 8; ++i){
    for(unsigned i = 6; i < 8; ++i){
        conv_neurons[i] = new bool***[128];
        for(unsigned j = 0; j < 128; ++j){
            conv_neurons[i][j] = new bool**[6];
            for(unsigned k = 0; k < 6; ++k){
                conv_neurons[i][j][k] = new bool*[6];
                for(unsigned l = 0; l < 6; ++l){
                    conv_neurons[i][j][k][l] = new bool[bit_len];
                    for(unsigned m = 0; m < bit_len; ++m){
                        conv_neurons[i][j][k][l][m] = 0;
                    }
                }
            }
        }
    }
    cout<<6<<endl;
    conv_neurons[6] = sc.maxpool2d(conv_neurons[4], 8, 128, 2, 2);
    conv_neurons[6] = sc.conv2d(conv_neurons[6], chart[6], sum, 4, 128,128,3,1,1);
    conv_neurons[6] = sc.conv2d(conv_neurons[6], chart[7], sum, 4, 128,128,3,1,1);
    for(unsigned j = 0; j < 128; ++j){
        conv_neurons[8][j] = new bool**[4];
        for(unsigned k = 0; k < 4; ++k){
            conv_neurons[8][j][k] = new bool*[4];
            for(unsigned l = 0; l < 4; ++l){
                conv_neurons[8][j][k][l] = new bool[bit_len];
                for(unsigned m = 0; m < bit_len; ++m){
                    conv_neurons[8][j][k][l][m] = 0;
                }
            }
        }
    }
    cout<<7<<endl;
    conv_neurons[8] = sc.maxpool2d(conv_neurons[6], 4, 128, 2, 2);
    conv_neurons[8] = sc.conv2d(conv_neurons[8], chart[8], sum, 2, 128,128,3,1,1);
    conv_neurons[8] = sc.conv2d(conv_neurons[8], chart[9], sum, 2, 128,128,3,1,1);

    conv_neurons[9] = new bool***[128];
    for(unsigned j = 0; j < 128; ++j){
        conv_neurons[9][j] = new bool**[2];
        for(unsigned k = 0; k < 2; ++k){
            conv_neurons[9][j][k] = new bool*[2];
            for(unsigned l = 0; l < 2; ++l){
                conv_neurons[9][j][k][l] = new bool[bit_len];
                for(unsigned m = 0; m < bit_len; ++m){
                    conv_neurons[9][j][k][l][m] = conv_neurons[8][j][k + 1][l + 1][m];
                }
            }
        }
    }
    
    return 0;
}

