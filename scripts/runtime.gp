reset
set ylabel 'time(sec)'
set style fill solid
set title 'performance comparison'
set term png enhanced font 'Verdana,10'
set output 'runtime.png'

plot [:][:0.250]\
'output.txt' using 2:xtic(1) with histogram title 'original', \
'' using 3:xtic(1) with histogram title 'smaz'  , \
'' using ($0-0.200):(0.110):2 with labels title ' ' textcolor lt 1, \
'' using ($0-0.200):(0.140):3 with labels title ' ' textcolor lt 2, \
