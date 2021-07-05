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
  
    bool***** conv_weight;
    conv_weight = new bool****[5];
    conv_weight[0] = new bool***[1];
    for(unsigned i = 0; i < 1; i++){
        conv_weight[0][i] = new bool**[128];
        for(unsigned j = 0; j < 128; j++){
            conv_weight[0][i][j] = new bool*[3];
            for(unsigned k = 0; k < 3; k++){
                conv_weight[0][i][j][k] = new bool[3];
                for(unsigned l = 0; l < 3; l++){
                    conv_weight[0][i][j][k][l] = 0;
                }
            }
        }
    }

    for(unsigned m = 1; m < 5; m++){
        conv_weight[m] = new bool***[128];
        for(unsigned i = 0; i < 128; i++){
            conv_weight[m][i] = new bool**[128];
            for(unsigned j = 0; j < 128; j++){
                conv_weight[m][i][j] = new bool*[3];
                for(unsigned k = 0; k < 3; k++){
                    conv_weight[m][i][j][k] = new bool[3];
                    for(unsigned l = 0; l < 3; l++){
                        conv_weight[m][i][j][k][l] = 0;
                    }
                }
            }
        }
    }
    cout<<2<<endl;
    fstream conv1_w_1("conv1_w-1.txt");
    if (!conv1_w_1){
        cout<<"error"<<endl;
    }
    char buf;
    // vector<int> C;
    // C.reserve(size);
    float buffer;
    for(size_t i = 0; i < 1; ++i){
        for(size_t j = 0; j < 128; ++j){
            for(size_t k = 0; k < 3; ++k){
                for(size_t l = 0; l < 3; ++l){
                    conv1_w_1 >> buffer;
                    if(buffer == -1) conv_weight[0][i][j][k][l] = false;
                    if(buffer == 1) conv_weight[0][i][j][k][l] = true;
                }
            }
        }
    }
    conv1_w_1.close();
    
    fstream conv_w_2("conv1_w-2.txt");
    for(size_t i = 0; i < 128; ++i){
        for(size_t j = 0; j < 128; ++j){
            for(size_t k = 0; k < 3; ++k){
                for(size_t l = 0; l < 3; ++l){
                    conv_w_2 >> buffer;
                    if(buffer == -1) conv_weight[1][i][j][k][l] = false;
                    if(buffer == 1) conv_weight[1][i][j][k][l] = true;
                }
            }
        }
    }
    conv_w_2.close();

    fstream conv_w_3("conv1_w-3.txt");
    for(size_t i = 0; i < 128; ++i){
        for(size_t j = 0; j < 128; ++j){
            for(size_t k = 0; k < 3; ++k){
                for(size_t l = 0; l < 3; ++l){
                    conv_w_2 >> buffer;
                    if(buffer == -1) conv_weight[2][i][j][k][l] = false;
                    if(buffer == 1) conv_weight[2][i][j][k][l] = true;
                }
            }
        }
    }
    conv_w_3.close();

    fstream conv_w_4("conv1_w-4.txt");
    for(size_t i = 0; i < 128; ++i){
        for(size_t j = 0; j < 128; ++j){
            for(size_t k = 0; k < 3; ++k){
                for(size_t l = 0; l < 3; ++l){
                    conv_w_2 >> buffer;
                    if(buffer == -1) conv_weight[3][i][j][k][l] = false;
                    if(buffer == 1) conv_weight[3][i][j][k][l] = true;
                }
            }
        }
    }
    conv_w_4.close();

    fstream conv_w_5("conv1_w-5.txt");
    for(size_t i = 0; i < 128; ++i){
        for(size_t j = 0; j < 128; ++j){
            for(size_t k = 0; k < 3; ++k){
                for(size_t l = 0; l < 3; ++l){
                    conv_w_2 >> buffer;
                    if(buffer == -1) conv_weight[4][i][j][k][l] = false;
                    if(buffer == 1) conv_weight[4][i][j][k][l] = true;
                }
            }
        }
    }
    conv_w_5.close();

    cout<<"completed!!!"<<endl;
    
    bool***** conv_neurons;

    conv_neurons = new bool****[3];
    conv_neurons[0] = new bool***[1];
    for(unsigned j = 0; j < 1; ++j){
        conv_neurons[0][j] = new bool**[30];
        for(unsigned k = 0; k < 30; ++k){
            conv_neurons[0][j][k] = new bool*[30];
            for(unsigned l = 0; l < 30; ++l){
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

    conv_neurons[1] = new bool***[128];
    for(unsigned j = 0; j < 128; ++j){
        conv_neurons[1][j] = new bool**[15];
        for(unsigned k = 0; k < 15; ++k){
            conv_neurons[1][j][k] = new bool*[15];
            for(unsigned l = 0; l < 15; ++l){
                conv_neurons[1][j][k][l] = new bool[bit_len];
                for(unsigned m = 0; m < bit_len; ++m){
                    conv_neurons[1][j][k][l][m] = 0;
                }
            }
        }
    }
    // conv_neurons[1] = sc.conv2d(conv_neurons[0], conv_weight[0], sum, 32, 3,128,3,1,1);
    
    conv_neurons[2] = new bool***[128];
    for(unsigned j = 0; j < 128; ++j){
        conv_neurons[2][j] = new bool**[8];
        for(unsigned k = 0; k < 8; ++k){
            conv_neurons[2][j][k] = new bool*[8];
            for(unsigned l = 0; l < 8; ++l){
                conv_neurons[2][j][k][l] = new bool[bit_len];
                for(unsigned m = 0; m < bit_len; ++m){
                    conv_neurons[2][j][k][l][m] = 0;
                }
            }
        }
    }
    
    bool*** fc_weight;
    fc_weight = new bool**[2];

    fc_weight[0] = new bool*[128 * 7 * 7];
    for(size_t i = 0; i < 128 * 7 * 7; ++i){
        fc_weight[0][i] = new bool[512];
        for(size_t j = 0; j < 512; ++j){
            fc_weight[0][i][j] = 0;
        }
    }

    fc_weight[1] = new bool*[512];
    
    for(size_t i = 0; i < 512; ++i){
        fc_weight[1][i] = new bool[10];
        for(size_t j = 0; j < 10; ++j){
            fc_weight[1][i][j] = 0;
        }
    }

    fstream fc_w_1("con_w-1.txt");
    for(size_t i = 0; i < 128 * 7 * 7; ++i){
        for(size_t j = 0; j < 512; ++j){
            fc_w_1 >> buffer;
            if(buffer == -1) fc_weight[0][i][j] = false;
            if(buffer == 1) fc_weight[0][i][j] = true;
        }
    }
    fc_w_1.close();

    fstream fc_w_2("con_w-2.txt");
    for(size_t i = 0; i < 512; ++i){
        for(size_t j = 0; j < 10; ++j){
            fc_w_1 >> buffer;
            if(buffer == -1) fc_weight[1][i][j] = false;
            if(buffer == 1) fc_weight[1][i][j] = true;
        }
    }
    fc_w_2.close();

    bool*** fc_neurons;
    fc_neurons = new bool**[3];
    
    fc_neurons[0] = new bool*[128 * 7 * 7];
    for(size_t i = 0; i < 128 * 7 * 7; ++i){
        fc_neurons[0][i] = new bool[bit_len];
        for(size_t j = 0; j < bit_len; ++j){
            fc_neurons[0][i][j] = 0;
        }
    }

    fc_neurons[1] = new bool*[512];
    for(size_t i = 0; i < 512; ++i){
        fc_neurons[1][i] = new bool[bit_len];
        for(size_t j = 0; j < bit_len; ++j){
            fc_neurons[1][i][j] = 0;
        }
    }

    fc_neurons[2] = new bool*[10];
    for(size_t i = 0; i < 10; ++i){
        fc_neurons[2][i] = new bool[bit_len];
        for(size_t j = 0; j < bit_len; ++j){
            fc_neurons[2][i][j] = 0;
        }
    }
    
    fstream input_txt("inupt.txt");
    fstream labels_txt("labels.txt");
    int label = 0, max_cand = 0, correct_count = 0;
    float max = 0;
    for(size_t i = 0; i < 1000; ++i)
    {
        for(size_t j = 1; j < 29; ++j)
        {
            for(size_t k = 1; k < 29; ++k)
            {
                input_txt >> buffer;
                conv_neurons[0][0][j][k] = sc.bit_gen(buffer / 255.0);
            }
        }

        labels_txt >> label;

        //for convolution layers
        conv_neurons[0] = sc.conv2d(conv_neurons[0], conv_weight[0], sum, 28, 1,128,3,1,1);
        cout<<"conv1"<<endl;
        conv_neurons[0] = sc.conv2d(conv_neurons[0], conv_weight[1], sum, 28, 1,128,3,1,1);
        cout<<"conv2"<<endl;
        conv_neurons[1] = sc.maxpool2d(conv_neurons[0], 28, 128, 2, 2);
        conv_neurons[1] = sc.conv2d(conv_neurons[1], conv_weight[2], sum, 14, 1,128,3,1,1);
        cout<<"conv3"<<endl;
        conv_neurons[1] = sc.conv2d(conv_neurons[1], conv_weight[3], sum, 14, 1,128,3,1,1);
        cout<<"conv4"<<endl;
        conv_neurons[2] = sc.maxpool2d(conv_neurons[1], 14, 128, 2, 2);
        conv_neurons[2] = sc.conv2d(conv_neurons[2], conv_weight[4], sum, 7, 1,128,3,1,1);
        cout<<"conv5"<<endl;

        //flatten the neurons
        fc_neurons[0] = sc.view(conv_neurons[2], 128, 7);
        fc_neurons[1] = sc.linear(fc_neurons[0], fc_weight[0], sum, 128 * 7 * 7, 512);
        cout<<"fc1"<<endl;
        fc_neurons[2] = sc.linear(fc_neurons[1], fc_weight[1], sum, 512, 10);
        cout<<"fc2"<<endl;


        max = -10000;
        max_cand = 0;
        for(size_t j = 0; j < 10; ++j)
        {
            cout << j + 1 << " : " << sc.print(fc_neurons[2][j]) << endl;
            if(sc.print(fc_neurons[2][j]) > max)
            {
                max = sc.print(fc_neurons[2][j]);
                max_cand = j;
            }
        }

        cout << "label is : " << label << " ;predict is : " << max_cand << endl;
        if(max_cand == label)
        {
            ++correct_count;
            cout << "correct!!!" << endl;
        }
        else cout << "wrong!!!" << endl;
        cout << "accuracy = " << (float)correct_count / (i + 1) << endl;
    }


    input_txt.close();
    labels_txt.close();
    // cout<<"5"<<endl;
    // conv_neurons[2] = sc.conv2d(conv_neurons[2], conv_weight[2], sum, 16, 128,128,3,1,1);
    // conv_neurons[2] = sc.conv2d(conv_neurons[2], conv_weight[3], sum, 16, 128,128,3,1,1);
    
    
    // conv_neurons[4] = sc.maxpool2d(conv_neurons[2], 16, 128, 2, 2);
    // conv_neurons[4] = sc.conv2d(conv_neurons[4], conv_weight[4], sum, 8, 128,128,3,1,1);
    // conv_neurons[4] = sc.conv2d(conv_neurons[4], conv_weight[5], sum, 8, 128,128,3,1,1);
    
    
    return 0;
}



// while (fin>>buffer){
    //     cout<<1<<endl;
    // }
    // bool flag = 1;
    // unsigned a = 0;
    // short rank = 0, in_channel = -1,conv = -1, out_channel = -1, kernal_1 = -1, kernal_2 = -1;

    // while(flag){
    //     fin>>buf;
    //     a++;
    //     if(buf == 'c')
    //         conv++;
    //     if(buf == '['){
    //         rank++;
    //         if(rank == 2)
    //             in_channel++;
    //         if(rank == 3)
    //             out_channel++;
    //         if(rank == 4)
    //             kernal_1++;
    //     }
    
    //     if(buf == ']'){
    //         rank--;
    //         if(rank == 0)
    //             in_channel = -1;
    //         if(rank == 1)
    //             out_channel = -1;
    //         if(rank == 2)
    //             kernal_1 = -1;
    //         if(rank == 3)
    //             kernal_2 = -1;
    //     }
    //     if(rank == 4){
    //         if(buf == '0'){
    //             kernal_2++;
    //             // cout<<conv <<" "<<in_channel<<" "<<out_channel<<" "<<kernal_1<<" "<<kernal_2<<endl;
    //             conv_weight[conv][in_channel][out_channel][kernal_1][kernal_2] = 0;
    //         }
    //         if(buf == '1'){
    //             kernal_2++;
    //             // cout<<conv<<" "<<in_channel<<" "<<out_channel<<" "<<kernal_1<<" "<<kernal_2<<endl;
    //             conv_weight[conv][in_channel][out_channel][kernal_1][kernal_2] = 1;
    //         }
    //     }
    //     if(buf == '?')
    //         flag = 0;
    // }
    // cout<<"complete=========zz==z=================="<<endl;
    // fin.close();
    // fstream fin_1("fc-6.txt");
    // if (!fin_1){
    //     cout<<"error"<<endl;
    // }
    // flag = 1;
    // short fc = -1, weight_1 = -1, weight_2 = -1;
    // rank = 0;
    // bool*** chart_1;
    // chart_1 = new bool**[5];
    // chart_1[0] = new bool*[512];
    // chart_1[4] = new bool*[128];

    // for(unsigned i = 0; i < 512; i++){
    //     chart_1[0][i] = new bool[128];
    //     for(unsigned j = 0; j < 128; j++){
    //         chart_1[0][i][j] = 0;
    //     }
    // }

    // for(unsigned i = 0; i < 128; i++){
    //     chart_1[4][i] = new bool[10];
    //     for(unsigned j = 0; j < 10; j++){
    //         chart_1[4][i][j] = 0;
    //     }
    // }

    // for(unsigned i = 1; i < 4; i++){
    //     chart_1[i] = new bool*[128];
    //     for(unsigned j = 0; j < 128; j++){
    //         chart_1[i][j] = new bool[128];
    //         for(unsigned k = 0; k < 128; k++){
    //             chart_1[i][j][k] = 0;
    //         }
    //     }
    // }

    // while(flag){
    //     fin_1>>buf;
    //     if(buf == 'f')
    //         fc++;
    //     if(buf == '['){
    //         rank++;
    //         if(rank == 2)
    //             weight_1++;
    //     }
    //     if(buf == ']'){
    //         rank--;
    //         if(rank == 0)
    //             weight_1 = -1;
    //         if(rank == 1)
    //             weight_2 = -1;
    //     }
    //     if(rank == 2){
    //         if(buf == '0'){
    //             weight_2++;
    //             // cout<<fc <<" "<<weight_1<<" "<<weight_2<<" "<<buf<<" "<<endl;
    //             chart_1[fc][weight_1][weight_2] = 0; 
    //         }
    //         if(buf == '1'){
    //             weight_2++;
    //             // cout<<fc <<" "<<weight_1<<" "<<weight_2<<" "<<buf<<" "<<endl;
    //             chart_1[fc][weight_1][weight_2] = 1; 
    //         }
    //     }
    //     if(buf == '?')
    //         flag = 0;
    // }
    // fin_1.close();
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
    // cout<<"1=========="<<endl;
