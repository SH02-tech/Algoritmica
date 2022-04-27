set title "Búsqueda Lineal V2"
set xlabel "Nº de componentes"
set ylabel "Tiempo (ms)"
set xrange [1:10000000]
set yrange [0:58]
set grid
f(x) = 3.49261e-06*x+0.999999
set terminal pdf
set output "output.pdf"
plot '1b-obvio/ejercicio-1-comp-fija-repetidos-lineal-tab.dat', f(x)

