set title "Caso obvio vs Caso Divide y Vencerás"
set xlabel "Nº de componentes"
set ylabel "Tiempo (ms)"
set xrange [1:4000]
set yrange [0:10]
set grid
set logscale y
f(x) = 3.37683e-06*x+0.999999
g(x) = 0.1323*log(x) + 0.001
set terminal pdf
set output "e1a-com.pdf"
plot '../1a-obvio/ejercicio-1-comp-fija-no-repetidos-lineal-tab.dat', f(x), '../1a-dyv/ejercicio-1-comp-fija-no-repetidos-tab.dat', g(x)
