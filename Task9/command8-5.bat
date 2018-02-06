set encoding utf8
set xl "t[sec]"
set yl "Amplitude"
set xrange [-0.25:0.249878]
set yrange [-0.0433343:0.330527]
set grid
set title "Waveform"
set term pngcairo enhanced size 1920,1080
set output "waveform8-5.png" 
plot "waveform8-5.plt" with lp
set output
