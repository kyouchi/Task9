#include "stdafx.h"
#include "ButterworthFilter.h"

void applyIirLowPassFilter(const std::vector<std::complex<double>> &input, std::vector<std::complex<double>> &output, const double sampling_rate, const double cutoff_frequency, const double q)
{
   // フィルタ係数を計算する
   const auto omega = 2.0 * pi *  cutoff_frequency / sampling_rate;
   const auto alpha = sin(omega) / (2.0f * q);

   const auto a0 = 1.0 + alpha;
   const auto a1 = -2.0 * cos(omega);
   const auto a2 = 1.0 - alpha;
   const auto b0 = (1.0 - cos(omega)) / 2.0;
   const auto b1 = 1.0 - cos(omega);
   const auto b2 = (1.0 - cos(omega)) / 2.0;

   // フィルタ計算用のバッファ変数。
   auto in1 = 0.0;//input[i-1]
   auto in2 = 0.0;//input[i-2]
   auto out1 = 0.0;//output[i-1]
   auto out2 = 0.0;//output[i-2]

   // フィルタを適用
   for (unsigned i = 0; i < input.size(); ++i)
   {
      // 入力信号にフィルタを適用し、出力信号として書き出す。
      output[i] = (b0 / a0 * input[i].real()) + (b1 / a0 * in1) + (b2 / a0 * in2) - (a1 / a0 * out1) - (a2 / a0 * out2);

      in2 = in1;       // 2つ前の入力信号を更新
      in1 = input[i].real();  // 1つ前の入力信号を更新

      out2 = out1;      // 2つ前の出力信号を更新
      out1 = output[i].real(); // 1つ前の出力信号を更新
   }
   return;
}
