# PARAMETERS: python3 TexTableGenerator.py <salida.txt> <tabla-1.dat> <tabla-2.dat> ... <tabla-n.dat>

import sys

output_file = open(sys.argv[1], "w")
input_files = [open(elem, 'r') for elem in sys.argv[2:]]

output_file.write("\\begin{table}\n")
output_file.write("\t\\footnotesize\n")
output_file.write("\t\\centering\n")
output_file.write("\t\\begin{tabular}{|")
output_file.write("|".join(["r" for i in range(len(input_files)+1)]))
output_file.write("|}\n")

for line in input_files[0].readlines():
	new_row = line.split()
	row = "\t\t" + str(int(round(float(new_row[0])))) + " & " + str("{:.4f}".format(round(float(new_row[1]),7)))
	
	for i in range(1, len(input_files)):
		new_row = input_files[i].readline().split()
		row += " & " + str("{:.4f}".format(round(float(new_row[1]),7)))
	
	row += " \\\\ \n"	
	output_file.write(row)

output_file.write("\t\\end{tabular}\n")
output_file.write("\\end{table}")
