//
//  my_seq.h
//  CRsim
//
//  Created by Ji on 14-10-3.
//  Copyright (c) 2014年 lj. All rights reserved.
//

#ifndef __CRsim__my_seq__
#define __CRsim__my_seq__

#include "include.h"
#include "chan_hop.h"

class MyHop: public ChanHop{
public:
    int st_hop_id; // The start seq index, starts with 1
    int st_id_rnd; //The start seq index in current round, starts with 1
    int hop_count;//The number of hops in a round
    int rnd_count;//The number of finished round
    int rnd_st_t;// The time a round starts

    MyHop();//the default total channel bumber in global.h
    MyHop(int cur_chan_n);//total channel number
    MyHop(int cur_chan_n, vI &avai);//total channel number, available channel set
    void init_my_hop(int t, int st_id); //t is the time start the hop, id is the index of seq to start
    void get_hop_para(int t);// get the parameters of my hopping at time t
    virtual void init_seq();// Init the channel hopping sequence
    virtual int getChanAtTimeT(int t); //Get the channel to hop to at time t if it needs the available set;
};

extern MyHop returnOneMyHopObj();
extern  MyHop returnOneMyHopObj(int cur_chan_n);
extern MyHop returnOneMyHopObj(int cur_chan_n, vI &avai);

#endif /* defined(__CRsim__my_seq__) */
