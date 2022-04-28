set title "Caso obvio vs Caso Divide y Vencerás (k constante)"
set xlabel "Nº de componentes"
set ylabel "Tiempo (ms)"
set xrange [0:10000]
set yrange [0:15]
set grid
f(x) = 1.62668*log(x)+-7.48572
g(x) = 0.000141585*x*x+0.0293831*x+-33.9298 
set terminal pdf
set output "output.pdf"
plot 'ejercicio-2-mezcla-dyv-k-tab.dat', f(x)
