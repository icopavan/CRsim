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
const   int START_REND_TIME = my_randint(1, TOTAL_TIME_SLOT/10);
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
        tmp.location = make_pair(SIDE_LENGTH*(i+1) / 3.0, SIDE_LENGTH*(i+1)/3.0);
        tmp.curSysTimeSlot = my_randint(1, 10000000);
        tmp.chanHop = new JsHop();
        tmp.neighborPU.clear();
        for(int j = 0; j < PU_NUM; j++){
            if(disTwoPoint(tmp.location.first, tmp.location.second, allPU[j].location.first, allPU[j].location.second) <= SENSE_RANGE_SU * SENSE_RANGE_SU){
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
    for(int i = 0; i < SU_NUM; i++){
        SU &su = allSU[i];
        su.avaiChan.clear();
        bool avai[TOTAL_CHAN_NUM+5];
        for(int j = 1; j <= TOTAL_CHAN_NUM; j++){
            avai[j] = true;
        }
        for(int j = 0; j < su.neighborPU.size(); j++){
            int n = su.neighborPU[j];
            int c = allPU[n].chanOfEachTimeSlot[t];
            if(c > 0){
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

void MyNetwork:: jumpStay(int t)
{
    SU &su0 = allSU[0];
    SU &su1 = allSU[1];
    int c0 = su0.chanHop->get_chan_t(allSU[0].curSysTimeSlot + t);
    int c1 = su1.chanHop->get_chan_t(allSU[1].curSysTimeSlot + t);
    su0.curStayChan = c0;
    su1.curStayChan = c1;
//    bool flag0 = vec_find_int(su0.avaiChan, c0);
//    bool flag1 = vec_find_int(su1.avaiChan, c1);
//    if(flag0 && flag1) SU0SU1avai += 1;
//    if(!flag0 && flag1) SU1avai += 1;
//    if(flag0 && !flag1) SU0avai += 1;
//    if(!flag1 && !flag0) SU0SU1notAvai += 1;
//    sort(su0.avaiChan.begin(), su0.avaiChan.end());
//    sort(su1.avaiChan.begin(), su1.avaiChan.end());
//            cout<<"Time "<<t<<' '; printVector(allSU[0].avaiChan);
//            cout<<"Time "<<t<<' '; printVector(allSU[1].avaiChan);
//            cout<<"Common available channels: ";
//    vI tmp = getComFromTwoVector(su0.avaiChan, su1.avaiChan);
//    cout<<su0.avaiChan.size()<<" : "; printVector(su0.avaiChan);
//    cout<<su1.avaiChan.size()<<" : "; printVector(su1.avaiChan);
//    cout<<tmp.size()<<" : "; printVector(tmp);
//    cout<<((double)1.0*tmp.size())/su0.avaiChan.size();
//    totalRatio += ((double)1.0*tmp.size())/su0.avaiChan.size();
//    totalSURatio += (1.0*su0.avaiChan.size())/TOTAL_CHAN_NUM;
    if(t < TOTAL_TIME_SLOT - 1){
//        cout<<", ";
    }
    if(t == TOTAL_TIME_SLOT - 1)  {
//        cout<<"];"<<endl;
//        totalAnswer1 += totalRatio / TOTAL_TIME_SLOT;
//        totalAnswer2 += totalSURatio / TOTAL_TIME_SLOT;
//        cout<<"Average common available ratio: "<<totalRatio / TOTAL_TIME_SLOT<<endl;
//        int tt = TOTAL_TIME_SLOT - START_REND_TIME;
//        cout<<"Average SU available ratio: "<<totalSURatio/tt<<endl;
//        cout<<"Ratio distribution: "<<SU0SU1avai/tt<<' '<<SU0avai/tt<<' '<<SU1avai/tt<<' '<<SU0SU1notAvai/tt<<endl;
//        double tmp = totalSURatio/tt;
//        cout<<"Calculated Distribution: "<<tmp*tmp<<' '<<tmp*(1-tmp)<<' '<<tmp*(1-tmp)<<' '<<(1-tmp)*(1-tmp)<<endl;
//        cout<<"Total replacement ratio: "<<(SU0avai+SU1avai+SU0SU1notAvai)/tt<<endl;
//        totalAnswer1 += (SU0avai+SU1avai+SU0SU1notAvai)/tt;
    }
//    cout<<"c0, c1: "<<c0<<' '<<c1<<endl;
//    if(c1 == c0){
//        if(vec_find_int(su0.avaiChan, c0) && vec_find_int(su1.avaiChan, c1)){
//                cout<<"Js: ";
//                cout<<t<<' '<<t-START_REND_TIME<<endl;
//        }
//    }
}

void MyNetwork::jsRadomRep(int t)
{
    /////////////////////////////////////Jump stay with random replacement////////////////////////////////////////////
    if(rendSuc1) return;
    SU &su0 = allSU[0];
    SU &su1 = allSU[1];
    int c0 = su0.curStayChan;
    int c1 = su1.curStayChan;
    if(!vec_find_int(su0.avaiChan, c0)) c0 = su0.avaiChan[my_randint(0, (int)su0.avaiChan.size()-1)];
    if(!vec_find_int(su1.avaiChan, c1)) c1 = su1.avaiChan[my_randint(0, (int)su1.avaiChan.size()-1)];
    if(c0 == c1){
//        cout<<"Js Random: ";
//        cout<<t<<' '<<t-START_REND_TIME<<endl;
        totalAnswer1 += t-START_REND_TIME;
        rendSuc1 = 1;
    }
}

void MyNetwork::jsRandomRepRandomSense(int t)
{
    /*********************************
     Jump stay with random replacement
     
     *********************************/
    SU &su0 = allSU[0];
    SU &su1 = allSU[1];
    int c0 = su0.curStayChan;
    int c1 = su1.curStayChan;
    if(!vec_find_int(su0.avaiChan, c0)){
        vI sen0 = generateDiffRandNum(MAX_SENSE_CHAN_NUM-1, 1, TOTAL_CHAN_NUM);
        sen0.push_back(c0);
        vI curAvai0;
        for(int i = 1; i <= TOTAL_CHAN_NUM; i++){
            if(vec_find_int(su0.avaiChan, i) && vec_find_int(sen0, i)){
                curAvai0.push_back(i);
            }
        }
        if(curAvai0.size() < 1) return;
        c0 = curAvai0[my_randint(0, (int)curAvai0.size()-1)];
    }
    if(!vec_find_int(su1.avaiChan, c1)){
        vI sen1 = generateDiffRandNum(MAX_SENSE_CHAN_NUM-1, 1, TOTAL_CHAN_NUM);
        sen1.push_back(c1);
        vI curAvai1;
        for(int i = 1; i <= TOTAL_CHAN_NUM; i++){
            if(vec_find_int(su1.avaiChan, i) && vec_find_int(sen1, i)){
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

void MyNetwork:: jsConAvaiTimeRandRendezvous(int t)
{
    /////////////////////////////////////Always choose the channel with the largest con avai time////////////////////////////////////////////
    if(rendSuc2) return;
    SU &su0 = allSU[0];
    SU &su1 = allSU[1];
    int c0 = su0.curStayChan;
    int c1 = su1.curStayChan;
    if(!vec_find_int(su0.avaiChan, c0)){
        sort(su0.allChanObj+1, su0.allChanObj+1+TOTAL_CHAN_NUM, cmpConAvaiTimeReverse);
        c0 = su1.allChanObj[my_randint(1, 7)].ID;
        sort(su0.allChanObj+1, su0.allChanObj+1+TOTAL_CHAN_NUM, cmpID);
    }
//    for(int i = 1; i <= TOTAL_CHAN_NUM; i++) cout<<su0.allChanObj[i].curConAvaiTime<<' '; cout<<endl;
    if(!vec_find_int(su1.avaiChan, c1)){
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

static int rendSucCount  = 0;
void MyNetwork:: conAvaiTimeRandRendezvous(int t)
{
    /////////////////////////////////////Always choose the channel with the largest con avai time////////////////////////////////////////////
    if(rendSuc3) return;
    SU &su0 = allSU[0];
    SU &su1 = allSU[1];
    sort(su0.allChanObj+1, su0.allChanObj+1+TOTAL_CHAN_NUM, cmpConAvaiTimeReverse);
    int c0 = su1.allChanObj[my_randint(1, 7)].ID;
    sort(su0.allChanObj+1, su0.allChanObj+1+TOTAL_CHAN_NUM, cmpID);
    //    for(int i = 1; i <= TOTAL_CHAN_NUM; i++) cout<<su0.allChanObj[i].curConAvaiTime<<' '; cout<<endl;
    sort(su1.allChanObj+1, su1.allChanObj+1+TOTAL_CHAN_NUM, cmpConAvaiTimeReverse);
    int c1 = su1.allChanObj[my_randint(1, 7)].ID;
    sort(su1.allChanObj+1, su1.allChanObj+1+TOTAL_CHAN_NUM, cmpID);
    //    for(int i = 1; i <= TOTAL_CHAN_NUM; i++) cout<<su1.allChanObj[i].curConAvaiTime<<' '; cout<<endl;
    //    cout<<c0<<' '<<c1<<endl;
    if(c0 == c1){
//        cout<<"Con avai time rend:  ";
//        cout<<t<<' '<<t-START_REND_TIME<<endl;
        totalAnswer3 += t-START_REND_TIME;
        rendSuc3 = 1;
        rendSucCount++; cout<<rendSucCount<<' ';
    }
}

void MyNetwork:: jsKeepRep(int t)
{
    SU &su0 = allSU[0];
    SU &su1 = allSU[1];
    int c0 = su0.curStayChan;
    int c1 = su1.curStayChan;
    if(!vec_find_int(su0.avaiChan, c0)){
        if(su0.lastStayChan < 1 || su0.alreadyStayTime >= KEEP_TIME || (!vec_find_int(su0.avaiChan, su0.lastStayChan))){
            c0 = su0.avaiChan[my_randint(0, (int)su0.avaiChan.size())];
            su0.lastStayChan = c0;
            su0.alreadyStayTime = 1;
        }
        else{
            c0 = su0.lastStayChan;
            su0.alreadyStayTime++;
        }
    }
    if(!vec_find_int(su1.avaiChan, c1)){
        if(su1.lastStayChan < 1 || su1.alreadyStayTime >= KEEP_TIME  || (!vec_find_int(su1.avaiChan, su1.lastStayChan))){
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

void MyNetwork::initSimulation()
{
    countAvaiTimeSlot.clear();
    memset(preAvai, 1, sizeof(preAvai));
//    cout<<"x = [";
//    totalRatio = 0;
//    totalSURatio = 0;
    rendSuc1 = rendSuc2 = rendSuc3 = 0;
    SU &su0 = allSU[0];
    SU &su1 = allSU[1];
    su0.lastStayChan = 0; su1.lastStayChan = 0;
    su0.alreadyStayTime = 0; su1.alreadyStayTime = 0;
    SU0SU1notAvai = SU0avai = SU1avai = SU0SU1avai = 0;
}

void MyNetwork::startSimulation()
{
    initSimulation();
//    for(int t = 0; t < TOTAL_TIME_SLOT; t++){
//        if(rendSuc1 && rendSuc2 && rendSuc3){
//            return;
//        }
//        getSUsCurAvaiChan(t);
//        getCurAllChanConAvaiTime();
//        if(t > START_REND_TIME){
//            jumpStay(t);
//            jsRadomRep(t);
//            jsConAvaiTimeRandRendezvous(t);
//            conAvaiTimeRandRendezvous(t);
//        }
//    }
    calConAvaiChanAverConAvaiTime();
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
