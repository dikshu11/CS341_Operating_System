#!/bin/sh

count=0

ls $1 | grep -E $2 |

while read file
do
	W="${file%%.*}"
	XYZ="${file#*.}"
	echo "$W"
	echo "$XYZ"
	found=`echo $W | grep -E $2`
	if [ ! -z $found ]
	then
		mv $1/$found"."$XYZ  $1/$3"_"$count"."$XYZ
	fi
	count=`expr $count + 1`

done