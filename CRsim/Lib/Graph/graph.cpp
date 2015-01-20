//
//  graph.cpp
//  CRsim
//
//  Created by Ji on 14-11-4.
//  Copyright (c) 2014年 lj. All rights reserved.
//

#include "graph.h"

Edge:: Edge(int s, int e)
{
    start = s;
    end = e;
    next = -1;
}

Edge flipAnEdge(const Edge &e)
{
    Edge tmp = e;
    int t = tmp.end;
    tmp.end = tmp.start;
    tmp.start= t;
    return tmp;
}

GraphEdgeList::GraphEdgeList(int n)
{
    edgeStartIndex.resize(n+1);
    edgeCurIndex.resize(n+1);
    for(int i = 0; i <= n; i++){
        edgeStartIndex[i] = -1;
        edgeCurIndex[i] = -1;
    }
    curEdgeNum = 0;
}

void GraphEdgeList:: addEdge(const Edge &e)
{
    allEdge.push_back(e);
    curEdgeNum++;
    if(edgeStartIndex[e.start] == -1){
        edgeStartIndex[e.start] = curEdgeNum-1; //edge index from 0
    }
    if(edgeCurIndex[e.start] != -1){
        allEdge[edgeCurIndex[e.start]].next = curEdgeNum-1;
    }
    edgeCurIndex[e.start] = curEdgeNum - 1;
}

GraphAdjMatrix:: GraphAdjMatrix()
{
    memset(adjMatrix, 0, sizeof(adjMatrix));
    memset(capacity, 0, sizeof(capacity));
    memset(remain, 0, sizeof(remain));
    maxCapacity = 0;
}

void GraphAdjMatrix:: printAdjMatrixFrom0()
{
    int n = nodeNum;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(capacity[i][j]) cout<<i<<' '<<j<<endl;
        }
    }
}

void GraphAdjMatrix:: printAdjMatrixFrom1()
{
    int n = nodeNum;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            cout<<adjMatrix[i][j]<<' ';
        }
        cout<<endl;
    }
}