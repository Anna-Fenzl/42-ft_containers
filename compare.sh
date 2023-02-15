#!/bin/bash

mkdir output && make
./ft_containers > output/ft.txt && ./std_containers > output/std.txt
echo "output is stored in output directory (need to comment out the rm -rf output)"
echo " "
echo " " "<<<<<<<<<<<<<<<<<<<<<<  CHECKING FOR DIFFERENCES: >>>>>>>>>>>>>>>>>>>>"
diff <(nl output/ft.txt) <(nl output/std.txt)
rm -rf output
