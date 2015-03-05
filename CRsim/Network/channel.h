//
//  channel.h
//  CRsim
//
//  Created by Ji on 15/2/25.
//  Copyright (c) 2015年 lj. All rights reserved.
//

#ifndef __CRsim__channel__
#define __CRsim__channel__

#include "include.h"
#include "debug.h"
#include "my_fun.h"

class CRchannel{
public:
    int ID;
    int curConAvaiTime;
    bool ifAvai;
    bool ifAvaiPreTime;
    vector<int> allConAvaiTime;
    double averageConAvaiTime;
    
    void printSortedAllConAvaiTime();
    double getAverConAvaiTime();
};

extern bool cmpID(const CRchannel &x, const CRchannel &y);

extern bool cmpConAvaiTime(const CRchannel &x, const CRchannel &y);

extern bool cmpConAvaiTimeReverse(const CRchannel &x, const CRchannel &y);

#endif /* defined(__CRsim__channel__) */
