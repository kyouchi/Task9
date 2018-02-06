set encoding utf8
set xl "t[sec]"
set yl "Amplitude"
set xrange [-0.25:0.249878]
set yrange [-1:1]
set grid
set title "Waveform"
set term pngcairo enhanced size 1920,1080
set output "waveform3-2.png" 
plot "waveform3-2.plt" with lp
set output
