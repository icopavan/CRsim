//
//  my_fun.h
//  CRsim
//
//  Created by Ji on 14-10-3.
//  Copyright (c) 2014年 lj. All rights reserved.
//

#ifndef __CRsim__my_fun__
#define __CRsim__my_fun__

#include "include.h"
#include "my_math.h"

template<class T>
void vecFromArrayIndex1(vector<T> &a, T b[], int n)
{
    a.resize(n+2);
    for(int i = 1; i <= n; i++) a[i] = b[i];
}

template<class T>
void vecFromArrayRange(vector<T> &a, T b[], int st, int n)
{
    a.resize(n+2);
    for(int i = st; i <= st+n-1; i++) a[i] = b[i];
}

/*generate n different number in the range [st, ed], return the vector */
extern vI generateDiffRandInt(int n, int st, int ed);

/*binary representation of n, put results into ans, ans[0] is the length*/
extern void binaryRepresent(int n, int ans[]);

/*binary representation with length l of n, put results into ans, ans[0] is the length*/
extern void binaryRepresent(int n, int l, int ans[]);

/*copy elements in a to vector b*/
extern void vectorCopy(vI &a, vI &b);

template<class T>
vector<T> getComFromTwoVector(vector<T> x, vector<T> y)
{
    vector<T> ans;
    for(int i = 0; i < x.size(); i++){
        for(int j = 0; j < y.size(); j++){
            if(x[i] == y[j]){
                ans.push_back(x[i]);
                break;
            }
        }
    }
    return ans;
}

extern void arrayCopyFrom0(int a[], int b[], int n); // copy a to b with n elements;

template<class T>
double averValOfVector(vector<T> x)
{
    double ans = 0;
    for(int i = 0; i < x.size(); i++) ans += x[i];
    return ans/x.size();
}

template<class T>
int vectorFind(const vector<T> &a, T x)
{
    for(int i = 0; i < a.size(); i++){
        if(a[i] == x) return i;
    }
    return -1;
}

template<class T>
int vectorFind(const vector<T> &a, T x, int st, int ed)
{
    assert(st<=ed);
    assert(ed < a.size());
    for(int i = st; i <= ed; i++){
        if(a[i] == x) return i;
    }
    return -1;
}

template<class T>
int vectorSortedFind(const vector<T> &a, T x)
{
    int r = (int)a.size(), l = 0;
    int ans = -1;
    while(l <= r){
        int mid = (l+r)>>1;
        if(a[mid] == x){
            ans = mid;
            break;
        }
        else if(a[mid] > x){
            r = mid - 1;
        }
        else{
            l = mid + 1;
        }
    }
    return ans;
}

template<class T>
int vectorSortedFind(const vector<T> &a, T x, int st, int ed)
{
    assert(st<=ed);
    assert(ed < a.size());
    int r = ed, l = st;
    int ans = -1;
    while(l <= r){
        int mid = (l+r)>>1;
        if(a[mid] == x){
            ans = mid;
            break;
        }
        else if(a[mid] > x){
            r = mid - 1;
        }
        else{
            l = mid + 1;
        }
    }
    return ans;
}

template<class T>
int vectorReverseSortedFind(const vector<T> &a, T x)
{
    int r = (int)a.size(), l = 0;
    int ans = -1;
    while(l <= r){
        int mid = (l+r)>>1;
        if(a[mid] == x){
            ans = mid;
            break;
        }
        else if(a[mid] > x){
            l = mid + 1;
        }
        else{
            r = mid - 1;
        }
    }
    return ans;
}

template<class T>
int vectorReverseSortedFind(const vector<T> &a, T x, int st, int ed)
{
    assert(st<=ed);
    assert(ed < a.size());
    int r = ed, l = st;
    int ans = -1;
    while(l <= r){
        int mid = (l+r)>>1;
        if(a[mid] == x){
            ans = mid;
            break;
        }
        else if(a[mid] > x){
            l = mid + 1;
        }
        else{
            r = mid - 1;
        }
    }
    return ans;
}

#endif /* defined(__CRsim__my_fun__) */
