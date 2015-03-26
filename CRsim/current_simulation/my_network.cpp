//
//  my_network.cpp
//  CRsim
//
//  Created by Ji on 14-10-7.
//  Copyright (c) 2014年 lj. All rights reserved.
//

#include "my_network.h"

double total_cal = 0;
double total_mea = 0;
double totalAnswer1 = 0.0;
double totalAnswer2 = 0.0;
double totalAnswer3 = 0.0;
double totalAnswer4 = 0.0;
bool rendSuc0 = 0;
bool rendSuc1 = 0;
bool rendSuc2= 0;
bool rendSuc3 = 0;
bool rendSuc4 = 0;
int START_REND_TIME = my_randint(1, TOTAL_TIME_SLOT/10);
//const int countChannelID = TOTAL_CHAN_NUM/2; //which channel to count the continuous available time slot;
bool preAvai[SU_NUM+2][TOTAL_CHAN_NUM+5] = {1};
vI countAvaiTimeSlot;
const int KEEP_TIME = 2;
double totalRatio = 0;
double totalSURatio = 0;
double SU0avai = 0;
double SU1avai = 0;
double SU0SU1avai = 0;
double SU0SU1notAvai = 0;

MyNetwork:: MyNetwork() : CRNetwork()
{
//    initAllSU();
    initAllSuSector();
}

void MyNetwork:: initSuNeighborSector(MySU &su)
{
    su.initSectorSplit();
    memset(su.sectorNeighborPU, 0, sizeof(su.sectorNeighborPU));
    for(int i = 0; i < su.transSectorNum; i++){
        for(int j = 0; j < PU_NUM; j++){
            if(disSquareTwoPoint(su.location.first, su.location.second, allPU[j].location.first, allPU[j].location.second) <= SENSE_RANGE_SU * SENSE_RANGE_SU &&
               pointInsideAngle(su.location, su.sectorSplit[i], su.sectorSplit[i+1], allPU[j].location)){
                su.sectorNeighborPU[i][++su.sectorNeighborPU[i][0]] = j;
            }
        }
    }
}

void MyNetwork:: initSuNeighborPU(MySU &su)
{
    su.neighborPU.clear();
    for(int j = 0; j < PU_NUM; j++){
        if(disSquareTwoPoint(su.location.first, su.location.second, allPU[j].location.first, allPU[j].location.second) <= SENSE_RANGE_SU * SENSE_RANGE_SU){
            su.neighborPU.push_back(j);
        }
    }
}

void MyNetwork:: getRendPair(const MySU &su0, const MySU &su1)
{
    int n0 = su0.transSectorNum, n1 = su1.transSectorNum;
    int ans1 = -1, ans2 = -1;
    for(int i = 0; i < n0; i++){
        if(pointInsideAngle(su0.location, su0.sectorSplit[i], su0.sectorSplit[i+1], su1.location)){
            ans1 = i;
            break;
        }
    }
    for(int i = 0; i < n1; i++){
        if(pointInsideAngle(su1.location, su1.sectorSplit[i], su1.sectorSplit[i+1], su0.location)){
            ans2 = i;
            break;
        }
    }
    rendPair = make_pair(ans1, ans2);
}

void MyNetwork:: initAllSuSector()
{
    for(int i = 0; i < 2; i++){
        MySU tmp;
        tmp.location = make_pair(SIDE_LENGTH*(i+1) / 3.0, SIDE_LENGTH*(i+1)/3.0);
        tmp.curSysTimeSlot = my_randint(1, 10000000);
        tmp.ID = i;
        SEND_OR_RECEIVE sendOrRev = SEND;
        if(i == 0){
            tmp.transSectorNum = SEND_SECTOR_NUM;
            sendOrRev = SEND;
        }
        else{
            tmp.transSectorNum = REV_SECTOR_NUM;
            sendOrRev = RECEIVE;
        }
        tmp.curSectorID = -1;
        tmp.secHop = new SectorHop(tmp.transSectorNum, sendOrRev);
        tmp.chanHop = new EnJsHop();
        initSuNeighborSector(tmp);
        allSU[i] = tmp;
    }
    getRendPair(allSU[0], allSU[1]);
    allSU[2] = allSU[0];
    allSU[3] = allSU[1];
}

void MyNetwork:: getAvaiChanEachSector(MySU &su, int t, int _sector)
{
    su.avaiChan.clear();
    bool not_avai[TOTAL_CHAN_NUM+5] = {0};
    for(int i = 1; i <= TOTAL_CHAN_NUM; i++){
        int n = su.sectorNeighborPU[_sector][0];
        for(int k = 1; k <= n; k++){
            int p = su.sectorNeighborPU[_sector][k];
            int c = allPU[p].chanOfEachTimeSlot[t];
            if(c > 0 && c <= TOTAL_CHAN_NUM){
                not_avai[c] = true;
            }
        }
    }
    for(int i = 1; i <= TOTAL_CHAN_NUM; i++){
        if(!not_avai[i]){
            su.avaiChan.push_back(i);
        }
    }
}

int total0 = 0;
int rend_count0 = 0;
int total1 = 0;
int rend_count1 = 0;
const int MTTR = TOTAL_CHAN_NUM;

void MyNetwork:: sectorRendOnly()
{
    SectorHop s0(SEND_SECTOR_NUM, SEND);
    SectorHop s1(REV_SECTOR_NUM, RECEIVE);
    rendPair = make_pair(my_randint(0, SEND_SECTOR_NUM-1), my_randint(0, REV_SECTOR_NUM-1));
    //    cout<<rendPair.first<<' '<<rendPair.second<<endl;
    int n = SEND_SECTOR_NUM*REV_SECTOR_NUM*2;
    for(int i = 0; i < n; i++){
        int t0 = s0.getCurIndex();
        int t1 = s1.getCurIndex();
        if(t0 == rendPair.first && t1 == rendPair.second){
            rend_count0++;
            total0 += i;
            break;
        }
    }
    for(int i = 0; i < n; i++){
        int t0 = my_randint(0, SEND_SECTOR_NUM-1);
        int t1 = my_randint(0, REV_SECTOR_NUM-1);
        if(t0 == rendPair.first && t1 == rendPair.second){
            rend_count1++;
            total1 += i;
            break;
        }
    }
}

void MyNetwork:: initChannelAndSectorRend()
{
    MySU &su0 = allSU[0];
    MySU &su1 = allSU[1];
    su0.secHop = new SectorHop(su0.transSectorNum, SEND);
    su1.secHop = new SectorHop(su1.transSectorNum, RECEIVE);
    su0.curSectorID = su0.secHop->getCurIndex();
    su1.curSectorID = su1.secHop->getCurIndex();
    su0.channelHopCount = 0;
    su1.channelHopCount = 0;
    rendSuc0 = 0;
}
void MyNetwork:: channelAndSectorRend(int t)
{
    MySU &su0 = allSU[0];
    MySU &su1 = allSU[1];
    su0.channelHopCount++;
    su1.channelHopCount++;
//    cout<<su0.curSectorID<<' '<<su1.curSectorID<<endl;
    if(su0.curSectorID == rendPair.first && su1.curSectorID == rendPair.second){
        getAvaiChanEachSector(su0, t, su0.curSectorID);
        getAvaiChanEachSector(su1, t, su1.curSectorID);
        int c0 = su0.chanHop->getChanAtTimeT(t+su0.curSysTimeSlot, su0.avaiChan);
        int c1 = su1.chanHop->getChanAtTimeT(t+su1.curSysTimeSlot, su1.avaiChan);
//        cout<<"my: "<<c0<<' '<<c1<<endl;
        if(c1 == c0){
            rendSuc0 = 1;
            total0 += t - START_REND_TIME;
            rend_count0++;
//            cout<<"my: "<<t - START_REND_TIME<<endl;
            return;
        }
    }
    else{
        if(su0.channelHopCount >= MTTR){
            su0.curSectorID = su0.secHop->getCurIndex();
            su0.channelHopCount = 0;
        }
        if(su1.channelHopCount >= MTTR){
            su1.curSectorID = su1.secHop->getCurIndex();
            su1.channelHopCount = 0;
        }
    }
}

void MyNetwork:: initChannelAndSectorRendRandom()
{
    MySU &su0 = allSU[2];
    MySU &su1 = allSU[3];
    su0.channelHopCount = 0;
    su1.channelHopCount = 0;
//    su0.chanHop = new EnJsHop();
//    su1.chanHop = new EnJsHop();
    su0.curSectorID = my_randint(0, su0.transSectorNum-1);
    su1.curSectorID = my_randint(0, su1.transSectorNum-1);
    rendSuc1 = 0;
}

void MyNetwork:: channelAndSectorRendRandom(int t)
{
    MySU &su0 = allSU[2];
    MySU &su1 = allSU[3];
    int  c0, c1;
    su0.channelHopCount++;
    su1.channelHopCount++;
    if(su0.curSectorID == rendPair.first && su1.curSectorID == rendPair.second){
        getAvaiChanEachSector(su0, t, su0.curSectorID);
        getAvaiChanEachSector(su1, t, su1.curSectorID);
//        cout<<su0.avaiChan.size()<<' '<<su1.avaiChan.size()<<endl;
        c0 = su0.chanHop->getChanAtTimeT(t+su0.curSysTimeSlot, su0.avaiChan);
        c1 = su1.chanHop->getChanAtTimeT(t+su1.curSysTimeSlot, su1.avaiChan);
//        cout<<"random: "<<c0<<' '<<c1<<endl;
        if(c1 == c0){
            rendSuc1 = 1;
            total1 += t - START_REND_TIME;
            rend_count1++;
//            cout<<"Random: "<<t - START_REND_TIME<<endl;
            return;
        }
    }
    else{
        if(su0.channelHopCount >= MTTR){
            su0.curSectorID = my_randint(0, su0.transSectorNum-1);
            su0.channelHopCount = 0;
        }
        if(su1.channelHopCount >= MTTR){
            su1.curSectorID = my_randint(0, su1.transSectorNum-1);
            su1.channelHopCount = 0;
        }
    }
}

void MyNetwork:: initAllSU()
{
    for(int i = 0; i < 2; i++){
        MySU tmp;
        tmp.location = make_pair(SIDE_LENGTH*(i+1) / 3.0, SIDE_LENGTH*(i+1)/3.0);
        tmp.curSysTimeSlot = my_randint(1, 10000000);
        tmp.chanHop = new JsHop();
        initSuNeighborPU(tmp);
        for(int j = 1; j <= TOTAL_CHAN_NUM; j++){
            tmp.allChanObj[j].ID = j;
            tmp.allChanObj[j].ifAvai = 0;
            tmp.allChanObj[j].curConAvaiTime = 0;
        }
        allSU[i] = tmp;
    }
//    allSU.push_back(allSU[0]);
//    allSU[2].chanHop = new EnJsHop();
//    allSU.push_back(allSU[1]);
//    allSU[3].chanHop = new EnJsHop();
//    allSU.push_back(allSU[0]);
//    allSU[4].chanHop = new EnJsHop();
//    allSU.push_back(allSU[1]);
//    allSU[5].chanHop = new EnJsHop();
}

void MyNetwork:: getSUsCurAvaiChan(int t)
{
    //////////////////get available channels of each SU on current time////////////////////////////////////////////////////////////
    if( t >= TOTAL_TIME_SLOT) return;
    for(int i = 0; i < SU_NUM; i++){
        SU &su = allSU[i];
        su.avaiChan.clear();
        bool avai[TOTAL_CHAN_NUM+5] = {0};
        for(int j = 1; j <= TOTAL_CHAN_NUM; j++){
            avai[j] = true;
        }
        for(int j = 0; j < su.neighborPU.size(); j++){
            int n = su.neighborPU[j];
            int c = allPU[n].chanOfEachTimeSlot[t];
            if(c > 0 && c <= TOTAL_CHAN_NUM){
                avai[c] = false;
            }
        }
        for(int j = 1; j <= TOTAL_CHAN_NUM; j++){
            if(avai[j] == true){
                su.avaiChan.push_back(j);
                su.allChanObj[j].ifAvai = true;
            }
            if(avai[j] == false){
                su.allChanObj[j].ifAvai = false;
            }
        }
    }
}

void MyNetwork:: jumpStayRend(int t)
{
    SU &su0 = allSU[0];
    SU &su1 = allSU[1];
    int c0 = su0.chanHop->getChanAtTimeT(allSU[0].curSysTimeSlot + t);
    int c1 = su1.chanHop->getChanAtTimeT(allSU[1].curSysTimeSlot + t);
    su0.curStayChan = c0;
    su1.curStayChan = c1;
//    cout<<c0<<' '<<c1<<endl;
    if( (c1 == c0+TOTAL_CHAN_NUM && vectorFind(su0.avaiChan, c0) && vectorFind(su1.avaiChan, c0))
     || (c0 == c1+TOTAL_CHAN_NUM && vectorFind(su1.avaiChan, c1) && vectorFind(su0.avaiChan, c1))
       ){
        rendSuc1 = 1;
        totalAnswer1 += t - START_REND_TIME;
        cout<<"JS: "<< t- START_REND_TIME<<endl;
    }
}

void MyNetwork:: enhanceJumpStayRend(int t)
{
    if(rendSuc1) return;
    SU &su0 = allSU[2];
    SU &su1 = allSU[3];
    int c0 = su0.chanHop->getChanAtTimeT(allSU[0].curSysTimeSlot + t, allSU[0].avaiChan);
    int c1 = su1.chanHop->getChanAtTimeT(allSU[1].curSysTimeSlot + t, allSU[1].avaiChan);
    su0.curStayChan = c0;
    su1.curStayChan = c1;
//    cout<<c0<<' '<<c1<<endl;
    if(c0 == c1){
        rendSuc1 = 1;
        totalAnswer1 += t - START_REND_TIME;
        cout<<"Enhanced JS: "<< t- START_REND_TIME<<endl;
    }
}

const int NUM_CHOOSE_CHAN = 8;
void MyNetwork:: enhanceJumpStayConAvaiTimeRend(int t)
{
    if(rendSuc2) return;
    SU &su0 = allSU[4];
    SU &su1 = allSU[5];
    int c0 = su0.chanHop->getChanAtTimeTBeforeReplace(allSU[0].curSysTimeSlot + t);
    int c1 = su1.chanHop->getChanAtTimeTBeforeReplace(allSU[1].curSysTimeSlot + t);
    
    su0 = allSU[0];
    su1 = allSU[1];
    sort(su0.allChanObj+1, su0.allChanObj+1+TOTAL_CHAN_NUM, cmpConAvaiTimeReverse);
    bool flag = 0;
    for(int i  = 1; i <= NUM_CHOOSE_CHAN; i++){
        if(su0.allChanObj[i].ID == c0){
            flag = 1;
            break;
        }
    }
    if(!flag) c0 = su0.allChanObj[my_randint(1, NUM_CHOOSE_CHAN)].ID;
    sort(su0.allChanObj+1, su0.allChanObj+1+TOTAL_CHAN_NUM, cmpID);
    
    sort(su1.allChanObj+1, su1.allChanObj+1+TOTAL_CHAN_NUM, cmpConAvaiTimeReverse);
    flag = 0;
    for(int i  = 1; i <= NUM_CHOOSE_CHAN; i++){
        if(su1.allChanObj[i].ID == c1){
            flag = 1;
            break;
        }
    }
    if(!flag) c1 = su1.allChanObj[my_randint(1, NUM_CHOOSE_CHAN)].ID;
    sort(su1.allChanObj+1, su1.allChanObj+1+TOTAL_CHAN_NUM, cmpID);

    if(c0 == c1){
        rendSuc2 = 1;
        totalAnswer2 += t - START_REND_TIME;
        cout<<"Enhanced JS con avai time: "<< t- START_REND_TIME<<endl;
    }
}

void MyNetwork::jsRadomRepRend(int t)
{
    /////////////////////////////////////Jump stay with random replacement////////////////////////////////////////////
    if(rendSuc1) return;
    SU &su0 = allSU[0];
    SU &su1 = allSU[1];
    int c0 = su0.curStayChan;
    int c1 = su1.curStayChan;
    if(!vectorFind(su0.avaiChan, c0)) c0 = su0.avaiChan[my_randint(0, (int)su0.avaiChan.size()-1)];
    if(!vectorFind(su1.avaiChan, c1)) c1 = su1.avaiChan[my_randint(0, (int)su1.avaiChan.size()-1)];
    if(c0 == c1){
//        cout<<"Js Random: ";
//        cout<<t-START_REND_TIME<<endl;
        totalAnswer1 += t-START_REND_TIME;
        rendSuc1 = 1;
    }
}

void MyNetwork::jsRandomRepRandomSenseRend(int t)
{
    /*********************************
     Jump stay with random replacement
     
     *********************************/
    SU &su0 = allSU[0];
    SU &su1 = allSU[1];
    int c0 = su0.curStayChan;
    int c1 = su1.curStayChan;
    if(!vectorFind(su0.avaiChan, c0)){
        vI sen0 = generateDiffRandInt(MAX_SENSE_CHAN_NUM-1, 1, TOTAL_CHAN_NUM);
        sen0.push_back(c0);
        vI curAvai0;
        for(int i = 1; i <= TOTAL_CHAN_NUM; i++){
            if(vectorFind(su0.avaiChan, i) && vectorFind(sen0, i)){
                curAvai0.push_back(i);
            }
        }
        if(curAvai0.size() < 1) return;
        c0 = curAvai0[my_randint(0, (int)curAvai0.size()-1)];
    }
    if(!vectorFind(su1.avaiChan, c1)){
        vI sen1 = generateDiffRandInt(MAX_SENSE_CHAN_NUM-1, 1, TOTAL_CHAN_NUM);
        sen1.push_back(c1);
        vI curAvai1;
        for(int i = 1; i <= TOTAL_CHAN_NUM; i++){
            if(vectorFind(su1.avaiChan, i) && vectorFind(sen1, i)){
                curAvai1.push_back(i);
            }
        }
        if(curAvai1.size() < 1) return;
        c1 = curAvai1[my_randint(0, (int)curAvai1.size()-1)];
    }
    if(c0 == c1){
//        cout<<"Js Random Sense Partial: ";
//        cout<<t<<' '<<t-START_REND_TIME<<endl;
        totalAnswer2 += t-START_REND_TIME;
        rendSuc2 = 1;
    }
}

void MyNetwork:: jsConAvaiTimeRandRend0(int t)
{
    if(rendSuc1) return;
    SU &su0 = allSU[0];
    SU &su1 = allSU[1];
    int c0 = su0.curStayChan;
    int c1 = su1.curStayChan;
    sort(su0.allChanObj+1, su0.allChanObj+1+TOTAL_CHAN_NUM, cmpConAvaiTimeReverse);
    if(!vectorReverseSortedFind(su0.avaiChan, c0)) c0 = su0.allChanObj[my_randint(1, NUM_CHOOSE_CHAN)].ID;
    sort(su0.allChanObj+1, su0.allChanObj+1+TOTAL_CHAN_NUM, cmpID);
    
    sort(su1.allChanObj+1, su1.allChanObj+1+TOTAL_CHAN_NUM, cmpConAvaiTimeReverse);
    if(!vectorReverseSortedFind(su1.avaiChan, c1)) c1 = su1.allChanObj[my_randint(1, NUM_CHOOSE_CHAN)].ID;
    sort(su1.allChanObj+1, su1.allChanObj+1+TOTAL_CHAN_NUM, cmpID);
    if(c0 == c1){
        //        cout<<"Js con avai time: ";
        //        cout<<t<<' '<<t-START_REND_TIME<<endl;
        totalAnswer1 += t-START_REND_TIME;
        rendSuc1 = 1;
    }
}

void MyNetwork:: jsConAvaiTimeRandRend1(int t)
{
    if(rendSuc1) return;
    SU &su0 = allSU[0];
    SU &su1 = allSU[1];
    int c0 = su0.curStayChan;
    int c1 = su1.curStayChan;
    sort(su0.allChanObj+1, su0.allChanObj+1+TOTAL_CHAN_NUM, cmpConAvaiTimeReverse);
    bool flag = 0;
    for(int i  = 1; i <= NUM_CHOOSE_CHAN; i++){
        if(su0.allChanObj[i].ID == c0){
            flag = 1;
            break;
        }
    }
    if(!flag) c0 = su0.allChanObj[my_randint(1, NUM_CHOOSE_CHAN)].ID;
    sort(su0.allChanObj+1, su0.allChanObj+1+TOTAL_CHAN_NUM, cmpID);
    
    sort(su1.allChanObj+1, su1.allChanObj+1+TOTAL_CHAN_NUM, cmpConAvaiTimeReverse);
    flag = 0;
    for(int i  = 1; i <= NUM_CHOOSE_CHAN; i++){
        if(su1.allChanObj[i].ID == c1){
            flag = 1;
            break;
        }
    }
    if(!flag) c1 = su1.allChanObj[my_randint(1, NUM_CHOOSE_CHAN)].ID;
    sort(su1.allChanObj+1, su1.allChanObj+1+TOTAL_CHAN_NUM, cmpID);
    if(c0 == c1){
        //        cout<<"Js con avai time: ";
        //        cout<<t<<' '<<t-START_REND_TIME<<endl;
        totalAnswer1 += t-START_REND_TIME;
        rendSuc1 = 1;
    }
}

void MyNetwork:: jsConAvaiTimeRandRend2(int t)
{
    if(rendSuc2) return;
    SU &su0 = allSU[0];
    SU &su1 = allSU[1];
    int c0 = su0.curStayChan;
    int c1 = su1.curStayChan;
    int n0 = (int)su0.avaiChan.size() / 2;
    int n1 = (int)su1.avaiChan.size() / 2;
    sort(su0.allChanObj+1, su0.allChanObj+1+TOTAL_CHAN_NUM, cmpConAvaiTimeReverse);
    bool flag = 0;
    for(int i  = 1; i <= n0; i++){
        if(su0.allChanObj[i].ID == c0){
            flag = 1;
            break;
        }
    }
    if(!flag) c0 = su0.allChanObj[my_randint(1, n0)].ID;
    sort(su0.allChanObj+1, su0.allChanObj+1+TOTAL_CHAN_NUM, cmpID);

    sort(su1.allChanObj+1, su1.allChanObj+1+TOTAL_CHAN_NUM, cmpConAvaiTimeReverse);
    flag = 0;
    for(int i  = 1; i <= n1; i++){
        if(su1.allChanObj[i].ID == c1){
            flag = 1;
            break;
        }
    }
    if(!flag) c1 = su1.allChanObj[my_randint(1, n1)].ID;
    sort(su1.allChanObj+1, su1.allChanObj+1+TOTAL_CHAN_NUM, cmpID);
    if(c0 == c1){
//        cout<<"Js con avai time: ";
//        cout<<t<<' '<<t-START_REND_TIME<<endl;
        totalAnswer2 += t-START_REND_TIME;
        rendSuc2 = 1;
    }
}

//static int rendSucCount1  = 0;
//static int rendSucCount2  = 0;
//int recCurPos = 0;
void MyNetwork:: conAvaiTimeRandRend(int t)
{
    if(rendSuc3) return;
    SU &su0 = allSU[0];
    SU &su1 = allSU[1];
    
    int n0 = (int)su0.avaiChan.size() / 3;
    sort(su0.allChanObj+1, su0.allChanObj+1+TOTAL_CHAN_NUM, cmpConAvaiTimeReverse);
    int c0 = su0.allChanObj[my_randint(1, n0)].ID;
    sort(su0.allChanObj+1, su0.allChanObj+1+TOTAL_CHAN_NUM, cmpID);
    
    sort(su1.allChanObj+1, su1.allChanObj+1+TOTAL_CHAN_NUM, cmpConAvaiTimeReverse);
//    recCurPos++;
//    if(recCurPos > 5) recCurPos = 1;
    int n1 = (int)su1.avaiChan.size() / 3;
    int c1 = su1.allChanObj[my_randint(1, n1)].ID;
    sort(su1.allChanObj+1, su1.allChanObj+1+TOTAL_CHAN_NUM, cmpID);
    
    if(c0 == c1){
//        cout<<"Con avai time rend:  ";
//        cout<<t-START_REND_TIME<<endl;
        totalAnswer3 += t-START_REND_TIME;
        rendSuc3 = 1;
//        rendSucCount1++;
//        cout<<rendSucCount1<<endl;
    }
}

void MyNetwork:: pureRandomRend(int t)
{
    if(rendSuc4) return;
    SU &su0  = allSU[0];
    SU &su1  = allSU[1];
    int c0 = su0.avaiChan[my_randint(0, (int)su0.avaiChan.size()-1)];
    int c1 = su1.avaiChan[my_randint(0, (int)su1.avaiChan.size()-1)];
    if(c0 == c1){
//        cout<<"Pure random rend: ";
//        cout<<t-START_REND_TIME<<endl;
        totalAnswer4 += t-START_REND_TIME;
        rendSuc4 = 1;
//        rendSucCount2++;
//        cout<<rendSucCount2<<endl;
    }
}

void MyNetwork:: jsKeepRepRend(int t)
{
    SU &su0 = allSU[0];
    SU &su1 = allSU[1];
    int c0 = su0.curStayChan;
    int c1 = su1.curStayChan;
    if(!vectorFind(su0.avaiChan, c0)){
        if(su0.lastStayChan < 1 || su0.alreadyStayTime >= KEEP_TIME || (!vectorFind(su0.avaiChan, su0.lastStayChan))){
            c0 = su0.avaiChan[my_randint(0, (int)su0.avaiChan.size())];
            su0.lastStayChan = c0;
            su0.alreadyStayTime = 1;
        }
        else{
            c0 = su0.lastStayChan;
            su0.alreadyStayTime++;
        }
    }
    if(!vectorFind(su1.avaiChan, c1)){
        if(su1.lastStayChan < 1 || su1.alreadyStayTime >= KEEP_TIME  || (!vectorFind(su1.avaiChan, su1.lastStayChan))){
            c1 = su1.avaiChan[my_randint(0, (int)su1.avaiChan.size())];
            su1.lastStayChan = c1;
            su1.alreadyStayTime = 1;
        }
        else{
            c1 = su1.lastStayChan;
            su1.alreadyStayTime++;
        }
 
    }
    if(c0 == c1){
        cout<<"Js Keep: ";
        cout<<t<<' '<<t-START_REND_TIME<<endl;
        totalAnswer3 += t-START_REND_TIME;
        rendSuc1 = 1;
    }
}

double MyNetwork:: calAverConAvaiTime()
{
    double p_act = PKT_ARR_RATE_PU*PKT_MAX_LEN_PU*TIME_SLOT_LEN/PKT_MAX_LEN_PU;
    int n = (int)allSU[0].neighborPU.size();
    int m = TOTAL_CHAN_NUM;
    double ans = 0;
    for(int k = 0; k <= n; k++){
        ans += myNchooseM(n, k) * pow(p_act*(1.0*m-1)/m, k) * pow(1-p_act, n-k);
    }
//    cout<<"P_avai: "<<ans<<endl;
//    cout<<"Aver_avai_len: "<<1.0/(1-ans)<<endl;
    total_cal += 1.0/(1.0-ans);
    return 1.0/(1.0-ans);
}

double MyNetwork:: calConAvaiChanAverConAvaiTime()
{
    double p_act = PKT_ARR_RATE_PU*PKT_MAX_LEN_PU*TIME_SLOT_LEN/PKT_MAX_LEN_PU;
    vI tmp = getComFromTwoVector(allSU[0].neighborPU, allSU[1].neighborPU);
    int n = (int)tmp.size();
    cout<<"Common number: "<<n<<endl;
    int m = TOTAL_CHAN_NUM;
    double ans = 0;
    for(int k = 0; k <= n; k++){
        ans += myNchooseM(n, k) * pow(p_act*(1.0*m-1)/m, k) * pow(1-p_act, n-k);
    }
    cout<<"Available at a time slot: "<<ans<<endl;
    cout<<"Exp length: "<<1.0/(1-ans)<<endl;
    //    cout<<"P_avai: "<<ans<<endl;
    //    cout<<"Aver_avai_len: "<<1.0/(1-ans)<<endl;
    total_cal += 1.0/(1.0-ans);
    return 1.0/(1.0-ans);
}

int count1 = 0;
void MyNetwork:: calChanEachTime()
{
    int P = TOTAL_CHAN_NUM*2+1;
    int r1 = my_randint(1, P), r2 = my_randint(1, P);
    while(r1 == r2){
        r1 = my_randint(1, P);
        r2 = my_randint(1, P);
    }
    int x1 = my_randint(0, P), x2 = my_randint(0, P);
    vI ans1, ans2;
//    cout<<r1<<' '<<r2<<endl;
//    int t1 = my_randint(1, P), t2 = my_randint(1, P);
    int t1 = 0, t2 = 0;
    while (ans1.size() < P) {
        ans1.push_back((x1+t1*r1)%P);
        t1++;
    }
    while (ans2.size() < P) {
        ans2.push_back((x2+t2*r2)%P);
        t2++;
    }
    for(int i = 0; i < P; i++){
//        cout<<v1%P<<' '<<v2%P<<endl;
        if(abs(ans1[i] - ans2[i]) == TOTAL_CHAN_NUM){
//            cout<<"shit"<<endl;
            count1++;
            break;
        }
    }
//    sort(ans1.begin(), ans1.end());
//    sort(ans2.begin(), ans2.end());
//    printVector(ans1);
//    printVector(ans2);
}

void MyNetwork:: getCurAllChanConAvaiTime()
{
    for(int i  = 0; i < SU_NUM; i++){
        SU &su = allSU[i];
        for(int j = 1; j <= TOTAL_CHAN_NUM; j++){
            if(su.allChanObj[j].ifAvai){
                su.allChanObj[j].curConAvaiTime++;
            }
            else{
                if(su.allChanObj[j].curConAvaiTime > 0){
                    su.allChanObj[j].allConAvaiTime.push_back(su.allChanObj[j].curConAvaiTime);
                    su.allChanObj[j].curConAvaiTime = 0;
                }
            }
        }
    }
}

void MyNetwork:: printTwoSUsConAvaiTime()
{
    cout<<"#####################"<<endl;
//    cout<<"Con avai chan: ";
    vI ans = getComFromTwoVector(allSU[0].avaiChan, allSU[1].avaiChan);
//    printVector(ans);
    cout<<ans.size()<<endl;
    for(int t = 0; t < SU_NUM; t++){
        SU &su = allSU[t];
        sort(su.allChanObj+1, su.allChanObj+1+TOTAL_CHAN_NUM, cmpConAvaiTimeReverse);
        for(int i  = 1; i <= TOTAL_CHAN_NUM; i++){
            cout<<su.allChanObj[i].ID<<":"<<su.allChanObj[i].curConAvaiTime<<' ';
        }
//        int n = 0;
//        for(int i  = 1; i <= 10; i++){
//            if(vectorSortedFind(ans, su.allChanObj[i].ID) > -1){
////                cout<<su.allChanObj[i].ID<<' ';
//                n++;
//            }
//        }
//        cout<<n;
        cout<<endl;
        sort(su.allChanObj+1, su.allChanObj+1+TOTAL_CHAN_NUM, cmpID);
    }
//    getCurConAvaiChan();
    cout<<"#####################"<<endl;
    cout<<endl;
}

void MyNetwork:: printAllChanConAvaiTime()
{
    SU &su = allSU[0];
    for(int i = 1; i <= TOTAL_CHAN_NUM; i++){
        cout<<"########################"<<endl;
        su.allChanObj[i].printSortedAllConAvaiTime();
        cout<<"########################"<<endl;
        cout<<endl;
    }
}

void MyNetwork:: getCommonAvaiRatio()
{
    SU &su0 = allSU[0];
    SU &su1 = allSU[1];
    for(int x : su0.avaiChan){
        chanAvaiCountSu0[x]++;
        if(vectorFind(su1.avaiChan, x)){
            chanComAvaiCountSu0Su1[x]++;
        }
    }
}

void MyNetwork:: getCurConAvaiChan()
{
    cout<<"Con avai chan: ";
    vI ans = getComFromTwoVector(allSU[0].avaiChan, allSU[1].avaiChan);
    printVector(ans);
}

const int AVAI_NUM = 15;
const int CON_AVAI_NUM = 11;
void MyNetwork:: calMaxProComAfterCut()
{
    SU &su0 = allSU[0];
    SU &su1 = allSU[1];
    int nc1, nc2, nc;
    nc1 = (int)su0.avaiChan.size();
    nc2 = (int)su1.avaiChan.size();
    nc = (int)getComFromTwoVector(su0.avaiChan, su1.avaiChan).size();
//    nc1 = 20;
//    nc2 = 20;
//    nc = 10;
    double ans = 0;
    int ansm = 0;
    for(int m = 1; m <= nc; m++){
        double p = 0;
        for(int k = max(0, m-nc1+nc); k <= min(m, nc); k++){
            p += k*myNchooseM(nc, k)*myNchooseM(nc, k)*myNchooseM(nc1-nc, m-k)*myNchooseM(nc2-nc, m-k);
        }
        p /= myNchooseM(nc1, m)*myNchooseM(nc2, m)*m;
//        cout<<p<<endl;
        if(p > ans){
            ans = p;
            ansm = m;
        }
    }
    cout<<"nc1: "<<nc1<<"  nc2: "<<nc2<<" nc:"<<nc<<endl;
    cout<<"Max number of chosen is: "<<ansm<<endl;
}

void MyNetwork::initSimulation()
{
//    cout<<"x = [";
//    totalRatio = 0;
//    totalSURatio = 0;
    rendSuc1 = rendSuc2 = rendSuc3 = rendSuc4 = 0;
//    recCurPos = 0;
    for(int i = 0; i < SU_NUM; i++){
        SU &su = allSU[i];
        for(int j = 1; j <= TOTAL_CHAN_NUM; j++){
            su.allChanObj[j].ifAvai = 0;
            su.allChanObj[j].curConAvaiTime = 0;
        }
    }
}

//void MyNetwork::startSimulation()
//{
//    totalAnswer1 = totalAnswer2 = totalAnswer3 = totalAnswer4 = 0;
//    count1 = 0;
//    for(int i = 0; i < SIMULATION_REPEAT_TIME; i++){
//        initSimulation();
//        cout<<i<<endl;
//        START_REND_TIME = my_randint(TOTAL_TIME_SLOT/5, TOTAL_TIME_SLOT/2);
//        for(int t = 0; t < TOTAL_TIME_SLOT; t++){
//            if(rendSuc1 && rendSuc2){//&& rendSuc3 && rendSuc4){
//                break;
//            }
//            getSUsCurAvaiChan(t);
//            getCurAllChanConAvaiTime();
//            if(t == TOTAL_TIME_SLOT-1){
//            }
//            if(t > START_REND_TIME){
//                jumpStayRend(t);
//                enhanceJumpStayRend(t);
//                enhanceJumpStayConAvaiTimeRend(t);
////                jsRadomRepRend(t);
////                jsConAvaiTimeRandRend1(t);
////                jsConAvaiTimeRandRend2(t);
////                pureRandomRend(t);
////                conAvaiTimeRandRend(t);
//            }
//        }
//    //    double sum = 0;
//    //    for(int i = 1; i <= TOTAL_CHAN_NUM; i++){
//    //        sum += 1.0*chanComAvaiCountSu0Su1[i]/chanAvaiCountSu0[i];
//    //    }
//    //    cout<<"get com avai ratio: "<< sum/TOTAL_CHAN_NUM<<endl;
//    //    calConAvaiChanAverConAvaiTime();
//    //    double sum = 0;
//    //    for(int i = 1; i <= TOTAL_CHAN_NUM; i++){
//    //        double tmp = averValOfVector(allSU[0].allChanObj[i].allConAvaiTime);
//    //        cout<<tmp<<' ';
//    //        sum += tmp;
//    //    }
//    //    cout<<endl;
//    //    cout<<sum/TOTAL_CHAN_NUM<<endl;
//    //    if(!rendSucRandSense) cout<<"Rend rand sense failed\n";
//    //    if(!rendSucRand) cout<<"Rend rand failed\n";
//    //    calAverConAvaiTime();
//    //    printConAvaiTime();
//    }
////    cout<<count1<<endl;
//}

void MyNetwork::startSimulation()
{
//    for(int i = 0; i < SIMULATION_REPEAT_TIME; i++){
//        START_REND_TIME = my_randint(TOTAL_TIME_SLOT/5, TOTAL_TIME_SLOT/2);
//        for(int t = 0; t < TOTAL_TIME_SLOT; t++){
//            }
//    }
//    MySU &su = allSU[0];
//    for(int i = 0; i < su.transSectorNum; i++){
//        int n = (int)su.sectorNeighborPU[i][0];
//        cout<<i<<" : ";
//        for(int j = 1; j <= n; j++){
//            cout<<su.sectorNeighborPU[i][j]<<' ';
//        }
//        cout<<endl;
//    }
//    cout<<rendPair.first<<' '<<rendPair.second<<endl;
//    MySU &su1 = allSU[1];
//    for(int i = 0; i < su1.transSectorNum; i++){
//        int n = (int)su1.sectorNeighborPU[i][0];
//        cout<<i<<" : ";
//        for(int j = 1; j <= n; j++){
//            cout<<su1.sectorNeighborPU[i][j]<<' ';
//        }
//        cout<<endl;
//    }
    
    /*******************Sector Rendezvous Only********************************/
//    for(int i = 0; i < SIMULATION_REPEAT_TIME; i++){
////        START_REND_TIME = my_randint(TOTAL_TIME_SLOT/5, TOTAL_TIME_SLOT/2);
//        sectorRendOnly();
//    }
//    cout<<"Aver time: "<<total0*1.0/rend_count0<<endl;
//    cout<<"rend times: "<<rend_count0*100.0/SIMULATION_REPEAT_TIME<<endl;
//    cout<<"Aver time: "<<total1*1.0/rend_count1<<endl;
//    cout<<"rend times: "<<rend_count1*100.0/SIMULATION_REPEAT_TIME<<endl;
    /*******************Sector Rendezvous Only********************************/
    
    /*******************Channel and sector rendezvous ***************************/
    total0 = total1 = 0;
    rend_count0 = rend_count1 = 0;
    for(int i = 0; i < SIMULATION_REPEAT_TIME; i++){
        START_REND_TIME = my_randint(TOTAL_TIME_SLOT/5, TOTAL_TIME_SLOT/4);
        initChannelAndSectorRend();
        initChannelAndSectorRendRandom();
        for(int t = 0; t < TOTAL_TIME_SLOT; t++){
            if(t >= START_REND_TIME){
                if(!rendSuc0) channelAndSectorRend(t);
                if(!rendSuc1) channelAndSectorRendRandom(t);
            }
        }
    }
    cout<<"my rend times: "<<total0/rend_count0<<endl;
    cout<<"random rend times: "<<total1/rend_count1<<endl;
    cout<<"my rend count: "<<rend_count0<<endl;
    cout<<"random rend count: "<<rend_count1<<endl;
    /*******************Channel and sector rendezvous ***************************/
}

