#!/bin/bash

cd part1/01
./pageRank 0.85 0.000010 1000 > outPut

diff -u outPut exp.txt

if test $? -eq 1 
then
    echo "Fail 01"
else
    echo "pass 01"
fi

cd ../02
./pageRank 0.85 0.000010 1000 > outPut

diff -u outPut exp.txt

if test $? -eq 1 
then
    echo "Fail 02"
else
    echo "pass 02"
fi

cd ../03

./pageRank 0.85 0.000010 1000 > outPut

diff -u outPut exp.txt

if test $? -eq 1 
then
    echo "Fail 03"
else
    echo "pass 03"
fi

rm outPut


