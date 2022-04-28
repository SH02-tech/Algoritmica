set title "Determinación del umbral"
set xlabel "Nº de componentes"
set ylabel "Tiempo (ms)"
set xrange [1:15]
set yrange [0:2]
set grid
f(x) = 0.5832*log(x) + 0.021
g(x) = 3.37683e-6*x + 0.999999
set terminal pdf
set output "output.pdf"
plot f(x), g(x)