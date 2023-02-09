#!/bin/bash

mkdir output && make
export MallocDebugReport=crash # to supress the error message wich comes straight from Apple's libmalloc (in std::vector.reserve(max_size + 1))
./ft_containers > output/ft.txt && ./std_containers > output/std.txt
echo " " "<<<<<<<<<<<<<<<<<<<<<<  CHECKING FOR DIFFERENCES: >>>>>>>>>>>>>>>>>>>>"
diff <(nl output/ft.txt) <(nl output/std.txt)
unset MallocDebugReport
rm -rf output
