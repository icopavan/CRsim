//
//  graph.h
//  CRsim
//
//  Created by Ji on 14-11-4.
//  Copyright (c) 2014年 lj. All rights reserved.
//

#ifndef CRsim_graph_h
#define CRsim_graph_h

#include "include.h"

const int MAX_NODE_NUM = 110;// maximum number of nodes

class Edge{
public:
    int start; //start node
    int end; //end node
    int capacity; //capability of each edge
    int remain; //remaining capability of each edge
    int weight; //the weight of each edge
    int next; //the id of the next edge with the same start point;
    Edge(int s, int e);
};

Edge flipAnEdge(int s, int e);

/* node id and edge id all start from 0 */
class GraphEdgeList{
public:
    int nodeNum;
    int edgeNum;
    int curEdgeNum;
    vI edgeStartIndex;
    vector<Edge> allEdge;
    
    GraphEdgeList(int n);
    void addEdge(const Edge &e);
private:
    vI edgeCurIndex;
};

class GraphAdjMatrix{
public:
    int nodeNum;
    int edgeNum;
    int adjMatrix[MAX_NODE_NUM][MAX_NODE_NUM];
    int capacity[MAX_NODE_NUM][MAX_NODE_NUM];
    int maxCapacity;
    int remain[MAX_NODE_NUM][MAX_NODE_NUM];
    int sourceID;
    int sinkID;
    
    GraphAdjMatrix();
    void printAdjMatrixFrom0();
    void printAdjMatrixFrom1();
};

class GraphAdjList{
public:
    int nodeNum;
    int edgeNum;
    struct node{
        int x;
        node* next;
    };
    node *adjList[MAX_NODE_NUM];
    GraphAdjList();
};

#endif
