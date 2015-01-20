//
//  main.cpp
//  CRsim
//
//  Created by Ji on 14-10-3.
//  Copyright (c) 2014年 lj. All rights reserved.
//

#include <iostream>
#include "debug.h"
#include "my_math.h"
#include "my_fun.h"
#include "jump_stay.h"
#include "en_jump_stay.h"
#include "my_seq.h"
#include "my_split_spec.h"
#include "su.h"
#include "my_network.h"
#include "my_su.h"
#include "graph.h"
#include "max_flow.h"
#include "user.h"

int main(int argc, const char * argv[]) {
//    MyNetwork my;
//    my.startSimulation();
    PU p;
    p.initAllPkt(PKT_ARR_RATE_PU, PKT_MAX_LEN_PU);
    for(int i = 0; i < p.allDataPkt.size(); i++){
//        cout<<p.allDataPkt[i].ID<<' '<<p.allDataPkt[i].arrivalTimeSlot<<' '<<p.allDataPkt[i].len<<endl;
    }
    p.getTrafficOfEachTimeSlot();
    return  0;
}