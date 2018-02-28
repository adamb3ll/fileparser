#!/usr/bin/python

import sys

def fileparser(argv):
	if len(argv) < 4:
		print "Usage: fileparser [inputfile] [firstsearchterm] [secondsearchterm]"
		print "       fileparser [-verbose] [inputfile] [firstsearchterm] [secondsearchterm]"
		sys.exit(1)
		
	inputFileIndex = 1
	mainParamStartIndex = 2
	verbose = False
	if len(argv) > 2 and sys.argv[1] == "-verbose":
		mainParamStartIndex+=1
		inputFileIndex+=1
		verbose = True
		
	currentSearchIndex = mainParamStartIndex
	with open( argv[inputFileIndex] ) as f:			
		for currentLine in f:
			if currentLine.find(argv[currentSearchIndex]) != -1:
				if verbose == True:
					print "Found", argv[currentSearchIndex]
					if currentSearchIndex + 1 == len(argv):
						sys.exit(0)
					currentSearchIndex+=1
		
if __name__ == "__main__":
   fileparser(sys.argv)