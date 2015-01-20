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
    vector<MySU> jsSu;
    vector<MySU> jsSu2;
    MyNetwork();
    
    void initChanSegment();
    void initAllSU();
    void initAllPU();
    void initSuChanHop();
    void initSuAvaiChan();
    void initSuNeighbor(int _id);
    void initAllSuNeighbors();
    
    void initFirstAlgorithmJs();
    void firstAlgorithmJs();
    void initSecondAlgorithmJs();
    void secondAlgorithmJsFirstVersion();
    void secondAlgorithmJs();
    void initThirdAlgorithmJs();
    void thirdAlgorithmJs();
    void theRandomAlgorithm();
    
    void startSimulation();
};

#endif /* defined(__CRsim__my_network__) */
