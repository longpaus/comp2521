#!/bin/bash

for fileNum in 1 2 3 4 5 6;do
    (./testGraphMST < tests/graphMST/$fileNum.in) > testFile
    diff -u testFile $fileNum.exp
    if test $? -eq 1 ;then
        echo "Fail task$fileNum"
    else
        echo "pass task$fileNum"
    fi
done
