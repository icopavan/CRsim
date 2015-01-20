//
//  max_flow.cpp
//  CRsim
//
//  Created by Ji on 14-11-4.
//  Copyright (c) 2014年 lj. All rights reserved.
//

#include "max_flow.h"

int maxFlowEkForAdjMatrix(GraphAdjMatrix *g)
{
    int source = g->sourceID, sink =g->sinkID;
    int flow = 0, maxc = g->maxCapacity, data;
    int vis[MAX_NODE_NUM], pre[MAX_NODE_NUM], low[MAX_NODE_NUM];
    for(data = 0; data < 31; data++){
        if((1<<data) > maxc) break;
    }
    data = (1<<(data-1));
    while(data >= 1){
        do{
            memset(vis, 0, sizeof(vis));
            memset(pre, 0, sizeof(pre));
            memset(low, 0, sizeof(low));
            int q[MAX_NODE_NUM], head = 1, tail = 0;
            low[source] = INT_MAX_VAL;
            q[head] = source;
            while(head != tail){
                int u = q[++tail];
                for(int v = source; v <= sink && !vis[sink]; v++){
                    if(!vis[v] && g->remain[u][v] >= data){
                        vis[v] = 1;
                        low[v] = g->remain[u][v];
                        pre[v] = u;
                        q[++head] = v;
                        if(low[v] > low[u]) low[v] = low[u];
                    }
                }
            }
            if(low[sink] > 0){
                flow += low[sink];
                int j = sink, i;
                while(j != source){
                    i = pre[j];
                    g->remain[i][j] -= low[sink];
                    g->remain[j][i] += low[sink];
                    j = i;
                }
            }
        }while(low[sink] > 0);
        data = data >> 1;
    }
    return flow;
}
