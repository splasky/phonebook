reset
set ylabel 'time(sec)'
set style fill solid
set title 'performance comparison'
set term png enhanced font 'Verdana,10'
set output 'runtime.png'

plot [:][:0.250]\
'output.txt' using 2:xtic(1) with histogram title 'original', \
'' using 3:xtic(1) with histogram title 'aphash'  , \
'' using 4:xtic(1) with histogram title 'bkdrhash' ,\
'' using 5:xtic(1) with histogram title 'dekhash' ,\
'' using 6:xtic(1) with histogram title 'djbhash' ,\
'' using 7:xtic(1) with histogram title 'elfhash' ,\
'' using 8:xtic(1) with histogram title 'jshash' ,\
'' using 9:xtic(1) with histogram title 'pjwhash' ,\
'' using 10:xtic(1) with histogram title 'rshash' ,\
'' using 11:xtic(1) with histogram title 'sdbmhash' ,\
'' using ($0-0.200):(0.110):2 with labels title ' ' textcolor lt 1, \
'' using ($0-0.200):(0.120):3 with labels title ' ' textcolor lt 2, \
'' using ($0-0.200):(0.130):4 with labels title ' ' textcolor lt 3, \
'' using ($0-0.200):(0.140):5 with labels title ' ' textcolor lt 4, \
'' using ($0-0.200):(0.150):6 with labels title ' ' textcolor lt 5, \
'' using ($0-0.200):(0.160):7 with labels title ' ' textcolor lt 6, \
'' using ($0-0.200):(0.170):8 with labels title ' ' textcolor lt 7, \
'' using ($0-0.200):(0.180):9 with labels title ' ' textcolor lt 8, \
'' using ($0-0.200):(0.190):10 with labels title ' ' textcolor lt 9, \
'' using ($0-0.200):(0.200):11 with labels title ' ' textcolor lt 10, \
