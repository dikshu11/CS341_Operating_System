#!/bin/sh

lines=0
while IFS="" read -r line
do
	lines=`expr $lines + 1`
done < $1

# echo $lines

if [ $lines  -lt $2 ]
then
	rm $1
fi


