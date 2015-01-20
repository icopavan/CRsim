//
//  jump_stay.h
//  CRsim
//
//  Created by Ji on 14-10-3.
//  Copyright (c) 2014年 lj. All rights reserved.
//

#ifndef __CRsim__jump_stay__
#define __CRsim__jump_stay__

#include "include.h"
#include "chan_hop.h"

class JsHop: public ChanHop{
private:
    
public:
    int P;
    int r0;
    int i0;
    int prime[TOTAL_CHAN_NUM*3];
    
    JsHop();
    JsHop(int chan_n);
    void init_prime_num();
    virtual void init_seq();// Init the channel hopping sequence
    virtual int get_chan_t(int t); //Get the channel to hop to at time t;

};

extern JsHop returnOneJsHopObj();
extern  JsHop returnOneJsHopObj(int cur_chan_n);
#endif /* defined(__CRsim__jump_stay__) */
