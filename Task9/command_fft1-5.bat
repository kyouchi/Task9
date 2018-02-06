set encoding utf8
set xl "f[Hz]"
set yl "Amplitude"
set xrange [0:8190]
set yrange [0:205.393]
set grid
set title "Apply FFT"
set term pngcairo enhanced size 1920,1080
set output "spectrum1-5.png" 
plot "spectrum1-5.plt" with lp
set output
