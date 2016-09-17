#!/bin/bash
file="$1"
if [ ! -d "$HOME/.trashBin/" ]
	then
	mkdir "$HOME/.trashBin/"
fi
if [ -e "$file" ]
	then
	date=$(date '+%y%m%d%H%M%S')
	prozessid=$$
	mv $file "$HOME/.trashBin/$date""_$prozessid.dat"
	echo "$date""_$prozessid.dat! $file" >> $HOME/.trashBin/.dir
	echo "$date""_$prozessid.dat"
fi
