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

extern void vec_copy_from0(vI &a, int b[], int n);

extern void vec_copy_from1(vI &a, int b[], int n);

extern bool vec_find_int(vI a, int x);

/*generate n different number in the range [st, ed], return the vector */
extern vI generateDiffRandNum(int n, int st, int ed);

/*binary representation of n, put results into ans, ans[0] is the length*/
extern void binaryRepresent(int n, int ans[]);

/*binary representation with length l of n, put results into ans, ans[0] is the length*/
extern void binaryRepresent(int n, int l, int ans[]);

/*copy elements in a to vector b*/
extern void vectorCopy(vI &a, vI &b);

extern vI getComFromTwoVector(vI x, vI y);

extern void arrayCopyFrom0(int a[], int b[], int n); // copy a to b with n elements;

template<typename T>
double averValOfVector(vector<T> x)
{
    double ans = 0;
    for(int i = 0; i < x.size(); i++) ans += x[i];
    return ans/x.size();
}

template<typename T>
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

template<typename T>
int vectorFind(const vector<T> &a, T x)
{
    for(int i = 0; i < a.size(); i++){
        if(a[i] == x) return i;
    }
    return -1;
}

#endif /* defined(__CRsim__my_fun__) */
