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
    

    float threshold_1[32] = {-0.09311132878065109, 0.01636984385550022, -1.1601179838180542, 1.0464071035385132, 1.1822867393493652, 1.316198706626892, -1.2384259700775146, 0.054702743887901306, -1.2490497827529907, -0.10826772451400757, 1.7383816242218018, 0.6806756258010864, 1.1886515617370605, -0.22215022146701813, -0.8769798278808594, 1.1012130975723267, 0.033998724073171616, 0.8128331899642944, -1.1804205179214478, -0.9115725755691528, -1.2905209064483643, -1.12577486038208, 0.009792732074856758, 0.05692753940820694, -1.2547390460968018, -0.8481188416481018, -1.2712393999099731, -0.9360234141349792, -1.1812881231307983, -1.2658339738845825, 1.3013828992843628, -0.6552966833114624};
    float threshold_2[32] = {-14.466394424438477, 7.169124126434326, 7.6124796867370605, -3.422462224960327, -12.81364631652832, 1.0367259979248047, -15.309078216552734, 0.8173356056213379, -13.388500213623047, -2.8168959617614746, -74.9836196899414, -19.821491241455078, -5.46647310256958, 1.3305840492248535, -19.099411010742188, 14.628715515136719, -5.3909592628479, -7.210825443267822, 15.642261505126953, 10.365299224853516, 0.6903009414672852, -10.747349739074707, -0.7748885154724121, 16.652774810791016, 45.145320892333984, -19.49041175842285, 15.762331008911133, 0.4253697395324707, 4.442461967468262, -12.98421859741211, 3.720792293548584, 17.38399314880371};
    float threshold_3[4] = {-2.493149518966675, -7.356795787811279, -7.115196228027344, -2.823887348175049};

    
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
            if(sc.print(fc_neurons[1][i]) < (threshold_1[i] / 64.0)) fc_neurons[1][i] = sc.bit_gen(-1);
            else fc_neurons[1][i] = sc.bit_gen(1);
            cout << sc.print(fc_neurons[1][i]) << endl;
            
        }
        cout<<"fc2"<<endl;
        fc_neurons[2] = sc.linear(fc_neurons[1], fc_weight[1], sum, 32, 32);
        for(size_t i = 0; i < 32; ++i){
            if(sc.print(fc_neurons[2][i]) < threshold_2[i] / 32.0) fc_neurons[2][i] = sc.bit_gen(-1);
            else fc_neurons[2][i] = sc.bit_gen(1);
            // cout << sc.print(fc_neurons[2][i]) << endl;
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

        cout << "label is : " << label << " ;predict is : " << max_cand << endl;
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


