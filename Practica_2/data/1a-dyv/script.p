set title "Caso obvio vs Caso Divide y Vencerás"
set xlabel "Nº de componentes"
set ylabel "Tiempo (ms)"
set xrange [1:10000000]
set yrange [0:250]
set grid
f(x) = 9.12713*(log(x)/(log(2)))+1.2032
set terminal pdf
set output "e1a-dyv.pdf"
plot 'ejercicio-1-comp-fija-no-repetidos-tab.dat', f(x)
