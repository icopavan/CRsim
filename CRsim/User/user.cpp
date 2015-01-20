//
//  user.cpp
//  CRsim
//
//  Created by Ji on 14-10-5.
//  Copyright (c) 2014年 lj. All rights reserved.
//

#include "user.h"

void User:: initAllPkt(double arrRate, int pkt_max_len)
{
    allDataPkt.clear();
    double st = myRandomExp(arrRate);
    int curID = 0;
    while(true){
        if(st - TOTAL_TIME_SLOT * TIME_SLOT_LEN > EPS){
            break;
        }
        DataPacket p;
        p.ID = curID++;
        p.arrivalTime = st;
        p.len = my_randint(1, pkt_max_len);
        allDataPkt.push_back(p);
        double tmp = myRandomExp(arrRate);
        st += tmp;
    }
    for(int i = 0; i < allDataPkt.size(); i++){
        allDataPkt[i].arrivalTimeSlot = (int) (allDataPkt[i].arrivalTime / TIME_SLOT_LEN);
    }
}
