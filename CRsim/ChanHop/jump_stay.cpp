//
//  jump_stay.cpp
//  CRsim
//
//  Created by Ji on 14-10-3.
//  Copyright (c) 2014年 lj. All rights reserved.
//

#include "jump_stay.h"
#include "my_math.h"
#include "debug.h"

JsHop:: JsHop(): ChanHop()
{
    init_seq();
}

JsHop::JsHop(int chan_n): ChanHop(chan_n)
{
    init_seq();
}

void JsHop:: init_prime_num()
{
    memset(prime, 0, sizeof(prime));
    for(int i = 2; i < M*2; i++){
        if(prime[i] == 0){
            for(int j = 2*i; j < M*2; j += i){
                prime[j] = 1;
            }
        }
    }
}

void JsHop::  init_seq()
{
    init_prime_num();
    for(int i = M; i < 2*M; i++){
        if(prime[i] == 0) {
            P = i;
            break;
        }
    }
    i0 = my_randint(1, M);
    r0 = my_randint(1, M);
}

int JsHop:: getChanAtTimeT(int t)
{
    int n = t / (3*P);
    int i;
    int r00 = (r0 + n - 1)%M + 1; //get the new r0
    if(n < 2*P){
        i = (i0 + n*r00 - 1) % P + 1;
    }
    else{
        i = r00;
    }
    if(i > M){
        i = (i-1)%M + 1;
    }
    curChan = i;
    return i;
}

int JsHop:: getChanAtTimeT(int t, const vI &avai)
{
    curChan = getChanAtTimeT(t);
    return curChan;
}
