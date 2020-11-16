#!/bin/sh

# $1 - integer argument 
if [ $#  -eq 0 ]
then
	printf "Error: Argument not passed\n"
else
    echo $1 | rev
fi



if [ $# -eq 0 ]
then
	printf "Error\n"
elif [ $# -eq 2 ]
then
	printf "More than 1 arg\n"
else	
	echo $1 | rev
fi