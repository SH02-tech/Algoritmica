set terminal pdf
set output "salida.pdf"
set ylabel "Tiempo de ejecución (ns)"
unset key
set yrange [0:400]
set boxwidth 0.2
set style fill solid 
plot "data.dat" using 1:3:xtic(2) with boxes
