//
//  sector_hop.h
//  CRsim
//
//  Created by Ji on 15/3/24.
//  Copyright (c) 2015年 lj. All rights reserved.
//

#ifndef __CRsim__sector_hop__
#define __CRsim__sector_hop__

#include "include.h"
#include "chan_hop.h"
#include "my_math.h"

class SectorHop{
public:
    SEND_OR_RECEIVE sendOrRev;
    int sectorNum;
    int startIndex;
    int hopCount;
    int curIndex;
    
    int getIndexAtTimeT(int t);
    int getCurIndex();
    int senderGetCurIndex();
    int receiverGetCurIndex();
    
    SectorHop(int n);
    SectorHop(int n, SEND_OR_RECEIVE _role);
    SectorHop();
    
};
#endif /* defined(__CRsim__sector_hop__) */
