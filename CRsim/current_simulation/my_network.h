//
//  my_network.h
//  CRsim
//
//  Created by Ji on 14-10-7.
//  Copyright (c) 2014年 lj. All rights reserved.
//

#ifndef __CRsim__my_network__
#define __CRsim__my_network__

#include "include.h"
#include "network.h"
#include "my_su.h"
#include "my_split_spec.h"
#include "debug.h"
#include "my_seq.h"
#include "jump_stay.h"
#include "en_jump_stay.h"
#include "my_fun.h"
#include "graph.h"
#include "max_clique.h"

class MyNetwork: public CRNetwork{
public:
    int segNum;
    int chanInSeg[100][CR_NUM+2];
    int curResult1;
    int curResult2;
    int ifRendezvous1;
    int ifRendezvous2;
    pair<int, int> rendPair;
    vector<MySU> jsSu;
    
    virtual void initAllSU();
    void initSuChanHop();
    void initSuAvaiChan();
    void jumpStayRend(int t);
    void enhanceJumpStayRend(int t);
    void enhanceJumpStayConAvaiTimeRend(int t);
    void jsRadomRepRend(int t);
    void jsRandomRepRandomSenseRend(int t);
    void jsKeepRepRend(int t);
    void conAvaiTimeRend(int t);
    void conAvaiTimeRandRend(int t);
    void jsConAvaiTimeRandRend0(int t);
    void jsConAvaiTimeRandRend1(int t);
    void jsConAvaiTimeRandRend2(int t);
    void pureRandomRend(int t);
    
    void getSUsCurAvaiChan(int t);
    void getCurConAvaiChan();
    void printTwoSUsConAvaiTime();
    void printAllChanConAvaiTime();
    double calAverConAvaiTime();
    double calConAvaiChanAverConAvaiTime();
    void getCurAllChanConAvaiTime();
    void getCommonAvaiRatio();
    void printSimulationResults();
    void calChanEachTime();
    void calMaxProComAfterCut();
    
    //considering directional antenna
    void initAllSuSector();
    void initSuNeighborSector(MySU &su);
    void initSuNeighborPU(MySU &su);
    void getAvaiChanEachSector(MySU &su, int t, int _sector);
    void getRendPair(const MySU &su0, const MySU &su1);
    void sectorRendOnly();
    void initChannelAndSectorRend();
    void channelAndSectorRend(int t);
    void initChannelAndSectorRendRandom();
    void channelAndSectorRendRandom(int t);
    
    MyNetwork();
    virtual void initSimulation();
    virtual void startSimulation();
};

#endif /* defined(__CRsim__my_network__) */
