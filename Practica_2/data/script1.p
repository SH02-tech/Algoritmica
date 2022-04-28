set title "Caso obvio vs Caso Divide y Vencerás"
set xlabel "Nº de componentes"
set ylabel "Tiempo (ms)"
set xrange [1:10000000]
set yrange [0:1100]
set grid
f(x) = 3.44948e-6*x+0.987649
g(x) = 9.12713*log(x)+1.2032
set terminal pdf
set output "output.pdf"
plot '1a-obvio/ejercicio-1-comp-fija-no-repetidos-lineal-tab.dat', f(x), '1a-dyv/ejercicio-1-comp-fija-no-repetidos-tab.dat', g(x)
