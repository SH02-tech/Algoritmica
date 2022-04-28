set title "Caso Divide y Vencerás"
set xlabel "Nº de componentes"
set ylabel "Tiempo (ms)"
set xrange [1:10000000]
set yrange [0:3]
set grid
f(x) = 0.1323*log(x) + 0.0012
set terminal pdf
set output "output.pdf"
plot 'ejercicio-1-comp-fija-no-repetidos-tab.dat', f(x)