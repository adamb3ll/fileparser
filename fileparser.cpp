//
//  main.cpp
//  fileparser
//
//  Created by Adam on 2018-02-24.
//  Copyright © 2018 Adam Bell. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>

int main(int argc, const char * argv[])
{
    std::vector<std::string> searches;
    std::vector<std::string> fileContents;
    
    if( argc < 4 )
    {
        std::cout << "Usage: ";
        std::cout << "fileparser [inputfile] [firstsearchterm] [secondsearchterm]" << std::endl;
        std::cout << "       fileparser [-verbose] [inputfile] [firstsearchterm] [secondsearchterm]" << std::endl;
        return 1;
    }
    int inputFileIndex = 1;
    int mainParamStartIndex = 2;
    bool verbose = false;
    if( argc > 2 && argv[1] == std::string("-verbose") )
    {
        mainParamStartIndex++;
        inputFileIndex++;
        verbose = true;
    }
    
    std::string inFile = argv[inputFileIndex];
    std::ifstream readfile( inFile.c_str() );
    
    for( int searchStr = mainParamStartIndex; searchStr < argc; searchStr++ )
    {
        searches.push_back( argv[searchStr] );
    }
    
    const int LINE_BUFFER = 1024;
    char inBuff[LINE_BUFFER] = "";
    if( readfile.is_open() )
    {
        while( readfile.getline( inBuff, LINE_BUFFER ) )
        {
            fileContents.push_back(inBuff);
        }
        readfile.close();
        int currSearchIndex = 0;
        std::string currString = searches[currSearchIndex];
        for( const std::string& curr : fileContents)
        {
            std::size_t found = curr.find(searches[currSearchIndex]);
            if (found!=std::string::npos)
            {
                if( verbose ) std::cout << "Found: " << searches[currSearchIndex] << std::endl;
                if( currSearchIndex + 1 == searches.size() )
                {
                    return 0;
                }
                currSearchIndex++;
            }
        }
    }
    else
    {
        if( verbose ) std::cout << "Failed to open file: " << inFile << std::endl;
    }
    return 1;
}
