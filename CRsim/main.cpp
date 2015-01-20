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
    MyNetwork my;
    my.startSimulation();
    return  0;
}

