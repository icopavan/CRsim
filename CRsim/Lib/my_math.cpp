//
//  my_math.cpp
//  CRsim
//
//  Created by Ji on 14-10-4.
//  Copyright (c) 2014年 lj. All rights reserved.
//

#include "my_math.h"

static unsigned int random_seed = (int)time(0);

int my_rand()
{
    srand(random_seed);
    int tmp = 0;
    int t = 100;
    int t1 = rand() % t;
    for(int i = 0; i < t; i++){
        tmp = rand();
        random_seed += tmp + (int)time(0);
        if(i == t1) break;
    }
    return tmp;
}

int my_randint(int start, int end)
{
    assert(start <= end);
    int len = end - start + 1;
    int ans = my_rand() % len;
    return start + ans;
}

double myRandomExp(double _lambda)
{
    if(_lambda <= EPS) return INT_MAX_VAL;
    double u = 0.0;
    while(1){
        u = (double)my_rand()/(double)RAND_MAX;
        if(1.0 - u >= 1e-6){
            break;
        }
    }
    u = (-1.0/_lambda) * log(1.0-u);
    return u;
}

int binaryStringToInt(string x)
{
    int ans = 0;
    for(int i = 0; i < x.length(); i++){
        if(x[i] == '0'){
            ans += 1<<(i);
        }
    }
    return ans;
}

string rightShift(string x, int n)
{
    string tmp(x.length(), '0');
    for(int i = 0; i < x.length(); i++){
        int cur = i + n;
        if(cur >= x.length()) cur -= x.length();
        tmp[cur] = x[i];
    }
    return tmp;
}

string intToBinaryString(int x)
{
    string ans = "";
    while(x > 0){
        int tmp = x % 2;
        ans += (char)(tmp + '0');
        x >>= 1;
    }
    return ans;
}

string intToBinaryString(int x, int n)
{
    string ans = "";
    while(x > 0){
        int tmp = x % 2;
        ans += (char)(tmp + '0');
        x >>= 1;
    }
    while(ans.length() < n) ans += '0';
    return ans;
}

double disSquareTwoPoint(double x1, double y1, double x2, double y2)
{
    return (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2);
}

static double nChooseM[105][105] = {0};
double myNchooseM(int n, int m)
{
    if(n < 0 || m < 0) return 0;
    if(m >= n) return 0;
    if(m == 0) return 1;
    if(m == 1) return n;
    if(nChooseM[n][m] > EPS) return nChooseM[n][m];
    nChooseM[n][m] = myNchooseM(n-1, m) + myNchooseM(n-1, m-1);
    return nChooseM[n][m];
}

