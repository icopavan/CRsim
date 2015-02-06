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
    avaiChanNumForPU = TOTAL_CHAN_NUM;
    memset(chanAllocToPuCount, 0, sizeof(chanAllocToPuCount));
    initAllPU();
    initAllPuTrafficEachTime();
}

void CRNetwork:: initAllPU()
{
    allPU.clear();
    for(int i = 0; i < PU_NUM; i++){
        PU p;
        allPU.push_back(p);
    }
}

void CRNetwork:: initAllPuTrafficEachTime()
{
    for(int i = 0; i < PU_NUM; i++){
        PU &pu = allPU[i];
        pu.ifTransmitting = false;
        pu.curComePktID = 0;
        while(!pu.pktTransQueue.empty()){
            pu.pktTransQueue.pop();
        }
        for(int j = 0; j < TOTAL_TIME_SLOT+2; j++){
            pu.chanOfEachTimeSlot[j] = -1;
        }
    }
    for(int t = 0; t < TOTAL_TIME_SLOT+1; t++){
//        cout<<"t: "<<t<<' '<<"avai chan: "<<avaiChanNumForPU<<endl;
        for(int i = 0; i < PU_NUM; i++){
            PU &pu = allPU[i];
            pu.chanOfEachTimeSlot[t] = pu.curStayChan;
            if(pu.curComePktID < pu.allDataPkt.size() && t >= pu.allDataPkt[pu.curComePktID].arrivalTimeSlot){
                pu.pktTransQueue.push(pu.allDataPkt[pu.curComePktID]);
                pu.curComePktID++;
            }
            if(pu.ifTransmitting == false && !pu.pktTransQueue.empty()){
                int tmp_chan;
#ifdef ALLOC_RANDOM_CHAN_PU
                tmp_chan = allocChanRandomToPU();
#endif
#ifdef ALLOC_UNUSED_CHAN_PU
                tmp_chan = allocChanUnUsedToPU();
#endif
                if(tmp_chan > 0){
                    pu.ifTransmitting = true;
                    pu.pktTransQueue.front().startTransTimeSlot = t;
                    pu.pktTransQueue.front().onWhichChan = tmp_chan;
                    pu.chanOfEachTimeSlot[t] = tmp_chan;
                    pu.curStayChan = tmp_chan;
                }
            }
            if(pu.ifTransmitting == true && t - pu.pktTransQueue.front().startTransTimeSlot >= pu.pktTransQueue.front().len - 1){
                pu.ifTransmitting = false;
                pu.pktTransQueue.pop();
                puReturnAllocChan(pu.curStayChan);
                pu.curStayChan  = -1;
            }
        }
    }
}

int CRNetwork:: allocChanRandomToPU()
{
    int tmp_chan = my_randint(1, TOTAL_CHAN_NUM);
    chanAllocToPuCount[tmp_chan]++;
    avaiChanNumForPU--;
    return tmp_chan;
}

int CRNetwork:: allocChanUnUsedToPU()
{
    if(avaiChanNumForPU > 0){
        while(true){
            int tmp = my_randint(1, TOTAL_CHAN_NUM);
            if(chanAllocToPuCount[tmp] == 0){
                chanAllocToPuCount[tmp]++;
                avaiChanNumForPU--;
//                printArrayFrom1(chanAllocToPuCount, TOTAL_CHAN_NUM);
                return tmp;
            }
        }
    }
    return 0;
}

void CRNetwork:: puReturnAllocChan(int _chan_id)
{
    chanAllocToPuCount[_chan_id]--;
    avaiChanNumForPU++;
}

void CRNetwork:: initAllSU()
{
}

void CRNetwork:: startSimulation()
{
    
}