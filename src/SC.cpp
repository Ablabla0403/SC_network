#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <unordered_map>
#include "SC.h"
#include "definition.h"
using namespace std;



double SC::to_bipolar(int a){
    return 2.0 * a / bit_len - 1;
}


double SC::print(bool* a){
    int count = 0;
    for (size_t i = 0; i < bit_len; i++){
        if (a[i] == true){
            count ++;
        }
    }
    return (double)count/bit_len;
    
}


bool* SC::bit_gen(double number){

    bool *bit_stream = new bool[bit_len];
    double prob = number;
    
    for(int i = 0; i < bit_len; i++){
        
        double r = (double)(rand()+500.483) * 3 / (RAND_MAX );
        if(r < prob){
            bit_stream[i] = true;
        }
        else{
            bit_stream[i] = false;
        }
    }
    
    return bit_stream;
}

// int* SC::int_SC_gen(double number){
//     int *int_stream = new int[bit_len];
//     double prob = (number + 1.0) / 2;
    
//     for(int i = 0; i< bit_len;i++){
        
//         double r = (double)rand() / (RAND_MAX );
//         if(r<prob){
//             bit_stream[i] = true;
//         }
//         else{
//             bit_stream[i] = false;
//         }
//     }
// }

bool* SC::AND(bool* a, bool* b)
{
    bool* AND_output = new bool[bit_len];
    for (size_t i=0; i<bit_len; i++) {
        AND_output[i] = a[i] & b[i];
    }
    return AND_output;
}

bool* SC::OR(bool* a, bool* b)
{
    bool* OR_output = new bool[bit_len];
    for(size_t i = 0; i < bit_len; ++i)
    {
        OR_output[i] = a[i] | b[i];
    }
    return OR_output;
}

bool* SC::tree_adder(vector<bool*> & vec)
{
    vector<bool*> tmp_vec = vec;
    // cout << "haha" << vec.size() << "\n";
    bool* tmp = new bool[bit_len];
    int num_before = vec.size(), num_after = (vec.size() + 1)/2 ;
    
    while (num_before > 1) {
        // cout << "num = " << num_before << "  " << num_after << endl;
        if (num_before % 2 == 0) {
            for (size_t i = 0; i < num_after; ++i) {
                // cout << "lll " << print(tmp_vec[2*i]) << " " << print(tmp_vec[2*i+1]) << endl;
                tmp = OR(tmp_vec[2*i], tmp_vec[2*i+1]);
                // cout << "bello " << print(tmp) << endl;
                tmp_vec.push_back(tmp);
            }
        } else {
            for (size_t i = 0; i < num_after-1; ++i) {
                tmp = OR(tmp_vec[2*i], tmp_vec[2*i+1]);
                // cout << "bello " << print(tmp) << endl;
                tmp_vec.push_back(tmp);
            }
            tmp_vec.push_back(vec[num_before - 1]);
            // for (size_t i = 0; i < num_after - 1; ++i) {
            //     cout << "lll " << print(tmp_vec[i]) << endl;
            // }
        }
        // for(size_t i = 0; i < tmp_vec.size(); ++i)
        // {
        //     cout << "bello " << print(tmp_vec[i]) << endl;
        // }
        tmp_vec.erase(tmp_vec.begin(), tmp_vec.begin()+num_before);
        // for(size_t i = 0; i < tmp_vec.size(); ++i)
        // {
        //     cout << "hello " << print(tmp_vec[i]) << endl;
        // }
        num_before = num_after;
        num_after = (num_after + 1)/2;
    }
    tmp = tmp_vec[0];
    return tmp;
}

bool* SC::XNOR(bool* a, bool* b)
{
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




bool* SC::MUX_general(vector<bool*> &bit_streams){
    bool* output = new bool[bit_len];
    float r;
    int count = 0;
    for(size_t i=0; i<bit_len; ++i){
        for(size_t j=0; j<bit_streams.size(); ++j){
            if(bit_streams[j][i]){
                count ++;
            }
        }
        if(count >= bit_streams.size()){
            output[i] = true;
            count -= bit_streams.size();
        }
        else{
            output[i] = false;
        }
    }
    return output;
}


//added by YEN-JU, construct conv2d for bipolar SC
bool**** SC::conv2d(bool**** input, vector<vector<vector<vector<float>>>>& filter,vector<float>& bias, vector<bool*> &vec, short img_size, short in_channels, short out_channels){
    vec.clear();
    int left, right, up, down, count = 0;
    //declare a 3D array(out_channel * img_size * img_size) for the output tensor
    bool**** output = new bool***[out_channels];
    for(unsigned i = 0; i < out_channels; ++i){ 
        output[i] = new bool**[img_size];
        for( unsigned j = 0; j < img_size; ++j){ 
            output[i][j] = new bool*[img_size];
            for(unsigned k = 0; k < img_size; ++k){
                output[i][j][k] = new bool[bit_len];
                output[i][j][k] = bit_gen(0);
            }
        }
    }
    
    //compute output channels
    for(unsigned i = 0; i < out_channels; ++i){
        for(unsigned j = 0; j < img_size; ++j){
            for(unsigned k = 0; k < img_size; ++k){
                vec.clear();
                left = -1, right = 2, up = -1, down = 2;
                if(j == 0) left = 0;
                if(j == img_size - 1) right = 1;
                if(k == 0) up = 0;
                if(k == img_size - 1) down = 1;
                for(int m = left; m < right; ++m){
                    for(int n = up; n < down; ++n){
                        for(unsigned t = 0; t < in_channels; ++t){
                            // vec.push_back(XNOR(input[t][j + m][k + n],bit_gen(filter[i][m][n])));
                            vec.push_back(AND(input[t][j + m][k + n] , bit_gen(filter[i][t][m+1][n+1])));
                            count++;
                        }
                    }
                }
                vec.push_back(bit_gen(bias[i]));
                output[i][j][k] = tree_adder(vec);
            }
        }
    }
    return output;
}

float*** SC::conv2d(float*** input, vector<vector<vector<vector<float>>>>& filter,vector<float>& bias, vector<bool*> &vec, short img_size, short in_channels, short out_channels){
    // vec.clear();
    //declare a 3D array(out_channel * img_size * img_size) for the output tensor
    float*** output = new float**[out_channels];
    for(unsigned i = 0; i < out_channels; ++i){ 
        output[i] = new float*[img_size];
        for(unsigned j = 0; j < img_size; ++j){ 
            output[i][j] = new float[img_size];
            for(unsigned k = 0; k < img_size; ++k){
                output[i][j][k] = 0;
            }
        }
    }
    float tmp = 0;
    int left, right, up, down, count = 0;
    //compute output channels
    for(unsigned i = 0; i < out_channels; ++i){
        for(unsigned j = 0; j < img_size; ++j){
            for(unsigned k = 0; k < img_size; ++k){
                // vec.clear();
                left = -1, right = 2, up = -1, down = 2;
                if(j == 0) left = 0;
                if(j == img_size - 1) right = 1;
                if(k == 0) up = 0;
                if(k == img_size - 1) down = 1;
                tmp = 0;
                count = 0;
                // cout << "up = " << up << " down = " << down << " left = " << left << " right = " << right << endl;
                for(int m = left; m < right; ++m){
                    for(int n = up; n < down; ++n){
                        for(unsigned t = 0; t < in_channels; ++t){
                            // vec.push_back(XNOR(input[t][j + m][k + n],bit_gen(filter[i][m][n])));
                            tmp += input[t][j + m][k + n] * filter[i][t][m+1][n+1];
                            count++;
                        }
                    }
                }
                // vec.push_back(bit_gen(bias[i]));
                // cout << "Count =  " << count << endl;
                tmp += bias[i];
                output[i][j][k] = (tmp>1)? 1 : tmp;
            }
        }
    }
    return output;
}


//added by yen_ju for fully connected layers
float* SC::linear(float* input, vector<vector<float>>& weight, vector<float>& bias, short in, short out, bool hardtanh){
    //new the output
    float* output = new float[out];
    for(unsigned i = 0; i < out; i++){
        output[i] = 0;
    }
    //compute the output of each neuron
    for(unsigned i = 0; i < out; ++i){ //for each output neuron
        for(unsigned j = 0; j < in; ++j){
            output[i] += input[j] * weight[i][j];
        }
        output[i] += bias[i];
        if(hardtanh)
        {
            if(output[i] > 1) output[i] = 1;
            if(output[i] < -1) output[i] = -1;
        }
    }
    return output;
}

bool** SC::linear(bool** input, vector<vector<float>>& weight, vector<float>& bias, vector<bool*>& vec, short in, short out, bool hardtanh){
    //new the output
    bool** output = new bool*[out];
    double count = 0;
    
    for(size_t i = 0; i < out; i++){
        output[i] = new bool[bit_len];
    }
    //compute the output of each neuron
    for(unsigned i = 0; i < out; ++i){ //for each output neuron

        count = 0;
        vec.clear();
        for(unsigned j = 0; j < in; ++j){
            vec.push_back(AND(input[j], bit_gen(weight[i][j])));
            // cout << "vec len = " << vec.size() << endl;
            // cout << "i = " << i << " j = " << j << " input " << print(input[j]) << " weight " << weight[i][j] << " pushed " << print(AND(input[j], bit_gen(weight[i][j]))) << " ans " << print(tree_adder(vec)) << endl;
        }
        // cout << "before bias : " << print(tree_adder(vec)) << endl;
        vec.push_back(bit_gen(bias[i]));
        // cout << "bias = " << print(vec[vec.size() - 1]) << endl;
        output[i] = tree_adder(vec);
        // cout << "after bias : " << print(output[i]) << endl;
    }

    return output;
}

//added by yen_ju for conv to linear transfermation
bool** SC::view(bool**** input, short channel, short input_size){
    bool** output = new bool*[channel * input_size * input_size];
    for(unsigned i = 0; i < channel * input_size * input_size; i++){
        output[i] = new bool[bit_len];
    }

    for(unsigned i = 0; i < channel; i++){
        for(unsigned j = 0; j < input_size; j++){
            for(unsigned k = 0; k < input_size; k++){
                output[i * input_size * input_size + j * input_size + k] = input[i][j][k];
            }
        }
    }
    return output;
}

float* SC::view(float*** input, short channel, short input_size){
    float* output = new float[channel * input_size * input_size];
    for(unsigned i = 0; i < channel * input_size * input_size; i++){
        output[i] = 0;
    }

    for(unsigned i = 0; i < channel; i++){
        for(unsigned j = 0; j < input_size; j++){
            for(unsigned k = 0; k < input_size; k++){
                output[i * input_size * input_size + j * input_size + k] = input[i][j][k];
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
    float max = 0;
    int x = 0, y = 0;
    for( unsigned i = 0; i < in_size / 2; ++i){ 
        for(unsigned j = 0; j < in_size / 2; ++j){
            // cout << i << " " << j << endl;
            for(unsigned k = 0; k < channel; k++)
            {
                max = -10000;
                x = 0;
                y = 0;
                for(unsigned l = 0; l < kernal; l++)
                {
                    for(unsigned m = 0; m < kernal; m++)
                    {
                        if(print(input[k][2 * i + l][2 * j + m]) > max)
                        {
                            x = l;
                            y = m;
                            max = print(input[k][2 * i + l][2 * j + m]);
                        }
                    }
                }
                if(max > 1) max = 1;
                if(max < -1) max = -1;
                output[k][i][j] = input[k][2 * i + x][2 * j + y];
            }
        }
    }
    return output;
}

float*** SC::maxpool2d(float*** input, short in_size, short channel, short kernal, short stride){
    //declare a 3D array(out_channel * img_size * img_size) for the output tensor
    float*** output = new float**[channel];
    for(unsigned i = 0; i < channel; i++){ 
        output[i] = new float*[in_size / 2];
        for( unsigned j = 0; j < in_size / 2; j++){ 
            output[i][j] = new float[in_size / 2];
            for(unsigned k = 0; k < in_size / 2; k++){
                output[i][j][k] = 0;
            }
        }
    }
    //find the max element of each kernal
    float max = 0;
    int x = 0, y = 0;
    for( unsigned i = 0; i < in_size / 2; ++i){ 
        for(unsigned j = 0; j < in_size / 2; ++j){
            // cout << i << " " << j << endl;
            for(unsigned k = 0; k < channel; k++)
            {
                max = -10000;
                x = 0;
                y = 0;
                for(unsigned l = 0; l < kernal; l++)
                {
                    for(unsigned m = 0; m < kernal; m++)
                    {
                        if(input[k][2 * i + l][2 * j + m] > max)
                        {
                            x = l;
                            y = m;
                            max = input[k][2 * i + l][2 * j + m];
                        }
                    }
                }
                if(max > 1) max = 1;
                if(max < -1) max = -1;
                output[k][i][j] = max;
            }
        }
    }
    return output;
}


bool* SC::Stanh(vector<bool*>& bit_streams){
    int num = bit_streams.size();
    bool* ans = new bool[bit_len];
    int counter = 0, S = 0;
    for(size_t i=0; i<bit_len; ++i){
        S = 0;
        for(size_t j=0; j<num; ++j){
            if(bit_streams[j][i]) S++;
            else S--;
        }
        // cout << counter <<  "  " << S << "\n";
        counter += S;

        if(counter > 2*num-1) counter = 2*num-1;
        else if(counter < 0) counter = 0;

        if(counter > num-1) ans[i] = true;
        else ans[i] = false;
    }
    return ans;

}

bool* SC::Hardtanh(vector<bool*>& bit_streams){
    int num = bit_streams.size();
    bool* output = new bool[bit_len];
    int n = 20;
    float count = 0, total = 0;

    for(size_t i = 0; i < bit_len; ++i){
        for(size_t j = 0; j < bit_streams.size(); ++j){
            if(bit_streams[j][i]) count ++;
            else count --;
        }
        total += (count + 1)/2;
        count = 0;

        if(i > n){
            if(total > 0){
                output[i] = true;
                total --;
            }
            else{
                output[i] = false;
            }
        }
    }
    // cout << total << "\n";
    for(size_t i = 0; i < n; ++i){
        if(total > 0){
            output[i] = true;
            total --;
        }
        else{
            output[i] = false;
        }
    }

    count = 0;
    for(size_t i = 0; i < bit_len; ++i){
        if(output[i]) count++;
    }
    
    return output;
}