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
    for(int i = 0; i < 2; i++){
        MySU tmp;
        tmp.location = make_pair(SIDE_LENGTH*(i+1) / 3.0, SIDE_LENGTH*(i+1)/3.0);
        tmp.curSysTimeSlot = my_randint(1, 10000000);
        tmp.chanHop = new JsHop();
        memset(tmp.chanAvaiTimeCount, 0, sizeof(tmp.chanAvaiTimeCount));
        memset(tmp.chanAvaiTimeTotal, 0, sizeof(tmp.chanAvaiTimeTotal));
        memset(tmp.chanAvaiRoundCount, 0, sizeof(tmp.chanAvaiRoundCount));
        memset(tmp.chanUsedTimeCount, 0, sizeof(tmp.chanUsedTimeCount));
        memset(tmp.chanCurTotalAvaiTime, 0, sizeof(tmp.chanCurTotalAvaiTime));
        tmp.neighborPU.clear();
        for(int j = 0; j < PU_NUM; j++){
            if(dis(tmp.location.first, tmp.location.second, allPU[j].location.first, allPU[j].location.second) <= SENSE_RANGE_SU * SENSE_RANGE_SU){
                tmp.neighborPU.push_back(j);
            }
        }
        allSU.push_back(tmp);
    }
    allSU.push_back(allSU[0]);//js with random replacement
    allSU.push_back(allSU[1]);
    allSU.push_back(allSU[0]);//js with optimal replacement
    allSU.push_back(allSU[1]);
}

double totalAnswer1 = 0.0;
double totalAnswer2 = 0.0;
double totalAnswer3 = 0.0;

const int countChannelID = 10; //which channel to count the continuous available time slot;

void MyNetwork::startSimulation()
{
//    const int START_REND_TIME = my_randint(1, TOTAL_TIME_SLOT/10);
    bool preVisted[SU_NUM+2][TOTAL_CHAN_NUM+5] = {1};
    vI countAvaiTimeSlot;
    for(int t = 0; t < TOTAL_TIME_SLOT; t++){
        //////////////////get available channels////////////////////////
        for(int i = 0; i < SU_NUM; i++){
            allSU[i].avaiChan.clear();
            bool vis[TOTAL_CHAN_NUM] = {0};
            for(int j = 0; j < allSU[i].neighborPU.size(); j++){
                int n = allSU[i].neighborPU[j];
//                if(allPU[n].pktTransQueue.size() == 0) printShit();
                int c = allPU[n].chanOfEachTimeSlot[t];
                if(c > 0){
                    vis[c] = 1;
                }
            }
            for(int j = 1; j <= TOTAL_CHAN_NUM; j++){
                if(!vis[j]){
                    if(preVisted[i][j] == true){
                        allSU[i].chanAvaiRoundCount[j]++;
                    }
                    allSU[i].chanCurTotalAvaiTime[j]++;
                    allSU[i].avaiChan.push_back(j);
                    allSU[i].chanAvaiTimeCount[j]++;
                    allSU[i].chanAvaiTimeTotal[j]++;
                }
                else{
                    if(preVisted[i][j] == false){
                        if(i == 0 && j == countChannelID){
                            countAvaiTimeSlot.push_back(allSU[i].chanCurTotalAvaiTime[j]);
                        }
                        allSU[i].chanCurTotalAvaiTime[j] = 0;
                    }
                    allSU[i].chanAvaiTimeCount[j] = 0;
                }
                preVisted[i][j] = vis[j];
            }
        }
        //////////////////get available channels////////////////////////
        
        ///////////////////////////////////////Jump stay rendezvous scheme/////////////////////////////////////////////
//        if(t > START_REND_TIME){
//            int c1 = allSU[0].chanHop->get_chan_t(allSU[0].curSysTimeSlot + t);
//            int c2 = allSU[1].chanHop->get_chan_t(allSU[1].curSysTimeSlot + t);
////            cout<<"#############################################"<<endl;
////            cout<<"Time "<<t<<' '; printVector(allSU[0].avaiChan);
////            cout<<"Time "<<t<<' '; printVector(allSU[1].avaiChan);
////            cout<<"Common available channels: ";
//            vI tmp = getComFromTwoVector(allSU[0].avaiChan, allSU[1].avaiChan);
//            printVector(tmp);
//            printArrayFrom1(allSU[0].chanAvaiTimeCount, TOTAL_CHAN_NUM);
//            printArrayFrom1(allSU[1].chanAvaiTimeCount, TOTAL_CHAN_NUM);
//            cout<<"c1: "<<c1<<endl;
//            cout<<"c2: "<<c2<<endl;
//            if(c1 == c2){
//                if(vec_find_int(allSU[0].avaiChan, c1) && vec_find_int(allSU[1].avaiChan, c2)){
//                    if(!rendSuc1){
//                        rendSuc1 = 1;
//                        totalAnswer1 += t - START_REND_TIME;
//                        cout<<"Js: ";
//                        cout<<t<<' '<<t-START_REND_TIME<<endl;
//                    }
//                }
//            }

//            cout<<"#############################################"<<endl<<endl;
//        }
        ///////////////////////////////////////Jump stay rendezvous scheme/////////////////////////////////////////////
    }
    cout<<"x = [";
    int n = (int)countAvaiTimeSlot.size();
    for(int i = 0; i < n; i++){
        cout<<countAvaiTimeSlot[i];
        if( i < n-1){
            cout<<", ";
        }
    }
    cout<<"];"<<endl;
//    cout<<"#############################################"<<endl;
//    double totalTime = 0;
//    int num = 0;
//    for(int i = 0; i < 2; i++){
////        printArrayFrom1(allSU[i].chanAvaiTimeTotal, TOTAL_CHAN_NUM);
////        printArrayFrom1(allSU[i].chanAvaiRoundCount, TOTAL_CHAN_NUM);
//        for(int j = 1; j <= TOTAL_CHAN_NUM; j++){
//            if(allSU[i].chanAvaiRoundCount[j] == 0) cout<<0<<' ';
//            else{
//                num++;
//                totalTime += allSU[i].chanAvaiTimeTotal[j]*1.0 / allSU[i].chanAvaiRoundCount[j];
//            }
//        }
////        cout<<"#############################################"<<endl<<endl;
//    }
//    totalAnswer += totalTime / num;
//    cout<<totalTime / num<<endl;
}






