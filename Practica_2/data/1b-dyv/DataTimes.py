import sys

output_file = open("salida_mod.dat", "w")
input_file = open(sys.argv[1], 'r')
factor = float(sys.argv[2])

for line in input_file.readlines():
    row = line.split()
    new_row = row[0] + " " + str(factor * float(row[1])) + "\n"
    output_file.write(new_row)
