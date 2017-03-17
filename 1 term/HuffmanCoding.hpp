//
//  HuffmanCoding.hpp
//  laba-3
//
//  Created by Андрей Пригода on 25.01.17.
//  Copyright © 2017 Андрей Пригода. All rights reserved.
//

#pragma once

#include <unordered_map>
#include <climits>
#include <string>
#include <thread>
#include <queue>


const int UniqueSymbols = 1 << CHAR_BIT;

class TNode
{
public:
    const int Frequency;
    
    virtual ~TNode() {}
    
protected:
    TNode(int Frequency) : Frequency(Frequency) {}
};

class InternalNode : public TNode
{
public:
    TNode *const Left;
    TNode *const Right;
    
    InternalNode(TNode* LeftTempNode, TNode* RightTempNode) :
    TNode(LeftTempNode->Frequency + RightTempNode->Frequency), Left(LeftTempNode), Right(RightTempNode) {}
    
    ~InternalNode()
    {
        delete Left;
        delete Right;
    }
};

class LeafNode : public TNode
{
public:
    const char Symbol;
    
    LeafNode(int Frequency, char Symbol) :
    TNode(Frequency), Symbol(Symbol) {}
};

struct NodeCompare
{
    bool operator()(const TNode* LeftTnode, const TNode* RightTnode) const
    {
        return LeftTnode->Frequency > RightTnode->Frequency;
    }
};


class HuffmanCoder
{
public:
    void AddToArchive(std::string InputName, std::string ArchiveName);
    void ConvertToArchive();
    HuffmanCoder();
    
private:
    typedef std::unordered_map<char, std::string> HuffCodeMap;
    bool Write = false;
    std::thread connectionThread;
    std::vector<std::thread> CompressionQueue;
    TNode* BuildTree(const int(&Frequencies)[UniqueSymbols]);
    void GenerateCodes(const TNode* Node, const std::string& Prefix,HuffCodeMap &CurrentCodeMap);
    void CompressToArchive(std::string InputName, std::string ArchiveName);
};
