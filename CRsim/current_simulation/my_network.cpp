//
//  my_network.cpp
//  CRsim
//
//  Created by Ji on 14-10-7.
//  Copyright (c) 2014年 lj. All rights reserved.
//

#include "my_network.h"

void MyNetwork:: initSuNeighbor(int cur_id)
{
    int n = (int)(SU_NUM * NEIGHBOR_RATIO);
    set<int> s;
    s.insert(cur_id);
    while((int)s.size() < n+1){
        int tmp = my_randint(1, SU_NUM);
        while(s.find(tmp) != s.end()){
            tmp = my_randint(1, SU_NUM);
        }
        s.insert(tmp);
    }
    set<int>::iterator it;
    jsSu[cur_id].neighbors.clear();
    for(it = s.begin(); it != s.end(); it++){
        if((*it) != cur_id){
            jsSu[cur_id].neighbors.push_back(*it);
        }
    }
}

void MyNetwork:: initAllSuNeighbors()
{
    for(int i = 1; i <= SU_NUM; i++){
        initSuNeighbor(i);
//        printVector(jsSu[i].neighbors);
    }
    for(int i = 1; i <= SU_NUM; i++){
        int n = (int)jsSu[i].neighbors.size();
        for(int j = 0; j < n; j++){
            int tmp = jsSu[i].neighbors[j];
            bool flag = 0;
            for(int k = 0; k < jsSu[tmp].neighbors.size(); k++){
                if(jsSu[tmp].neighbors[k] == i){
                    flag = 1;
                    break;
                }
            }
            if(!flag) jsSu[tmp].neighbors.push_back(i);
        }
    }
}

void MyNetwork:: initAllSU()
{
    for(int i = 1; i <= suNum+2; i++){
        MySU tmp;
        tmp.ID = i;
        tmp.curSysTimeSlot = my_randint(0, 100000);
        for(int j = 1; j <= CR_NUM+2; j++){
            CognitiveRadio tmp1;
            tmp.allCR.push_back(tmp1);
        }
        jsSu.push_back(tmp);
    }
}

void MyNetwork::startSimulation()
{
}