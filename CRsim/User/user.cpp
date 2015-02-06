//
//  user.cpp
//  CRsim
//
//  Created by Ji on 14-10-5.
//  Copyright (c) 2014年 lj. All rights reserved.
//

#include "user.h"

void User::printPktInterval()
{
    int sum = 0;
    for(int i = 1; i < allDataPkt.size(); i++){
        int tmp = allDataPkt[i].arrivalTimeSlot - allDataPkt[i-1].arrivalTimeSlot;
        sum += tmp;
        cout<<tmp<<' ';
    }
    cout<<endl<<sum/(allDataPkt.size()-1)<<endl;
}
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
#ifdef SET_RANDOM_PU_PKT_LEN
//        p.len = my_randint(1, PKT_MAX_LEN_PU);
        p.len = my_randint(PKT_MIN_LEN_PU, pkt_max_len);
#endif
        
#ifdef SET_STATIC_PU_PKT_LEN
        p.len = pkt_max_len;
#endif
        allDataPkt.push_back(p);
        double tmp = myRandomExp(arrRate);
        st += tmp;
    }
    for(int i = 0; i < allDataPkt.size(); i++){
        allDataPkt[i].arrivalTimeSlot = (int) (allDataPkt[i].arrivalTime / TIME_SLOT_LEN);
//        cout<<allDataPkt[i].arrivalTimeSlot<<' ';
    }
//    cout<<endl<<endl;
//    printPktInterval();
}
