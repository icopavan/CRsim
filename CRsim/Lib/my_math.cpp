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
