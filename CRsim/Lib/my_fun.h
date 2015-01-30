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

extern bool vectorFindFrom1(vI a, int x);

extern bool vectorFindFrom0(const vI &a, int x);

template <typename T>
bool findInSortedVector(const vector<T> &a, T x);

extern bool find_sorted_vec_int0(const vI a, int x); //index from 0;

extern bool find_sorted_vec_int1(const vI a, int x); //index from 0;

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

#endif /* defined(__CRsim__my_fun__) */
