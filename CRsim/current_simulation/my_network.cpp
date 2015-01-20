//
//  my_network.cpp
//  CRsim
//
//  Created by Ji on 14-10-7.
//  Copyright (c) 2014年 lj. All rights reserved.
//

#include "my_network.h"

MyNetwork:: MyNetwork()
{
    initAllPU();
    initAllSU();
}

void MyNetwork:: initAllPU()
{
    allPU.clear();
    for(int i = 0; i < PU_NUM; i++){
        PU p;
        allPU.push_back(p);
    }
}

double dis(double x1, double y1, double x2, double y2)
{
    return (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2);
}

void MyNetwork:: initAllSU()
{
    MySU tmp;
    tmp.location = make_pair(SIDE_LENGTH / 3.0, SIDE_LENGTH/3.0);
    MySU tmp1;
    tmp1.location = make_pair(SIDE_LENGTH*2.0/3.0, SIDE_LENGTH*2.0/3.0);
    allSU.push_back(tmp);
    allSU.push_back(tmp1);
    for(int i = 0; i < 2; i++){
        allSU[i].neighborPU.clear();
        for(int j = 0; j < PU_NUM; j++){
            if(dis(allSU[i].location.first, allSU[i].location.second, allPU[j].location.first, allPU[j].location.second) <= SENSE_RANGE_SU * SENSE_RANGE_SU){
                allSU[i].neighborPU.push_back(j);
            }
        }
    }
}

void MyNetwork::startSimulation()
{
    for(int t = 0; t < TOTAL_TIME_SLOT; t++){
        cout<<"#############################################"<<endl;
        for(int i = 0; i < 2; i++){
            allSU[i].avaiChan.clear();
            bool vis[TOTAL_CHAN_NUM] = {0};
            for(int j = 0; j < allSU[i].neighborPU.size(); j++){
                int n = allSU[i].neighborPU[j];
                int c = allPU[n].chanOfEachTimeSlot[t];
                if(c > 0){
                    vis[c] = 1;
                }
            }
            for(int j = 1; j <= TOTAL_CHAN_NUM; j++){
                if(!vis[j]){
                    allSU[i].avaiChan.push_back(j);
                }
            }
            cout<<t<<' '; printVector(allSU[i].avaiChan);
        }
        cout<<"#############################################"<<endl;
    }
}