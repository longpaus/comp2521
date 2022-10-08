#!/bin/bash
.././runTest 1 > task1Output

diff task1Output 1.exp

if test $? -eq 1 
then
    cat difference
    echo "Fail task1"
else
    echo "pass task1"
fi

rm task1Output

.././runTest 2 > task2Output

diff task2Output 2.exp

if test $? -eq 1 
then
    cat difference
    echo "Fail task2"
else
    echo "pass task2"
fi