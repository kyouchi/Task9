set encoding utf8
set xl "t[sec]"
set yl "Amplitude"
set xrange [-0.25:0.249878]
set yrange [-0.0391978:0.360896]
set grid
set title "Waveform"
set term pngcairo enhanced size 1920,1080
set output "waveform4-5.png" 
plot "waveform4-5.plt" with lp
set output
