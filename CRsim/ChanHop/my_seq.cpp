//
//  my_seq.cpp
//  CRsim
//
//  Created by Ji on 14-10-3.
//  Copyright (c) 2014年 lj. All rights reserved.
//

#include "my_seq.h"
#include "my_fun.h"
#include "debug.h"

MyHop:: MyHop():ChanHop()
{
    init_seq();
}

MyHop:: MyHop(int cur_chan_n):ChanHop(cur_chan_n)
{
    init_seq();
}

MyHop:: MyHop(int cur_chan_n, vI &avai):ChanHop(cur_chan_n)
{
    this->avai_chan = avai;
    init_seq();
}

void MyHop::init_my_hop(int t, int st_id)
{
    hop_count = 0;
    rnd_count = 0;
    rnd_st_t = 0;
    st_hop_id = st_id;
    st_id_rnd = 1;
    st_hop_t = t;
}

vector<pI> generate_4m_pairs(int x)
{
    vector<pI>  n_pair;
    int m = x/4;
    for(int r = 0; r < 2*m; r++){
        n_pair.push_back(make_pair(4*m+r, 8*m-r));
    }
    n_pair.push_back(make_pair(2*m+1, 6*m));
    n_pair.push_back(make_pair(2*m, 4*m-1));
    for(int r = 1; r < m; r++){
        n_pair.push_back(make_pair(r, 4*m-1-r));
    }
    n_pair.push_back(make_pair(m,m+1));
    for(int r = 0; r < m-2; r++){
        n_pair.push_back(make_pair(m+2+r, 3*m-1-r));
    }
    return n_pair;
}

vector<pI> generate_4m1_pairs(int x)
{
    vector<pI>  n_pair;
    int m = x/4;
    for(int r = 0; r < 2*m; r++){
        n_pair.push_back(make_pair(4*m+r+2, 8*m+2-r));
    }
    n_pair.push_back(make_pair(2*m+1, 6*m+2));
    n_pair.push_back(make_pair(2*m+2, 4*m+1));
    for(int r = 1; r < m+1; r++){
        n_pair.push_back(make_pair(r, 4*m+1-r));
    }
    n_pair.push_back(make_pair(m+1,m+2));
    for(int r = 1; r < m-1; r++){
        n_pair.push_back(make_pair(m+2+r, 3*m+1-r));
    }
    return n_pair;
}

void MyHop:: init_seq()
{
    
    hop_seq.clear();
    if(M == 0 || M % 4 == 2 || M % 4 == 3){
        return;
    }
    if(M == 4){
        int b[9] = {0,1,1,4,2,3,2,4,3};
        hop_seq.resize(10);
        vecFromArrayIndex1(hop_seq, b, 8);
        return;
    }
    hop_seq.resize(2*M+1);
    vector<pI> n_pairs;
    if(M % 4 == 0){
        n_pairs = generate_4m_pairs(M);
    }
    if(M % 4 == 1){
        n_pairs = generate_4m1_pairs(M);
    }
    for(int i = 0; i < n_pairs.size(); i++){
        hop_seq[n_pairs[i].first] = n_pairs[i].second - n_pairs[i].first;
        hop_seq[n_pairs[i].second] = n_pairs[i].second - n_pairs[i].first;
    }
}

void MyHop:: get_hop_para(int t)
{
    int l = (int)hop_seq.size() - 1;
    rnd_count = (t - st_hop_t) / l;
    st_id_rnd = st_hop_id + rnd_count;
    if(st_id_rnd > l){
        st_id_rnd -= l;
    }
    rnd_st_t = st_hop_t + rnd_count * l ;
    hop_count = t - rnd_st_t + 1;
}

int MyHop:: getChanAtTimeT(int t)
{
    get_hop_para(t);
    int tmp = t - rnd_st_t;
    int cur = st_id_rnd + tmp;
    if(cur > (hop_seq.size()-1)){
        cur -= (hop_seq.size()-1);
    }
    curChan = hop_seq[cur];
    return curChan;
}
