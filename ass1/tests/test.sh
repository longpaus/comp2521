#!/bin/bash

# test 1

.././testFlightDb 1 > task1Output

diff task1Output 1.exp

if test $? -eq 1 
then
    cat difference
    echo "Fail task1"
else
    echo "pass task1"
fi

rm task1Output