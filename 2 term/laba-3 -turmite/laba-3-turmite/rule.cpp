//
//  rule.cpp
//  laba-3(turmite)
//
//  Created by Андрей Пригода on 25.04.17.
//  Copyright © 2017 Андрей Пригода. All rights reserved.
//

#include "rule.h"

Rule::Rule(pair<char, int> beg, pair<char, int> end, DIR dir) {
    cur_state = beg.first;
    cur_col = beg.second;
    
    new_state = end.first;
    new_col = end.second;
    
    direction = dir;
}
