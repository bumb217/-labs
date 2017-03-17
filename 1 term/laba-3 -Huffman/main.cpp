//
//  main.cpp
//  laba-3
//
//  Created by Андрей Пригода on 23.01.17.
//  Copyright © 2017 Андрей Пригода. All rights reserved.
//

#include "HuffmanCoding.hpp"
#include <iostream>
#include <thread>


int main()
{
    HuffmanCoder Compressor = HuffmanCoder();
    
    std::cout << "Choose archive file:\n";
    std::string OutputFile;
    std::cin >> OutputFile;
    
    while (true)
    {
        std::cout << "Choose coding file or press Q to exit:\n";
        std::string InputFile;
        std::cin >> InputFile;
        if (InputFile == "Q" || InputFile == "q")
            break;
        else Compressor.AddToArchive(InputFile, OutputFile);
    }
    
    Compressor.ConvertToArchive();
    return 0;
}
