# fileparser

A simple tool for searching for a string and then searching for a second string after the first one is found. 

```
fileparse [optional: -verbose] [inputfile] ["first search string"] ["second search string"]
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
