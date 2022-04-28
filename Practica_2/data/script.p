set title "Caso obvio vs Caso Divide y Vencerás (k constante)"
set xlabel "Nº de componentes"
set ylabel "Tiempo (ms)"
set xrange [0:2]
set yrange [0:0.5]
set grid
set logscale x
f(x) = 0.000199152*x+0.999999
g(x) = 3.85058e-05*x*log(x)+1
set terminal pdf
set output "output.pdf"
plot '2-dyv/ejercicio-2-mezcla-dyv-tab.dat', f(x), '2-obvio/ejercicio-2-mezcla-n-tab.dat', g(x)
