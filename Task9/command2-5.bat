set encoding utf8
set xl "t[sec]"
set yl "Amplitude"
set xrange [-0.25:0.249878]
set yrange [-0.51752:0.554316]
set grid
set title "Waveform"
set term pngcairo enhanced size 1920,1080
set output "waveform2-5.png" 
plot "waveform2-5.plt" with lp
set output
