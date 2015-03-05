//
//  chan_hop.cpp
//  CRsim
//
//  Created by Ji on 14-10-4.
//  Copyright (c) 2014年 lj. All rights reserved.
//

#include "chan_hop.h"

ChanHop:: ChanHop()
{
    M = TOTAL_CHAN_NUM;
    avai_chan.clear();
    for(int i = 1; i <= M; i++){
        avai_chan.push_back(i);
    }
    avai_chan_n = M;
}

ChanHop:: ChanHop(int chan_n)
{
    M = chan_n;
    avai_chan.clear();
    for(int i = 1; i <= M; i++){
        avai_chan.push_back(i);
    }
    avai_chan_n = M;
}

ChanHop:: ChanHop(int chan_n, vI &avai)
{
    M = chan_n;
    avai_chan = avai;
    avai_chan_n = (int)avai_chan.size();
}

void ChanHop:: init_seq()
{
    hop_seq.clear();
    hop_seq.push_back(-1); //Make the idex start from 1
    return;
}

int ChanHop:: getChanAtTimeT(int t)
{
    cout<<"shit"<<endl;
    curChan = 1;
    return curChan;
}

