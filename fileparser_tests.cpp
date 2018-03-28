//
//  fileparser_tests.cpp
//  fileparser_tests
//
//  Created by Adam on 2018-03-22.
//  Copyright © 2018 Adam Bell. All rights reserved.
//

#include <iostream>
#include "gtest/gtest.h"

GTEST_API_ int main(int argc, char **argv)
{
    printf("Running main() from gtest_main.cc\n");
    testing::InitGoogleTest(&argc, argv);
    //test
    return RUN_ALL_TESTS();
}
