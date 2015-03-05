//
//  my_fun.cpp
//  CRsim
//
//  Created by Ji on 14-10-3.
//  Copyright (c) 2014年 lj. All rights reserved.
//

#include "my_fun.h"
#include "debug.h"

bool vec_find_int(vI a, int x)
{
    int l = (int)a.size();
    for(int i = 0; i < l; i++){
        if(a[i] == x) return true;
    }
    return false;
}

vI generateDiffRandInt(int n, int st, int ed)
{
    vI ans;
    set<int> s;
//    cout<<st<<' '<<ed<<endl;
    while(s.size() < n){
        int tmp = my_randint(st, ed);
        if(s.find(tmp) == s.end()){
            s.insert(tmp);
        }
    }
    for(auto it  = s.begin(); it != s.end(); it++){
        ans.push_back(*it);
    }
    return ans;
}

void binaryRepresent(int n, int ans[])
{
    int m = n;
    int i = 0;
    while(m > 0){
        ans[++i] = m % 2;
        m /= 2;
    }
    ans[0] = i;
}

void binaryRepresent(int n, int l, int ans[])
{
    int m = n;
    int i = 0;
    while(m > 0){
        ans[i++] = m % 2;
        m /= 2;
    }
    for(int j = i; j < l; j++) ans[j] = 0;
}

void vectorCopy(vI &a, vI &b)
{
    int n = (int)a.size();
    b.resize(n);
    for(int i = 0; i < n; i++){
        b[i] = a[i];
    }
}

bool vectorFindFrom1(vI a, int x)
{
    for(int i = 1; i < a.size(); i++){
        if(a[i] == x) return true;
    }
    return  false;
}

bool vectorFindFrom0(const vI &a, int x)
{
    for(int i = 0; i < a.size(); i++){
        if(a[i] == x) return true;
    }
    return  false;
}

vI getComFromTwoVector(vI x, vI y)
{
    vI ans;
    for(int i = 0; i < x.size(); i++){
        bool flag = 0;
        for(int j = 0; j < y.size(); j++){
            if(x[i] == y[j]){
                flag = 1;
                break;
            }
        }
        if(flag == 1){
            ans.push_back(x[i]);
        }
    }
    return ans;
}

void arrayCopyFrom0(int a[], int b[], int n)
{
    for(int i = 0; i < n; i++){
        a[i] = b[i];
    }
}

