//
//  my_su.h
//  CRsim
//
//  Created by Ji on 14-10-7.
//  Copyright (c) 2014年 lj. All rights reserved.
//

#ifndef __CRsim__my_su__
#define __CRsim__my_su__

#include "include.h"
#include "su.h"
#include "my_seq.h"
#include "graph.h"
#include "max_flow.h"
#include "jump_stay.h"

class MySU: public SU{
private:
    void binaryRepresent(int n, int ans[]);
public:
    int curState;
    int usedChanNum;
    int notUsedCrNum;
    vI usedChan;
    vI stillAvaiChan;
    vI newAllocChan;
    vI newAllocChanRandom;
    int sendOrReceiveAlloc[CR_NUM+2];
    
    vector<vI> avaiChanOnSs;
    
};

#endif /* defined(__CRsim__my_su__) */
