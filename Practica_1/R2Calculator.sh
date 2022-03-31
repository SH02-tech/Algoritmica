#!/bin/bash

aux='aux.p'
graf=$1

printf "" > $aux

echo " # General part " >> $aux 
echo " set fit quiet " >> $aux 
echo " " >> $aux 
echo " mean(x)= m
 " >> $aux 
echo " fit mean(x) '$graf' using 1:2 via m # 1 is the x axis and 2 is the y axis
 " >> $aux 
echo " SST = FIT_WSSR/(FIT_NDF+1)
 " >> $aux 
echo " 
 " >> $aux 
echo " ######################################################
 " >> $aux 
echo " # Logarithmic
 " >> $aux 
echo " f(x) = a*log(x) + b
 " >> $aux 
echo " fit f(x) '$graf' using 1:2 via a, b
 " >> $aux 
echo " SSE=FIT_WSSR/(FIT_NDF)
 " >> $aux 
echo " 
 " >> $aux 
echo " SSR=SST-SSE
 " >> $aux 
echo " R2=SSR/SST
 " >> $aux 
echo " 
 " >> $aux 
echo " print sprintf('logarithmic: %.4f',R2)
 " >> $aux 
echo " 
 " >> $aux 
echo " ######################################################
 " >> $aux 
echo " # Linear
 " >> $aux 
echo " f(x) = a*x + b
 " >> $aux 
echo " fit f(x) '$graf' using 1:2 via a, b
 " >> $aux 
echo " SSE=FIT_WSSR/(FIT_NDF)
 " >> $aux 
echo " 
 " >> $aux 
echo " SSR=SST-SSE
 " >> $aux 
echo " R2=SSR/SST
 " >> $aux 
echo " 
 " >> $aux 
echo " print sprintf('linear: %.4f',R2)
 " >> $aux 
echo " 
 " >> $aux 
echo " ######################################################
 " >> $aux 
echo " # Superlinear
 " >> $aux 
echo " f(x) = a*x*log(x) + b
 " >> $aux 
echo " fit f(x) '$graf' using 1:2 via a, b
 " >> $aux 
echo " SSE=FIT_WSSR/(FIT_NDF)
 " >> $aux 
echo " 
 " >> $aux 
echo " SSR=SST-SSE
 " >> $aux 
echo " R2=SSR/SST
 " >> $aux 
echo " 
 " >> $aux 
echo " print sprintf('superlinear: %.4f',R2)
 " >> $aux 
echo " 
 " >> $aux 
echo " ######################################################
 " >> $aux 
echo " # Quadratic
 " >> $aux 
echo " f(x) = a*x*x + b*x + c
 " >> $aux 
echo " fit f(x) '$graf' using 1:2 via a, b, c
 " >> $aux 
echo " SSE=FIT_WSSR/(FIT_NDF)
 " >> $aux 
echo " 
 " >> $aux 
echo " SSR=SST-SSE
 " >> $aux 
echo " R2=SSR/SST
 " >> $aux 
echo " 
 " >> $aux 
echo " print sprintf('quadratic: %.4f',R2)
 " >> $aux 
echo " 
 " >> $aux 
echo " ######################################################
 " >> $aux 
echo " # Cubic
 " >> $aux 
echo " f(x) = a*x*x*x + b*x*x + c*x + d
 " >> $aux 
echo " fit f(x) '$graf' using 1:2 via a, b, c, d
 " >> $aux 
echo " SSE=FIT_WSSR/(FIT_NDF)
 " >> $aux 
echo " 
 " >> $aux 
echo " SSR=SST-SSE
 " >> $aux 
echo " R2=SSR/SST
 " >> $aux 
echo " 
 " >> $aux 
echo " print sprintf('cubic: %.4f',R2)
 " >> $aux 
 
gnuplot $aux
rm $aux
