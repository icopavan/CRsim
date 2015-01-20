//
//  split_spectrum.h
//  CRsim
//
//  Created by Ji on 14-10-3.
//  Copyright (c) 2014年 lj. All rights reserved.
//

#ifndef __CRsim__split_spectrum__
#define __CRsim__split_spectrum__

#include "include.h"

class SplitSpec{
public:
    vI SSL;// Spectrum splitting list
    int M; //total number of channels
    
    SplitSpec();
    SplitSpec(int cur_chan_n);
    void get_ssl(void (*split_scheme) (int , vI &), int cur_chan_n, vI &ssl);
};

#endif /* defined(__CRsim__split_spectrum__) */
