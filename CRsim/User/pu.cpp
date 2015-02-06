//
//  pu.cpp
//  CRsim
//
//  Created by Ji on 14-10-6.
//  Copyright (c) 2014年 lj. All rights reserved.
//

#include "pu.h"
#include "debug.h"

PU::PU()
{
    initAllPkt(PKT_ARR_RATE_PU, PKT_MAX_LEN_PU);
    initLocationRandom();
}

void PU::initLocationRandom()
{
    int x = my_randint(0, SIDE_LENGTH);
    int y = my_randint(0, SIDE_LENGTH);
    location = make_pair((double)x, (double)y);
}
