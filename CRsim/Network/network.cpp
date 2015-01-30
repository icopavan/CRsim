//
//  network.cpp
//  CRsim
//
//  Created by Ji on 14-10-6.
//  Copyright (c) 2014年 lj. All rights reserved.
//

#include "network.h"

CRNetwork::CRNetwork()
{
    this->totalChanNum = TOTAL_CHAN_NUM;
    this->suNum = SU_NUM;
    this->simTimeSlot = TOTAL_TIME_SLOT;
    this->timeslotLength  = TIME_SLOT_LEN;
    memset(ChanAllocToPuCount, 0, sizeof(ChanAllocToPuCount));
    AvaiChanNumForPU = TOTAL_CHAN_NUM;
}


void CRNetwork:: startSimulation()
{
    
}