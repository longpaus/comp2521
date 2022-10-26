#!/bin/bash

# test 1

.././testFlightDb 1 > task1Output

diff -u task1Output 1.exp

if test $? -eq 1 
then
    echo "Fail task1"
else
    echo "pass task1"
fi

rm task1Output

# test 2
.././testFlightDb 2 > task2Output

diff -u task2Output 2.exp

if test $? -eq 1 
then
    echo "Fail task2"
else
    echo "pass task2"
fi

rm task2Output

# test 3

.././testFlightDb 3 > task3Output

diff -u task3Output 3.exp

if test $? -eq 1 
then
    echo "Fail task3"
else
    echo "pass task3"
fi

rm task3Output

# test 4
.././testFlightDb 4 > task4Output

diff -u task4Output 4.exp

if test $? -eq 1 
then
    echo "Fail task4"
else
    echo "pass task4"
fi

rm task4Output

# test 5
.././testFlightDb 5 > task5Output

diff -u task5Output 5.exp

if test $? -eq 1 
then
    echo "Fail task5"
else
    echo "pass task5"
fi

rm task5Output
