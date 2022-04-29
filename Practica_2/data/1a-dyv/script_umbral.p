set title "Determinación del umbral"
set xlabel "Nº de componentes"
set ylabel "Tiempo (ns)"
set xrange [2:7]
set yrange [10:30]
set grid
f(x) = 9.8250*log(x) + 1.113
g(x) = 3.37683*x + 0.25
set terminal pdf
set output "output.pdf"
plot f(x), g(x)