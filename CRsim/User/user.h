//
//  user.h
//  CRsim
//
//  Created by Ji on 14-10-5.
//  Copyright (c) 2014年 lj. All rights reserved.
//

#ifndef __CRsim__user__
#define __CRsim__user__

#include "include.h"
#include "chan_hop.h"
#include "my_math.h"
#include "packet.h"

class User{
public:
    pair<double, double> location;
    vI allChan;
    vI avaiChan;
    vector<DataPacket> allDataPkt;
    queue<DataPacket> pktTransQueue;
    
    int avaiChanNum;
    int curStayChan;
    int ID; //from 1 to the number of total SUs
    SEND_OR_RECEIVE sendOrReceive;
    
    double init_sys_t; // the initial time of each user
    double init_sys_slot; //the initial time slot of each user
    double st_sys_t; //the time to start simulation
    double st_sys_slot; // the time slot to start simu
    double cur_sys_t;//current system time
    double pktArrivalRate;
    int curSysTimeSlot;//current system time slot
    vI neighborPU; //neighbors
    vI neighborSU; //neighbors
    double transRange; //transmission range
    double transPower; //power,
    
    ChanHop *chanHop;
    
    void initAllPktArrivalTime(double arrRate);
    void initAllPkt(double arrRate, int pkt_max_len);
};

#endif /* defined(__CRsim__user__) */
