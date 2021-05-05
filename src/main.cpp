#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <definition.h>
#include <SC.h>

using namespace std;

int main(int argc,char** argv){
    SC sc;
    srand(time(NULL));
    cout<<"program in"<<endl;
    bool all_one[bit_len];
    bool all_zero[bit_len];
    bool* stream1;
    bool* stream2;
    bool* stream3;
    // for(unsigned i = 0; i < 10000; i++){
    //     double r1 = (double)rand() / (RAND_MAX + 1.0);
    //     stream1 = sc.bit_gen(r1);
    //     double r2 = (double)rand() / (RAND_MAX + 1.0);
    //     stream2 = sc.bit_gen(r2);
    //     stream3 = sc.MUX(stream2,stream1);
    //     cout<<sc.print(stream3) - (r1 + r2) / 2.0 <<endl;
    // }
    // ESL w,x,y,z,out1,out2,a;
    // double answer1 = 0,answer2 = 0;
    // x = sc.number_gen(0.3); //error here!!!
    // y = sc.number_gen(0.6);
    // z = sc.number_gen(0.6);
    // w = sc.number_gen(3);
    // cout<<"numnber generated"<<endl;
    // out1 = sc.APC(x,y);
    // out2 = sc.XNOR(w,z);
    // a = sc.XNOR(out1,out2);

    // cout<<"out1 = "<<sc.print(out1)<<endl;

    double weight_1[5][4] = {{-0.8943432569503784,0.9737143516540527,-0.9517430067062378,-0.9852113723754883},
{0.9137420654296875,0.9004345536231995,-0.9898185729980469,-0.9060466885566711},
{0.21185515820980072,-0.9543663859367371,0.9667595028877258,0.9933619499206543},
{-0.9737479090690613,0.9187009334564209,-0.9989287257194519,-0.9001524448394775},
{0.6824721693992615,0.957975447177887,-0.9171951413154602,-0.9900959730148315}};
// double bias_1[5] = {0.00.00.00.00.0};
double weight_2[3][5] = {{0.9719899892807007,0.9846965074539185,-0.9358288049697876,0.9626417756080627,0.9860727787017822},
{-0.20465542376041412,-0.9981417655944824,0.9513555765151978,0.44339847564697266,-0.9466770887374878},
{-0.9862060546875,-0.9905967712402344,0.9926243424415588,-0.9577712416648865,-0.9542217254638672}};
double bias_2[3] = {0.9194463491439819,0.9914700388908386,-0.9804202914237976};
    
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

    int train_label[120] = {0 ,0, 1, 0, 0, 2, 1, 0, 0, 0, 2, 1, 1, 0, 0, 1, 2, 2, 1, 2, 1, 2, 1, 0, 2, 1, 0, 0, 0, 1, 2, 0, 0, 0, 1, 0, 1,
        2, 0, 1, 2, 0, 2, 2, 1, 1, 2, 1, 0, 1, 2, 0, 0, 1, 1, 0, 2, 0, 0, 1, 1, 2, 1, 2, 2, 1, 0, 0, 2, 2, 0, 0, 0, 1,
        2, 0, 2, 2, 0, 1, 1, 2, 1, 2, 0, 2, 1, 2, 1, 1, 1, 0, 1, 1, 0, 1, 2, 2, 0, 1, 2, 2, 0, 2, 0, 1, 2, 2, 1, 2, 1,
        1, 2, 2, 0, 1, 2, 0, 1, 2};
  
    bool* aa;
    bool* bb;
    bool* cc;
    double summention = 0;
    // for(int i = 0;i < 10000; i++){
    //     double r1 = (double)rand() / (RAND_MAX + 1.0);
    //     aa = sc.bit_gen(2.0*r1-1.0);
    //     double r2 = (double)rand() / (RAND_MAX + 1.0);
    //     bb = sc.bit_gen(2.0*r2-1.0);
    //     cc = sc.MUX(aa,bb);
    //     summention += abs(sc.print(cc) - (r1 + r2) / 2.0);
    // }
    // cout<<"error = "<<summention/10000.0<<endl;

    bool* layer_0[4];
    for(size_t i=0; i<4; i++){
        layer_0[i] = sc.bit_gen(0);
    } 

    bool* layer_1[5];
    for(size_t i=0; i<5; i++){
        layer_1[i] = sc.bit_gen(0);
    } 

    bool* layer_2[3];
    for(size_t i=0; i<5; i++){
        layer_2[i] = sc.bit_gen(0);
    } 

    double _layer_0[4];
    double _layer_1[10];
    double _layer_2[3];

    double store_layer_1[30][10];

    float corr_count = 0;
    float max = 0, max_cand = 0;
    double temp = 0;

    //--------------divide the data by 10.0---------------
    for(unsigned i =0; i < 30; i++){
        for(unsigned j = 0; j < 4; j++){
            x_test[i][j] /= 10.0;
        }
    }

    // divide the weights and bias by 10.0
    // for(unsigned i =0; i < 5; i++){
    //     for(unsigned j = 0; j < 4; j++){
    //         weight_1[i][j] /= 10.0;
    //     }
    // }

    // for(unsigned i =0; i < 5; i++){
    //     bias_1[i] /= 40.0;
    // }

    // for(unsigned i =0; i < 3; i++){
    //     for(unsigned j = 0; j < 5; j++){
    //         weight_2[i][j] /= 10.0;
    //     }
    // }

    // for(unsigned i =0; i < 3; i++){
    //     bias_2[i] /= 400.0;
    // }

    //
    corr_count = 0;
    for(int k=0; k<30; k++){
        for(int i=0;i<4;i++){
            _layer_0[i] = x_test[k][i];
        }
        for(int i=0;i<5;i++){
            _layer_1[i] = 0;
        }
        for(int i=0;i<3;i++){
            _layer_2[i] = 0;
                  }


        for(int i=0;i<5;i++){
            for(int j=0;j<4;j++){
                _layer_1[i] += _layer_0[j] * weight_1[i][j];
            }
            // _layer_1[i] /= 4.0;
            store_layer_1[k][i]=_layer_1[i];
            // _layer_1[i] += bias_1[i];
            // _layer_1[i] /= 4.0;
            // _layer_1[i] /= 2.0;
        }
    
        for(int i=0;i<3;i++){
            for(int j=0;j<5;j++){
                _layer_2[i] += _layer_1[j] * weight_2[i][j];
            }
            // _layer_2[i] /= 5.0;
            _layer_2[i] += bias_2[i];
            // _layer_2[i] /= 5.0;
            // _layer_2[i] /= 2.0;
        }
        
        
        
        max = -10000;
        max_cand = 0;

        for(size_t j=0; j<3;j++){
            if(_layer_2[j] > max){
                max = _layer_2[j];
                max_cand = j;
            }
            // cout << "layer 2[" << j << "] is :" << _layer_2[j] <<endl;
            // cout << "max cand is : " << max_cand << endl;
        }
        // cout<<max_cand<<endl;

        if(max_cand == corr_answer[k]){
            corr_count += 1;
            // cout<<"correct!!!!!("<<corr_count<<'/'<<k+1<<')'<<endl;
        }
        else{
            // cout<<"wrong!!!!!("<<corr_count<<'/'<<k+1<<')'<<endl;
        }

    }
    cout<<"The rate of correctness is: "<<corr_count/30.0<<endl;
    
    //----------------------------------------------------------------------------------
    corr_count = 0;

    for(int k=0; k<30; k++){
        for(int i=0;i<4;i++){
            layer_0[i] = sc.bit_gen(x_test[k][i]);
        }
            
        for(int i=0;i<5;i++){
            layer_1[i] = sc.bit_gen(0);
        }

        for(int i=0;i<3;i++){
            layer_2[i] = sc.bit_gen(0);
        }


        for(int i=0;i<5;i++){
            // for(int j=0;j<4;j++){
            //     layer_1[i] = sc.APC(layer_1[i] ,sc.XNOR(layer_0[j],sc.bit_gen(weight_1[i][j])));
            // }
            layer_1[i] = sc.MUX_4(sc.XNOR(layer_0[0],sc.bit_gen(weight_1[i][0])),sc.XNOR(layer_0[1],sc.bit_gen(weight_1[i][1])),sc.XNOR(layer_0[2],sc.bit_gen(weight_1[i][2])),sc.XNOR(layer_0[3],sc.bit_gen(weight_1[i][3])));
            // cout<<(store_layer_1[k][i]-sc.print(layer_1[i]))<<endl;
            // cout << store_layer_1[k][i] << endl;
            // layer_1[i] = sc.MUX(layer_1[i],sc.bit_gen(bias_1[i]));
        }
    
        for(int i=0;i<3;i++){
            // for(int j=0;j<5;j++){
            //      layer_2[i] = sc.APC(layer_2[i] ,sc.XNOR(layer_1[j],sc.bit_gen(weight_2[i][j])));
            // }
            layer_2[i] = sc.MUX_5(sc.XNOR(layer_1[0],sc.bit_gen(weight_2[i][0])),sc.XNOR(layer_1[1],sc.bit_gen(weight_2[i][1])),sc.XNOR(layer_1[2],sc.bit_gen(weight_2[i][2])),sc.XNOR(layer_1[3],sc.bit_gen(weight_2[i][3])),sc.XNOR(layer_1[4],sc.bit_gen(weight_2[i][4])));  
            layer_2[i] = sc.MUX(layer_2[i],sc.bit_gen(bias_2[i]));
            
        }
        
        
        max = -10000;
        max_cand = 0;

        for(size_t j=0; j<3;j++){
            if(sc.print(layer_2[j]) > max){
                max = sc.print(layer_2[j]);
                max_cand = j;
            }
            // cout << "layer 2[" << j << "] is :" << sc.print(layer_2[j]) <<endl;
            // cout << "max cand is : " << max_cand << endl;
        }
        // cout<<max_cand<<endl;

        if(max_cand == corr_answer[k]){
            corr_count += 1;
            // cout<<"correct!!!!!("<<corr_count<<'/'<<k+1<<')'<<endl;
        }
        else{
            // cout<<"wrong!!!!!("<<corr_count<<'/'<<k+1<<')'<<endl;
        }

    }
    cout<<"The rate of correctness is: "<<corr_count/30.0<<endl;
    
    return 0;
}


// bool* aa;
//     bool* bb;
//     bool* cc;
//     double summention = 0;
//     for(int i = 0;i < 10000; i++){
//         double r1 = (double)rand() / (RAND_MAX + 1.0);
//         aa = sc.bit_gen(2.0*r1-1.0);
//         double r2 = (double)rand() / (RAND_MAX + 1.0);
//         bb = sc.bit_gen(2.0*r2-1.0);
//         cc = sc.MUX(aa,bb);
//         summention += abs(sc.print(cc) - (r1 + r2) / 2.0);
//     }
//     cout<<"error = "<<summention/10000.0<<endl;

//     ESL layer_0[4];
//     for(size_t i=0; i<4; i++){
//         layer_0[i] = sc.number_gen(0);
//     } 

//     ESL layer_1[10];
//     for(size_t i=0; i<10; i++){
//         layer_1[i] = sc.number_gen(0);
//     } 

//     ESL layer_2[3];
//     for(size_t i=0; i<5; i++){
//         layer_2[i] = sc.number_gen(0);
//     } 

//     double _layer_0[4];
//     double _layer_1[10];
//     double _layer_2[3];

//     double store_layer_1[30][10];

//     float corr_count = 0;
//     float max = 0, max_cand = 0;
//     double temp = 0;

//     //-----------------------------
//     corr_count = 0;
//     for(int k=0; k<30; k++){
//         for(int i=0;i<4;i++){
//             _layer_0[i] = x_test[k][i];
//         }
//         for(int i=0;i<5;i++){
//             _layer_1[i] = 0;
//         }
//         for(int i=0;i<3;i++){
//             _layer_2[i] = 0;
//                   }


//         for(int i=0;i<5;i++){
//             for(int j=0;j<4;j++){
//                 _layer_1[i] += _layer_0[j] * weight_1[i][j];
//             }
//             store_layer_1[k][i]=_layer_1[i];
//             _layer_1[i] += bias_1[i];
//         }
    
//         for(int i=0;i<3;i++){
//             for(int j=0;j<5;j++){
//                 _layer_2[i] += _layer_1[j] * weight_2[i][j];
//             }
//             _layer_2[i] += bias_2[i];
//         }
        
        
        
//         max = -10000;
//         max_cand = 0;

//         for(size_t j=0; j<3;j++){
//             if(_layer_2[j] > max){
//                 max = _layer_2[j];
//                 max_cand = j;
//             }
//             // cout << "layer 2[" << j << "] is :" << _layer_2[j] <<endl;
//             // cout << "max cand is : " << max_cand << endl;
//         }
//         // cout<<max_cand<<endl;

//         if(max_cand == corr_answer[k]){
//             corr_count += 1;
//             // cout<<"correct!!!!!("<<corr_count<<'/'<<k+1<<')'<<endl;
//         }
//         else{
//             // cout<<"wrong!!!!!("<<corr_count<<'/'<<k+1<<')'<<endl;
//         }

//     }
//     cout<<"The rate of correctness is: "<<corr_count/30.0<<endl;
    
//     //----------------------------------------------------------------------------------
//     corr_count = 0;

//     for(int k=0; k<30; k++){
//         for(int i=0;i<4;i++){
//             layer_0[i] = sc.number_gen(x_test[k][i]);
//         }
            
//         for(int i=0;i<5;i++){
//             layer_1[i] = sc.number_gen(0);
//         }

//         for(int i=0;i<3;i++){
//             layer_2[i] = sc.number_gen(0);
//         }


//         for(int i=0;i<5;i++){
//             // for(int j=0;j<4;j++){
//             //     layer_1[i] = sc.NEW_APC(layer_1[i] ,sc.XNOR(layer_0[j],sc.number_gen(weight_1[i][j])));
//             // }
//             layer_1[i] = sc.ESL_Adder_4(sc.XNOR(layer_0[0],sc.number_gen(weight_1[i][0])),sc.XNOR(layer_0[1],sc.number_gen(weight_1[i][1])),sc.XNOR(layer_0[2],sc.number_gen(weight_1[i][2])),sc.XNOR(layer_0[3],sc.number_gen(weight_1[i][3])));
//             // cout<<abs((store_layer_1[k][i]-sc.print(layer_2[i])))<<endl;
//             layer_1[i] = sc.ESL_Adder(layer_1[i],sc.number_gen(bias_1[i]));
//         }
    
//         for(int i=0;i<3;i++){
//             for(int j=0;j<5;j++){
//                 layer_2[i] = sc.ESL_Adder_5(sc.XNOR(layer_1[0],sc.number_gen(weight_2[i][0])),sc.XNOR(layer_1[1],sc.number_gen(weight_2[i][1])),sc.XNOR(layer_1[2],sc.number_gen(weight_2[i][2])),sc.XNOR(layer_1[3],sc.number_gen(weight_2[i][3])),sc.XNOR(layer_1[4],sc.number_gen(weight_2[i][4])));
                
//             }
//             layer_2[i] = sc.ESL_Adder(layer_2[i],sc.number_gen(bias_2[i]));
            
//         }
        
        
//         max = -10000;
//         max_cand = 0;

//         for(size_t j=0; j<3;j++){
//             if(sc.print(layer_2[j]) > max){
//                 max = sc.print(layer_2[j]);
//                 max_cand = j;
//             }
//             // cout << "layer 2[" << j << "] is :" << sc.print(layer_2[j]) <<endl;
//             // cout << "max cand is : " << max_cand << endl;
//         }
//         // cout<<max_cand<<endl;

//         if(max_cand == corr_answer[k]){
//             corr_count += 1;
//             // cout<<"correct!!!!!("<<corr_count<<'/'<<k+1<<')'<<endl;
//         }
//         else{
//             // cout<<"wrong!!!!!("<<corr_count<<'/'<<k+1<<')'<<endl;
//         }

//     }
//     cout<<"The rate of correctness is: "<<corr_count/30.0<<endl;
    
//     return 0;
// }