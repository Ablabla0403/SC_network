#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include "SC.h"
using namespace std;

int main(int argc,char** argv){
    SC sc;
    srand(time(NULL));
    cout<<"program in"<<endl;
    bool all_one[bit_len];
    bool all_zero[bit_len];
    for(int i = 0; i< bit_len; i++){
        all_one[i] = true;
        all_zero[i] = false;
    }

    // ESL w,x,y,z,out1,out2,a;
    // double answer1 = 0,answer2 = 0;
    // x = sc.number_gen(0.3); //error here!!!
    // y = sc.number_gen(0.6);
    // z = sc.number_gen(0.6);
    // w = sc.number_gen(3);
    // cout<<"numnber generated"<<endl;
    // out1 = sc.APC(x,y);
    // out2 = sc.ESL_Multiplier(w,z);
    // a = sc.ESL_Multiplier(out1,out2);

    // cout<<"out1 = "<<sc.print(out1)<<endl;
    double weight_1[10][4] = {{-0.0036, -0.8222,  1.1428,  0.8296},
        { 0.6314,  1.0744, -0.6075, -0.9300},
        {-0.5994,  0.3998, -0.5392, -0.5632},
        {-0.3951, -0.5440,  0.9229,  0.6974},
        { 0.2935, -0.5858,  0.5480,  0.7649},
        {-0.3082,  0.0779, -0.1027,  0.5359},
        {-0.5498, -1.0539,  0.1032,  0.6222},
        { 0.3159,  1.2263, -1.0419, -1.1550},
        { 0.3984,  0.8920, -0.9523, -0.9732},
        {-0.6400, -1.2013,  0.8489,  0.8327}};
    double bias_1[10] = {-0.4965,  0.8319,  0.3620, -1.0174,  0.1545, -0.0132, -0.7016,  0.2359,
         0.0676, -0.8299};
    double weight_2[5][10] = {{-7.9623e-01,  1.1132e+00,  2.6681e-01, -1.1179e+00, -9.5079e-01,
         -1.7036e-01, -6.6915e-01,  5.8790e-01,  1.2805e+00, -1.1847e+00},
        { 7.4836e-01, -7.3824e-01, -4.6857e-01,  7.5429e-01,  4.6071e-01,
         -1.5590e-01,  2.8225e-01, -3.9838e-01, -1.6447e+00,  4.3118e-01},
        {-7.0173e-01,  5.2113e-01,  2.9718e-01, -8.2672e-01, -4.9541e-01,
         -5.4771e-02, -5.2749e-02,  5.4581e-01,  9.2271e-01, -2.8102e-01},
        {-1.9237e-01,  7.9316e-01, -1.8080e-01, -7.0296e-01,  1.7126e-01,
         -2.8067e-01, -6.8195e-01,  5.8475e-01,  8.8074e-01, -8.1795e-01},
        { 4.4365e-01, -7.3126e-01, -5.9054e-01,  8.3146e-01,  7.9397e-01,
          1.4095e-03,  1.6442e-01, -5.3120e-01, -1.2742e+00,  7.2953e-01}};
    double bias_2[5] = {0.2280, -0.2295,  0.1262,  0.3017, -0.0261};
    double weight_3[3][5] = {{ 0.7964, -0.9222,  0.7322,  0.1037, -0.9549},
        { 0.7318, -0.2856,  0.2709,  1.0410, -0.2754},
        {-0.8330,  0.7460, -0.6412, -0.8243,  0.6237}};
    double bias_3[3] =  {0.4752, -0.0459, -0.1071}; 

    

    double x_test[30][4] = {{6.1000, 2.8000, 4.7000, 1.2000},
        {5.7000, 3.8000, 1.7000, 0.3000},
        {7.7000, 2.6000, 6.9000, 2.3000},
        {6.0000, 2.9000, 4.5000, 1.5000},
        {6.8000, 2.8000, 4.8000, 1.4000},
        {5.4000, 3.4000, 1.5000, 0.4000},
        {5.6000, 2.9000, 3.6000, 1.3000},
        {6.9000, 3.1000, 5.1000, 2.3000},
        {6.2000, 2.2000, 4.5000, 1.5000},
        {5.8000, 2.7000, 3.9000, 1.2000},
        {6.5000, 3.2000, 5.1000, 2.0000},
        {4.8000, 3.0000, 1.4000, 0.1000},
        {5.5000, 3.5000, 1.3000, 0.2000},
        {4.9000, 3.1000, 1.5000, 0.1000},
        {5.1000, 3.8000, 1.5000, 0.3000},
        {6.3000, 3.3000, 4.7000, 1.6000},
        {6.5000, 3.0000, 5.8000, 2.2000},
        {5.6000, 2.5000, 3.9000, 1.1000},
        {5.7000, 2.8000, 4.5000, 1.3000},
        {6.4000, 2.8000, 5.6000, 2.2000},
        {4.7000, 3.2000, 1.6000, 0.2000},
        {6.1000, 3.0000, 4.9000, 1.8000},
        {5.0000, 3.4000, 1.6000, 0.4000},
        {6.4000, 2.8000, 5.6000, 2.1000},
        {7.9000, 3.8000, 6.4000, 2.0000},
        {6.7000, 3.0000, 5.2000, 2.3000},
        {6.7000, 2.5000, 5.8000, 1.8000},
        {6.8000, 3.2000, 5.9000, 2.3000},
        {4.8000, 3.0000, 1.4000, 0.3000},
        {4.8000, 3.1000, 1.6000, 0.2000}};
    float corr_answer[30] = {1, 0, 2, 1, 1, 0, 1, 2, 1, 1, 2, 0, 0, 0, 0, 1, 2, 1, 1, 2, 0, 2, 0, 2,
        2, 2, 2, 2, 0, 0};
    
    double train_data[120][4] {{4.6000, 3.6000, 1.0000, 0.2000},
        {5.7000, 4.4000, 1.5000, 0.4000},
        {6.7000, 3.1000, 4.4000, 1.4000},
        {4.8000, 3.4000, 1.6000, 0.2000},
        {4.4000, 3.2000, 1.3000, 0.2000},
        {6.3000, 2.5000, 5.0000, 1.9000},
        {6.4000, 3.2000, 4.5000, 1.5000},
        {5.2000, 3.5000, 1.5000, 0.2000},
        {5.0000, 3.6000, 1.4000, 0.2000},
        {5.2000, 4.1000, 1.5000, 0.1000},
        {5.8000, 2.7000, 5.1000, 1.9000},
        {6.0000, 3.4000, 4.5000, 1.6000},
        {6.7000, 3.1000, 4.7000, 1.5000},
        {5.4000, 3.9000, 1.3000, 0.4000},
        {5.4000, 3.7000, 1.5000, 0.2000},
        {5.5000, 2.4000, 3.7000, 1.0000},
        {6.3000, 2.8000, 5.1000, 1.5000},
        {6.4000, 3.1000, 5.5000, 1.8000},
        {6.6000, 3.0000, 4.4000, 1.4000},
        {7.2000, 3.6000, 6.1000, 2.5000},
        {5.7000, 2.9000, 4.2000, 1.3000},
        {7.6000, 3.0000, 6.6000, 2.1000},
        {5.6000, 3.0000, 4.5000, 1.5000},
        {5.1000, 3.5000, 1.4000, 0.2000},
        {7.7000, 2.8000, 6.7000, 2.0000},
        {5.8000, 2.7000, 4.1000, 1.0000},
        {5.2000, 3.4000, 1.4000, 0.2000},
        {5.0000, 3.5000, 1.3000, 0.3000},
        {5.1000, 3.8000, 1.9000, 0.4000},
        {5.0000, 2.0000, 3.5000, 1.0000},
        {6.3000, 2.7000, 4.9000, 1.8000},
        {4.8000, 3.4000, 1.9000, 0.2000},
        {5.0000, 3.0000, 1.6000, 0.2000},
        {5.1000, 3.3000, 1.7000, 0.5000},
        {5.6000, 2.7000, 4.2000, 1.3000},
        {5.1000, 3.4000, 1.5000, 0.2000},
        {5.7000, 3.0000, 4.2000, 1.2000},
        {7.7000, 3.8000, 6.7000, 2.2000},
        {4.6000, 3.2000, 1.4000, 0.2000},
        {6.2000, 2.9000, 4.3000, 1.3000},
        {5.7000, 2.5000, 5.0000, 2.0000},
        {5.5000, 4.2000, 1.4000, 0.2000},
        {6.0000, 3.0000, 4.8000, 1.8000},
        {5.8000, 2.7000, 5.1000, 1.9000},
        {6.0000, 2.2000, 4.0000, 1.0000},
        {5.4000, 3.0000, 4.5000, 1.5000},
        {6.2000, 3.4000, 5.4000, 2.3000},
        {5.5000, 2.3000, 4.0000, 1.3000},
        {5.4000, 3.9000, 1.7000, 0.4000},
        {5.0000, 2.3000, 3.3000, 1.0000},
        {6.4000, 2.7000, 5.3000, 1.9000},
        {5.0000, 3.3000, 1.4000, 0.2000},
        {5.0000, 3.2000, 1.2000, 0.2000},
        {5.5000, 2.4000, 3.8000, 1.1000},
        {6.7000, 3.0000, 5.0000, 1.7000},
        {4.9000, 3.1000, 1.5000, 0.2000},
        {5.8000, 2.8000, 5.1000, 2.4000},
        {5.0000, 3.4000, 1.5000, 0.2000},
        {5.0000, 3.5000, 1.6000, 0.6000},
        {5.9000, 3.2000, 4.8000, 1.8000},
        {5.1000, 2.5000, 3.0000, 1.1000},
        {6.9000, 3.2000, 5.7000, 2.3000},
        {6.0000, 2.7000, 5.1000, 1.6000},
        {6.1000, 2.6000, 5.6000, 1.4000},
        {7.7000, 3.0000, 6.1000, 2.3000},
        {5.5000, 2.5000, 4.0000, 1.3000},
        {4.4000, 2.9000, 1.4000, 0.2000},
        {4.3000, 3.0000, 1.1000, 0.1000},
        {6.0000, 2.2000, 5.0000, 1.5000},
        {7.2000, 3.2000, 6.0000, 1.8000},
        {4.6000, 3.1000, 1.5000, 0.2000},
        {5.1000, 3.5000, 1.4000, 0.3000},
        {4.4000, 3.0000, 1.3000, 0.2000},
        {6.3000, 2.5000, 4.9000, 1.5000},
        {6.3000, 3.4000, 5.6000, 2.4000},
        {4.6000, 3.4000, 1.4000, 0.3000},
        {6.8000, 3.0000, 5.5000, 2.1000},
        {6.3000, 3.3000, 6.0000, 2.5000},
        {4.7000, 3.2000, 1.3000, 0.2000},
        {6.1000, 2.9000, 4.7000, 1.4000},
        {6.5000, 2.8000, 4.6000, 1.5000},
        {6.2000, 2.8000, 4.8000, 1.8000},
        {7.0000, 3.2000, 4.7000, 1.4000},
        {6.4000, 3.2000, 5.3000, 2.3000},
        {5.1000, 3.8000, 1.6000, 0.2000},
        {6.9000, 3.1000, 5.4000, 2.1000},
        {5.9000, 3.0000, 4.2000, 1.5000},
        {6.5000, 3.0000, 5.2000, 2.0000},
        {5.7000, 2.6000, 3.5000, 1.0000},
        {5.2000, 2.7000, 3.9000, 1.4000},
        {6.1000, 3.0000, 4.6000, 1.4000},
        {4.5000, 2.3000, 1.3000, 0.3000},
        {6.6000, 2.9000, 4.6000, 1.3000},
        {5.5000, 2.6000, 4.4000, 1.2000},
        {5.3000, 3.7000, 1.5000, 0.2000},
        {5.6000, 3.0000, 4.1000, 1.3000},
        {7.3000, 2.9000, 6.3000, 1.8000},
        {6.7000, 3.3000, 5.7000, 2.1000},
        {5.1000, 3.7000, 1.5000, 0.4000},
        {4.9000, 2.4000, 3.3000, 1.0000},
        {6.7000, 3.3000, 5.7000, 2.5000},
        {7.2000, 3.0000, 5.8000, 1.6000},
        {4.9000, 3.6000, 1.4000, 0.1000},
        {6.7000, 3.1000, 5.6000, 2.4000},
        {4.9000, 3.0000, 1.4000, 0.2000},
        {6.9000, 3.1000, 4.9000, 1.5000},
        {7.4000, 2.8000, 6.1000, 1.9000},
        {6.3000, 2.9000, 5.6000, 1.8000},
        {5.7000, 2.8000, 4.1000, 1.3000},
        {6.5000, 3.0000, 5.5000, 1.8000},
        {6.3000, 2.3000, 4.4000, 1.3000},
        {6.4000, 2.9000, 4.3000, 1.3000},
        {5.6000, 2.8000, 4.9000, 2.0000},
        {5.9000, 3.0000, 5.1000, 1.8000},
        {5.4000, 3.4000, 1.7000, 0.2000},
        {6.1000, 2.8000, 4.0000, 1.3000},
        {4.9000, 2.5000, 4.5000, 1.7000},
        {5.8000, 4.0000, 1.2000, 0.2000},
        {5.8000, 2.6000, 4.0000, 1.2000},
        {7.1000, 3.0000, 5.9000, 2.1000}};


int train_label[120] = {
  0 ,0, 1, 0, 0, 2, 1, 0, 0, 0, 2, 1, 1, 0, 0, 1, 2, 2, 1, 2, 1, 2, 1, 0, 2, 1, 0, 0, 0, 1, 2, 0, 0, 0, 1, 0, 1,
 2, 0, 1, 2, 0, 2, 2, 1, 1, 2, 1, 0, 1, 2, 0, 0, 1, 1, 0, 2, 0, 0, 1, 1, 2, 1, 2, 2, 1, 0, 0, 2, 2, 0, 0, 0, 1,
 2, 0, 2, 2, 0, 1, 1, 2, 1, 2, 0, 2, 1, 2, 1, 1, 1, 0, 1, 1, 0, 1, 2, 2, 0, 1, 2, 2, 0, 2, 0, 1, 2, 2, 1, 2, 1,
 1, 2, 2, 0, 1, 2, 0, 1, 2
};
        
    ESL layer_0[4];
    for(size_t i=0; i<4; i++){
        layer_0[i] = sc.number_gen(0);
    } 
    ESL layer_1[10];
    for(size_t i=0; i<10; i++){
        layer_1[i] = sc.number_gen(0);
    } 
    // bool* layer_1_1[10];
    // for(size_t i=0; i<10; i++){
    //     layer_1_1[i] = new bool[bit_len];
    // } 
    ESL layer_2[5];
    for(size_t i=0; i<5; i++){
        layer_2[i] = sc.number_gen(0);
    } 
    ESL layer_3[3];
    for(size_t i=0; i<3; i++){
        layer_3[i] = sc.number_gen(0);
    } 

    float corr_count = 0;
    float max=0,temp=0,max_cand=0;
    sc.NEW_APC(layer_0[0],layer_1[0]);

for(int k=0;k<50;k++){
    cout << "forward processing!" << k << "th epoch" << endl;
        for(int i=0; i<4; i++){
            layer_0[i] = sc.number_gen(train_data[k][i]);
        }
            

        for(int i=0;i<10;i++){
            for(int j=0;j<4;j++){
                layer_1[i] = sc.NEW_APC(layer_1[i] ,sc.ESL_Multiplier(layer_0[j],sc.number_gen(weight_1[i][j])));
            }
            sc.APC(layer_1[i],sc.number_gen(bias_1[i]));
            // if (sc.print(layer_1[i]) > 1){
            //     layer_1_1[i] = all_one;
            // }
            // else if(sc.print(layer_1[i]) < -1){
            //     layer_1_1[i] = all_zero;
            // }
            // else{
            //     layer_1_1[i] = sc.bit_gen(sc.print(layer_1[i]));
            // }
            // layer_1_1[i] = sc.ReLU(layer_1_1[i]);
            
        }


    
        for(int i=0;i<5;i++){
            for(int j=0;j<10;j++){
                layer_2[i] = sc.APC(sc.ESL_Multiplier(layer_1[j],layer_2[i]),layer_2[i]);
            }
            // layer_2[i] = sc.APC(layer_2[i],sc.bit_gen(bias_2[i]));
        }
        
        for(int i=0; i<3; i++){
            for(int j=0;j<5;j++){
                layer_3[i] = sc.APC(layer_3[i] ,sc.ESL_Multiplier(layer_2[j],sc.number_gen(weight_3[i][j])));
            }   
            // layer_3[i] = sc.APC(layer_3[i],sc.bit_gen(bias_3[i]));    
        }
        int answer1;
        for(int j=0; j<3; j++){
            answer1 = 0;
            cout << "the " << k << "'th training" << j << "th output is: " << sc.print(layer_3[j]) << endl;
            
        }
        cout << "backward processing!" << k << "th training data" << endl;
        ESL deltas_1[10],deltas_2[10];
        ESL delta_w,tmp;
        for (size_t i = 0; i < 3; i++){
            deltas_1[i] = sc.ESL_Multiplier(sc.APC(sc.number_gen(train_label[k]) ,sc.ESL_Multiplier(sc.number_gen(-1),layer_3[i])),layer_3[i]);
            for (size_t j = 0; j < 5; j++){
                delta_w = sc.ESL_Multiplier(deltas_1[i],layer_2[j]);
                weight_3[i][j] += lr * sc.print(delta_w);
            }
        }
        for (size_t i = 0; i < 5; i++){
            tmp = sc.number_gen(0);
            for (size_t j = 0; j < 3; j++){
                sc.APC(tmp, sc.ESL_Multiplier(deltas_1[j],sc.number_gen(weight_3[j][i])));
            }
            deltas_2[i] = sc.ESL_Multiplier(layer_2[i], tmp);
            for (size_t j = 0; j < 10; j++){
                delta_w = sc.ESL_Multiplier(deltas_2[i],layer_2[j]);
                weight_2[i][j] += lr * sc.print(delta_w);
            }
        }
        for (size_t i = 0; i < 5; i++){
            tmp = sc.number_gen(0);
            for (size_t j = 0; j < 3; j++){
                sc.APC(tmp, sc.ESL_Multiplier(deltas_1[j],sc.number_gen(weight_3[j][i])));
            }
            deltas_2[i] = sc.ESL_Multiplier(layer_2[i], tmp);
            for (size_t j = 0; j < 10; j++){
                delta_w = sc.ESL_Multiplier(deltas_2[i],layer_2[j]);
                weight_2[i][j] += lr * sc.print(delta_w);
            }
        }

        for (size_t i = 0; i < 10; i++){
            tmp = sc.number_gen(0);
            for (size_t j = 0; j < 5; j++){
                sc.APC(tmp, sc.ESL_Multiplier(deltas_2[j],sc.number_gen(weight_2[j][i])));
            }
            deltas_1[i] = sc.ESL_Multiplier(layer_1[i], tmp);
            for (size_t j = 0; j < 4; j++){
                delta_w = sc.ESL_Multiplier(deltas_1[i],layer_1[j]);
                weight_1[i][j] += lr * sc.print(delta_w);
            }
        }
    }
    
    cout << "training finished" << endl;

    for(int k=0;k<30;k++){
        for(int i=0;i<4;i++){
            layer_0[i] = sc.number_gen(x_test[k][i]);
        }
            
        for(int i=0;i<10;i++){
            layer_1[i] = sc.number_gen(0);
        }
        for(int i=0;i<5;i++){
            layer_2[i] = sc.number_gen(0);
        }
        for(int i=0;i<3;i++){
            layer_3[i] = sc.number_gen(0);
        }

        for(int i=0;i<10;i++){
            for(int j=0;j<4;j++){
                layer_1[i] = sc.APC(layer_1[i] ,sc.ESL_Multiplier(layer_0[j],sc.number_gen(weight_1[i][j])));
            }
            sc.APC(layer_1[i],sc.number_gen(bias_1[i]));
        }
    
        for(int i=0;i<5;i++){
            for(int j=0;j<10;j++){
                layer_2[i] = sc.APC(layer_2[i] ,sc.ESL_Multiplier(layer_1[j],sc.number_gen(weight_2[i][j])));
            }
            layer_2[i] = sc.APC(layer_2[i],sc.number_gen(bias_2[i]));
            cout<<"layer2 i = "<<i<<' '<<sc.print(layer_2[i])<<endl;
        }
        
        for(int i=0;i<3;i++){
            for(int j=0;j<5;j++){
                layer_3[i] = sc.APC(layer_3[i] ,sc.ESL_Multiplier(layer_2[j],sc.number_gen(weight_3[i][j])));

            }
            
            layer_3[i] = sc.APC(layer_3[i],sc.number_gen(bias_3[i]));
            
        }
        for(int j=0;j<3;j++){
            size_t answer1 = 0;
            size_t answer2 = 0;
            for(int i = 0; i< bit_len; i++){
                if (layer_3[j].h[i] == true){
                    answer1 += 1;
                }
                if (layer_3[j].l[i] == true){
                    answer2 += 1;
                }
            }
            temp = (2*answer1/bit_len - 1)/(2*answer2/bit_len - 1);
            cout<<temp<<endl;
            if(j==0){
                max = temp;
                max_cand = 0;
            }
            else{
                if(temp > max){
                    max = temp;
                    max_cand = j;
                }
            }

        }
        cout<<max_cand<<endl;
        if(max_cand == corr_answer[k]){
            corr_count += 1;
            cout<<"correct!!!!!("<<corr_count<<'/'<<k+1<<')'<<endl;
        }
        else{
            cout<<"wrong!!!!!("<<corr_count<<'/'<<k+1<<')'<<endl;
        }

    }
    
    cout<<"The rate of correctness is: "<<corr_count/30.0<<endl;
    return 0;
}
//     for(int k=0;k<30;k++){
//         for(int i=0;i<4;i++){
//             layer_0[i] = sc.number_gen(x_test[k][i],all_one);
//         }
            
//         for(int i=0;i<10;i++){
//             layer_1[i] = sc.number_gen(0,all_one);
//         }
//         for(int i=0;i<5;i++){
//             layer_2[i] = sc.number_gen(0,all_one);
//         }
//         for(int i=0;i<3;i++){
//             layer_3[i] = sc.number_gen(0,all_one);
//         }

//         for(int i=0;i<10;i++){
//             for(int j=0;j<4;j++){
//                 layer_1[i] = sc.APC(layer_1[i] ,sc.ESL_Multiplier(layer_0[j],sc.number_gen(weight_1[i][j],all_one)));
//             }
//             sc.APC(layer_1[i],sc.number_gen(bias_1[i],all_one));
//         }
    
//         for(int i=0;i<5;i++){
//             for(int j=0;j<10;j++){
//                 layer_2[i] = sc.APC(layer_2[i] ,sc.ESL_Multiplier(layer_1[j],sc.number_gen(weight_2[i][j],all_one)));
//             }
//             layer_2[i] = sc.APC(layer_2[i],sc.number_gen(bias_2[i],all_one));
//             cout<<"layer2 i = "<<i<<' '<<sc.print(layer_2[i])<<endl;
//         }
        
//         for(int i=0;i<3;i++){
//             for(int j=0;j<5;j++){
//                 layer_3[i] = sc.APC(layer_3[i] ,sc.ESL_Multiplier(layer_2[j],sc.number_gen(weight_3[i][j],all_one)));

//             }
            
//             layer_3[i] = sc.APC(layer_3[i],sc.number_gen(bias_3[i],all_one));
            
//         }
//         for(int j=0;j<3;j++){
//             answer1 = 0;
//             answer2 = 0;
//             for(int i = 0; i< bit_len; i++){
//                 if (layer_3[j].h[i] == true){
//                     answer1 += 1;
//                 }
//                 if (layer_3[j].l[i] == true){
//                     answer2 += 1;
//                 }
//             }
//             temp = (2*answer1/bit_len - 1)/(2*answer2/bit_len - 1);
//             cout<<temp<<endl;
//             if(j==0){
//                 max = temp;
//                 max_cand = 0;
//             }
//             else{
//                 if(temp > max){
//                     max = temp;
//                     max_cand = j;
//                 }
//             }

//         }
//         cout<<max_cand<<endl;
//         if(max_cand == corr_answer[k]){
//             corr_count += 1;
//             cout<<"correct!!!!!("<<corr_count<<'/'<<k+1<<')'<<endl;
//         }
//         else{
//             cout<<"wrong!!!!!("<<corr_count<<'/'<<k+1<<')'<<endl;
//         }

//     }
    
//     cout<<"The rate of correctness is: "<<corr_count/30.0<<endl;
