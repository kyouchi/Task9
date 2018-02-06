// Task9.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include "../GPlotTools/plot.h"
#include "../generateWaveHelper/generateWave.h"
#include "../generateSignalHelper/generateSignalHelper.h"
#include "../generateWaveHelper/ButterworthFilter.h"
#include <string>
#include "../FFT/fft.h"
constexpr auto fs = 8192;//サンプリング周波数(2のべき乗)



//[in]question_number = 問題番号,[in] fc = キャリア周波数
void printTask9Answer(const unsigned int question_number, const unsigned int fc, const unsigned int fc_mod, const double move_time, const unsigned int cutoff_frequency)
{
   const auto graph_title = "waveform" + std::to_string(question_number) + "-";
   const auto graph_title_fft = "spectrum" + std::to_string(question_number) + "-";
   const auto file_name = "command" + std::to_string(question_number) + "-";
   const auto file_name_fft = "command_fft" + std::to_string(question_number) + "-";

   //情報信号
   GenerateWave graph1(fs, 0.5);
   graph1.generateTriangle(0.15, 1.5);
   graph1.generateSquare(0.05, 0.0);
   graph1.moveAmplitude(0.075);
   //Plot(graph1.getGraph().x, graph1.getGraph().y, "t[sec]", "Amplitude", "Waveform", graph_title + "1.plt", file_name + "1.bat").executionPlot();
   //Plot(graph1.applyFft().x, graph1.applyFft().y, "f[Hz]", "Amplitude", "Apply FFT", graph_title_fft + "1.plt", file_name_fft + "1.bat").executionPlotAbs();

   //搬送波
   GenerateWave graph2(fs, 0.5);
   graph2.generateCarrierWave(fc, 1.0);
   //Plot(graph2.getGraph().x, graph2.getGraph().y, "t[sec]", "Amplitude", "Waveform", graph_title + "2.plt", file_name + "2.bat").executionPlot();
   //Plot(graph2.applyFft().x, graph2.applyFft().y, "f[Hz]", "Amplitude", "Apply FFT", graph_title_fft + "2.plt", file_name_fft + "2.bat").executionPlotAbs();

   //DSB変調波
   auto graph3 = graph1 * graph2;
   //Plot(graph3.getGraph().x, graph3.getGraph().y, "t[sec]", "Amplitude", "Waveform", graph_title + "3.plt", file_name + "3.bat").executionPlot();
   //Plot(graph3.applyFft().x, graph3.applyFft().y, "f[Hz]", "Amplitude", "Apply FFT", graph_title_fft + "3.plt", file_name_fft + "3.bat").executionPlotAbs();

   //同期検波(受信)用の搬送波
   GenerateWave graph2_mod(fs, 0.5);
   graph2_mod.generateCarrierWave(fc_mod, 1.0);
   graph2_mod.moveAmplitude(move_time);
   Plot(graph2_mod.getGraph().x, graph2_mod.getGraph().y, "t[sec]", "Amplitude", "Waveform", graph_title + "2.plt", file_name + "2.bat").executionPlot();
   Plot(graph2_mod.applyFft().x, graph2_mod.applyFft().y, "f[Hz]", "Amplitude", "Apply FFT", graph_title_fft + "2.plt", file_name_fft + "2.bat").executionPlotAbs();

   //同期検波
   auto graph4 = graph3 * graph2_mod;
   //Plot(graph4.getGraph().x, graph4.getGraph().y, "t[sec]", "Amplitude", "Waveform", graph_title + "4.plt", file_name + "4.bat").executionPlot();
   //Plot(graph4.applyFft().x, graph4.applyFft().y, "f[Hz]", "Amplitude", "Apply FFT", graph_title_fft + "4.plt", file_name_fft + "4.bat").executionPlotAbs();

   //復調
   std::vector<std::complex<double>> output;
   output.resize(graph4.getGraph().y.size());
   applyIirLowPassFilter(graph4.getWaveData(), output, fs, cutoff_frequency, 1.0);
   Plot(graph4.getGraph().x, output, "t[sec]", "Amplitude", "Waveform", graph_title + "5.plt", file_name + "5.bat").executionPlot();
   Plot(graph4.applyFft().x, applyFft(output, fs, cutoff_frequency), "f[Hz]", "Amplitude", "Apply FFT", graph_title_fft + "5.plt", file_name_fft + "5.bat").executionPlotAbs();
   return;
}

void printTask9AnswerSsb(const unsigned int question_number, const unsigned int fc, const unsigned int fc_mod, const double move_time, const unsigned int cutoff_frequency)
{
   const auto graph_title = "waveform" + std::to_string(question_number) + "-";
   const auto graph_title_fft = "spectrum" + std::to_string(question_number) + "-";
   const auto file_name = "command" + std::to_string(question_number) + "-";
   const auto file_name_fft = "command_fft" + std::to_string(question_number) + "-";

   //情報信号
   GenerateWave graph1(fs, 0.5);
   graph1.generateTriangle(0.15, 1.5);
   graph1.generateSquare(0.05, 0.0);
   graph1.moveAmplitude(0.075);
   //Plot(graph1.getGraph().x, graph1.getGraph().y, "t[sec]", "Amplitude", "Waveform", graph_title + "1.plt", file_name + "1.bat").executionPlot();
   //Plot(graph1.applyFft().x, graph1.applyFft().y, "f[Hz]", "Amplitude", "Apply FFT", graph_title_fft + "1.plt", file_name_fft + "1.bat").executionPlotAbs();

   //搬送波
   GenerateWave graph2(fs, 0.5);
   graph2.generateCarrierWave(fc, 1.0);
   //Plot(graph2.getGraph().x, graph2.getGraph().y, "t[sec]", "Amplitude", "Waveform", graph_title + "2.plt", file_name + "2.bat").executionPlot();
   //Plot(graph2.applyFft().x, graph2.applyFft().y, "f[Hz]", "Amplitude", "Apply FFT", graph_title_fft + "2.plt", file_name_fft + "2.bat").executionPlotAbs();

   //SSB変調波
   auto graph3 = graph1 * graph2;
   std::vector<std::complex<double>> ssb;
   ssb.resize(graph3.getGraph().y.size());
   applyIirLowPassFilter(graph3.getWaveData(), ssb, fs, fc, 1.0);
   GenerateWave graph_ssb(fs, 0.5);
   graph_ssb.generateCarrierWave(fc, 1.0);
   graph_ssb.setWaveData(ssb);
   Plot(graph3.getGraph().x, ssb, "t[sec]", "Amplitude", "Waveform", graph_title + "ssb.plt", file_name + "ssb.bat").executionPlot();
   Plot(graph3.applyFft().x, applyFft(ssb, fs, fc), "f[Hz]", "Amplitude", "Apply FFT", graph_title_fft + "ssb.plt", file_name_fft + "ssb.bat").executionPlotAbs();

   //同期検波(受信)用の搬送波
   GenerateWave graph2_mod(fs, 0.5);
   graph2_mod.generateCarrierWave(fc_mod, 1.0);
   graph2_mod.moveAmplitude(move_time);
   Plot(graph2_mod.getGraph().x, graph2_mod.getGraph().y, "t[sec]", "Amplitude", "Waveform", graph_title + "2.plt", file_name + "2.bat").executionPlot();
   Plot(graph2_mod.applyFft().x, graph2_mod.applyFft().y, "f[Hz]", "Amplitude", "Apply FFT", graph_title_fft + "2.plt", file_name_fft + "2.bat").executionPlotAbs();

   //同期検波
   auto graph4 = graph_ssb * graph2_mod;
   //Plot(graph4.getGraph().x, graph4.getGraph().y, "t[sec]", "Amplitude", "Waveform", graph_title + "4.plt", file_name + "4.bat").executionPlot();
   //Plot(graph4.applyFft().x, graph4.applyFft().y, "f[Hz]", "Amplitude", "Apply FFT", graph_title_fft + "4.plt", file_name_fft + "4.bat").executionPlotAbs();

   //復調
   std::vector<std::complex<double>> output;
   output.resize(graph4.getGraph().y.size());
   applyIirLowPassFilter(graph4.getWaveData(), output, fs, cutoff_frequency, 1.0);
   Plot(graph4.getGraph().x, output, "t[sec]", "Amplitude", "Waveform", graph_title + "5.plt", file_name + "5.bat").executionPlot();
   Plot(graph4.applyFft().x, applyFft(output, fs, cutoff_frequency), "f[Hz]", "Amplitude", "Apply FFT", graph_title_fft + "5.plt", file_name_fft + "5.bat").executionPlotAbs();
   return;
}


int main()
{
   printTask9Answer(1, 250, 250, 0, 150);
   printTask9Answer(2, 250, 260, 0, 150);
   printTask9Answer(3, 250, 240, 0, 150);
   printTask9Answer(4, 250, 250, (5.0/fs), 150);
   printTask9Answer(5, 250, 250, (10.0/fs), 150);
   printTask9AnswerSsb(6, 250, 250, 0, 150);
   printTask9AnswerSsb(7, 250, 260, 0, 150);
   printTask9AnswerSsb(8, 250, 240, 0, 150);
   printTask9AnswerSsb(9, 250, 250, (5.0 / fs), 150);
   printTask9AnswerSsb(10, 250, 250, (10.0 / fs), 150);
   return 0;
}
