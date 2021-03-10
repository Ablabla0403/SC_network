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
    
    double weight_1[10][4] = {{1e-05, 1e-05,  1e-05,  1e-05},
        { 1e-05,  0.00744, -0.00075, -0.00020},
        {1e-05,  0.00098, -0.00092, -0.00032},
        {1e-05, -0.00440,  0.00029,  0.00074},
        { 1e-05, 1e-05,  0.00480,  0.00049},
        {1e-05,  1e-05, -0.00027,  0.00059},
        {1e-05, 1e-05,  0.00032,  0.00022},
        { 1e-05,  1e-05, -0.00419, -0.00050},
        { 1e-05,  1e-05, -0.00523, -0.00032},
        {1e-05, 1e-05,  0.00489,  0.00327}};
    for (int i = 0; i < 10; i++){
        for (int j = 0; j < 4; j++){
            weight_1[i][j] = 1e-5;
        }
    }
    double bias_1[10] = {-0.00965,  0.00319,  0.00620, -0.00174,  0.00545, -0.00132, -0.00016,  0.00359,
         0.00676, -0.00299};
    double weight_2[5][10] = {{-7.9623e-04,  1.1132e-04,  2.6681e-04, -1.1179e-04, -9.5079e-04,
         -1.7036e-04, -6.6915e-04,  5.8790e-04,  1.2805e-04, -1.1847e-04},
        { 7.4836e-04, -7.3824e-04, -4.6857e-04,  7.5429e-04,  4.6071e-04,
         -1.5590e-04,  2.8225e-04, -3.9838e-04, -1.6447e-04,  4.3118e-04},
        {-7.0173e-04,  5.2113e-04,  2.9718e-04, -8.2672e-04, -4.9541e-04,
         -5.4771e-04, -5.2749e-04,  5.4581e-04,  9.2271e-04, -2.8102e-04},
        {-1.9237e-04,  7.9316e-04, -1.8080e-04, -7.0296e-04,  1.7126e-04,
         -2.8067e-04, -6.8195e-04,  5.8475e-04,  8.8074e-04, -8.1795e-04},
        { 4.4365e-04, -7.3126e-04, -5.9054e-04,  8.3146e-04,  7.9397e-04,
          1.4095e-04,  1.6442e-04, -5.3120e-04, -1.2742e-04,  7.2953e-04}};
    for (int i = 0; i < 5; i++){
        for (int j = 0; j < 10; j++){
            weight_1[i][j] = 1e-5;
        }
    }
    double bias_2[5] = {0.00280, -0.00295,  0.00262,  0.00017, -0.00261};
    double weight_3[3][5] = {{ 0.00964, -0.00222,  0.00322,  0.00037, -0.00549},
        { 0.00318, -0.00856,  0.00709,  0.00410, -0.00054},
        {-0.00330,  0.00460, -0.00412, -0.00243,  0.00237}};
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 5; j++){
            weight_1[i][j] = 1e-5;
        }
    }
    double bias_3[3] =  {0.00752, -0.00459, -0.00071}; 

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
    bool* layer_1_1[10];
    for(size_t i=0; i<10; i++){
        layer_1_1[i] = new bool[bit_len];
    } 
    bool* layer_2[5];
    for(size_t i=0; i<5; i++){
        layer_2[i] = new bool[bit_len];
    } 
    bool* layer_3[3];
    for(size_t i=0; i<3; i++){
        layer_3[i] = new bool[bit_len];
    } 

    float corr_count = 0;
    float max=0,temp=0,max_cand=0;
    sc.APC(layer_0[0],layer_1[0]);

for(int k=0;k<120;k++){
    cout << "forward processing!" << k << "th epoch" << endl;
        for(int i=0; i<4; i++){
            layer_0[i] = sc.number_gen(train_data[k][i]);
        }
            

        for(int i=0;i<10;i++){
            for(int j=0;j<4;j++){
                layer_1[i] = sc.APC(layer_1[i] ,sc.ESL_Multiplier(layer_0[j],sc.number_gen(weight_1[i][j])));
            }
            sc.APC(layer_1[i],sc.number_gen(bias_1[i]));
            if (sc.print(layer_1[i]) > 1){
                layer_1_1[i] = all_one;
            }
            else if(sc.print(layer_1[i]) < -1){
                layer_1_1[i] = all_zero;
            }
            else{
                layer_1_1[i] = sc.bit_gen(sc.print(layer_1[i]));
            }
            // layer_1_1[i] = sc.ReLU(layer_1_1[i]);
            
        }


    
        for(int i=0;i<5;i++){
            for(int j=0;j<10;j++){
                layer_2[i] = sc.APC(sc.XNOR(layer_1_1[j],layer_2[i]),layer_2[i]);
            }
            // layer_2[i] = sc.APC(layer_2[i],sc.bit_gen(bias_2[i]));
        }
        
        for(int i=0; i<3; i++){
            for(int j=0;j<5;j++){
                layer_3[i] = sc.APC(layer_3[i] ,sc.XNOR(layer_2[j],sc.bit_gen(weight_3[i][j])));
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
            deltas_1[i] = sc.ESL_Multiplier(sc.APC(sc.number_gen(train_label[k]) ,sc.ESL_Multiplier(sc.number_gen(-1),sc.ToESL(layer_3[i]))),sc.ReLU_grad(sc.ToESL(layer_3[i])));
            for (size_t j = 0; j < 5; j++){
                delta_w = sc.ESL_Multiplier(deltas_1[i],sc.ToESL(layer_2[j]));
                weight_3[i][j] += lr * sc.print(delta_w);
            }
        }
        for (size_t i = 0; i < 5; i++){
            tmp = sc.number_gen(0);
            for (size_t j = 0; j < 3; j++){
                sc.APC(tmp, sc.ESL_Multiplier(deltas_1[j],sc.number_gen(weight_3[j][i])));
            }
            deltas_2[i] = sc.ESL_Multiplier(sc.ReLU_grad(sc.ToESL(layer_2[i])), tmp);
            for (size_t j = 0; j < 10; j++){
                delta_w = sc.ESL_Multiplier(deltas_2[i],sc.ToESL(layer_2[j]));
                weight_2[i][j] += lr * sc.print(delta_w);
            }
        }
        for (size_t i = 0; i < 5; i++){
            tmp = sc.number_gen(0);
            for (size_t j = 0; j < 3; j++){
                sc.APC(tmp, sc.ESL_Multiplier(deltas_1[j],sc.number_gen(weight_3[j][i])));
            }
            deltas_2[i] = sc.ESL_Multiplier(sc.ReLU_grad(sc.ToESL(layer_2[i])), tmp);
            for (size_t j = 0; j < 10; j++){
                delta_w = sc.ESL_Multiplier(deltas_2[i],sc.ToESL(layer_2[j]));
                weight_2[i][j] += lr * sc.print(delta_w);
            }
        }

        for (size_t i = 0; i < 10; i++){
            tmp = sc.number_gen(0);
            for (size_t j = 0; j < 5; j++){
                sc.APC(tmp, sc.ESL_Multiplier(deltas_2[j],sc.number_gen(weight_2[j][i])));
            }
            deltas_1[i] = sc.ESL_Multiplier(sc.ReLU_grad(sc.ToESL(layer_1_1[i])), tmp);
            for (size_t j = 0; j < 4; j++){
                delta_w = sc.ESL_Multiplier(deltas_1[i],sc.ToESL(layer_1_1[j]));
                weight_1[i][j] += lr * sc.print(delta_w);
            }
        }
    }
    
    cout << "training finished" << endl;
    return 0;
}
//     for(int k=0;k<30;k++){
//         for(int i=0;i<4;i++){
//             layer_0[i] = sc.number_gen(x_test[k][i]);
//         }
            
//         for(int i=0;i<10;i++){
//             layer_1[i] = sc.number_gen(0);
//         }
//         for(int i=0;i<5;i++){
//             layer_2[i] = sc.number_gen(0);
//         }
//         for(int i=0;i<3;i++){
//             layer_3[i] = sc.number_gen(0);
//         }

//         for(int i=0;i<10;i++){
//             for(int j=0;j<4;j++){
//                 layer_1[i] = sc.APC(layer_1[i] ,sc.ESL_Multiplier(layer_0[j],sc.number_gen(weight_1[i][j])));
//             }
//             sc.APC(layer_1[i],sc.number_gen(bias_1[i]));
//         }
    
//         for(int i=0;i<5;i++){
//             for(int j=0;j<10;j++){
//                 layer_2[i] = sc.APC(layer_2[i] ,sc.ESL_Multiplier(layer_1[j],sc.number_gen(weight_2[i][j])));
//             }
//             layer_2[i] = sc.APC(layer_2[i],sc.number_gen(bias_2[i]));
//             cout<<"layer2 i = "<<i<<' '<<sc.print(layer_2[i])<<endl;
//         }
        
//         for(int i=0;i<3;i++){
//             for(int j=0;j<5;j++){
//                 layer_3[i] = sc.APC(layer_3[i] ,sc.ESL_Multiplier(layer_2[j],sc.number_gen(weight_3[i][j])));

//             }
            
//             layer_3[i] = sc.APC(layer_3[i],sc.number_gen(bias_3[i]));
            
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
//     return 0;
// }