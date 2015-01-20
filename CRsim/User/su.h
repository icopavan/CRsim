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
    
    vI getAvaiChanRandom(int _chan_n);
    vI getAvaiChanRandom();
    void getNeighRandom();
    void initAllCognitiveRadio(int n);
};

#endif /* defined(__CRsim__su__) */
