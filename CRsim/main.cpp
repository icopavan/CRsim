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

extern double totalAnswer1;
extern double totalAnswer2;
extern double totalAnswer3;
extern double totalAnswer4;
extern double total_cal;
extern double total_mea;

int main(int argc, const char * argv[]) {
    //totalAnswer1 = totalAnswer2 = totalAnswer3 = totalAnswer4 = 0;
//    cout<<"Aver time: "<<total0*1.0/rend_count0<<endl;
//    cout<<"rend times: "<<rend_count0*100.0/simulation_times<<endl;
//    cout<<"Aver time: "<<total1*1.0/rend_count1<<endl;
//    cout<<"rend times: "<<rend_count1*100.0/simulation_times<<endl;
    for(int i = 1; i <= 1; i++){
//        cout<<"#######################"<<endl;
        MyNetwork my;
        my.startSimulation();
//        cout<<"#######################"<<endl<<endl;
    }
//    for(auto x: v) cout<<x<<' '; cout<<endl;
//    cout<<"JS rend aver time: "<<totalAnswer1/SIMULATION_REPEAT_TIME<<endl;
//    cout<<endl;
//    cout<<"En Js rend aver time: "<<totalAnswer1/SIMULATION_REPEAT_TIME<<endl;
//    cout<<"JS con avai  time rend 1 aver time: "<<totalAnswer1/SIMULATION_REPEAT_TIME<<endl;
//    cout<<"En JS con avai  time rend 2 aver time: "<<totalAnswer2/SIMULATION_REPEAT_TIME<<endl;
//    cout<<"Con avai time  rend aver time:  "<<totalAnswer3/SIMULATION_REPEAT_TIME<<endl;
//    cout<<"Pure rand rend aver time: "<<totalAnswer4/SIMULATION_REPEAT_TIME<<endl;
    return  0;
}

