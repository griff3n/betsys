#!/bin/bash
dateiexistiert() {
  file="$1"
  if [ -e "$file" ] 
    then
      echo "Die Datei $file existiert"
  elif [ -d "$file" ]
    then
      echo "Das Verzeichnis $file existiert"
  else
    echo "$file existiert nicht"
  fi
}

dateiregular() {
  file="$1"
  if [ -f "$file" ] 
    then
      echo "$file ist eine regulaere Datei"
  elif [ -d "$file" ]
    then
      echo "$file ist ein Verzeichnis"
  else
    echo "$file ist weder eine regulaere Datei oder ein Verzeichnis" 
  fi
}

symblink() {
  file="$1"
  if [ -h "$file" ] 
    then
      echo "$file ist ein symbolischer Link"
  else
    echo "$file ist kein symbolischer Link"
  fi
}

aufruferbesitzer() {
  file="$1"
  if [ -O "$file" ] 
    then
      echo "der Aufrufer besitzt die Datei $file"
  else
    echo "der Aufrufer besitzt die Datei $file nicht"
  fi
}

besitzer() {
  file="$1"
  user=$(ls -la  | grep $file | cut -d" " -f4)
  echo "$user besitzt die Datei"
}

dateiexistiert $1
dateiregular $1
symblink $1
aufruferbesitzer $1
besitzer $1