set title "Caso Divide y Vencerás"
set xlabel "Nº de componentes"
set ylabel "Tiempo (ns)"
set xrange [1:10000000]
set yrange [0:180]
set grid
f(x) = 8.8250*log(x) + 1.113
set terminal pdf
set output "output.pdf"
plot 'ejercicio-1-comp-fija-no-repetidos-tab.dat', f(x)