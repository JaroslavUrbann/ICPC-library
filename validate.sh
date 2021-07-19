#!/usr/bin/env bash
# validate.sh solution validator generator numTests
# validator gets concatenated input and solution
 
g++ "$1" -o sol
g++ "$2" -o val
g++ "$3" -o gen
for ((testNum=0;testNum<$4;testNum++))
do
    ./gen > genin
    ./sol < genin > out
    cat genin out > data
    ./val < data > res
    result=$(cat res)
    if [ "${result:0:2}" != "OK" ];
    then
        echo "Error found!"
        echo "Input:"
        cat geinin
        echo "Output:"
        cat out
        echo "Validator Result:"
        cat res 
        exit
    fi
done
echo Passed $4 tests
 
 
