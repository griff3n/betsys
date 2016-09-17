#!bin/bash
file=$1
txt=${file##*.}
if [ $txt == txt -a -e "$file" ]
  then
    read -p "$file ist ein Textdokument soll sie angezeigt werden. Ja/Nein" answer
    case "$answer" in
      Yes|yes|Ja|ja|Y|y|J|j)
      	less $file
      ;;
      *)
      ;;
    esac
fi
