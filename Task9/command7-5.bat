set encoding utf8
set xl "t[sec]"
set yl "Amplitude"
set xrange [-0.25:0.249878]
set yrange [-0.334591:0.0720624]
set grid
set title "Waveform"
set term pngcairo enhanced size 1920,1080
set output "waveform7-5.png" 
plot "waveform7-5.plt" with lp
set output
