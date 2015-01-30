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
        if(cur < allDataPkt.size() && t >= allDataPkt[cur].arrivalTimeSlot){
            pktTransQueue.push(allDataPkt[cur]);
            cur++;
        }
        if(ifTransmitting == false && !pktTransQueue.empty()){
            ifTransmitting = true;
            pktTransQueue.front().startTransTimeSlot = t;
            int tmp_chan = getChanUnUsed();
            pktTransQueue.front().onWhichChan = tmp_chan;
            chanOfEachTimeSlot[t] = tmp_chan;
            curStayChan = tmp_chan;
        }
        if(ifTransmitting == true && t - pktTransQueue.front().startTransTimeSlot >= pktTransQueue.front().len - 1){
            ifTransmitting = false;
            pktTransQueue.pop();
            returnAllocChan(curStayChan);
        }
    }
}

int PU:: getChanRandom()
{
    int tmp_chan = my_randint(1, TOTAL_CHAN_NUM);
    ChanAllocToPuCount[tmp_chan]++;
    return tmp_chan;
}

int PU:: getChanUnUsed()
{
    if(AvaiChanNumForPU > 0){
        while(true){
            int tmp = my_randint(1, TOTAL_CHAN_NUM);
            if(ChanAllocToPuCount[tmp] == 0){
                ChanAllocToPuCount[tmp]++;
                AvaiChanNumForPU--;
                return tmp;
            }
        }
    }
    return 0;
}

void PU:: returnAllocChan(int _chan_id)
{
    ChanAllocToPuCount[_chan_id]--;
    AvaiChanNumForPU++;
}

void PU::initLocationRandom()
{
    int x = my_randint(0, SIDE_LENGTH);
    int y = my_randint(0, SIDE_LENGTH);
    location = make_pair((double)x, (double)y);
}
