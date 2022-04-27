set title "Caso obvio vs Caso Divide y Vencerás"
set xlabel "Nº de componentes"
set ylabel "Tiempo (ms)"
set xrange [1:10000000]
set yrange [0:65]
set grid
f(x) = 3.49261e-06*x+0.999999
g(x) = 4.6553e-6*x+0.85
set terminal pdf
set output "output.pdf"
plot '1b-obvio/ejercicio-1-comp-fija-repetidos-lineal-tab.dat', f(x), '1b-dyv/ejercicio-1-comp-fija-repetidos-tab.dat', g(x)