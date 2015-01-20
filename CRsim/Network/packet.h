//
//  packet.h
//  CRsim
//
//  Created by Ji on 15/1/20.
//  Copyright (c) 2015年 lj. All rights reserved.
//

#ifndef __CRsim__packet__
#define __CRsim__packet__

#include "include.h"

class DataPacket{
public:
    int ID; // id starts from 0
    int len; //length time slot
    double arrivalTime; //arrival time
    int arrivalTimeSlot; //arrival time slot;
    int startTransTimeSlot; //start transmission time slot;
    int onWhichChan;
};

#endif /* defined(__CRsim__packet__) */
