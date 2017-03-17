//
//  HuffmanCoding.cpp
//  laba-3
//
//  Created by Андрей Пригода on 25.01.17.
//  Copyright © 2017 Андрей Пригода. All rights reserved.
//

#include "HuffmanCoding.hpp"
#include <fstream>

void HuffmanCoder::CompressToArchive(std::string InputName, std::string ArchiveName)
{
    std::ofstream ArchiveFile;
    if (Write)
        ArchiveFile.open(ArchiveName, std::ios_base::app);
    else ArchiveFile.open(ArchiveName, std::ios_base::out), Write = true;
    std::ifstream InputFile;
    InputFile.open(InputName, std::ios_base::in);
    if (InputFile.is_open())
    {
        int Frequency[UniqueSymbols] = { 0 };
        std::string InputBuffer, TotalBuffer = "";
        while (std::getline(InputFile, InputBuffer))
        {
            TotalBuffer += InputBuffer;
            for (auto Symbol : InputBuffer)
                Frequency[int(Symbol)]++;
        }
        TNode* Root = BuildTree(Frequency);
        HuffCodeMap CurrentCodeMap;
        CurrentCodeMap.clear();
        GenerateCodes(Root, std::string(), CurrentCodeMap);
        for (auto Symbol : TotalBuffer)
            ArchiveFile << CurrentCodeMap[Symbol];
    }
}

void HuffmanCoder::AddToArchive(std::string InputName, std::string ArchiveName)
{
    CompressionQueue.push_back(std::thread(&HuffmanCoder::CompressToArchive, this, InputName, ArchiveName));
}

void HuffmanCoder::ConvertToArchive()
{
    while (CompressionQueue.size())
    {
        if (CompressionQueue.back().joinable())
        {
            CompressionQueue.back().join();
            CompressionQueue.pop_back();
        }
    }
}

HuffmanCoder::HuffmanCoder()
{
    CompressionQueue.clear();
    Write = false;
}

TNode* HuffmanCoder::BuildTree(const int(&Frequencies)[UniqueSymbols])
{
    std::priority_queue<TNode*, std::vector<TNode*>, NodeCompare> Trees;
    
    for (int Symbol = 0; Symbol < UniqueSymbols; ++Symbol)
    {
        if (Frequencies[Symbol] != 0)
            Trees.push(new LeafNode(Frequencies[Symbol], (char)Symbol));
    }
    while (Trees.size() > 1)
    {
        TNode* RightChild = Trees.top();
        Trees.pop();
        
        TNode* LeftChild = Trees.top();
        Trees.pop();
        
        TNode* Parent = new InternalNode(RightChild, LeftChild);
        Trees.push(Parent);
    }
    return (Trees.size() ? Trees.top() : nullptr);
}

void HuffmanCoder::GenerateCodes(const TNode* Node, const std::string& Prefix, HuffCodeMap &CurrentCodeMap)
{
    if (!Node)
        return;
    
    if (const LeafNode* Leaf = dynamic_cast<const LeafNode*>(Node))
        CurrentCodeMap[Leaf->Symbol] = Prefix;
    else if (const InternalNode* Internal = dynamic_cast<const InternalNode*>(Node))
    {
        std::string LeftPrefix = Prefix;
        LeftPrefix += "0";
        GenerateCodes(Internal->Left, LeftPrefix, CurrentCodeMap);
        
        std::string RightPrefix = Prefix;
        RightPrefix += "1";
        GenerateCodes(Internal->Right, RightPrefix, CurrentCodeMap);
    }
}
