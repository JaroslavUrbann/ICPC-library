#!/usr/bin/env bash
# stress.h mysol slowsol generator number of tests

g++ "$1" -o mysol
g++ "$2" -o slowsol
g++ "$3" -o gen
x=$4/10+1
for ((testNum=0;testNum<$4;testNum++))
do
    ./gen > input
    ./slowsol < input > outSlow
    ./mysol < input > outWrong
    H1=`md5sum outWrong`
    H2=`md5sum outSlow`
    if !(cmp -s "outWrong" "outSlow")
    then
        echo "Error found!"
        echo "Input:"
        cat input
        echo "Wrong Output:"
        cat outWrong
        echo "Slow Output:"
        cat outSlow
        exit
    fi
		if !((testNum%x))
		then
			echo "passed $testNum tests"
		fi
done
echo Passed $4 tests
 
 
