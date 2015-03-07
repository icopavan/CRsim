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
bool rendSuc1 = 0;
bool rendSuc2= 0;
bool rendSuc3 = 0;
int START_REND_TIME = my_randint(1, TOTAL_TIME_SLOT/10);
const int countChannelID = TOTAL_CHAN_NUM/2; //which channel to count the continuous available time slot;
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
    initAllSU();
}

void MyNetwork:: initAllSU()
{
    for(int i = 0; i < SU_NUM; i++){
        MySU tmp;
        tmp.location = make_pair(SIDE_LENGTH*(i+2) / 5.0, SIDE_LENGTH*(1)/2.0);
        tmp.curSysTimeSlot = my_randint(1, 10000000);
        tmp.chanHop = new JsHop();
        tmp.neighborPU.clear();
        for(int j = 0; j < PU_NUM; j++){
            if(disSquareTwoPoint(tmp.location.first, tmp.location.second, allPU[j].location.first, allPU[j].location.second) <= SENSE_RANGE_SU * SENSE_RANGE_SU){
                tmp.neighborPU.push_back(j);
            }
        }
        for(int j = 1; j <= TOTAL_CHAN_NUM; j++){
            tmp.allChanObj[j].ID = j;
            tmp.allChanObj[j].ifAvai = 0;
            tmp.allChanObj[j].curConAvaiTime = 0;
        }
        allSU.push_back(tmp);
    }
    allSU.push_back(allSU[0]);
    allSU.push_back(allSU[1]);
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
        cout<<"Js Random: ";
        cout<<t-START_REND_TIME<<endl;
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

void MyNetwork:: jsConAvaiTimeRandRend(int t)
{
    /////////////////////////////////////Always choose the channel with the largest con avai time////////////////////////////////////////////
    if(rendSuc2) return;
    SU &su0 = allSU[0];
    SU &su1 = allSU[1];
    int c0 = su0.curStayChan;
    int c1 = su1.curStayChan;
    if(!vectorFind(su0.avaiChan, c0)){
        sort(su0.allChanObj+1, su0.allChanObj+1+TOTAL_CHAN_NUM, cmpConAvaiTimeReverse);
        c0 = su1.allChanObj[my_randint(1, 7)].ID;
        sort(su0.allChanObj+1, su0.allChanObj+1+TOTAL_CHAN_NUM, cmpID);
    }
//    for(int i = 1; i <= TOTAL_CHAN_NUM; i++) cout<<su0.allChanObj[i].curConAvaiTime<<' '; cout<<endl;
    if(!vectorFind(su1.avaiChan, c1)){
        sort(su1.allChanObj+1, su1.allChanObj+1+TOTAL_CHAN_NUM, cmpConAvaiTimeReverse);
        c1 = su1.allChanObj[my_randint(1, 7)].ID;
        sort(su1.allChanObj+1, su1.allChanObj+1+TOTAL_CHAN_NUM, cmpID);
    }
//    for(int i = 1; i <= TOTAL_CHAN_NUM; i++) cout<<su1.allChanObj[i].curConAvaiTime<<' '; cout<<endl;
//    cout<<c0<<' '<<c1<<endl;
    if(c0 == c1){
//        cout<<"Js con avai time: ";
//        cout<<t<<' '<<t-START_REND_TIME<<endl;
        totalAnswer2 += t-START_REND_TIME;
        rendSuc2 = 1;
    }
}

static int rendSucCount1  = 0;
static int rendSucCount2  = 0;
const int NUM_CHOOSE_CHAN = 7;
void MyNetwork:: conAvaiTimeRandRend(int t)
{
    /////////////////////////////////////Always choose the channel with the largest con avai time////////////////////////////////////////////
    if(rendSuc3) return;
    SU &su0 = allSU[0];
    SU &su1 = allSU[1];
    
    sort(su0.allChanObj+1, su0.allChanObj+1+TOTAL_CHAN_NUM, cmpConAvaiTimeReverse);
    int c0 = su1.allChanObj[my_randint(1, NUM_CHOOSE_CHAN)].ID;
    sort(su0.allChanObj+1, su0.allChanObj+1+TOTAL_CHAN_NUM, cmpID);
    
    sort(su1.allChanObj+1, su1.allChanObj+1+TOTAL_CHAN_NUM, cmpConAvaiTimeReverse);
    int c1 = su1.allChanObj[my_randint(1, NUM_CHOOSE_CHAN)].ID;
    sort(su1.allChanObj+1, su1.allChanObj+1+TOTAL_CHAN_NUM, cmpID);
    
    if(c0 == c1){
        cout<<"Con avai time rend:  ";
        cout<<t-START_REND_TIME<<endl;
        totalAnswer3 += t-START_REND_TIME;
        rendSuc3 = 1;
        rendSucCount1++;
        cout<<rendSucCount1<<endl;
    }
}

void MyNetwork:: pureRandomRend(int t)
{
    if(rendSuc2) return;
    SU &su0  = allSU[0];
    SU &su1  = allSU[1];
    int c0 = su0.avaiChan[my_randint(0, (int)su0.avaiChan.size()-1)];
    int c1 = su1.avaiChan[my_randint(0, (int)su1.avaiChan.size()-1)];
    if(c0 == c1){
                cout<<"Pure random rend: ";
                cout<<t-START_REND_TIME<<endl;
        totalAnswer2 += t-START_REND_TIME;
        rendSuc2 = 1;
        rendSucCount2++;
        cout<<rendSucCount2<<endl;
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

void MyNetwork::initSimulation()
{
//    cout<<"x = [";
//    totalRatio = 0;
//    totalSURatio = 0;
    rendSuc1 = rendSuc2 = rendSuc3 = 0;
    for(int i = 0; i < SU_NUM; i++){
        SU &su = allSU[i];
        for(int j = 1; j <= TOTAL_CHAN_NUM; j++){
            su.allChanObj[j].ifAvai = 0;
            su.allChanObj[j].curConAvaiTime = 0;
        }
    }
}

void MyNetwork::startSimulation()
{
    totalAnswer1 = totalAnswer2 = totalAnswer3 = 0;
    for(int i = 0; i < SIMULATION_REPEAT_TIME; i++){
        initSimulation();
        START_REND_TIME = my_randint(TOTAL_TIME_SLOT/5, TOTAL_TIME_SLOT/2);
        for(int t = 0; t < TOTAL_TIME_SLOT; t++){
            if(rendSuc1 && rendSuc2 && rendSuc3){
                break;
            }
            getSUsCurAvaiChan(t);
            getCurAllChanConAvaiTime();
//            printTwoSUsConAvaiTime();
            if(t == TOTAL_TIME_SLOT-1){
//                printAllChanConAvaiTime();
            }
            if(t > START_REND_TIME){
                jumpStayRend(t);
                jsRadomRepRend(t);
                pureRandomRend(t);
                conAvaiTimeRandRend(t);
            }
        }
    //    double sum = 0;
    //    for(int i = 1; i <= TOTAL_CHAN_NUM; i++){
    //        sum += 1.0*chanComAvaiCountSu0Su1[i]/chanAvaiCountSu0[i];
    //    }
    //    cout<<"get com avai ratio: "<< sum/TOTAL_CHAN_NUM<<endl;
    //    calConAvaiChanAverConAvaiTime();
    //    double sum = 0;
    //    for(int i = 1; i <= TOTAL_CHAN_NUM; i++){
    //        double tmp = averValOfVector(allSU[0].allChanObj[i].allConAvaiTime);
    //        cout<<tmp<<' ';
    //        sum += tmp;
    //    }
    //    cout<<endl;
    //    cout<<sum/TOTAL_CHAN_NUM<<endl;
    //    if(!rendSucRandSense) cout<<"Rend rand sense failed\n";
    //    if(!rendSucRand) cout<<"Rend rand failed\n";
    //    calAverConAvaiTime();
    //    printConAvaiTime();
    }
}
