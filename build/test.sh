#!/bin/bash -x
cmake ..
make
cat ../testin | ./PA3 -K dot
cat ../testin | ./PA3 -K dot -Tpng -o PA3.png
