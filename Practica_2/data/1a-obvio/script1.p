set title "Caso obvio"
set xlabel "Nº de componentes"
set ylabel "Tiempo (ms)"
set xrange [1:10000000]
set yrange [0:40]
set grid
f(x) = 3.37683e-06*x+0.999999
set terminal pdf
set output "e1a-obvio.pdf"
plot 'ejercicio-1-comp-fija-no-repetidos-lineal-tab.dat', f(x)