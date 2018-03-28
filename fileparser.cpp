//
//  fileparser.cpp
//  fileparser
//
//  Created by Adam on 2018-03-22.
//  Copyright © 2018 Adam Bell. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "fileparser.h"

int FileParser(int argc, const char * argv[])
{
    std::vector<std::string> searches;
    std::vector<std::string> stringContents;
    
    if( CheckHelp( argc, argv ) )
    {
        OutputUsage();
        return 1;
    }
    
    if( CheckInstall( argc, argv) )
    {
        int suc = Install();
        if( suc == 0 )
            std::cout << "Installed" << std::endl;
        else std::cout << "Error " << suc << std::endl;
        return suc;
    }
    
    if( argc < 3 )
    {
        OutputUsage();
        return 1;
    }
    
    // Mark out param indices doe input file index and the search params
    int inputFileIndex = 1;
    int mainParamStartIndex = 2;
    
    // Check for verbose mode
    if( CheckVerbose( argc, argv ) )
    {
        mainParamStartIndex++;
        inputFileIndex++;
        verbose = true;
    }
    
    // If user wants to read from pipe, then do so
    if( argv[inputFileIndex] == std::string("-pipe") )
    {
        ReadPipe(stringContents);
    }
    if( verbose ) std::cout << "Pipe: " << stringContents.size() << std::endl;
    
    // Grab our searches
    for( int searchStr = mainParamStartIndex; searchStr < argc; searchStr++ )
    {
        searches.push_back( argv[searchStr] );
    }
    
    // If not read from pipe read from file
    if( stringContents.size() == 0 )
    {
        std::string inFile = argv[inputFileIndex];
        if( ReadFile(inFile, stringContents) == false )
        {
            if( verbose ) std::cout << "Failed to open file: " << inFile << std::endl;
        }
    }
    
    return Parse( stringContents, searches );
}

void OutputUsage()
{
    std::cout << "Usage: " << std::endl;
    std::cout << " sudo fileparser -install" << std::endl;
    std::cout << " fileparser ?" << std::endl;
    std::cout << " fileparser <-verbose> [inputfile] [firstsearchterm] <secondsearchterm> ..." << std::endl;
    std::cout << " fileparser <-verbose> [-pipe] [firstsearchterm] <secondsearchterm> ..." << std::endl;
}

int Install()
{
    return system( "cp -f fileparser /usr/local/bin" );
}

bool CheckHelp(int argc, const char * argv[])
{
    return ( argc == 2 && argv[1] == std::string("?") );
}

bool CheckInstall(int argc, const char * argv[])
{
    return ( argc == 2 && argv[1] == std::string("-install") );
}

bool CheckVerbose(int argc, const char * argv[])
{
    return ( argc > 2 && argv[1] == std::string("-verbose") );
}

void ReadPipe( std::vector<std::string>& pipeContents )
{
    std::ios_base::sync_with_stdio(false);
    for (std::string line; std::getline(std::cin, line);)
    {
        pipeContents.push_back(line);
    }
}

bool ReadFile( const std::string& filename, std::vector<std::string>& fileContents )
{
    bool returnVal = false;
    std::ifstream readfile( filename.c_str() );
    const int LINE_BUFFER = 1024;
    char inBuff[LINE_BUFFER] = "";
    if( readfile.is_open() )
    {
        while( readfile.getline( inBuff, LINE_BUFFER ) )
        {
            fileContents.push_back(inBuff);
        }
        readfile.close();
        returnVal = true;
    }
    return returnVal;
}

int Parse( const std::vector<std::string>& stringContents, const std::vector<std::string>& searches )
{
    if( stringContents.size() )
    {
        int currSearchIndex = 0;
        std::string currString = searches[currSearchIndex];
        for( const std::string& curr : stringContents)
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
    return 1;
}

