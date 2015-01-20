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

/* generate a random number in [start, end] */
extern int my_randint(int start, int end);

extern int binaryStringToInt(string x);

extern string rightShift(string x, int n);

extern string intToBinaryString(int x);

extern string intToBinaryString(int x, int n);

#endif /* defined(__CRsim__my_math__) */
