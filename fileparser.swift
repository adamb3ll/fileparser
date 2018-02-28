//
//  fileparser.swift
//  fileparser
//
//  Created by Adam on 2018-02-26.
//  Copyright © 2018 Adam Bell. All rights reserved.
//

import Foundation

if CommandLine.arguments.count < 4
{
    print( "Usage: fileparser [inputfile] [firstsearchterm] [secondsearchterm]" )
    print( "       fileparser [-verbose] [inputfile] [firstsearchterm] [secondsearchterm]" )
    exit(1)
}

var inputFileIndex = 1
var mainParamStartIndex = 2
var verbose = false

if CommandLine.arguments.count > 2 && CommandLine.arguments[1] == "-verbose"
{
    mainParamStartIndex += 1
    inputFileIndex += 1
    verbose  = true
}

var searches = [String]()

for searchStr in mainParamStartIndex..<CommandLine.arguments.count
{
    searches.append( CommandLine.arguments[searchStr])
}


let fileURL = URL( fileURLWithPath: CommandLine.arguments[inputFileIndex])
var inBuff = ""
do
{
    inBuff = try String( contentsOf: fileURL )
}
catch
{
    if verbose
    {
        print( "Error reading: " + CommandLine.arguments[inputFileIndex] )
    }
    exit(1)
}

let splitString = inBuff.split( separator: "\n")
var currSearchIndex = 0
for currString in splitString
{
    let asString = String(currString)
    if asString.range( of: searches[currSearchIndex] ) != nil
    {
        if verbose
        {
            print( "Found " + searches[currSearchIndex] );
        }
        if currSearchIndex + 1 == searches.count
        {
            exit(0)
        }
        currSearchIndex = currSearchIndex + 1
    }
}

exit(1)
