//
//  en_jump_stay.h
//  CRsim
//
//  Created by Ji on 14-10-3.
//  Copyright (c) 2014年 lj. All rights reserved.
//

#ifndef __CRsim__en_jump_stay__
#define __CRsim__en_jump_stay__

#include "include.h"
#include "jump_stay.h"

class EnJsHop : public JsHop{
public:
    EnJsHop();
    EnJsHop(int cur_avai_n);
    EnJsHop(int cur_chan_n, vI &avai);
    virtual void init_seq();// Init the channel hopping sequence
    virtual int getChanAtTimeT(int t); //Get the channel to hop to at time t if it needs the available set;
    virtual int getChanAtTimeT(int t, const vI &avai); //Get the channel to hop to at time t;
    virtual int getChanAtTimeTBeforeReplace(int t); 
};

#endif /* defined(__CRsim__en_jump_stay__) */
