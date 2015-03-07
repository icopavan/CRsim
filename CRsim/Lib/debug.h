//
//  debug.h
//  CRsim
//
//  Created by Ji on 14-10-3.
//  Copyright (c) 2014年 lj. All rights reserved.
//

#ifndef __CRsim__debug__
#define __CRsim__debug__

#include "include.h"

void printArrayFrom0(int x[], int n);
void printArrayFrom1(int x[], int n);

template<class T>
void printVector(vector<T> x)
{
    if(x.size() <= 0){
        cout<<"The vector is empty\n";
    }
    for(auto p : x){
        cout<<p<<' ';
    }
    cout<<endl;
}

void printVectorFrom1(vI x);
void printVectorVector(vector<vI> x);
void printVectorOfPair(vP x);
void printShit();

#endif /* defined(__CRsim__debug__) */
