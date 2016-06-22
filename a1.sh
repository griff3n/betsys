#!/bin/bash

if [ "$1" == '' ] 
	then
		echo "Es wurden keine Parameter uebergeben."
		exit(1)
fi

zahl1=$1
zahl2=1
shift
while [ "$1" != '' ]
	do
	zahl2= $zahl2 * $1
	shift
done
echo $zahl2 / $zahl1