//
//  sector_hop.cpp
//  CRsim
//
//  Created by Ji on 15/3/24.
//  Copyright (c) 2015年 lj. All rights reserved.
//

#include "sector_hop.h"

SectorHop:: SectorHop(int n)
{
    sectorNum = n;
    curIndex = startIndex = -1;
    hopCount = 0;
}

SectorHop:: SectorHop()
{
    curIndex = startIndex = -1;
    hopCount = 0;
}

int SectorHop:: getIndexAtTimeT(int t)
{
    return 0;
}

int SectorHop:: senderGetNextIndex()
{
    if(curIndex == -1){
        curIndex = startIndex = my_randint(0, sectorNum-1);
        hopCount = 1;
        return curIndex;
    }
    if(hopCount <= sectorNum*sectorNum){
        if(hopCount % sectorNum == 1) curIndex += 2;
        else curIndex++;
        hopCount++;
    }
    else{
        curIndex++;
        hopCount++;
    }
    if(curIndex > sectorNum-1){
        curIndex -= sectorNum-1;
    }
    return curIndex;
}

int SectorHop:: receiverGetNextIndex()
{
    if(curIndex == -1){
        curIndex = startIndex = my_randint(0, sectorNum-1);
        hopCount = 1;
        return curIndex;
    }
    else{
        curIndex++;
        hopCount++;
        if(curIndex > sectorNum-1){
            curIndex -= sectorNum-1;
        }
    }
    return curIndex;
}

int SectorHop:: getNextIndex()
{
    if(role == SEND) return senderGetNextIndex();
    else return receiverGetNextIndex();
}
