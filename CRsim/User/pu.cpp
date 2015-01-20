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
    initTrafficOfEachTimeSlot();
    initLocationRandom();
}

void PU::initTrafficOfEachTimeSlot()
{
//    for(int i = 0; i < allDataPkt.size(); i++){
//        cout<<allDataPkt[i].len<<' ';
//    }
    while(!pktTransQueue.empty()){
        pktTransQueue.pop();
    }
    for(int i = 0; i < TOTAL_TIME_SLOT+5; i++){
        chanOfEachTimeSlot[i] = -1;
    }
    ifTransmitting = false;
    int cur = 0;
    for(int t = 0; t < TOTAL_TIME_SLOT; t++){
        if(ifTransmitting){
            chanOfEachTimeSlot[t] = pktTransQueue.front().onWhichChan;
        }
        if(ifTransmitting){
//            cout<<t<<' '<<chanOfEachTimeSlot[t]<<endl;
        }
        if(cur < allDataPkt.size() && t >= allDataPkt[cur].arrivalTimeSlot){
            pktTransQueue.push(allDataPkt[cur]);
            cur++;
//            cout<<cur<<endl;
        }
        if(ifTransmitting == false && !pktTransQueue.empty()){
            ifTransmitting = true;
            pktTransQueue.front().startTransTimeSlot = t;
            int tmp = my_randint(1, TOTAL_CHAN_NUM);
            pktTransQueue.front().onWhichChan = tmp;
            chanOfEachTimeSlot[t] = tmp;
        }
        if(ifTransmitting == true && t - pktTransQueue.front().startTransTimeSlot >= pktTransQueue.front().len - 1){
//            cout<<t<<endl;
            ifTransmitting = false;
            pktTransQueue.pop();
        }
    }
}

void PU::initLocationRandom()
{
    int x = my_randint(0, SIDE_LENGTH);
    int y = my_randint(0, SIDE_LENGTH);
    location = make_pair((double)x, (double)y);
}
