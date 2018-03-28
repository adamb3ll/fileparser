//
//  test_fileparser.cpp
//  fileparser_tests
//
//  Created by Adam on 2018-03-22.
//  Copyright © 2018 Adam Bell. All rights reserved.
//

#include <stdio.h>
#include "fileparser.h"
#include "gtest/gtest.h"

TEST(FileParserTest, CheckInstall)
{
    // EXPECT RETURN TRUE: Correct number of params (2) and one is install
    {
        char param1[] = "fileparser";
        char param2[] = "-install";
        const char* params[] = { param1, param2 };
        int count = sizeof(params) / sizeof(char*);
        EXPECT_EQ(::CheckInstall(count, params), true );
    }
    // EXPECT RETURN FALSE: Correct number of params (2) and one is wrong
    {
        char param1[] = "fileparser";
        char param2[] = "-install2";
        const char* params[] = { param1, param2 };
        int count = sizeof(params) / sizeof(char*);
        EXPECT_EQ(::CheckInstall(count, params), false );
    }
}

TEST(FileParserTest, CheckHelp)
{
    // EXPECT RETURN TRUE: Correct number of params (2) and one is ?
    {
        char param1[] = "fileparser";
        char param2[] = "?";
        const char* params[] = { param1, param2 };
        int count = sizeof(params) / sizeof(char*);
        EXPECT_EQ(::CheckHelp(count, params), true );
    }
    // EXPECT RETURN FALSE: Correct number of params (2) and one is wrong
    {
        char param1[] = "fileparser";
        char param2[] = "-9";
        const char* params[] = { param1, param2 };
        int count = sizeof(params) / sizeof(char*);
        EXPECT_EQ(::CheckHelp(count, params), false );
    }
}

TEST(FileParserTest, CheckVerbose)
{
    // EXPECT RETURN TRUE: Correct number of params (more than 2) and one is verbose
    {
        char param1[] = "fileparser";
        char param2[] = "-verbose";
        char param3[] = "test";
        const char* params[] = { param1, param2, param3 };
        int count = sizeof(params) / sizeof(char*);
        EXPECT_EQ(::CheckVerbose(count, params), true );
    }
  
    // EXPECT RETURB FALSE: Incorrect number of params (less than 2) and one is verbose
    {
        char param1[] = "fileparser";
        char param2[] = "-verbose";
        const char* params[] = { param1, param2 };
        int count = sizeof(params) / sizeof(char*);
        EXPECT_EQ(::CheckVerbose(count, params), false );
    }
    
    // EXPECT RETURN FALSE: Correct number of params (more than 2) and one is not verbose
    {
        char param1[] = "fileparser";
        char param2[] = "-verboose";
        char param3[] = "test";
        const char* params[] = { param1, param2, param3 };
        int count = sizeof(params) / sizeof(char*);
        EXPECT_EQ(::CheckVerbose(count, params), false );
    }
    
    // EXPECT RETURN FALSE: Correct number of params (more than 2) and one verbose in wrong place
    {
        char param1[] = "fileparser";
        char param2[] = "test";
        char param3[] = "-verboose";
        const char* params[] = { param1, param2, param3 };
        int count = sizeof(params) / sizeof(char*);
        EXPECT_EQ(::CheckVerbose(count, params), false );
    }
}

TEST(FileParserTest, ReadPipe)
{
    std::vector<std::string> pipeContents;
    
    // Too Slow
    //::ReadPipe(pipeContents);
    //EXPECT_EQ(pipeContents.size(), 0);
    
    std::streambuf *backup;
    std::istringstream oss("testdata\ntestdata2\0");
    backup = std::cin.rdbuf();
    std::cin.rdbuf(oss.rdbuf());
    
    ::ReadPipe(pipeContents);
    EXPECT_EQ(pipeContents.size(), 2);
}

TEST( FileParserTest, ReadFile)
{
    std::string filename = "/usr/libexec/apache2/httpd.exp";
    std::vector<std::string> fileContents;
    
    // EXPECT RETURN FALSE
    EXPECT_EQ( ReadFile("noFileFound", fileContents), false );
  
    // EXPECT RETURN TRUE
    EXPECT_EQ( ReadFile(filename, fileContents), true );
    EXPECT_GE( fileContents.size(), 20 );
    EXPECT_EQ( fileContents[5], "ap_expr_exec" );
}

TEST( FileParserTest, Parse )
{
    std::vector<std::string> contents;
    std::vector<std::string> searches;
    
    contents.push_back( "Line 1" );
    contents.push_back( "Line 2" );
    contents.push_back( "Line 3" );
    contents.push_back( "BOOP" );
    contents.push_back( "Line 4" );
    contents.push_back( "Line 5" );
    
    // EXPECT 1 - NOTHING FOUND
    searches.clear();
    searches.push_back( "NOTHIN" );
    EXPECT_EQ( Parse(contents, searches), 1);

    // EXPECT 1 - NOTHING FOUND
    searches.clear();
    searches.push_back( "LINE 2" );
    EXPECT_EQ( Parse(contents, searches), 1);
    
    // EXPECT 0 - FOUND
    searches.clear();
    searches.push_back( "Line 2" );
    EXPECT_EQ( Parse(contents, searches), 0);
    
    // EXPECT 0 - FOUND
    searches.clear();
    searches.push_back( "Line 2" );
    searches.push_back( "BOOP" );
    EXPECT_EQ( Parse(contents, searches), 0);
    
    // EXPECT 1 - NOT FOUND ALL
    searches.clear();
    searches.push_back( "Line 2" );
    searches.push_back( "BOOD" );
    EXPECT_EQ( Parse(contents, searches), 1);
    
    // EXPECT 0 - FOUND
    searches.clear();
    searches.push_back( "Line 2" );
    searches.push_back( "BOOP" );
    searches.push_back( "Line 4" );
    EXPECT_EQ( Parse(contents, searches), 0);
    
    // EXPECT 0 - FOUND
    searches.clear();
    searches.push_back( "Line 2" );
    searches.push_back( "BOOP" );
    searches.push_back( "Line 4" );
    searches.push_back( "Line 5" );
    EXPECT_EQ( Parse(contents, searches), 0);
    
    // EXPECT 1 - NOT FOUND
    searches.clear();
    searches.push_back( "Line 2" );
    searches.push_back( "BOOP" );
    searches.push_back( "Line 4" );
    searches.push_back( "Line 5" );
    searches.push_back( "Line 8" );
    EXPECT_EQ( Parse(contents, searches), 1);
}
