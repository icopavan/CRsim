//
//  network.h
//  CRsim
//
//  Created by Ji on 14-10-6.
//  Copyright (c) 2014年 lj. All rights reserved.
//

#ifndef __CRsim__network__
#define __CRsim__network__

#include "include.h"
#include "su.h"
#include "pu.h"
#include "debug.h"

class CRNetwork{
public:
    vector<SU> allSU;
    vector<PU> allPU;
    int totalChanNum; //total number of channels;
    double simTime;
    double timeslotLength;
    int simTimeSlot;
    int suNum;
    int puNum;
    int chanAllocToPuCount[TOTAL_CHAN_NUM+5];
    int avaiChanNumForPU;
    
    void initAllPU();
    void initAllPuTrafficEachTime();
    virtual void initAllSU();
    int allocChanRandomToPU();
    int allocChanUnUsedToPU();
    void puReturnAllocChan(int _chan_id);
    
    CRNetwork();
    virtual void initSimulation();
    virtual void startSimulation();
};
#endif /* defined(__CRsim__network__) */
