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
        memset(tmp.chanAvaiTimeCount, 0, sizeof(tmp.chanAvaiTimeCount));
        memset(tmp.chanAvaiTimeTotal, 0, sizeof(tmp.chanAvaiTimeTotal));
        memset(tmp.chanAvaiRoundCount, 0, sizeof(tmp.chanAvaiRoundCount));
        memset(tmp.chanUsedTimeCount, 0, sizeof(tmp.chanUsedTimeCount));
        memset(tmp.chanCurTotalAvaiTime, 0, sizeof(tmp.chanCurTotalAvaiTime));
        tmp.neighborPU.clear();
        for(int j = 0; j < PU_NUM; j++){
            if(disTwoPoint(tmp.location.first, tmp.location.second, allPU[j].location.first, allPU[j].location.second) <= SENSE_RANGE_SU * SENSE_RANGE_SU){
                tmp.neighborPU.push_back(j);
            }
        }
        allSU.push_back(tmp);
    }
    allSU.push_back(allSU[0]);
    allSU.push_back(allSU[1]);
}

double totalAnswer1 = 0.0;
double totalAnswer2 = 0.0;
double totalAnswer3 = 0.0;
const   int START_REND_TIME = my_randint(1, TOTAL_TIME_SLOT/10);
const int countChannelID = TOTAL_CHAN_NUM/2; //which channel to count the continuous available time slot;
bool preAvai[SU_NUM+2][TOTAL_CHAN_NUM+5] = {1};
vI countAvaiTimeSlot;

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
                if(preAvai[i][j] == false){
                    su.chanAvaiRoundCount[j]++;
                }
                su.chanCurTotalAvaiTime[j]++;
                su.chanAvaiTimeCount[j]++;
                su.chanAvaiTimeTotal[j]++;
                if(t == TOTAL_TIME_SLOT-1){
                    if(i == 0 && j == countChannelID){
                        countAvaiTimeSlot.push_back(su.chanCurTotalAvaiTime[j]);
                    }
                }
            }
            if(avai[j] == false){
                if(preAvai[i][j] == true){
                    if(i == 0 && j == countChannelID){
                        countAvaiTimeSlot.push_back(su.chanCurTotalAvaiTime[j]);
                    }
                    su.chanCurTotalAvaiTime[j] = 0;
                }
                su.chanAvaiTimeCount[j] = 0;
            }
            preAvai[i][j] = avai[j];
        }
    }
}

double totalRatio = 0;

void MyNetwork:: jumpStay(int t)
{
    SU &su0 = allSU[0];
    SU &su1 = allSU[1];
    int c0 = su0.chanHop->get_chan_t(allSU[0].curSysTimeSlot + t);
    int c1 = su1.chanHop->get_chan_t(allSU[1].curSysTimeSlot + t);
    su0.curStayChan = c0;
    su1.curStayChan = c1;
    sort(su0.avaiChan.begin(), su0.avaiChan.end());
    sort(su1.avaiChan.begin(), su1.avaiChan.end());
//            cout<<"Time "<<t<<' '; printVector(allSU[0].avaiChan);
//            cout<<"Time "<<t<<' '; printVector(allSU[1].avaiChan);
//            cout<<"Common available channels: ";
    vI tmp = getComFromTwoVector(su0.avaiChan, su1.avaiChan);
    cout<<su0.avaiChan.size()<<" : "; printVector(su0.avaiChan);
    cout<<su1.avaiChan.size()<<" : "; printVector(su1.avaiChan);
    cout<<tmp.size()<<" : "; printVector(tmp);
//    cout<<((double)1.0*tmp.size())/su0.avaiChan.size();
//    totalRatio += ((double)1.0*tmp.size())/su0.avaiChan.size();
    if(t < TOTAL_TIME_SLOT - 1){
//        cout<<", ";
    }
    if(t == TOTAL_TIME_SLOT - 1)  {
//        cout<<"];"<<endl;
//        cout<<totalRatio / TOTAL_TIME_SLOT<<endl;
    }
    cout<<"c0, c1: "<<c0<<' '<<c1<<endl;
//    if(c1 == c0){
//        if(vec_find_int(su0.avaiChan, c0) && vec_find_int(su1.avaiChan, c1)){
//                cout<<"Js: ";
//                cout<<t<<' '<<t-START_REND_TIME<<endl;
//        }
//    }
}

void MyNetwork::jumpStayRadomRep(int t)
{
    /////////////////////////////////////Jump stay with random replacement////////////////////////////////////////////
    /////////////////////////////////////Jump stay with random replacement////////////////////////////////////////////
    SU &su0 = allSU[0];
    SU &su1 = allSU[1];
    int c2 = su0.curStayChan;
    int c3 = su1.curStayChan;
    if(!vec_find_int(su0.avaiChan, c2)) c2 = su0.avaiChan[my_randint(0, (int)su0.avaiChan.size()-1)];
    if(!vec_find_int(su1.avaiChan, c3)) c3 = su1.avaiChan[my_randint(0, (int)su1.avaiChan.size()-1)];
    cout<<"c2, c3: "<<c2<<' '<<c3<<endl;
//    if(c3 == c2){
//        cout<<"Js Random: ";
//        cout<<t<<' '<<t-START_REND_TIME<<endl;
//    }
}

void MyNetwork:: printConAvaiTime()
{
    /////////////////////////////////////Print continuous available time for a channel////////////////////////////////////////////
//    cout<<"x = [";
    int n = (int)countAvaiTimeSlot.size();
    int sum = 0;
    for(int i = 0; i < n; i++){
//        cout<<countAvaiTimeSlot[i];
        sum += countAvaiTimeSlot[i];
        if( i < n-1){
//            cout<<", ";
        }
    }
//    cout<<"];"<<endl;
//    cout<<"Aver avai len: "<<sum/n<<endl;
    total_mea += (double)sum/n;
}

void MyNetwork:: calAverConAvaiTime()
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
}

void MyNetwork::startSimulation()
{
    countAvaiTimeSlot.clear();
    memset(preAvai, 1, sizeof(preAvai));
//    cout<<"x = [";
    for(int t = 0; t < TOTAL_TIME_SLOT; t++){
        getSUsCurAvaiChan(t);
//        if(t > START_REND_TIME){
//            cout<<"#############################################"<<endl;
//            cout<<"t: "<<t<<endl;
//            jumpStay(t);
//            jumpStayRadomRep(t);
//            cout<<"#############################################"<<endl<<endl;
//        }
    }
    calAverConAvaiTime();
    printConAvaiTime();
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
