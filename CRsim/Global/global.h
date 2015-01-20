//
//  global.h
//  CRsim
//
//  Created by Ji on 14-10-3.
//  Copyright (c) 2014年 lj. All rights reserved.
//

#ifndef CRsim_global_h
#define CRsim_global_h

const int   TOTAL_CHAN_NUM  = 30;
const int   SU_NUM  = 2; //number of SUs
const int   CR_NUM = 4; //number of cognitive radio of SU
const int   PU_NUM  = 30; //number of PUs
const int   TOTAL_TIME_SLOT  = 800; //simulation time slots
const double   CHAN_AVAI_RATIO = 0.5; //channel available ration of each SU
const int   SIMULATION_REPEAT_TIME = 10000;
const double   NEIGHBOR_RATIO = 0.5; //channel available ration of each SU
const double   USED_CHAN_RATIO = 0.5; //channel available ration of each SU
#define   Sim_Time 5.0 //the length of total simulation
#define   TIME_SLOT_LEN  0.002 //length of each time slot
#define   SU_PKT_MAX_LEN   10 //packet size
#define   LAMBDA_SU   20
#define   LAMBDA_PU   100
#define   SideLength   200//area side length
#define   Tran_Range   100//transmission range
#define   Nei_Ratio_Max   0.6//the number of neighbors over all users
#define   Nei_Ratio_Min   0.2//the number of neighbors over all users
#define   Sen_Range   100//sensing range
#define   Com_Ratio   0.8 //common available ratio between SUs
#define   THETA_OF_SSL   20 //minimum channels in a ss

#define INT_MAX_VAL INT32_MAX

enum SEND_OR_RECEIVE{SEND = 0, RECEIVE = 1};

#endif
