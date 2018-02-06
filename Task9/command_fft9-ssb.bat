set encoding utf8
set xl "f[Hz]"
set yl "Amplitude"
set xrange [0:8190]
set yrange [0:205.393]
set grid
set title "Apply FFT"
set term pngcairo enhanced size 1920,1080
set output "spectrum9-ssb.png" 
plot "spectrum9-ssb.plt" with lp
set output
