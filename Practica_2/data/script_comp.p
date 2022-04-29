set title "Determinación del umbral"
set xlabel "Nº de componentes"
set ylabel "Tiempo (ns)"
set xrange [1:10000000]
set yrange [0:700000]
set logscale y
set grid
set terminal pdf
set output "output.pdf"
plot '1a-dyv/ejercicio-1-comp-fija-no-repetidos-tab.dat', '1a-obvio/tablas-ns.dat'