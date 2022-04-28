set title "0.000199152*x+0.999999"
set xlabel "Nº de vectores"
set ylabel "Tiempo (ms)"
set xrange [0:10000]
set yrange [0:25]
set logscale y
set grid
f(x) = 1.62668*log(x)+-7.48572
set terminal pdf
set output "output.pdf"
plot 'ejercicio-2-mezcla-dyv-k-tab.dat', f(x)
