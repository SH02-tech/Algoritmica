#!/bin/bash

# Name:         MainGraph
# Author:       Shao Jie Hu Chen
# Description:  This file obtain GNUPLOT graphs from a C++ source file.
# Parameters:   --xlabel <label>.                            Label of X axis.
#               --ylabel <label>.                    Label of Y axis.
#               --min-x <number>.                    Minimum value of X axis.
#               --max-x <number>.                    Maximum value of X axis.
#               --num-points <number>.               Number of points to measure.
#               --repetitions-per-point <number>.    Number of repetitions per point. 
#               <executable-name>.                   Source file.
# Return:       A directory structure with the following information:
#               data/<executable-name>-tab.dat              Table obtained from the source.
#               data/<executable-name>-graph.pdf            PDF with graphics obtained from the
#                                                           source.
#               data/<executable-name>-general-stat.txt     File with information about types
#                                                           of regression, reg function and RMS. 
#               data/<executable-name>-best-stat.txt        File with best fit of the file. 
# Example:      ./MainGraph.sh example.cpp --xlabel "This is X label." --ylabel
#               "This is Y label." --min-x 5 --max-x 10 --num-points 10 
#               --repetitions-per-point 10 insercion.cpp

DATA_PATH="data/"

xlabel="X Axis"
ylabel="Y Axis"
min_x=5
max_x=10
num_points=2
src_file=""
repetitions=1

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
      	--min-x)
			min_x="$2"
			shift # past argument
			shift # past value
      	;;
      	--max-x)
			max_x="$2"
			shift # past argument
			shift # past value
      	;;
      	--num-points)
      		num_points="$2"
      		shift # past argument
			shift # past value
		;;
		--repetitions-per-point)
			repetitions="$2"
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

#if test ! -f "$src_file";
#then
#	printf "Non valid source file: $src_file.\n";
#	exit 1;
#fi

if test ! -d "$DATA_PATH"
then
	mkdir "$DATA_PATH"
fi

src_name=${src_file##*/}


./TableGenerator.sh "$src_file" $min_x $max_x $num_points $repetitions "$DATA_PATH/$src_name-tab.dat"
./Regressions.sh "$DATA_PATH/$src_name-tab.dat" "$DATA_PATH/$src_name-general-stat.txt"
./BestFitter.sh "$DATA_PATH/$src_name-general-stat.txt" "$DATA_PATH/$src_name-best-stat.txt"
./PointsPlotter.sh "$DATA_PATH/$src_name-tab.dat" "$src_name" "$xlabel" $min_x $max_x "$ylabel" "$DATA_PATH/$src_name-points.pdf"
./GraphPlotter.sh "$DATA_PATH/$src_name-tab.dat" "$DATA_PATH/$src_name-best-stat.txt" "$src_name" "$xlabel" $min_x $max_x "$ylabel" "$DATA_PATH/$src_name-graph.pdf"
