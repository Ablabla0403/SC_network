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
    int bb;
    char buf;
    // vector<int> C;
    // C.reserve(size);
    float buffer;
    

    float threshold_1[128] = { 31.2520, 31.7295, 31.9860, 32.1967, 32.0069, 32.0034, 32.3052, 31.9504, 32.4089, 32.4746, 31.4086, 31.3334, 31.4526, 31.9276, 32.0633, 31.9319, 31.5040, 32.0485, 32.0162, 31.9209, 31.7469, 32.4703, 31.5708, 31.9206, 32.1030, 31.3721, 32.2054, 31.6669, 31.9272, 32.0241, 31.9745, 32.6506, 31.9937, 32.3388, 32.6166, 32.0039, 31.4741, 32.0569, 31.8851, 32.6083, 31.9731, 31.9418, 31.8967, 31.5112, 32.1618, 32.5812, 31.3821, 32.1179, 31.5979, 32.4539, 32.4840, 32.2521, 32.4708, 31.8354, 32.0963, 32.0062, 31.8156, 31.7275, 32.4793, 32.0065, 31.9370, 32.0240, 31.8934, 31.5410, 32.0278, 32.0413, 31.9087, 32.4337, 31.9831, 32.5080, 32.2738, 31.9739, 31.6519, 31.9105, 32.0018, 32.0519, 32.0336, 31.9877, 32.0234, 32.1694, 32.4154, 31.9914, 32.0289, 31.9392, 32.2670, 31.9570, 32.5110, 32.0338, 31.4954, 31.5612, 32.0339, 32.0321, 31.9244, 32.2526, 31.4804, 31.9997, 31.8574, 32.5920, 31.9483, 31.4156, 31.8468, 32.0847, 32.0728, 31.6358, 31.5948, 32.1716, 32.0847, 32.4497, 32.7448, 31.5364, 31.9967, 31.8685, 32.0237, 32.7138, 32.4012, 31.8359, 31.7007, 32.9600, 32.0915, 32.0115, 32.5817, 31.5854, 32.0745, 31.9814, 32.0036, 32.4555, 32.0280, 31.5026} ;
    float threshold_2[64] = { 80.5260, 78.8360, 70.4906, 53.8416, 57.2258, 49.5227, 80.4251, 40.4497, 62.8976, 61.5424, 89.6907, 71.7569, 41.4356, 70.6796, 57.0597, 74.4207, 57.7348, 86.1379, 43.4228, 59.1331, 74.3588, 85.4249, 39.8367, 77.6866, 54.3752, 36.5591, 55.3117, 55.1413, 74.1729, 56.2914, 86.8700, 70.6369} ;
    float threshold_3[4] = { 20.3713, 21.2846, 22.3680, 12.4577} ;

    
    int*** fc_weight;
    fc_weight = new int**[4];

    fc_weight[0] = new int*[64];
    for(size_t i = 0; i < 64; ++i){
        fc_weight[0][i] = new int[32];
        for(size_t j = 0; j < 32; ++j){
            fc_weight[0][i][j] = 0;
        }
    }
    cout<<"a"<<endl;
    fc_weight[1] = new int*[32];
    
    for(size_t i = 0; i < 32; ++i){
        fc_weight[1][i] = new int[32];
        for(size_t j = 0; j < 32; ++j){
            fc_weight[1][i][j] = 0;
        }
    }
    cout<<"b"<<endl;
    fc_weight[2] = new int*[32];
    
    for(size_t i = 0; i < 32; ++i){
        fc_weight[2][i] = new int[4];
        for(size_t j = 0; j < 4; ++j){
            fc_weight[2][i][j] = 0;
        }
    }
    cout<<"c"<<endl;
    fc_weight[3] = new int*[32];
    
    for(size_t i = 0; i < 32; ++i){
        fc_weight[3][i] = new int[4];
        for(size_t j = 0; j < 4; ++j){
            fc_weight[3][i][j] = 0;
        }
    }

    fstream fc("fc.txt");
    if (!fc){
        cerr<<"error _fc_"<<endl;
    }
    for(size_t i = 0; i < 64; ++i){
        for(size_t j = 0; j < 32; ++j){
            fc >> buffer;
            // cout << buffer <<endl;
            if(buffer == -1) fc_weight[0][i][j] = -1;
            if(buffer == 1) fc_weight[0][i][j] = 1;
        }
    }
    
    for(size_t i = 0; i < 32; ++i){
        for(size_t j = 0; j < 32; ++j){
            fc >> buffer;
            // cout << buffer << endl;
            if(buffer == -1) fc_weight[1][i][j] = -1;
            if(buffer == 1) fc_weight[1][i][j] = 1;
        }
    }
    cout<<"1"<<endl;

    for(size_t i = 0; i < 32; ++i){
        for(size_t j = 0; j < 4; ++j){
            fc >> buffer;
            // cout << buffer << endl;
            if(buffer == -1) fc_weight[2][i][j] = -1;
            if(buffer == 1) fc_weight[2][i][j] = 1;
        }
    }
    cout<<"2"<<endl;
    for(size_t i = 0; i < 32; ++i){
        for(size_t j = 0; j < 4; ++j){
            fc >> buffer;
            // cout << buffer << endl;
            if(buffer == -1) fc_weight[3][i][j] = -1;
            if(buffer == 1) fc_weight[3][i][j] = 1;
        }
    }

    fc.close();
    cout<<"3"<<endl;
    bool*** fc_neurons;
    fc_neurons = new bool**[5];
    
    fc_neurons[0] = new bool*[64];
    for(size_t i = 0; i < 64; ++i){
        fc_neurons[0][i] = new bool[bit_len];
        for(size_t j = 0; j < bit_len; ++j){
            fc_neurons[0][i][j] = 0;
        }
    }

    fc_neurons[1] = new bool*[128];
    for(size_t i = 0; i < 128; ++i){
        fc_neurons[1][i] = new bool[bit_len];
        for(size_t j = 0; j < bit_len; ++j){
            fc_neurons[1][i][j] = 0;
        }
    }

    fc_neurons[2] = new bool*[128];
    for(size_t i = 0; i < 128; ++i){
        fc_neurons[2][i] = new bool[bit_len];
        for(size_t j = 0; j < bit_len; ++j){
            fc_neurons[2][i][j] = 0;
        }
    }

    fc_neurons[3] = new bool*[32];
    for(size_t i = 0; i < 32; ++i){
        fc_neurons[3][i] = new bool[bit_len];
        for(size_t j = 0; j < bit_len; ++j){
            fc_neurons[3][i][j] = 0;
        }
    }

    fc_neurons[4] = new bool*[4];
    for(size_t i = 0; i < 4; ++i){
        fc_neurons[4][i] = new bool[bit_len];
        for(size_t j = 0; j < bit_len; ++j){
            fc_neurons[4][i][j] = 0;
        }
    }
    
    

    fstream labels_txt("labels-2.txt");
    if (!labels_txt){
        cerr<<"error"<<endl;
    }

    fstream inputs_txt("inputs.txt");
    if (!inputs_txt){
        cerr<<"error"<<endl;
    }
    
    int label = 0, max_cand = 0, correct_count = 0;
    float max = 0;
    // char b;
    for(size_t i = 0; i < 3; ++i)
    {
        for(size_t j = 0; j < 64; ++j)
        {
            inputs_txt >> bb;
            // cout << "buffer = " << bb << endl;
            fc_neurons[0][j] = sc.bit_gen(bb / 128.0);
        }
        // cout<<"\n";

        labels_txt >> label;
        

        //for convolution layers
        // cout << conv_neurons[0][0][0][0] << endl;
        cout<<"fc1"<<endl;
        fc_neurons[1] = sc.linear(fc_neurons[0], fc_weight[0], sum, 64, 32);
        for(size_t i = 0; i < 32; ++i){
            cout << sc.print(fc_neurons[1][i]) << " " << threshold_1[i] / 64.0<< endl;
            if(sc.print(fc_neurons[1][i]) < (threshold_1[i] / 64.0)) fc_neurons[1][i] = sc.bit_gen(-1);
            else fc_neurons[1][i] = sc.bit_gen(1);
            
        }
        cout<<"fc2"<<endl;
        fc_neurons[2] = sc.linear(fc_neurons[1], fc_weight[1], sum, 32, 32);
        for(size_t i = 0; i < 32; ++i){
            if(sc.print(fc_neurons[2][i]) < threshold_2[i] / 32.0) fc_neurons[2][i] = sc.bit_gen(-1);
            else fc_neurons[2][i] = sc.bit_gen(1);
        }
        fc_neurons[3] = sc.linear(fc_neurons[2], fc_weight[2], sum, 32, 4);
        for(size_t i = 0; i < 4; ++i){
            fc_neurons[3][0] = sc.MUX(fc_neurons[3][0], sc.bit_gen(threshold_3[0] / 32.0));
            for(size_t j = 1; j < 4; ++j)
            {
                fc_neurons[3][j] = sc.MUX(fc_neurons[3][j], sc.bit_gen(threshold_3[j] / 32.0));
                fc_neurons[3][j] = sc.XNOR(fc_neurons[3][j], sc.bit_gen(-1));
            }
        }

        max = sc.print(fc_neurons[3][0]);
        max_cand = 0;
        for(size_t j = 0; j < 4; ++j)
        {
            // cout << j + 1 << " : " << sc.print(fc_neurons[3][j]) << endl;
            if(sc.print(fc_neurons[3][j]) > max)
            {
                max = sc.print(fc_neurons[3][j]);
                max_cand = j;
            }
        }

        // cout << "label is : " << label << " ;predict is : " << max_cand << endl;
        if(max_cand == label)
        {
            ++correct_count;
            // cout << "correct!!!" << endl;
        }
        // else cout << "wrong!!!" << endl;
        cout << "accuracy = " << (float)correct_count / (i + 1) << endl;
    }


    inputs_txt.close();
    labels_txt.close();
    // cout<<"5"<<endl;
    // conv_neurons[2] = sc.conv2d(conv_neurons[2], conv_weight[2], sum, 16, 128,128,3,1,1);
    // conv_neurons[2] = sc.conv2d(conv_neurons[2], conv_weight[3], sum, 16, 128,128,3,1,1);
    
    
    // conv_neurons[4] = sc.maxpool2d(conv_neurons[2], 16, 128, 2, 2);
    // conv_neurons[4] = sc.conv2d(conv_neurons[4], conv_weight[4], sum, 8, 128,128,3,1,1);
    // conv_neurons[4] = sc.conv2d(conv_neurons[4], conv_weight[5], sum, 8, 128,128,3,1,1);
    
    
    return 0;
}


