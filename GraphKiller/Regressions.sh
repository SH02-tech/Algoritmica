#!/bin/bash

# Parameters:
#     - <table.dat>.        Table with data to obtain statistical information.
#     - <output-name>.      Name of the output-file.
# Return:
#     - <output-name>.txt.  File with all regression relevant to the table, including the following information:
#                            - Type of regression.
#                            - Function obtained.
#                            - Root Mean Square (RMS). 
# Usage:   ./Regressions.sh <table-file> <output-name>

# Function to find the values of parameters in gnuplot log output. 
# $1: Table with data.
# $2: Name of the parameter to look for.
# Return: Print the value of the parameter. 
find_value () {  
	cat $1 | grep "$2 * =" | awk '{printf $3}' || printf "Error";
}

# Function to find the rms of regression.
# $1: Table with data.
# Return: Print the value of the Root Mean Square. 
find_rms () {
	cat $1 | grep "rms of residuals" | awk '{printf $NF}' || printf "Error";
}

FILE_NAME=$0;
SYNTAX="$FILE_NAME <table-file> <output-name>";
declare -a TYPE_REGRESSION;
TYPE_REGRESSION=('constant' 'logarithmic' 'lineal' 'sublogarithmic' 'quadratic' 'cubic' 'exponential');

# Checking parameters. 

if [[ $# -ne 2 ]]; 
then 
	printf "$FILE_NAME: Illegal number of parameters. Syntax: $SYNTAX.\n";
	exit 1; 
fi;

table=$1;
output=$2;

if test ! -f $1;
then
	printf "Table $1 does not exist.\n";
	exit 1;
fi

# Generating document

LOG_FILE="log_file.txt";
printf "" > $output;

for ((i=0;i<${#TYPE_REGRESSION[@]};++i));
do
	echo "" > $LOG_FILE;
	
	case ${TYPE_REGRESSION[$i]} in 
	'constant')
		gnuplot <<< "set fit logfile '$LOG_FILE';     \
                     f(x)=a;                          \
                     fit f(x) '$table' via a;"
        
        parameter_a=$(find_value $LOG_FILE "a");
        rms=$(find_rms $LOG_FILE);
        
        if [[ "$rms" =~ ^-?[0-9]+([.][0-9]+)?+e?+E?+-?[0-9]+([.][0-9]+)?$ ]];
        then
        	printf "type:constant function:f(x)=$parameter_a RMS:$rms\n" >> $output;
        fi
		;;
	'logarithmic')
		gnuplot <<< "set fit logfile '$LOG_FILE';     \
                     f(x)=a*log(x) + b;               \
                     fit f(x) '$table' via a,b;"
        
        parameter_a=$(find_value $LOG_FILE "a");
        parameter_b=$(find_value $LOG_FILE "b");
        rms=$(find_rms $LOG_FILE);   
        
        if [[ "$rms" =~ ^-?[0-9]+([.][0-9]+)?+e?+E?+-?[0-9]+([.][0-9]+)?$ ]];
        then
        	printf "type:logarithmic function:f(x)=$parameter_a*log(x)+$parameter_b  RMS:$rms\n" >> $output;
        fi
		;;
	'lineal')
		gnuplot <<< "set fit logfile '$LOG_FILE';     \
                     f(x)=a*x + b;                    \
                     fit f(x) '$table' via a,b;"
        
        parameter_a=$(find_value $LOG_FILE "a");
        parameter_b=$(find_value $LOG_FILE "b");
        rms=$(find_rms $LOG_FILE);   
        
        if [[ "$rms" =~ ^-?[0-9]+([.][0-9]+)?+e?+E?+-?[0-9]+([.][0-9]+)?$ ]];
        then
        	printf "type:lineal function:f(x)=$parameter_a*x+$parameter_b  RMS:$rms\n" >> $output;
        fi
		;;
	'sublogarithmic')
		gnuplot <<< "set fit logfile '$LOG_FILE';     \
                     f(x)=a*x*log(x) + b;             \
                     fit f(x) '$table' via a,b;"
        
        parameter_a=$(find_value $LOG_FILE "a");
        parameter_b=$(find_value $LOG_FILE "b");
        rms=$(find_rms $LOG_FILE);   
        
        if [[ "$rms" =~ ^-?[0-9]+([.][0-9]+)?+e?+E?+-?[0-9]+([.][0-9]+)?$ ]];
        then 
        	printf "type:sublogarithmic function:f(x)=$parameter_a*x*log(x)+$parameter_b  RMS:$rms\n" >> $output;
		fi
		;;
	'quadratic')
		gnuplot <<< "set fit logfile '$LOG_FILE';     \
                     f(x)=a*x*x + b*x + c;            \
                     fit f(x) '$table' via a,b,c;"
        
        parameter_a=$(find_value $LOG_FILE "a");
        parameter_b=$(find_value $LOG_FILE "b");
        parameter_c=$(find_value $LOG_FILE "c");
        rms=$(find_rms $LOG_FILE); 
        
        if [[ "$rms" =~ ^-?[0-9]+([.][0-9]+)?+e?+E?+-?[0-9]+([.][0-9]+)?$ ]];
        then  
        	printf "type:quadratic function:f(x)=$parameter_a*x*x+$parameter_b*x+$parameter_c  RMS:$rms\n" >> $output;
        fi
		;;
	'cubic')
		gnuplot <<< "set fit logfile '$LOG_FILE';     \
                     f(x)=a*x*x*x + b*x*x + c*x + d;  \
                     fit f(x) '$table' via a,b,c,d;"
        
        parameter_a=$(find_value $LOG_FILE "a");
        parameter_b=$(find_value $LOG_FILE "b");
        parameter_c=$(find_value $LOG_FILE "c");
        parameter_d=$(find_value $LOG_FILE "d");
        rms=$(find_rms $LOG_FILE);   
        
        if [[ "$rms" =~ ^-?[0-9]+([.][0-9]+)?+e?+E?+-?[0-9]+([.][0-9]+)?$ ]];
        then 
        	printf "type:cubic function:f(x)=$parameter_a*x*x*x+$parameter_b*x*x+$parameter_c*x+$parameter_d  RMS:$rms\n" >> $output;
        fi
		;;
	'exponential')
		gnuplot <<< "set fit logfile '$LOG_FILE';     \
                     f(x)=a*exp(b*x);  \
                     fit f(x) '$table' via a,b;"
        
        parameter_a=$(find_value $LOG_FILE "a");
        parameter_b=$(find_value $LOG_FILE "b");
        rms=$(find_rms $LOG_FILE);  
        
        if [[ "$rms" =~ ^-?[0-9]+([.][0-9]+)?+e?+E?+-?[0-9]+([.][0-9]+)?$ ]];
        then 
        	printf "type:exponential function:f(x)=$parameter_a*exp($parameter_b*x)  RMS:$rms\n" >> $output;
        fi
        ;;
	esac
	
	rm $LOG_FILE;
done
