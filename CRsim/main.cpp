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

extern double total_cal;
extern double total_mea;
int main(int argc, const char * argv[]) {
    for(int i = 0; i < SIMULATION_REPEAT_TIME; i++){
        MyNetwork my;
        my.startSimulation();
    }
    cout<<"Aver cal: "<<total_cal/SIMULATION_REPEAT_TIME<<endl;
    cout<<"Aver mea: "<<total_mea/SIMULATION_REPEAT_TIME<<endl;
//    cout<<totalAnswer2/SIMULATION_REPEAT_TIME<<endl;
//    cout<<totalAnswer3/SIMULATION_REPEAT_TIME<<endl;
    return  0;
}

