#!/bin/bash

selected_files="$@"

if [ "$1" = "" ]; then
	echo "Usage: ./speed_tests.sh [executable]"
	exit 1
elif [ "$1" = "all" ]; then
	selected_files=*_speedtest.cpp
	echo "$selected_files"
fi

for file in $selected_files; do
	exec=${file%.cpp}
	echo -n "$exec"
	time "./$exec" > /dev/null
	printf "\n"
done