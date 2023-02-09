#!/bin/bash

mkdir output
./ft_containers > output/ft.txt && ./std_containers | cat > output/std.txt
echo " " "<<<<<<<<<<<<<<<<<<<<<<  CHECKING FOR DIFFERENCES: >>>>>>>>>>>>>>>>>>>>"
diff <(nl output/ft.txt) <(nl output/std.txt)
rm -rf output
