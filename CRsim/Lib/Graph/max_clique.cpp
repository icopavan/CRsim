//
//  max_clique.cpp
//  CRsim
//
//  Created by Ji on 14/12/9.
//  Copyright (c) 2014年 lj. All rights reserved.
//

#include "max_clique.h"

bool ifIsClique(GraphAdjMatrix g, vI x)
{
    int n = (int)x.size();
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(g.adjMatrix[x[i]][x[j]] == 0){
                return false;
            }
        }
    }
    return true;
}

void maxCliqueAdjMatrix(GraphAdjMatrix g, int n, vI &ans)
{
    int m = 0;
    for(int i = 1; i < (1<<n); i++){
        vI tmp;
        for(int j = 0; j < n; j++){
            if((1<<j) & i){
                tmp.push_back(j+1);
            }
            if(ifIsClique(g, tmp) && tmp.size() > m){
                m = (int)tmp.size();
                ans.clear();
                for(int i = 0; i < m; i++) ans.push_back(tmp[i]);
            }
        }
    }
}
