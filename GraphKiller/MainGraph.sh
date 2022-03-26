#!/bin/bash

# Name:         MainGraph
# Author:       Shao Jie Hu Chen
# Description:  This file obtain GNUPLOT graphs from a C++ source file.
# Parameters:   --xlabel <label>.     Label of X axis.
#               --ylabel <label>.     Label of Y axis.
#               <cpp-name>.cpp.       C++ source file.
# Return:       A directory structure with the following information:
#               data/<cpp-name>-tab.dat    Table obtained from the source.
#               data/<cpp-name>-graph.pdf  PDF with graphics obtained from the
#                                          source.
#               data/<cpp-name>-stat.txt   File with information about type
#                                          of regression, reg function and RMS. 
# Example:      ./MainGraph.sh example.cpp --xlabel "This is X label." --ylabel
#               "This is Y label."

DATA_PATH="data/"

src_file=""
xlabel="X Axis"
ylabel="Y Axis"

# Parameters filter.

while [[ $# -gt 0 ]]; do
	case $1 in
		--xlabel)
			xlabel="$2"
			shift # past argument
			shift # past value
      	;;
      	--ylabel)
			ylabel="$2"
			shift # past argument
			shift # past value
      	;;
      	-*|--*)
			echo "Unknown option $1"
			exit 1
			;;
		*)
			src_file="$1"
			shift # past argument
			;;
	esac
done

src_name=""

if [[ -z "$src_file" ]];
then
	printf "No source file provided.\n";
	exit 1;
fi

IFS='.'; 
arr_src=($src_file); 
unset IFS;

if test ! -f "$src_file";
then
	printf "Non valid source file: $src_file.\n";
	exit 1;
fi

if [[ ${#arr_src[@]} -eq 2 && ${arr_src[1]} == "cpp" ]];
then
	src_name="${arr_src[0]}";
else
	printf "Non C++ source file provided.\n";
	exit 1;
fi
