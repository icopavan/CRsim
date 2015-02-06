//
//  pu.h
//  CRsim
//
//  Created by Ji on 14-10-6.
//  Copyright (c) 2014年 lj. All rights reserved.
//

#ifndef __CRsim__pu__
#define __CRsim__pu__

#include "include.h"
#include "user.h"

class PU: public User{
public:
    int licensedChan;
    int curComePktID;
    int chanOfEachTimeSlot[TOTAL_TIME_SLOT+10];//equal to -1 if pu is inactive
    bool ifTransmitting;

    
    void initLocationRandom();
    
    PU();
};

#endif /* defined(__CRsim__pu__) */
