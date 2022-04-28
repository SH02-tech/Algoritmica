set title "Caso obvio vs Caso Divide y Vencerás"
set xlabel "Nº de componentes"
set ylabel "Tiempo (ms)"
set xrange [1:10000000]
set yrange [0:65]
set grid
f(x) = 3.44948e-6*x+0.987649
g(x) = 75.7534*log(x)-266.05
set terminal pdf
set output "output.pdf"
plot '1a-obvio/ejercicio-1-comp-fija-no-repetidos-lineal-tab.dat', '1a-dyv/ejercicio-1-comp-fija-no-repetidos-tab.dat'
