#! /bin/bash

file="img/Joli.inr.gz"
tmp="img/tmp.inr.gz"

./harris -K 0.02 -s 2 -t 0.001 $file | ./sloc | xvisdraw -p -b1 -c 255/0/0 > $tmp
xvis -nu $file  -xsh $tmp
