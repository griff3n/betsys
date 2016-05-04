#!/bin/bash
file="$1"
if [ -e "$file" ]
	then
	date=$(date '+%y%m%d%H%M%S')
	prozessid=$$
	mv $file $HOME/.trashBin/$date_$prozessid.dat
	echo "$date_$prozessid.dat! $file"
else

fi