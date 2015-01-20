//
//  includes.h
//  CRsim
//
//  Created by Ji on 14-10-3.
//  Copyright (c) 2014年 lj. All rights reserved.
//

#ifndef CRsim_includes_h
#define CRsim_includes_h

#include <vector>
#include <utility>
#include <iostream>
#include <map>
#include <set>
#include <algorithm>
#include <stack>
#include <queue>
#include <string>
#include <cstring>
#include <cmath>
#include <random>
#include <cassert>
#include <cstdlib>
#include <cstdio>
#include <list>
#include <bitset>

#include "global.h"

using namespace std;

typedef long long LL;
typedef unsigned long long ULL;
typedef vector<int> vI;
typedef vector<double> vD;
typedef vector<string> vS;
typedef vector<pair<int, int> > vP;
typedef pair<int, int> pI;
typedef map<int, int> mI;
typedef map<string, int> mSI;
typedef set<int> sI;
typedef set<pI> spI;
typedef priority_queue<int> qmax;
typedef priority_queue<int, vector<int>, greater<int> >qmin;
typedef map<int, int>::iterator mI_it;
typedef set<int>::iterator sI_it;

#define TWO(k)  (1<<(k))
#define LTWO(k) (((LL)(1)<<(k)))
#define MIN(a,b) ( (a)<(b)?(a):(b) )
#define MAX(a,b) ( (a)>(b)?(a):(b) )
#define MP make_pair
#define PB push_back
#define F0(i, n) for( int (i) = 0; (i) < (n); (i)++)
#define F1(i, n) for( int (i) = 1; (i) <= (n); (i)++)

const double EPS = 1e-9;
const double PI = acos(-1.0);
const int ioo = (~0)-(1<<31);
const LL loo = (~(LL)0)-((LL)1<<63);//

#endif
