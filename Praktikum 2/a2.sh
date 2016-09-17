#!bin/bash
for file
  do
    /bin/bash ./a1.sh $file
    /bin/bash ./a3.sh $file
done
