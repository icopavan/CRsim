//
//  su.h
//  CRsim
//
//  Created by Ji on 14-10-6.
//  Copyright (c) 2014年 lj. All rights reserved.
//

#ifndef __CRsim__su__
#define __CRsim__su__

#include "include.h"
#include "user.h"
#include "chan_hop.h"
#include "my_seq.h"
#include "cognitive_radio.h"

class SU: public User{
public:
    vector<CognitiveRadio> allCR;
    vI channelToSense;
    int chanAvaiTimeCount[TOTAL_CHAN_NUM+5];
    int chanAvaiTimeTotal[TOTAL_CHAN_NUM+5];
    int chanCurTotalAvaiTime[TOTAL_CHAN_NUM+5];
    int chanAvaiRoundCount[TOTAL_CHAN_NUM+5];
    int chanUsedTimeCount[TOTAL_CHAN_NUM+5];
    int allChanConAvaiTime[TOTAL_CHAN_NUM+2];
    int lastStayChan;
    int alreadyStayTime;
    
    
    vI getAvaiChanRandom(int _chan_n);
    vI getAvaiChanRandom();
    void getNeighRandom();
    void initAllCognitiveRadio(int n);
};

#endif /* defined(__CRsim__su__) */
