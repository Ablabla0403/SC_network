#include <cstring>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
using namespace std;
const int bit_len = 1500000;
struct ESL{  //數字struct，一個存分子一個存分母
    bool *h;
    bool *l;
};

double to_bipolar(int a){
    return 2.0 * a / bit_len - 1;
}

double print(ESL a){
    int answer1 = 0, answer2 = 0;
    for(int i = 0; i< bit_len; i++){
        if (a.h[i] == true){
            answer1 += 1;
        }
        if (a.l[i] == true){
            answer2 += 1;
        }
    }
    return to_bipolar(answer1) / to_bipolar(answer2);
}


bool *bit_gen(double number){
    bool *bit_stream = new bool[bit_len];
    double prob = (number + 1.0) / 2;
    
    for(int i = 0; i< bit_len;i++){
        
        double r = (double)rand() / (RAND_MAX );
        // cout<<r<<endl;
        if(r<prob){
            bit_stream[i] = true;
        }
        else{
            bit_stream[i] = false;
        }
    }
    
    return bit_stream;
}

ESL number_gen(double number, bool *all_one){ //分母先都初始化為一
    ESL output;
    output.h = new bool[bit_len];
    output.l = new bool[bit_len];
    double r = (double)rand() / (RAND_MAX ) / 8.0 + 0.875;
    if(number<=1 && number>=-1){
        // cout<<"generating"<<endl;
        output.h = bit_gen(number*r);
        output.l = bit_gen(r);
    }
    else{
        // cout<<"generating"<<endl;
        output.l = bit_gen(1.0/number * r);
        output.h = bit_gen(r);
    }
    return output;
}



bool *XNOR(bool *a, bool *b){
    bool *XNOR_output = new bool[bit_len];
    int count = 0;
    for(int i = 0; i < bit_len; i++){
        if(a[i] == b[i]){
            XNOR_output[i] = true;
            count ++;
        }
        else{
            XNOR_output[i] = false;
        }
    }
    return bit_gen(to_bipolar(count));
}

ESL APC(ESL a, ESL b){
    ESL output;
    int count1 = 0, count2 = 0, count3 = 0, count4 = 0;
    for(int i = 0 ; i < bit_len ; i++){
        if (a.h[i] == 1){
            count1 ++;
        }
        if (a.l[i] == 1){
            count2 ++;
        }
        if (b.h[i] == 1){
            count3 ++;
        }
        if (b.l[i] == 1){
            count4 ++;
        }
    }
    double h = (to_bipolar(count1)*to_bipolar(count4)+to_bipolar(count3)*to_bipolar(count2));
    double l = to_bipolar(count2)*to_bipolar(count4);
    if (h > 1 || h < -1 || l > 1 || l<-1){
        output.h = bit_gen(h*0.5);
        output.l = bit_gen(l*0.5);
    }else if (h < 0.5 && h > -0.5 && l < 0.5 && l > -0.5)
    {
        output.h = bit_gen(h * 2);
        output.l = bit_gen(l * 2);
    }else
    {
        output.h = bit_gen(h);
        output.l = bit_gen(l);
    }
    
    
    
    return output;
}


bool *MUX(bool *a, bool *b){

    bool *MUX_output = new bool[bit_len];
    for(int i = 0; i < bit_len; i++){
        
        double r = (double)rand() / (RAND_MAX + 1.0);
        if(r > 0.5){
            MUX_output[i] = a[i];
        }
        else{
            MUX_output[i] = b[i];
        }
    }
    return MUX_output;
}

ESL ESL_Multiplier(ESL a, ESL b){
    ESL out;
    out.h = new bool[bit_len];
    out.l = new bool[bit_len];
    out.h = XNOR(a.h,b.h);
    out.l = XNOR(a.l,b.l);
    return out;
}

ESL ESL_Adder(ESL a, ESL b){
    ESL out;
    out.h = new bool[bit_len];
    out.l = new bool[bit_len];
    out.h = MUX(XNOR(a.h,b.l),XNOR(a.l,b.h));
    out.l = MUX(XNOR(a.l,b.l),bit_gen(0));
    
    return out;
}

int main(int argc,char** argv){
    srand(time(NULL));
    cout<<"program in"<<endl;
    bool all_one[bit_len];
    for(int i = 0; i< bit_len; i++){
        all_one[i] = true;
    }
    // cout<<"all_one completed"<<endl;
    ESL w,x,y,z,out1,out2,a;
    // cout<<"ESL item completed"<<endl;
    double answer1 = 0,answer2 = 0;
    x = number_gen(2,all_one);//宣告兩個數字
    y = number_gen(4,all_one);
    z = number_gen(0.6,all_one);
    w = number_gen(3,all_one);
    cout<<"numnber generated"<<endl;
    out1 = APC(x,y);
    // cout<<"multiplied"<<endl;
    out2 = ESL_Multiplier(w,z);
    a = ESL_Multiplier(out1,out2);
    cout<<"added"<<endl;

    cout<<"w = "<<print(w)<<endl;
    cout<<"z = "<<print(z)<<endl;
    cout<<"out2 = "<<print(out2)<<endl;
    
    // answer1 = 0;
    // answer2 = 0;

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
    double layer_0[4];
    double layer_1[20];
    double layer_2[10];
    double layer_3[3];
    float corr_count = 0;
    float max=0,temp=0,max_cand=0;
    for(int k=0;k<30;k++){
        for(int i=0;i<4;i++){
            layer_0[i] = x_test[k][i];
            
        }
            
        for(int i=0;i<20;i++){
            layer_1[i] = 0;
        }
        for(int i=0;i<5;i++){
            layer_2[i] = 0;
        }
        for(int i=0;i<3;i++){
            layer_3[i] = 0;
        }

        for(int i=0;i<20;i++){
            for(int j=0;j<4;j++){
                layer_1[i] += layer_0[j] * weight_1[i][j];
            }
            layer_1[i] += bias_1[i];
        }

        for(int i=0;i<5;i++){
            for(int j=0;j<4;j++){
                layer_2[i] += layer_1[j] * weight_2[i][j];
                answer1 = 0;
                answer2 = 0;
            }
            layer_2[i] += bias_2[i];
        }
        
        for(int i=0;i<3;i++){
            for(int j=0;j<5;j++){
                layer_3[i] += layer_2[j] * weight_3[i][j];
                
            }
            cout<<"layer_3[i] = "<<layer_3[i]<<' '<<"bias_3[i] = "<<bias_3[i]<<endl;
            layer_3[i] += bias_3[i];
            cout<<"i = "<<i<<' '<<layer_3[i]<<endl;
        }
        
        for(int j=0;j<3;j++){
            
            temp = layer_3[j];
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