set title "Mezcla clásica (n constante)"
set xlabel "Nº de componentes"
set ylabel "Tiempo (ms)"
set xrange [1:10000]
set yrange [0:16500]
set grid
f(x) = 0.000141585*x*x+0.0293831*x+-33.9298
set terminal pdf
set output "e2-obvio-k.pdf"
plot 'ejercicio-2-mezcla-k-tab.dat', f(x)
