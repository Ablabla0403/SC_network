
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include "SC.h"
#include "definition.h"
using namespace std;



double SC::to_bipolar(int a){
    return 2.0 * a / bit_len - 1;
}

double SC::print(ESL a){
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

double SC::print(bool* a){
    int count = 0;
    for (size_t i = 0; i < bit_len; i++){
        if (a[i] == true){
            count ++;
        }
    }
    return to_bipolar(count);
    
}


bool* SC::bit_gen(double number){
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

ESL SC::number_gen(double number){ //分母先都初始化為一
    ESL output;
    output.h = new bool[bit_len];
    output.l = new bool[bit_len];
    double r = 1.0;
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



bool* SC::XNOR(bool* a, bool* b){
    bool* XNOR_output = new bool[bit_len];
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
    return XNOR_output;
}

bool* SC::XNOR_4(bool* a, bool* b,bool* c, bool* d){
    bool* XNOR_output = new bool[bit_len];
    int count = 0;
    for(int i = 0; i < bit_len; i++){
        if(a[i] == b[i] == c[i] == d[i]){
            XNOR_output[i] = true;
            count ++;
        }
        else{
            XNOR_output[i] = false;
        }
    }
    return XNOR_output;
}

bool* SC::XNOR_5(bool* a, bool* b, bool* c, bool*d,bool* e){
    bool* XNOR_output = new bool[bit_len];
    int count = 0;
    for(int i = 0; i < bit_len; i++){
        if(a[i] == b[i] == c[i] == d[i] == e[i]){
            XNOR_output[i] = true;
            count ++;
        }
        else{
            XNOR_output[i] = false;
        }
    }
    return XNOR_output;
}

bool* SC::APC(bool* a, bool* b){
    int count = 0;
    for(size_t i=0; i<bit_len; i++){
        if(a[i] == true){
            count ++;
        }
        else if(b[i] == true){
            count ++;
        }
    }
    if(count > bit_len){
        count = bit_len;
    }
    return bit_gen(to_bipolar(count));
}

ESL SC::APC(ESL a, ESL b){
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

    //TODO : reconstruct APC and study APC in the paper
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

ESL SC::NEW_APC(bool* a, bool* b){
    ESL output;
    bool* h = new bool[bit_len];
    bool* l = bit_gen(0.5);
    int counter;
    int count = 0;
    for(int i=0; i<bit_len; i++){
        if(i % 2 == 0){
            if(a[i] == true && b[i] == true){
                h[i] = true;
                count++;
            }
            else{
                h[i] = false;
            }
        }
        else{
            if(a[i] == false && b[i] == false){
                h[i] = false;
            }
            else{
                h[i] = true;
                count++;
            }
        }
    }
    output.h = h;
    output.l = l;

    return output;  
}

bool* SC::NEW_APC_B(bool* a, bool* b){
    bool* h = new bool[bit_len];
    int counter;
    int count = 0;
    for(int i=0; i<bit_len; i++){
        if(i % 2 == 0){
            if(a[i] == true && b[i] == true){
                h[i] = true;
                count++;
            }
            else{
                h[i] = false;
            }
        }
        else{
            if(a[i] == false && b[i] == false){
                h[i] = false;
            }
            else{
                h[i] = true;
                count++;
            }
        }
    }

    return bit_gen(print(h)*2);  
}

ESL SC::NEW_APC(ESL a, ESL b){
    ESL output;
    output.l = XNOR(XNOR(a.l, b.l), bit_gen(0.5));
    output.h = NEW_APC(XNOR(a.h, b.l), XNOR(a.l, b.h)).h;
}

bool* SC::MUX(bool* a, bool* b){

    bool *MUX_output = new bool[bit_len];
    for(size_t i = 0; i < bit_len; i++){
        
        double r = (double)rand() / (RAND_MAX + 1.0);
        if(r > 0.5){
            MUX_output[i] = a[i];
        }
        else{
            MUX_output[i] = b[i];
        }
        
    }
    if(print(MUX_output)*2 > 1){
        MUX_output = bit_gen(1);
    }
    else{
        MUX_output = bit_gen(print(MUX_output)*2);
    }
    return MUX_output;
}




// ESL SC::ESL_Adder(ESL a, ESL b){
//     ESL out;
//     out.h = new bool[bit_len];
//     out.l = new bool[bit_len];
//     out.h = MUX(XNOR(a.h,b.l),XNOR(a.l,b.h));
//     out.l = MUX(XNOR(a.l,b.l),bit_gen(0));
    
//     return out;
// }

bool* SC::ReLU(bool* a){
    bool* out = new bool[bit_len];
    double r ;
    int counter = 0;
    for (int i = 0; i < bit_len; i++){
        r = (double)rand() / (RAND_MAX );
        if (a[i] == 1){
            counter ++;
        }
        else{
            counter --;
        }
        if (counter >= 0){
            out[i] = a[i];
        }
        else{
            if (r > 0.5){
                out[i] = 1;
            }
            else{
                out[i] = 0;
            }
        }
    }
    return out;
}

ESL SC::ReLU_grad(ESL a){
    if (print(a) < 0){
        return number_gen(0);
    }
    else{
        return number_gen(1);
    }
}

bool* SC::ReLU_grad(bool* a){
    if (print(a) < 0){
        return bit_gen(0);
    }
    else{
        return bit_gen(1);
    }
}

ESL SC::ToESL(bool* a){
    ESL output;
    output.h = a;
    output.l = bit_gen(1);
    return output;
}
// ESL SC::ReLU(ESL a){
//     ESL out;
//     bool* out_l = bit_gen(1);
//     bool* out_h = new bool[bit_len];
//     double r = (double)rand() / (RAND_MAX );
//     int counter = 0;
//     for (int i = 0; i < bit_len; i++){
//         if (a.h[i] == 1){
//             counter ++;
//         }
//         else{
//             counter --;
//         }
//         if (counter >= 0){
//             out_h[i] = a.h[i];
//         }
//         else{
//             if (r > 0.5){
//                 out_h[i] = 1;
//             }
//             else{
//                 out_h[i] = 0;
//             }
//         }
//     }
//     out.h = out_h;
//     out.l = out_l;
//     return out;
// }

bool* SC::MUX_general(vector<bool*> &bit_streams){
    bool* output = new bool[bit_len];
    float r;
    for(int i = 0; i < bit_len; ++i){
        r = int((float)rand() / (RAND_MAX) * (float)bit_streams.size()) % bit_streams.size();
        output[i] = bit_streams[r][i];
    }
    return output;
}

//added by YEN-JU, construct conv2d for bipolar SC
bool**** SC::conv2d(bool**** input, bool**** filter,vector<bool*> &vec, short img_size, short in_channels, short out_channels, short kernel_size, short stride, short padding){
    vec.clear();
    //declare a 3D array(out_channel * img_size * img_size) for the output tensor
    bool**** output = new bool***[out_channels];
    for(unsigned i = 0; i < out_channels; i++){ 
        output[i] = new bool**[img_size + 2 * padding];
        for( unsigned j = 0; j < img_size + 2; j++){ 
            output[i][j] = new bool*[img_size + 2 * padding];
            for(unsigned k = 0; k < img_size + 2; k++){
                output[i][j][k] = new bool[bit_len];
                output[i][j][k] = bit_gen(0);
            }
        }
    }

    //compute output channels
    for(unsigned i = 0; i < out_channels; i++){
        for(unsigned j = 0; j < img_size; j++){
            for(unsigned k = 0; k < img_size; k++){
                vec.clear();
                for(unsigned m = 0; m < kernel_size; m++){
                    for(unsigned n = 0; n < kernel_size; n++){
                        for(unsigned t = 0; t < in_channels; t++){
                            // cout<<i<<" "<<j<<" "<<k<<" "<<m<<" "<<n<<" "<<t<<endl;
                            vec.push_back(XNOR(input[t][j + m][k + n],bit_gen(filter[t][i][m][n])));
                            // cout<<i<<" "<<j<<" "<<k<<" "<<m<<" "<<n<<" "<<t<<endl;
                        }
                    }
                }
                // cout<<i<<j<<k<<endl;
                output[i][j + padding][k + padding] = MUX_general(vec);
                // cout<<i<<j<<k<<endl;
            }
        }
    }
    return output;
}

//added by yen_ju for fully connected layers
bool** SC::linear(bool** input, bool** weight, vector<bool*> & vec, bool* bias, short in, short out){
    //new the output
    bool** output = new bool*[out];
    for(unsigned i = 0; i < out; i++){
        output[i] = new bool[bit_len];
    }
    //compute the output of each neuron
    for(unsigned i = 0; i < out; i++){ //for each output neuron
        vec.clear();
        for(unsigned j = 0; j < in; j++){
            vec.push_back(XNOR(input[j], bit_gen(weight[j][i])));
        }
        output[i] = MUX_general(vec);
    }
    return output;
}

//added by yen_ju for conv to linear transfermation
bool** SC::view(bool**** input, short channel, short kernal){
    bool** output = new bool*[channel * kernal * kernal];
    for(unsigned i = 0; i < channel * kernal * kernal; i++){
        output[i] = new bool[bit_len];
    }

    for(unsigned i = 0; i < channel; i++){
        for(unsigned j = 0; j < kernal; j++){
            for(unsigned k = 0; k < kernal; k++){
                output[i * kernal * kernal + j * kernal + k] = input[i][j][k];
            }
        }
    }
    return output;
}

//
bool**** SC::maxpool2d(bool**** input, short in_size, short channel, short kernal, short stride){
    //declare a 3D array(out_channel * img_size * img_size) for the output tensor
    bool**** output = new bool***[channel];
    for(unsigned i = 0; i < channel; i++){ 
        output[i] = new bool**[in_size / 2 + 2];
        for( unsigned j = 0; j < in_size / 2 + 2; j++){ 
            output[i][j] = new bool*[in_size / 2 + 2];
            for(unsigned k = 0; k < in_size / 2 + 2; k++){
                output[i][j][k] = new bool[bit_len];
                output[i][j][k] = bit_gen(0);
            }
        }
    }
    //find the max element of each kernal
    int max = 0, x = 0, y = 0, matrix[kernal][kernal];
    for( unsigned i = 0; i < in_size / 2; i++){ 
        for(unsigned j = 0; j < in_size / 2; j++){
            for(unsigned k = 0; k < kernal; k++){
                for(unsigned l = 0; l < 2; l++){
                    matrix[k][l] = 0;
                }
            }
            for(unsigned k = 0; k < kernal; k++){
                for(unsigned l = 0; l < kernal; l++){
                    for(unsigned m = 0; m < channel; m++){
                        matrix[k][l] += print(input[m][2 * i + k + 1][2 * j + l + 1]);
                    }
                }
            }
            max = 0;
            x = 0;
            y = 0;
            for(unsigned k = 0; k < kernal; k++){
                for(unsigned l = 0; l < 2; l++){
                    if(matrix[k][l] > max){
                        max = matrix[k][l];
                        x = k;
                        y = l;
                    }
                }
            }
            for(unsigned k = 0; k < channel; k++){
                output[k][i + 1][j + 1] = input[k][2 * i + x + 1][2 * j + y +1];
            }
        }
    }
    return output;
}