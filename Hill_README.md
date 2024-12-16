# Hill_PA3
Luke Hill Programming Assignment 3

Environment Setup:
code is tested on ubuntu linux with graphviz and cmake installed.
input data is pasted in to testin.txt for bash script execution, however manual input option is available.

Compiling and running code:
Option 1 (using bash script):
  replace existing input data inside of testin.txt with desired input data
  cd into build directory
  enter command "./test.sh"

Option 2 (manually with input file):
  cd into build directory and use the following commands (replace INPUTFILENAME with desired input file):
  cmake ..
  make
  cat INPUTFILENAME.txt | ./PA3 -K dot -Tpng -o PA3.png

Option 3 (manually):
  cd into build directory and use the following commands:
  cmake ..
  make
  ./PA3 -K dot -Tpng -o PA3.png
  [ENTER MULTI-LINE INPUT FOR ENTIRE INPUT DATA, USE CTRL-D WHEN DONE]

If everything is configured correctly, execution will produce PA3.png, which is a png image of the graphviz visualization of each graph output graph. For each graph input, there are two graphs produced and the graphviz output goes in order from left to right, starting with the initial first graph, then the reflexive transitive closure of the first graph, then the second graph, the rtc of the second graph, and so on. Input data is expected to be in the same format as provided in the example in canvas.
