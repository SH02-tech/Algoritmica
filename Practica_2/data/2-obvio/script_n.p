set title "Mezcla clásica (k constante)"
set xlabel "Nº de componentes"
set ylabel "Tiempo (ms)"
set xrange [1:10000000]
set yrange [0:8200]
set grid
f(x) = 3.85058e-05*x*log(x)+1
set terminal pdf
set output "output.pdf"
plot 'ejercicio-2-mezcla-n-tab.dat', f(x)