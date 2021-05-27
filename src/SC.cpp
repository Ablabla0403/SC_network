
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
    int count = 0;
    for(size_t i = 0; i < bit_len; i++){
        if(MUX_output[i] = true){
            count += 2;
        }
        else{
            if(count > 0){
                MUX_output[i] = true;
                count --;
            }
        }
    }
    return MUX_output;
}

bool* SC::MUX_4(bool* a, bool* b,bool* c, bool* d){

    bool *MUX_output = new bool[bit_len];
    for(size_t i = 0; i < bit_len; i++){
        
        double r = (double)rand() / (RAND_MAX + 1.0);
        if(r >= 0.75){
            MUX_output[i] = a[i];
        }
        else if(r<0.75 && r >= 0.5){
            MUX_output[i] = b[i];
        }
        else if(r<0.5 && r >= 0.25){
            MUX_output[i] = c[i];
        }
        else if(r<0.25 && r >= 0.0){
            MUX_output[i] = d[i];
        }
    }
    int count = 0;
    for(size_t i = 0; i < bit_len; i++){
        if(MUX_output[i] = true){
            count += 4;
        }
        else{
            if(count > 0){
                MUX_output[i] = true;
                count --;
            }
        }
    }
    return MUX_output;
}

bool* SC::MUX_5(bool* a, bool* b,bool* c, bool* d,bool* e){
    int count = 0;

    bool *MUX_output = new bool[bit_len];
    for(size_t i = 0; i < bit_len; i++){
        
        double r = (double)rand() / (RAND_MAX + 1.0);
        if(r >= 0.8){
            MUX_output[i] = a[i];
        }
        else if(r<0.8 && r >= 0.6){
            MUX_output[i] = b[i];
        }
        else if(r<0.6 && r >= 0.4){
            MUX_output[i] = c[i];
        }
        else if(r<0.4 && r >= 0.2){
            MUX_output[i] = d[i];
        }
        else if(r<0.2 && r >= 0.0){
            MUX_output[i] = e[i];
        }
    }
    for(size_t i = 0; i < bit_len; i++){
        if(MUX_output[i] = true){
            count += 5;
        }
        else{
            if(count > 0){
                MUX_output[i] = true;
                count --;
            }
        }
    }
    return MUX_output;
}

ESL SC::ESL_Multiplier(ESL a, ESL b){
    ESL out;
    out.h = new bool[bit_len];
    out.l = new bool[bit_len];
    out.h = XNOR(a.h,b.h);
    out.l = XNOR(a.l,b.l);
    return out;
}

ESL SC::ESL_Adder(ESL a, ESL b){
    ESL out;
    out.h = new bool[bit_len];
    out.l = new bool[bit_len];
    out.h = MUX(XNOR(a.h,b.l),XNOR(a.l,b.h));
    out.l = MUX(XNOR(a.l,b.l),bit_gen(0));
    
    return out;
}

ESL SC::ESL_Adder_4(ESL a, ESL b,ESL c,ESL d){
    ESL out;
    out.h = new bool[bit_len];
    out.l = new bool[bit_len];
    out.h = MUX_4(XNOR_4(a.h,b.l,c.l,d.l),XNOR_4(a.l,b.h,c.l,d.l),XNOR_4(a.l,b.l,c.h,d.l),XNOR_4(a.l,b.l,c.l,d.h));
    out.l = MUX_4(XNOR_4(a.l,b.l,c.l,d.l),bit_gen(0),bit_gen(0),bit_gen(0));
    
    return out;
}

ESL SC::ESL_Adder_5(ESL a, ESL b,ESL c,ESL d,ESL e){
    ESL out;
    out.h = new bool[bit_len];
    out.l = new bool[bit_len];
    out.h = MUX_5(XNOR_5(a.h,b.l,c.l,d.l,e.l),XNOR_5(a.l,b.h,c.l,d.l,e.l),XNOR_5(a.l,b.l,c.h,d.l,e.l),XNOR_5(a.l,b.l,c.l,d.h,e.l),XNOR_5(a.l,b.l,c.l,d.l,e.h));
    out.l = MUX_5(XNOR_5(a.l,b.l,c.l,d.l,e.l),bit_gen(0),bit_gen(0),bit_gen(0),bit_gen(0));
    
    return out;
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

bool SC::CMP(bool* a){
    double r = (double)rand() / (RAND_MAX );
    int counter = 0;
    for (int i = 0; i < bit_len; i++){
        if (a[i] == 1){
            counter ++;
        }
        else{
            counter --;
        }
    }
    if(counter > 0){
        return true;
    }
    else{
        return false;
    }
}

bool SC::CMP(ESL a){
    if(CMP(a.h) > 0 && CMP(a.l) > 0){
        return true;
    }
    else if(CMP(a.h) < 0 && CMP(a.l) < 0){
        return true;
    } 
    else{
        return false;
    }
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

bool* SC::lin_gain(bool* a, int gain, int tmp){

    float K = 0;

    if(gain == 2){
        K = -0.35;
    } 
    else if(gain == 3){
        K = 0;
    }     
    else if(gain == 4){
        K = 0.25;
    }  
    else if(gain == 5){
        K = 0.25;
    }  
    else if(gain == 8){
        K = 0.78;
    }
    else{
        cerr << "wrong gain!!";
    } 
    
    bool* z = new bool[bit_len];
    int S_min = 0;
    int S_max = bit_len-1; 
    int S_bound = bit_len/2;

    int S = S_bound;
    bool* k = bit_gen(K);

    for(size_t i=0; i<bit_len; i++){
        if(S >= S_bound){
            if(S == S_max){
                if(a[i] == 1){
                    S = S_max;
                }
                else{
                    S = S-1;
                }   
            }
            else{
                if(a[i] == 1 and k[i] == 0){
                     S = S;
                }
                else if(a[i] == 1 and k[i] == 1){
                    S = S+1;
                }  
                else if(a[i] == 0){
                    S = S-1;
                }  
            }
                
        }
        else{
            if(S == S_min){
                if(a[i] == 0){
                    S = S_min;
                }
                else{
                    S = S+1;
                } 
            }
                
            else{
                if(a[i] == 0 and k[i] == 0){
                    S = S;
                }  
                else if(a[i] == 0 and k[i] == 1){
                    S = S-1;
                }
                else if(a[i] == 1){
                    S = S+1;
                } 
            }
        }
            
        if(S >= S_bound){
            z[i] = 1;
        }
        else{
            z[i] = 0;
        }
    }
    return z;
}

bool* SC::MUX_general(vector<bool*> bit_streams){
    bool* output = new bool[bit_len];
    float r;
    for(int i = 0; i < bit_len; ++i){
        r = int((float)rand() / (RAND_MAX) * (float)bit_streams.size()) % bit_streams.size();
        output[i] = bit_streams[r][i];
    }
    return output;
}