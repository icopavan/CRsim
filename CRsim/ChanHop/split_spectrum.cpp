//
//  split_spectrum.cpp
//  CRsim
//
//  Created by Ji on 14-10-3.
//  Copyright (c) 2014年 lj. All rights reserved.
//

#include "split_spectrum.h"
#include "my_split_spec.h"

SplitSpec:: SplitSpec()
{
    M = CHAN_N;
    SSL.clear();
    SSL.push_back(-1);//make sure from index 1
}

SplitSpec:: SplitSpec(int cur_chan_n)
{
    M = cur_chan_n;
    SSL.clear();
    SSL.push_back(-1);//make sure from index 1
}

void SplitSpec:: get_ssl(void (*split_scheme) (int , vI &), int cur_chan_n, vI &ssl)
{
    split_scheme(cur_chan_n, ssl);
}

