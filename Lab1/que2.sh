#!/bin/sh

a=$1

if [ $a -le $2 ]
then
  while [ $a -le $2 ]
  do
	printf "%s " $a
	a=`expr $a + 1`
  done
else
  while [ $a -ge $2 ]
  do
	printf "%s " $a
	a=`expr $a - 1`
  done
fi


echo "$1"
a=$2
if [ $a -le $1 ]
then
  while [ $a -le $1 ]
  do
    printf "Print %s " $a
    a=`expr $a + 1`
  done
else
  while [ $a -ge $1 ]
  do
    printf "X %s " $a
    a=`expr $a - 1`
  done
fi
