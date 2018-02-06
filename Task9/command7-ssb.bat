set encoding utf8
set xl "t[sec]"
set yl "Amplitude"
set xrange [-0.25:0.249878]
set yrange [-0.912904:0.950007]
set grid
set title "Waveform"
set term pngcairo enhanced size 1920,1080
set output "waveform7-ssb.png" 
plot "waveform7-ssb.plt" with lp
set output
