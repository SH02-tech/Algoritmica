set title "ejercicio-2-mezcla-dyv-k"
set xlabel "Nº de vectores"
set ylabel "Tiempo (ms)"
set xrange [-1:10000]
set yrange [0:25]
set logscale y
set grid
f(x) = 1.62668*log(x)-7.48572
g(x) = 0.00014158*x*x+0.0294*x+0.0219
set terminal pdf
set output "output.pdf"
plot f(x), g(x)
