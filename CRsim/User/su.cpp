//
//  su.cpp
//  CRsim
//
//  Created by Ji on 14-10-6.
//  Copyright (c) 2014年 lj. All rights reserved.
//

#include "su.h"
#include "my_math.h"
#include "my_fun.h"
#include "network.h"

vI SU::getAvaiChanRandom(int _chan_n)
{
    vI ans;
    this->avaiChanNum = _chan_n * CHAN_AVAI_RATIO;
    int tmp = 0;
    while(tmp < avaiChanNum){
        int t1 = my_randint(1, _chan_n);
        if(!vectorFind(ans, t1)){
            ans.push_back(t1);
            tmp++;
        }
    }
    sort(ans.begin(), ans.end());
    return  ans;
}

vI SU::getAvaiChanRandom()
{
    return getAvaiChanRandom(TOTAL_CHAN_NUM);
}

void SU:: initAllCognitiveRadio(int numOfCR)
{
    for(int i = 0; i < numOfCR; i++){
        CognitiveRadio tmp;
        this->allCR.push_back(tmp);
    }
}
