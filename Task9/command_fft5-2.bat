set encoding utf8
set xl "f[Hz]"
set yl "Amplitude"
set xrange [0:8190]
set yrange [0:2048]
set grid
set title "Apply FFT"
set term pngcairo enhanced size 1920,1080
set output "spectrum5-2.png" 
plot "spectrum5-2.plt" with lp
set output
