//
//  channel.cpp
//  CRsim
//
//  Created by Ji on 15/2/25.
//  Copyright (c) 2015年 lj. All rights reserved.
//

#include "channel.h"

bool cmpID(const CRchannel &x, const CRchannel &y)
{
    return x.ID < y.ID;
};

bool cmpConAvaiTime(const CRchannel &x, const CRchannel &y)
{
    return x.curConAvaiTime < y.curConAvaiTime;
};

bool cmpConAvaiTimeReverse(const CRchannel &x, const CRchannel &y)
{
    if(x.curConAvaiTime == y.curConAvaiTime){
        return x.ID < y.ID;
    }
    else{
        return x.curConAvaiTime > y.curConAvaiTime;
    }
}

