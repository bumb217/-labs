//
//  main.cpp
//  laba05
//
//  Created by Андрей Пригода on 25.01.17.
//  Copyright © 2017 Андрей Пригода. All rights reserved.
//

#define _CRT_SECURE_NO_WARNINGS
#include "TwoDimensionalArray.h"
#include <iostream>
#include <cstdio>
#include <list>

int main()
{
    freopen("input.txt", "r", stdin); freopen("output.txt", "w", stdout);
    int NumberCol, NumberRow;
    std::cin >> NumberRow >> NumberCol;
    TwoDimensionalArray<int> st(NumberRow, NumberCol);
    int Data;
    for (int i = 0; i < NumberRow; i++)
        for (int j = 0; j < NumberCol; j++)
        {
            std::cin >> Data;
            st.SetValue(i, j, Data);
        }
    for (int i = 0; i < NumberRow; i++)
    {
        for (int j = 0; j < NumberCol; j++)
            std::cout << st[i][j] << ' ';
        puts("");
    }
    return 0;
}
