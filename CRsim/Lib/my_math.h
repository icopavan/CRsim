//
//  my_math.h
//  CRsim
//
//  Created by Ji on 14-10-4.
//  Copyright (c) 2014年 lj. All rights reserved.
//

#ifndef __CRsim__my_math__
#define __CRsim__my_math__

#include "include.h"

extern int my_rand();

/* generate a random number in [start, end] */
extern int my_randint(int start, int end);

extern double myRandomExp(double _lambda);

extern int binaryStringToInt(string x);

extern string rightShift(string x, int n);

extern string intToBinaryString(int x);

extern string intToBinaryString(int x, int n);

double disSquareTwoPoint(double x1, double y1, double x2, double y2);

double myNchooseM(int n, int m);

/* If point z is above the line connected by point x and y */
template<class T>
bool pointAboveLine(pair<T, T> x, pair<T, T> y, pair<T, T> z)
{
    return (y.first-x.first)*(z.second-x.second) - (y.second-x.second)*(z.first-x.first) > EPS;
}

/* If point z is inside the angle formed by line ax and line ay */
template <class T>
bool pointInsideAngle(pair<T,T> a, pair<T, T> x, pair<T, T> y, pair<T, T> z) {
    return pointAboveLine(a, x, z) && pointAboveLine(a, z, y);
}
#endif /* defined(__CRsim__my_math__) */
