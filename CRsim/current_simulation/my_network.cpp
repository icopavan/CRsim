//
//  my_network.cpp
//  CRsim
//
//  Created by Ji on 14-10-7.
//  Copyright (c) 2014年 lj. All rights reserved.
//

#include "my_network.h"

MyNetwork:: MyNetwork() : CRNetwork()
{
//    initChanSegment();
    suNum = SU_NUM;
    initAllSU();
    simTimeSlot = TOTAL_TIME_SLOT;
    curResult1 = INT_MAX_VAL;
}

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

/*split the whole spectrum into several segments,
 the number of channel in each segments is the number
 of CR of each SU
 */
void MyNetwork:: initChanSegment()
{
    segNum = (TOTAL_CHAN_NUM + CR_NUM - 1) / CR_NUM;
    for(int i = 1; i <= TOTAL_CHAN_NUM/CR_NUM; i++){
        for(int j = 1; j <= CR_NUM; j++){
            chanInSeg[i][j] = (i-1)*CR_NUM + j;
        }
    }
    if(segNum > TOTAL_CHAN_NUM/CR_NUM){
        int tmp = TOTAL_CHAN_NUM % CR_NUM;
        int m = TOTAL_CHAN_NUM/CR_NUM * CR_NUM;
        for(int i = 1; i <= tmp; i++){
            chanInSeg[segNum][i] = i+m;
        }
        vI tmp1 = generateDiffRandNum(CR_NUM-tmp, 1, m);
        for(int i = tmp+1; i <= CR_NUM; i++){
            chanInSeg[segNum][i] = tmp1[i-tmp-1];
        }
    }
}

void MyNetwork:: initFirstAlgorithmJs()
{
    for(int i = 1; i <= 2; i++){
        jsSu[i].avaiChan.clear();
        jsSu[i].avaiChan = jsSu[i].getAvaiChanRandom();
        for(int j = 1; j <= CR_NUM; j++){
            jsSu[i].allCR[j].chanHop = new JsHop(TOTAL_CHAN_NUM);
            jsSu[i].allCR[j].curSysTimeSlot = my_randint(0, 100000);
        }
    }
    curResult1 = INT_MAX_VAL;
    ifRendezvous1 = 0;
}

void MyNetwork::firstAlgorithmJs()
{
    initFirstAlgorithmJs();
    cout<<"#########################"<<endl;
    for(int t = 1; t <= TOTAL_TIME_SLOT; t++){
        for(int i = 1; i <= 2; i++){
            int vis[TOTAL_CHAN_NUM+2][SU_NUM+2] = {0};
            int count = 0;
            for(int j = 1; j <= CR_NUM; j++){
                int tmp = jsSu[i].allCR[j].chanHop->get_chan_t(jsSu[i].allCR[j].curSysTimeSlot+t);
                jsSu[i].allCR[j].curStayChan = tmp;
                jsSu[i].allCR[j].sendOrReceive = (SEND_OR_RECEIVE)0;
                if(vis[tmp][0] == 0){
                    count++;
                }
                vis[tmp][++vis[tmp][0]] = j;
            }
            int bi[TOTAL_CHAN_NUM+2] = {0};
            binaryRepresent(my_randint(0, max(0,(1<<CR_NUM)-1)), count, bi);
            int cur = 0;
            for(int j = 1; j <= TOTAL_CHAN_NUM; j++){
                if(vis[j][0] > 0){
                    cur++;
                    if(bi[cur-1] == 1){
                        int tmp = my_randint(1, vis[j][0]);
                        tmp = vis[j][tmp];
                        jsSu[i].allCR[tmp].sendOrReceive = (SEND_OR_RECEIVE)1;
                    }
                }
            }
        }
        for(int i = 1; i <= CR_NUM; i++){
            for(int j = 1; j <= CR_NUM; j++){
                if(jsSu[1].allCR[i].curStayChan == jsSu[2].allCR[j].curStayChan &&
                   (jsSu[1].allCR[i].sendOrReceive ^ jsSu[2].allCR[j].sendOrReceive) == 1 &&
                   vec_find_int(jsSu[1].avaiChan, jsSu[1].allCR[i].curStayChan) &&
                   vec_find_int(jsSu[2].avaiChan, jsSu[2].allCR[j].curStayChan) ){
                    cout<<"Time for type 1 is: "<<t<<endl;
                    curResult1 = t;
                    ifRendezvous1 = 1;
                    return;
                }
            }
        }
    }
    cout<<"#########################"<<endl;
}

void MyNetwork:: initSecondAlgorithmJs()
{
    jsSu2.clear();
    for(int i = 0; i < jsSu.size(); i++){
        jsSu2.push_back(jsSu[i]);
    }
    for(int i = 1; i <= 2; i++){
        jsSu2[i].chanHop = new JsHop(segNum);
    }
    curResult2 = INT_MAX_VAL;
    ifRendezvous2 = 0;
}

void MyNetwork::secondAlgorithmJsFirstVersion()
{
    initSecondAlgorithmJs();
    for(int t = 1; t <= simTimeSlot; t++){
        for(int i = 1; i <= suNum; i++){
            jsSu2[i].curStayChan = jsSu2[i].chanHop->get_chan_t(jsSu2[i].curSysTimeSlot+t);
        }
        int c1 = jsSu2[1].curStayChan;
        int c2 = jsSu2[2].curStayChan;
        if(c1 == c2){
            int vis1[TOTAL_CHAN_NUM+2][SU_NUM+2] = {0};
            int vis2[TOTAL_CHAN_NUM+2][SU_NUM+2] = {0};
            int num1 = 0, num2 = 0;
            vI curAvai1;
            vI curAvai2;
            for(int j = 1; j <= CR_NUM; j++){
                int t1 = chanInSeg[c1][j], t2 = chanInSeg[c2][j];
                if(vec_find_int(jsSu2[1].avaiChan, t1)){
                    curAvai1.push_back(t1);
                }
                if(vec_find_int(jsSu2[2].avaiChan, t2)){
                    curAvai2.push_back(t2);
                }
            }
            if(curAvai1.size() == 0 || curAvai2.size() == 0){
                continue;
            }
            for(int j = 1; j <= CR_NUM; j++){
                int t1 = chanInSeg[c1][j], t2 = chanInSeg[c2][j];
                jsSu2[1].allCR[j].sendOrReceive = (SEND_OR_RECEIVE)0;
                jsSu2[2].allCR[j].sendOrReceive = (SEND_OR_RECEIVE)0;
                if(vec_find_int(jsSu2[1].avaiChan, t1)){
                    jsSu2[1].allCR[j].curStayChan = t1;
                }
                else{
//                    jsSu2[1].allCR[j].curStayChan = curAvai1[my_randint(0, (int)curAvai1.size()-1)];
                    jsSu2[1].allCR[j].curStayChan = jsSu2[1].avaiChan[my_randint(0, (int)jsSu2[1].avaiChan.size()-1)];
                }
                int t11 = jsSu2[1].allCR[j].curStayChan;
                if(vis1[t11][0] == 0) num1++;
                vis1[t11][++vis1[t11][0]] = j;
                
                if(vec_find_int(jsSu2[2].avaiChan, t2)){
                    jsSu2[2].allCR[j].curStayChan = t2;
                }
                else{
//                    jsSu2[2].allCR[j].curStayChan = curAvai2[my_randint(0, (int)curAvai2.size()-1)];
                    jsSu2[2].allCR[j].curStayChan = jsSu2[2].avaiChan[my_randint(0, (int)jsSu2[2].avaiChan.size()-1)];
                }
                int t22 = jsSu2[2].allCR[j].curStayChan;
                if(vis2[t22][0] == 0) num2++;
                vis2[t22][++vis2[t22][0]] = j;
            }
            int tmp = my_randint(0, max(0,(1<<num1)-1));
            int tmp1 = my_randint(0, max(0,(1<<num2)-1));
            int b1[100] = {0}, b2[100] = {0};
            binaryRepresent(tmp, num1, b1);
            binaryRepresent(tmp1, num2, b2);
            for(int j = 1; j <= CR_NUM; j++){
                if(b1[j-1] == 1){
                    int c1 = jsSu2[1].allCR[j].curStayChan;
                    int t1 = my_randint(1, vis1[c1][0]);
                    jsSu2[1].allCR[vis1[c1][t1]].sendOrReceive = (SEND_OR_RECEIVE)1;
                }
                if(b2[j-1] == 1){
                    int c2 = jsSu2[2].allCR[j].curStayChan;
                    int t2 = my_randint(1, vis2[c2][0]);
                    jsSu2[2].allCR[vis2[c2][t2]].sendOrReceive = (SEND_OR_RECEIVE)1;
                }
            }
            for(int i = 1; i <= CR_NUM; i++){
                for(int j = 1; j <= CR_NUM; j++){
                    if(jsSu2[1].allCR[i].curStayChan == jsSu2[2].allCR[j].curStayChan &&
                       (jsSu2[1].allCR[i].sendOrReceive ^ jsSu2[2].allCR[j].sendOrReceive) == 1){
                        cout<<"Time for type 2 is: "<<t<<endl;
                        curResult2 = t;
                        ifRendezvous2 = 1;
                        return;
                    }
                }
            }
        }
    }
}

void MyNetwork:: secondAlgorithmJs()
{
    initSecondAlgorithmJs();
    for(int t = 1; t <= simTimeSlot; t++){
        for(int i = 1; i <= 2; i++){
            jsSu2[i].curStayChan = jsSu2[i].chanHop->get_chan_t(jsSu2[i].curSysTimeSlot+t);
        }
        int c1 = jsSu2[1].curStayChan;
        int c2 = jsSu2[2].curStayChan;
        vI curAvai1;
        vI curAvai2;
        bool flag = 0;
        for(int i = c1; ; ){
            for(int j = 1; j <= CR_NUM; j++){
                if(vec_find_int(jsSu2[1].avaiChan, chanInSeg[i][j])){
                    curAvai1.push_back(chanInSeg[i][j]);
                    if(curAvai1.size() >= CR_NUM){
                        flag = 1;
                        break;
                    }
                }
            }
            if(flag) break;
            i++;
            if(i > segNum) i  = 1;
        }
        flag = 0;
        for(int i = c2; ; ){
            for(int j = 1; j <= CR_NUM; j++){
                if(vec_find_int(jsSu2[2].avaiChan, chanInSeg[i][j])){
                    curAvai2.push_back(chanInSeg[i][j]);
                    if(curAvai2.size() >= CR_NUM){
                        flag = 1;
                        break;
                    }
                }
            }
            if(flag) break;
            i++;
            if(i > segNum) i  = 1;
        }
        int b1[CR_NUM+2] = {0};
        int b2[CR_NUM+2] = {0};
        binaryRepresent(my_randint(0, (1<<CR_NUM)-1), CR_NUM, b1);
        binaryRepresent(my_randint(0, (1<<CR_NUM)-1), CR_NUM, b2);
        for(int i = 0; i < CR_NUM; i++){
            for(int j = 0; j < CR_NUM; j++){
                if(curAvai1[i] == curAvai2[j] && ((b1[i] ^ b2[j]) == 1)){
                    cout<<"Time for type 2 is: "<<t<<endl;
                    curResult2 = t;
                    ifRendezvous2 = 1;
                    return;
                }
            }
        }
    }
}

void MyNetwork:: initThirdAlgorithmJs()
{
    initAllSuNeighbors();
    for(int i  = 1; i <= suNum; i++){
        jsSu[i].avaiChan = jsSu[i].getAvaiChanRandom();
        jsSu[i].avaiChanNum = (int)jsSu[i].avaiChan.size();
        jsSu[i].usedChanNum = min(jsSu[i].avaiChanNum, (int)(CR_NUM * USED_CHAN_RATIO));
        jsSu[i].notUsedCrNum = CR_NUM - jsSu[i].usedChanNum;
        jsSu[i].stillAvaiChan.clear();
        for(int j = jsSu[i].usedChanNum; j < jsSu[i].avaiChanNum; j++){
            jsSu[i].stillAvaiChan.push_back(jsSu[i].avaiChan[j]);
        }
        printVector(jsSu[i].stillAvaiChan);
        jsSu[i].newAllocChanRandom.clear();
        for(int j = 0; j < jsSu[i].stillAvaiChan.size(); j++){
            jsSu[i].newAllocChanRandom.push_back(jsSu[i].stillAvaiChan[j]);
            if(jsSu[i].newAllocChanRandom.size() >= jsSu[i].notUsedCrNum){
                break;
            }
        }
    }
}

int myMin(int x, int y)
{
    return x < y ? x : y;
}

void MyNetwork:: theRandomAlgorithm()
{
    for(int i = 1; i <= suNum; i++){
        printVector(jsSu[i].stillAvaiChan);
        jsSu[i].newAllocChanRandom.clear();
        vI tmp = generateDiffRandNum(myMin(jsSu[i].notUsedCrNum, (int)jsSu[i].stillAvaiChan.size()), 0, (int)jsSu[i].stillAvaiChan.size()-1);
        printVector(tmp);
        for(int j = 0; j < tmp.size(); j++){
            jsSu[i].newAllocChanRandom.push_back(jsSu[i].stillAvaiChan[tmp[j]]);
        }
        printVector(jsSu[i].newAllocChanRandom);
    }
    int ans = 0;
    for(int i = 1; i <= suNum; i++){
        for(int j = 0; j < jsSu[i].newAllocChanRandom.size(); j++){
            bool flag = 1;
            for(int k = 0; k < jsSu[i].neighbors.size(); k++){
                if(vectorFindFrom0(jsSu[k].newAllocChanRandom, jsSu[i].newAllocChanRandom[j])){
                    flag = 0;
                    break;
                }
            }
            if(flag) ans++;
        }
    }
    cout<<"Random Algorithm: "<<ans*1.0/suNum<<endl;
}

bool cmp(vI a, vI b)
{
    return a.size() > b.size();
}

void MyNetwork:: thirdAlgorithmJs()
{
    initThirdAlgorithmJs();
    theRandomAlgorithm();
    vI chanAllocList[TOTAL_CHAN_NUM+2];
    for(int i = 1; i <= TOTAL_CHAN_NUM; i++){
        GraphAdjMatrix g;
        g.nodeNum = suNum;
        for(int j = 1; j <= suNum; j++){
            if(vectorFindFrom0(jsSu[j].avaiChan, i)){
                g.adjMatrix[j][j] = 1;
            }
        }
        for(int j = 1; j <= suNum; j++){
            for(int k = 1; k <= suNum; k++){
                if(j != k && vectorFindFrom0(jsSu[j].stillAvaiChan, i) &&
                   vectorFindFrom0(jsSu[k].stillAvaiChan, i) &&
                   !vectorFindFrom0(jsSu[j].neighbors, k)){
                    g.adjMatrix[j][k] = g.adjMatrix[k][j] = 1;
                }
            }
        }
        maxCliqueAdjMatrix(g, suNum, chanAllocList[i]);
        chanAllocList[i].push_back(i);
    }
    sort(chanAllocList+1, chanAllocList+1+TOTAL_CHAN_NUM, cmp);
    for(int i = 1; i <= TOTAL_CHAN_NUM; i++){
    }
    int totalAllocChanNum = 0;
    for(int i = 1; i <= TOTAL_CHAN_NUM; i++){
        int curChan = chanAllocList[i][chanAllocList[i].size()-1];
        for(int j = 1; j <= suNum; j++){
            if(vectorFindFrom0(chanAllocList[i], j) &&
               jsSu[j].notUsedCrNum > 0){
                jsSu[j].newAllocChan.push_back(curChan);
                totalAllocChanNum++;
                jsSu[j].notUsedCrNum--;
            }
        }
    }
    for(int i = 1; i <= suNum; i++){
//        printVector(jsSu[i].newAllocChan);
    }
    cout<<"My Algorithm: "<<totalAllocChanNum*1.0/suNum<<endl;
}

void MyNetwork::startSimulation()
{
//    thirdAlgorithmJs();
//    int sum1 = 0, sum2 = 0;
//    int count1 = 0, count2 = 0;
//    for(int i = 0; i < SIMULATION_REPEAT_TIME; i++){
//        firstAlgorithmJs();
//        if(ifRendezvous1){
//            sum1 += curResult1;
//            count1++;
//        }
//        secondAlgorithmJs();
//        if(ifRendezvous2){
//            sum2 += curResult2;
//            count2++;
//        }
//    }
//    cout<<"Average rendezvous time of first one: "<<sum1*1.0/count1<<endl;
//    cout<<"Successful ratio of first one: "<<count1*1.0/SIMULATION_REPEAT_TIME*100<<endl;
//    cout<<"Average rendezvous time of second one: "<<sum2*1.0/count2<<endl;
//    cout<<"Successful ratio of second one: "<<count2*1.0/SIMULATION_REPEAT_TIME*100<<endl;
    return;
}