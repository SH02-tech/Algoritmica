set terminal pdf
set output "output.pdf"
unset key
set xlabel "Número de componentes del vector"
set ylabel "Tiempo de ejecución (en microsegundos)"
set xrange[0:45000]
plot 'lenovo/seleccion-mejor-tab.dat' with lines, 'lenovo/seleccion-tab.dat' with lines, 'lenovo/seleccion-peor-tab.dat' with lines
