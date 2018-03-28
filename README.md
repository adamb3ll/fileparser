# fileparser

A simple tool for searching for a string and then searching for a second string after the first one is found. 
Written in C++. Python and for people who love large executables, Swift.  All versions tested on mac OS High Sierra Only

[Swift Version](https://github.com/adamb3ll/fileparser_swift)

[Python Version](https://github.com/adamb3ll/fileparser_python)

```
fileparser [optional: -verbose] [inputfile] ["first search string"] ["second search string"]
fileparser [optional: -verbose] [-pipe] ["first search string"] ["second search string"]
sudo fileparser -install
```

Returns 0 for successfully finding the first and second string.

## Example usage:

Check to see if a phone is connected to a computer via Bluetooth:

```
system_profiler SPBluetoothDataType > btdata.txt
./fileparser btdata.txt "My iPhone" "Connected: Yes"

if [ $? == 0 ]; then
  echo "Connected"
else
  echo "Not Connected"
fi
```
Using pipe rather than intermediary file:
```
system_profiler SPBluetoothDataType | fileparser -pipe "My iPhone" "Connected: Yes"

if [ $? == 0 ]; then
  echo "Connected"
else
  echo "Not Connected"
fi
```
