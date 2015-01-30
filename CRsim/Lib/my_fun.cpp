//
//  my_fun.cpp
//  CRsim
//
//  Created by Ji on 14-10-3.
//  Copyright (c) 2014年 lj. All rights reserved.
//

#include "my_fun.h"
#include "debug.h"

/* all index from 1, copy an array to a vector*/
void vec_copy_from1(vI &a, int b[], int n)
{
    a.resize(n+1);
    for(int i = 1; i <= n; i++){
        a[i] = b[i];
    }
}

void vec_copy_from0(vI &a, int b[], int n)
{
    a.resize(n);
    for(int i = 0; i < n; i++){
        a[i] = b[i];
    }
}

bool vec_find_int(vI a, int x)
{
    int l = (int)a.size();
    for(int i = 0; i < l; i++){
        if(a[i] == x) return true;
    }
    return false;
}

bool find_sorted_vec_int0(const vI a, int x)
{
    int l = 0, r = (int)a.size();
    int mid;
    while(l <= r){
        mid = (l + r) >> 1;
        if(a[mid] == x){
            return true;
        }
        else if(a[mid] > x){
            r = mid - 1;
        }
        else{
            l = mid + 1;
        }
    }
    return false;
}

bool find_sorted_vec_int1(const vI a, int x)
{
    int l = 1, r = (int)a.size();
    int mid;
    while(l <= r){
        mid = (l + r) >> 1;
        if(a[mid] == x){
            return true;
        }
        else if(a[mid] > x){
            r = mid - 1;
        }
        else{
            l = mid + 1;
        }
    }
    return false;
}

vI generateDiffRandNum(int n, int st, int ed)
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

template<typename T>
bool findInSortedVector(const vector<T> &a, T x)
{
    int n = (int)a.size();
    for(int i = 0; i < n; i++){
        if(a[i] == x) return true;
    }
    return false;
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
