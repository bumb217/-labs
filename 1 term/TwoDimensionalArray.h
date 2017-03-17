//
//  TwoDimensionalArray.h
//  laba05
//
//  Created by Андрей Пригода on 25.01.17.
//  Copyright © 2017 Андрей Пригода. All rights reserved.
//

#pragma once

#include <iterator>
#include <cassert>
#include <vector>

template <typename AnyData>
class TwoDimensionalArray
{
public:
    TwoDimensionalArray();
    TwoDimensionalArray(int NumberColumn, int NumberRow);
    
    class OneDimensionalArray
    {
    public:
        friend class TwoDimensionalArray<AnyData>;
        OneDimensionalArray(std::vector<AnyData> TempList): TempList(TempList){}
        
        AnyData operator[](int index) {
            assert(0 <= index && index < (int)TempList.size());
            return TempList[index];
        }
        
    private:
        std::vector<AnyData> TempList;
    };
    
    OneDimensionalArray operator[](int index){
        assert(0 <= index && index < (int)ValueList.size());
        return OneDimensionalArray(ValueList[index]);
    }
    
    void SetValue(int Row, int Column, AnyData Val);
    
private:
    int ColumnNumber, RowNumber;
    std::vector<std::vector<AnyData> >  ValueList;
};

template<typename AnyData>
TwoDimensionalArray<AnyData>::TwoDimensionalArray()
{
    ValueList.clear();
    RowNumber = 0;
    ColumnNumber = 0;
}

template<typename AnyData>
TwoDimensionalArray<AnyData>::TwoDimensionalArray(int NumberRow, int NumberColumn)
{
    RowNumber = NumberRow;
    ColumnNumber = NumberColumn;
    ValueList.resize(NumberRow, std::vector<AnyData>(NumberColumn, 0));
}

template<typename AnyData>
inline void TwoDimensionalArray<AnyData>::SetValue(int Row, int Column, AnyData Val)
{
    assert(0 <= Row && Row < RowNumber);
    assert(0 <= Column && Column < ColumnNumber);
    ValueList[Row][Column] = Val;
}
