#!/bin/bash
cmake -S . -B build
cp -r ui build
cd build && make

retVal=$?
if [ $retVal -ne 0 ]; then
    echo "Error while building"
    exit $retVal
fi

if [[ $# > 0 && "$1" == "t" ]]
then 
   ./timerapptest --gtest_catch_exceptions=0
else
    ./timerapp
fi

cd ..