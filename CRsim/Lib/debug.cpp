//
//  debug.cpp
//  CRsim
//
//  Created by Ji on 14-10-3.
//  Copyright (c) 2014年 lj. All rights reserved.
//

#include "debug.h"

void printArrayFrom1(int x[], int n)
{
    for(int i = 1; i <= n; i++) cout<<x[i]<<' ';
    cout<<endl;
}

void printArrayFrom0(int x[], int n)
{
    for(int i = 0; i < n; i++) cout<<x[i]<<' ';
    cout<<endl;
}

void printVectorFrom1(vI x)
{
    for(int i = 1; i < x.size(); i++){
        cout<<x[i]<<' ';
    }
    cout<<endl;
}

void printVectorVector(vector<vI> x)
{
    if(x.size() <= 1){
        cout<<"The vector is empty\n";
    }
    for(int i = 1; i < x.size(); i++){
        for(int j = 0; j < x[i].size(); j++){
            cout<<x[i][j]<<' ';
        }
        cout<<endl;
    }
}

void printVectorOfPair(vP x)
{
    for(int i = 0; i < x.size(); i++){
        cout<<x[i].first<<' '<<x[i].second<<"; ";
    }
    cout<<endl;
}

void printShit()
{
    cout<<"shit"<<endl;
}
