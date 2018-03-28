//
//  fileparser.h
//  fileparser
//
//  Created by Adam on 2018-03-22.
//  Copyright © 2018 Adam Bell. All rights reserved.
//

#ifndef fileparser_h
#define fileparser_h

#include <vector>
#include <string>

static bool verbose = false;

int FileParser(int argc, const char * argv[]);
void HandleParameters();
void OutputUsage();
int Install();
bool CheckHelp(int argc, const char * argv[]);
bool CheckInstall(int argc, const char * argv[]);
bool CheckVerbose(int argc, const char * argv[]);
void ReadPipe( std::vector<std::string>& pipeContents );
bool ReadFile( const std::string& filename, std::vector<std::string>& fileContents );
int Parse( const std::vector<std::string>& stringContents, const std::vector<std::string>& searches );


#endif /* fileparser_h */
