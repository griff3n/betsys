#!/bin/bash
file="$1"
if [ ! -d "$HOME/.trashBin/" ]
	then
	mkdir "$HOME/.trashBin/"
fi
trash="$HOME/.trashBin/"
if [ -e "$trash$file" ]
	then
	zeilen=$(wc -l "$HOME/.trashBin/.dir" | cut -d" " -f1)
	tdir=""	
	for((i=1;i <= $zeilen;i++))
	do
		line=$(head -n $i "$HOME/.trashBin/.dir" | tail -n 1)
		temp=${line%%"!"*}
		
		if [  $file = $temp ]
			then
			ziel=${line##*" "}
			zieldir=${ziel%"/"*}
			if [ -d "$zieldir" ]
				then
				mv $trash$file $ziel
			else
				echo "Der ursprüngliche Pfad existiert nicht mehr"
				$tdir = $tdir + $line + "\n\c"	
			fi
		else
		$tdir = $tdir + $line + "\n\c"	
		fi
	done
	echo $tdir > "$HOME/.trashBin/.dir"
fi
