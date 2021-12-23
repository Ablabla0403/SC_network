#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <unordered_map>
#include "../inc/SC.h"
#include "../inc/definition.h"
#include <cmath>

using namespace std;

int main(int argc,char** argv){

    vector<double> lfsr;
    bool flag_b = false;
    int vec_num = 1000;
    unordered_map<int, bool> hash;
    double ran;
    int num = 0;
    if( argc > 1) flag_b = true;
    // cout << "flag_b = " << flag_b << " " << argv[1] << endl;
    while(hash.size() < vec_num){
        ran = (double)rand() / (RAND_MAX );
        num = ran*vec_num;
        if(hash.find(num) == hash.end()){
            hash[num] = true;
            lfsr.push_back(num);
        }
    }

    SC sc(lfsr);

    srand(time(NULL));
    cout<<"program in"<<endl;

    vector<vector<float>> layer_1_w(10, vector<float>(1568, 0));
    vector<float> layer_1_b(10, 0);
    

    vector<vector<vector<float>>> w_params{layer_1_w};
    vector<vector<float>> b_params = {layer_1_b};


    ifstream fin;
    int count = 0, tmp = 0;
    string str = "";
    cout << "fc_weight.txt" << endl;
    fin.open("fc_weight.txt");
    if(!fin){
        cerr << "cannot open file!";
        return 0;
    }
    for(size_t i = 0; i < 10; ++i)
    {
        for(size_t j = 0; j < 1568; ++j)
        {
            fin >> str;
            w_params[0][i][j] = stof(str);
        }
    } 
    fin.close();
    cout << "fc_weight.txt finished!!" << endl;
    if(!fin){
        cerr << "cannot open file!";
        return 0;
    }
    fin.open("fc_bias.txt");
    for(size_t i = 0; i < 10; ++i)
    {
        fin >> str;
        b_params[0][i] = stof(str);
    }
    fin.close();
    cout << "fc_bias finished!!" << endl;



    vector<vector<vector<vector<float>>>> cnn_layer_1_w(32, vector<vector<vector<float>>>(1, vector<vector<float>>(3, vector<float>(3))));
    vector<float> cnn_layer_1_b(32, 0);
    vector<vector<vector<vector<float>>>> cnn_layer_2_w(32, vector<vector<vector<float>>>(32, vector<vector<float>>(3, vector<float>(3))));
    vector<float> cnn_layer_2_b(32, 0);
    vector<vector<vector<vector<float>>>> cnn_layer_3_w(32, vector<vector<vector<float>>>(32, vector<vector<float>>(5, vector<float>(5))));
    vector<float> cnn_layer_3_b(32, 0);

    vector<vector<vector<vector<vector<float>>>>> cnn_w_params{cnn_layer_1_w,cnn_layer_2_w,cnn_layer_3_w};
    vector<vector<float>> cnn_b_params = {cnn_layer_1_b, cnn_layer_2_b, cnn_layer_3_b};
    
    fin.open("cnn_weight.txt");
    if(!fin){
        cerr << "cannot open file!";
        return 0;
    }
    for(size_t i = 0; i < 32; ++i)
    {
        for(size_t j = 0; j < 1; ++j)
        {
            for(size_t k = 0; k < 3; ++k)
            {
                for(size_t l = 0; l < 3; ++l)
                {
                    fin >> str;
                    cnn_w_params[0][i][j][k][l] = stof(str);
                }
            }
        }
    }
    for(size_t i = 0; i < 32; ++i)
    {
        for(size_t j = 0; j < 32; ++j)
        {
            for(size_t k = 0; k < 3; ++k)
            {
                for(size_t l = 0; l < 3; ++l)
                {
                    fin >> str;
                    cnn_w_params[1][i][j][k][l] = stof(str);
                }
            }
        }
    }
    for(size_t i = 0; i < 32; ++i)
    {
        for(size_t j = 0; j < 32; ++j)
        {
            for(size_t k = 0; k < 5; ++k)
            {
                for(size_t l = 0; l < 5; ++l)
                {
                    fin >> str;
                    cnn_w_params[2][i][j][k][l] = stof(str);
                }
            }
        }
    }
    cout << "cnn_weight finished!!" << endl;
    fin.close();

/*
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
    */
    
    vector<float> test;
    vector<vector<float>> testVecVec;
    vector<vector<vector<float>>> testVecVecVec;
    vector<vector<vector<vector<float>>>> test_images;
    vector<int> test_labels;
    count = 0;

    fin.open("train_images.txt");

    if(!fin){
        cerr << "train file cannot open!";
        return 0;
    }
    while(fin >> str){
        // cout << "test data " << str << endl;
        test.push_back(stof(str));
        count ++;
        if(count % 28 == 0){
            testVecVec.push_back(test);
            test.clear();
        }
        if(count % 784 == 0){
            testVecVecVec.push_back(testVecVec);
            testVecVec.clear();
        }
        if(count == 784){
            test_images.push_back(testVecVecVec);
            testVecVecVec.clear();
            count = 0;
            // testVecVec.push_back(test);
            // test.clear();
            // count = 0;
        }
    }
    cout << "\n";   

    fin.close();

    fin.open("train_labels.txt");

    if(!fin){
        cerr << "train label cannot open!";
        return 0;
    }
    count = 0;
    while(fin >> str){
        if(count < 1000){
            test_labels.push_back(stoi(str));
            count ++;
        }
    }
    fin.close();


    bool***** cnn_neurons;
    cnn_neurons = new bool****[3];

    cnn_neurons[0] = new bool***[1];
    for(size_t i = 0; i < 1; ++i){
        cnn_neurons[0][i] = new bool**[28];
        for(size_t j = 0; j < 28; ++j){
            cnn_neurons[0][i][j] = new bool*[28];
            for(size_t k = 0; k < 28; ++k){
                cnn_neurons[0][i][j][k] = new bool[bit_len];
                for(size_t l = 0; l < bit_len; ++l){
                    cnn_neurons[0][i][j][k][l] = 0;
                }
            }
        }
    }

    cnn_neurons[1] = new bool***[32];
    for(size_t i = 0; i < 32; ++i){
        cnn_neurons[1][i] = new bool**[28];
        for(size_t j = 0; j < 28; ++j){
            cnn_neurons[1][i][j] = new bool*[28];
            for(size_t k = 0; k < 28; ++k){
                cnn_neurons[1][i][j][k] = new bool[bit_len];
                for(size_t l = 0; l < bit_len; ++l){
                    cnn_neurons[1][i][j][k][l] = 0;
                }
            }
        }
    }

    cnn_neurons[2] = new bool***[32];
    for(size_t i = 0; i < 32; ++i){
        cnn_neurons[2][i] = new bool**[28];
        for(size_t j = 0; j < 28; ++j){
            cnn_neurons[2][i][j] = new bool*[28];
            for(size_t k = 0; k < 28; ++k){
                cnn_neurons[2][i][j][k] = new bool[bit_len];
                for(size_t l = 0; l < bit_len; ++l){
                    cnn_neurons[2][i][j][k][l] = 0;
                }
            }
        }
    }


    float**** cnn_neurons_b;
    cnn_neurons_b = new float***[4];

    cnn_neurons_b[0] = new float**[1];
    for(size_t i = 0; i < 1; ++i){
        cnn_neurons_b[0][i] = new float*[28];
        for(size_t j = 0; j < 28; ++j){
            cnn_neurons_b[0][i][j] = new float[28];
            for(size_t k = 0; k < 28; ++k){
                cnn_neurons_b[0][i][j][k] = 0;
            }
        }
    }

    cnn_neurons_b[1] = new float**[32];
    for(size_t i = 0; i < 32; ++i){
        cnn_neurons_b[1][i] = new float*[28];
        for(size_t j = 0; j < 28; ++j){
            cnn_neurons_b[1][i][j] = new float[28];
            for(size_t k = 0; k < 28; ++k){
                cnn_neurons_b[1][i][j][k] = 0;
            }
        }
    }

    cnn_neurons_b[2] = new float**[32];
    for(size_t i = 0; i < 32; ++i){
        cnn_neurons_b[2][i] = new float*[28];
        for(size_t j = 0; j < 28; ++j){
            cnn_neurons_b[2][i][j] = new float[28];
            for(size_t k = 0; k < 28; ++k){
                    cnn_neurons_b[2][i][j][k] = 0;
            }
        }
    }


    bool*** fc_neurons;
    fc_neurons = new bool**[2];
    
    fc_neurons[0] = new bool*[1568];
    for(size_t i = 0; i < 1568; ++i){
        fc_neurons[0][i] = new bool[bit_len];
        for(size_t j = 0; j < bit_len; ++j){
            fc_neurons[0][i][j] = 0;
        }
    }

    fc_neurons[1] = new bool*[10];
    for(size_t i = 0; i < 10; ++i){
        fc_neurons[1][i] = new bool[bit_len];
        for(size_t j = 0; j < bit_len; ++j){
            fc_neurons[1][i][j] = 0;
        }
    }

    float** fc_neurons_b;
    fc_neurons_b = new float*[1];

    fc_neurons_b[0] = new float[10];
    for(size_t i = 0; i < 10; ++i){
        fc_neurons_b[0][i] = 0;
    }
    
    
    
    int label = 0, max_cand = 0, correct_count = 0;
    int max_cand_b = 0, correct_count_b = 0;
    float max = 0, max_b = 0;
    vector<bool*> vec;

    // char b;
    cout << "set input " << endl;
    for(size_t i = 0; i < 1000; ++i)
    {
        count = 0;
        for(size_t j = 0; j < 1; ++j)
        {
            // cout << test_images[i][j] << "\n";
            for(size_t k = 0; k < 28; ++k)
            {
                for(size_t l = 0; l < 28; ++l)
                {
                    cnn_neurons[0][j][k][l] = sc.bit_gen(test_images[i][j][k][l]);
                    if(flag_b) cnn_neurons_b[0][j][k][l] = test_images[i][j][k][l];
                }
            }
        }

        cout << "cnn1 start" << endl;
        cnn_neurons[1] = sc.conv2d(cnn_neurons[0], cnn_w_params[0], cnn_b_params[0], vec, 28, 1, 32);
        // if(flag_b) cnn_neurons_b[1] = sc.conv2d(cnn_neurons_b[0], cnn_w_params[0], cnn_b_params[0], vec, 28, 1, 32);
        cout << "cnn1 ended" << endl;
        
        
        
        if(flag_b) cnn_neurons_b[1] = sc.maxpool2d(cnn_neurons_b[1], 32, 6, 2, 2);
        cnn_neurons[1] = sc.maxpool2d(cnn_neurons[1], 32, 6, 2, 2);
        // cout << "maxpool succeed" << endl;
        if(flag_b) cnn_neurons_b[2] = sc.conv2d(cnn_neurons_b[1], cnn_w_params[1], cnn_b_params[1], vec, 16, 6, 16);
        cnn_neurons[2] = sc.conv2d(cnn_neurons[1], cnn_w_params[1], cnn_b_params[1], vec, 16, 6, 16);
        
        
        if(flag_b) cnn_neurons_b[2] = sc.maxpool2d(cnn_neurons_b[2], 16, 16, 2, 2);
        cnn_neurons[2] = sc.maxpool2d(cnn_neurons[2], 16, 16, 2, 2);

        if(flag_b) cnn_neurons_b[3] = sc.conv2d(cnn_neurons_b[2], cnn_w_params[2], cnn_b_params[2], vec, 8, 16, 16);
        cnn_neurons[3] = sc.conv2d(cnn_neurons[2], cnn_w_params[2], cnn_b_params[2], vec, 8, 16, 16);

        if(flag_b) cnn_neurons_b[3] = sc.maxpool2d(cnn_neurons_b[3], 8, 16, 2, 2);
        cnn_neurons[3] = sc.maxpool2d(cnn_neurons[3], 8, 16, 2, 2);

        if(flag_b) fc_neurons_b[0] = sc.view(cnn_neurons_b[3], 16, 4);
        fc_neurons[0] = sc.view(cnn_neurons[3], 16, 4);
        
        if(flag_b) fc_neurons_b[1] = sc.linear(fc_neurons_b[0], w_params[0], b_params[0], 256, 64, true);
        fc_neurons[1] = sc.linear(fc_neurons[0], w_params[0], b_params[0], vec, 256, 64, true);


        if(flag_b) fc_neurons_b[2] = sc.linear(fc_neurons_b[1], w_params[1], b_params[1], 64, 10, false);
        fc_neurons[2] = sc.linear(fc_neurons[1], w_params[1], b_params[1], vec, 64, 10, false);
        // fc_neurons_b[2] = sc.linear(fc_neurons_b[1], w_params[1], b_params[1], 128, 128, true);

        // cout << 2 << "\n";

        // for(int k = 0; k < 256; ++k){
        //     cout << fc_neurons[2][k] << "\n";
        // }
        
        // fc_neurons[3] = sc.linear(fc_neurons[2], w_params[2], b_params[2], vec, 128, 64, true);
        // fc_neurons_b[3] = sc.linear(fc_neurons_b[2], w_params[2], b_params[2], 128, 64, true);

        // cout << 3 << "\n";

        // for(int k = 0; k < 128; ++k){
        //     cout << sc.print(fc_neurons[3][k]) << "\n";
        // }

        // fc_neurons[4] = sc.linear(fc_neurons[3], w_params[3], b_params[3], vec, 64, 10, false);
        // fc_neurons_b[4] = sc.linear(fc_neurons_b[3], w_params[3], b_params[3], 64, 10, false);

        cout << 4 << "\n";

        for(int k = 0; k < 10; ++k){
            cout << sc.print(fc_neurons[2][k]) << "\n";
            if(flag_b) cout << "b " << fc_neurons_b[2][k] << "\n";
        }


        max = sc.print(fc_neurons[4][0]);
        max_cand = 0;
        if(flag_b) max_b = fc_neurons_b[2][0];
        max_cand_b = 0;
        for(size_t j = 0; j < 10; ++j)
        {
            if(sc.print(fc_neurons[2][j]) > max)
            {
                max = sc.print(fc_neurons[2][j]);
                max_cand = j;
            }
            if(flag_b && fc_neurons_b[2][j] > max_b)
            {
                max_b = fc_neurons_b[2][j];
                max_cand_b = j;
            }
        }

        cout << "label is : " << test_labels[i] << " ;predict is : " << max_cand << endl;
        if(flag_b) cout << "label is :(b) " << test_labels[i] << " ;predict is : " << max_cand_b << endl;
        if(max_cand == test_labels[i])
        {
            ++correct_count;
            // cout << "correct!!!" << endl;
        }
        // else cout << "wrong!!!" << endl;
        if(flag_b && max_cand_b == test_labels[i])
        {
            ++correct_count_b;
            // cout << "correct!!!" << endl;
        }
        cout << "accuracy = " << (float)correct_count / (i + 1) << endl;
        if(flag_b) cout << "accuracy =(b) " << (float)correct_count_b / (i + 1) << endl;
    }
    
    return 0;
}

