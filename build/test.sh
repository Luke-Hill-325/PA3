#!/bin/bash -x
cmake ..
make
cat ../testin.txt | ./PA3 -K dot
cat ../testin.txt | ./PA3 -K dot -Tpng -o PA3.png
