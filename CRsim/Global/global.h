//
//  global.h
//  CRsim
//
//  Created by Ji on 14-10-3.
//  Copyright (c) 2014年 lj. All rights reserved.
//

#ifndef CRsim_global_h
#define CRsim_global_h

const int   TOTAL_CHAN_NUM  = 20; // total number of channels in the whole spectrum

const int   SU_NUM  = 6; //number of SUs

const int   CR_NUM = 4; //number of cognitive radio of SU

const int   PU_NUM  = 20; //number of PUs

const double PKT_ARR_RATE_PU = 10; // pu packet arrival rate

const int PKT_MAX_LEN_PU =  100; //packet size

const int   SIMULATION_REPEAT_TIME = 1;

const int   TOTAL_TIME_SLOT  = 800000; //simulation time slots

const double   TIME_SLOT_LEN  = 0.002; //length of each time slot

const double   CHAN_AVAI_RATIO = 0.5; //channel available ration of each SU

const double   NEIGHBOR_RATIO = 0.5; //channel available ration of each SU

const double   USED_CHAN_RATIO = 0.5; //channel available ration of each SU

const double EPS = 1e-7; // Precision of double number

const int PKT_MAX_LEN_SU =  10; //packet size

const double PKT_ARR_RATE_SU = 10; // su packet arrival rate

const int SIDE_LENGTH = 200; //area side length

const double SENSE_RANGE_SU = 100; // sensing range of SU

///////////////////////////////////////////////////////////////////////////////////

static int ChanAllocToPuCount[TOTAL_CHAN_NUM+5];

static int AvaiChanNumForPU;

#define   Tran_Range   100//transmission range

#define   Nei_Ratio_Max   0.6//the number of neighbors over all users

#define   Nei_Ratio_Min   0.2//the number of neighbors over all users

#define   Sen_Range   100//sensing range

#define   Com_Ratio   0.8 //common available ratio between SUs

#define   THETA_OF_SSL   20 //minimum channels in a ss

#define INT_MAX_VAL     INT32_MAX

enum SEND_OR_RECEIVE{SEND = 0, RECEIVE = 1};

#endif
