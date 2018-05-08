#! /bin/bash

if [[ $# -ne 1 ]]; then
  echo "at least one argument is required usage :"
  echo "$0 filename"
  exit 1
fi

detc -sob $1 | cco -f | mh -n 0 | cco -f > $1.cont
./hough $1.cont $1.acc > $1.draw
xvis $1 -xsh $1.draw
