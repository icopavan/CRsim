//
//  chan_hop.h
//  CRsim
//
//  Created by Ji on 14-10-4.
//  Copyright (c) 2014年 lj. All rights reserved.
//

#ifndef __CRsim__chan_hop__
#define __CRsim__chan_hop__

#include "include.h"

class ChanHop{
public:
    int M;
    int avai_chan_n; //The number of the available channels
    int curChan; //current channel to hop
    int st_hop_t;//The time to start the hopping
    vI avai_chan; //Available channel set
    vI hop_seq;//Hopping sequence, index from 1
   
    ChanHop();
    ChanHop(int chan_n);
    ChanHop(int chan_n, vI &avai);
    virtual void init_seq();// Init the channel hopping sequence
    virtual int getChanAtTimeT(int t) = 0; //Get the channel to hop to at time t;
    virtual int getChanAtTimeT(int t, const vI &avai) = 0; //Get the channel to hop to at time t;
    virtual int getChanAtTimeTBeforeReplace(int t) = 0;
};

#endif /* defined(__CRsim__chan_hop__) */
