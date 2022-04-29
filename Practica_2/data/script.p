set title "ejercicio-2-mezcla-dyv-k"
set xlabel "Nº de vectores"
set ylabel "Tiempo (ms)"
set xrange [0:10000]
set yrange [0:25]
set logscale y
set grid
f(x) = 0.000139217*x*log(x)+-0.295521
set terminal pdf
set output "output.pdf"
plot 'ejercicio-2-mezcla-dyv-k-tab.dat', f(x)
