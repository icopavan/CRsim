//
//  pu.cpp
//  CRsim
//
//  Created by Ji on 14-10-6.
//  Copyright (c) 2014年 lj. All rights reserved.
//

#include "pu.h"

void PU::getTrafficOfEachTimeSlot()
{
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
        cout<<chanOfEachTimeSlot[t]<<' '<<ifTransmitting<<endl;
        if(cur < allDataPkt.size() && t == allDataPkt[cur].arrivalTimeSlot){
            pktTransQueue.push(allDataPkt[cur]);
            cur++;
        }
        if(ifTransmitting == false && !pktTransQueue.empty()){
            ifTransmitting = true;
            pktTransQueue.front().startTransTimeSlot = t;
            int tmp = my_randint(1, TOTAL_CHAN_NUM);
            pktTransQueue.front().onWhichChan = tmp;
            chanOfEachTimeSlot[t] = tmp;
        }
        if(ifTransmitting == true && t - pktTransQueue.front().startTransTimeSlot >= pktTransQueue.front().len - 1){
            ifTransmitting = false;
            pktTransQueue.pop();
        }
    }
}