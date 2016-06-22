#!/bin/bash

stunde=$(date +%H)
name=$(whoami)
if [ "$stunde" -lt "12" ]
	then
		echo "Guten Morgen $name"
elif [ "$stunde" -lt "17" ]
	then
		echo "Guten Tag $name"
else
	echo "Guten Abend $name"
fi
