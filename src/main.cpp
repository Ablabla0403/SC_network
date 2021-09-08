#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include "../inc/SC.h"
#include "../inc/definition.h"
#include <cmath>

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

    vector<vector<float>> layer_1_w(512, vector<float>(784, 0));
    vector<float> layer_1_b(512, 0);
    vector<vector<float>> layer_2_w(256, vector<float>(512, 0));
    vector<float> layer_2_b(256, 0);
    vector<vector<float>> layer_3_w(128, vector<float>(256, 0));
    vector<float> layer_3_b(128, 0);
    vector<vector<float>> layer_4_w(10, vector<float>(128, 0));
    vector<float> layer_4_b(10, 0);

    vector<vector<vector<float>>> w_params{layer_1_w,layer_2_w,layer_3_w,layer_4_w};

    vector<vector<float>> b_params = {layer_1_b, layer_2_b, layer_3_b, layer_4_b};

    ifstream fin;
    int count = 0, tmp = 0;
    string str = "";

    for(int i=0; i<4; ++i){

        fin.open("input/layer_" + to_string(i+1) + "_w.txt");
        if(!fin){
            cerr << "cannot open file!";
        }
        count = 0;
        tmp = w_params[i][0].size();
        while(!fin.eof()){
            fin >> str;
            if(count/tmp < w_params[i].size()){
                w_params[i][count / tmp][count % tmp] = stof(str);
            }
            count ++;
        }
        fin.close();

        fin.open("input/layer_" + to_string(i+1)+ "_b.txt");
        if(!fin){
            cerr << "cannot open file!";
        }
        count = 0;
        while(!fin.eof()){
            fin >> str;
            if(count < b_params[i].size()){
                b_params[i][count]= stof(str);
            }
            count ++;
        }
        fin.close();
    }
    
    
    vector<float> test;
    vector<vector<float>> test_images;
    vector<int> test_labels;
    count = 0;

    fin.open("train_images.txt");

    if(!fin){
        cerr << "tests file cannot open!";
    }
    while(!fin.eof()){
        if(count == 784){
            test_images.push_back(test);
            test.clear();
            count = 0;
        }
        fin >> str;
        test.push_back(stof(str)/256);
        count ++;
    }

    fin.close();

    fin.open("train_labels.txt");

    if(!fin){
        cerr << "tests file cannot open!";
    }
    count = 0;
    while(!fin.eof()){
        fin >> str;
        if(count < 1000){
            test_labels.push_back(stoi(str));
            count ++;
            // cout << count << "  " << stoi(str) << "\n";
        }
        
    }

    float** fc_neurons;
    fc_neurons = new float*[5];
    
    fc_neurons[0] = new float[784];
    for(size_t i = 0; i < 784; ++i){
        fc_neurons[0][i] = 0;
    }

    fc_neurons[1] = new float[512];
    for(size_t i = 0; i < 512; ++i){
        fc_neurons[1][i] = 0;
    }

    fc_neurons[2] = new float[256];
    for(size_t i = 0; i < 256; ++i){
        fc_neurons[2][i] = 0;
    }

    fc_neurons[3] = new float[128];
    for(size_t i = 0; i < 128; ++i){
        fc_neurons[3][i] = 0;
    }

    fc_neurons[4] = new float[10];
    for(size_t i = 0; i < 10; ++i){
        fc_neurons[4][i] = 0;
    }
    
    
    int label = 0, max_cand = 0, correct_count = 0;
    float max = 0;
    // char b;
    for(size_t i = 0; i < 1; ++i)
    {
        for(size_t j = 0; j < 784; ++j)
        {
            fc_neurons[0][j] = test_images[i][j];
        }

        fc_neurons[1] = sc.linear(fc_neurons[0], w_params[0], b_params[0], 784, 512);


        for(int k = 0; k < 512; ++k){
            if(fc_neurons[1][k] > 1) fc_neurons[1][k] = 1;
            else if(fc_neurons[1][k] < -1) fc_neurons[1][k] = -1;
        }

        // for(size_t k = 0; k < 100; ++k){
        //     cout << fc_neurons[1][k] << "\n";
        // }



        fc_neurons[2] = sc.linear(fc_neurons[1], w_params[1], b_params[1], 512, 256);

        for(int k = 0; k < 256; ++k){
            if(fc_neurons[2][k] > 1) fc_neurons[2][k] = 1;
            else if(fc_neurons[2][k] < -1) fc_neurons[2][k] = -1;
            // cout << fc_neurons[2][k] << "\n";
        }
        
        fc_neurons[3] = sc.linear(fc_neurons[2], w_params[2], b_params[2], 256, 128);

        for(int k = 0; k < 128; ++k){
            if(fc_neurons[3][k] > 1) fc_neurons[3][k] = 1;
            else if(fc_neurons[3][k] < -1) fc_neurons[3][k] = -1;
            // cout << fc_neurons[3][k] << "\n";
        }

        fc_neurons[4] = sc.linear(fc_neurons[3], w_params[3], b_params[3], 128, 10);

        // for(int k = 0; k < 10; ++k){
        //     cout << fc_neurons[4][k] << "\n";
        // }


        max = fc_neurons[4][0];
        max_cand = 0;
        for(size_t j = 0; j < 9; ++j)
        {
            if(fc_neurons[4][j] > max)
            {
                max = fc_neurons[4][j];
                max_cand = j;
            }
        }

        cout << "label is : " << test_labels[i] << " ;predict is : " << max_cand << endl;
        if(max_cand == test_labels[i])
        {
            ++correct_count;
            cout << "correct!!!" << endl;
        }
        else cout << "wrong!!!" << endl;
        cout << "accuracy = " << (float)correct_count / (i + 1) << endl;
    }
    
    return 0;
}

