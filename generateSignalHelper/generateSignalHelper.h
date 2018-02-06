#pragma once
#include "stdafx.h"
#include <sprout/array.hpp>
#include <sprout/tuple.hpp>
#include <sprout/math.hpp>

//SamplingRate サンプリング周波数,Sec 波形の秒数
template<unsigned SamplingRate, unsigned Sec>
class Signal
{
   const double center_point_ = SamplingRate * Sec / 2.0;
public:
   constexpr Signal<SamplingRate, Sec>();
   sprout::array<double, SamplingRate*Sec> x;//時間軸
   sprout::array<sprout::tuple<double, double>, SamplingRate*Sec> y;//complex型

   Signal<SamplingRate, Sec> operator +(Signal<SamplingRate, Sec> gw) const;
   Signal<SamplingRate, Sec> operator *(Signal<SamplingRate, Sec> signal) const;

   //特殊化出来なかった
   constexpr void multipleY(const double factor) const;

   constexpr void generateSquare(const double tau, const double a) const;
   constexpr void generateTriangle(const double tau, const double a) const;
   constexpr void generateSineWave(const double tau, const double a, const double cycle) const;
   constexpr void generateSineUnsignedWave(const double tau, const double a, const double cycle) const;
   constexpr void generateCosineWave(const double tau, const double a, const double cycle) const;
   constexpr void generateCosineUnsignedWave(const double tau, const double a, const double cycle) const;
   constexpr void generateCarrierWave(const double fc, const double a) const;
   constexpr void generatePow2CosineWave(const double tau, const double a, const double cycle) const;
   constexpr void applyRandomNoise(const double random_max) const;

   //std::vector<std::complex<double>> getWaveData() const;
   //bool setWaveData(const std::vector<std::complex<double>> &p_v);

   //信号をずらす為の関数
   constexpr void moveAmplitude(const double start_time) const;

   //Use for FFT
private:
   sprout::array<double, SamplingRate*Sec> output_frequence_;
   sprout::array<sprout::tuple<double, double>, SamplingRate*Sec> output_amplitude_;

public:
   constexpr Signal<SamplingRate, Sec> applyFft();
};

template <unsigned SamplingRate, unsigned Sec>
constexpr Signal<SamplingRate, Sec>::Signal()
{
}

template <unsigned SamplingRate, unsigned Sec>
Signal<SamplingRate, Sec> Signal<SamplingRate, Sec>::operator+(Signal<SamplingRate, Sec> gw) const
{
   //コピーを作成
   Signal<SamplingRate, Sec> output;

   for (unsigned int i = 0; i < SamplingRate*Sec; ++i)
   {
      output.y[i] = this->y[i] + gw.y[i];
   }

   return output;
}

template <unsigned SamplingRate, unsigned Sec>
Signal<SamplingRate, Sec> Signal<SamplingRate, Sec>::operator*(Signal<SamplingRate, Sec> signal) const
{
   //コピーを作成
   Signal<SamplingRate, Sec> output;

   for (unsigned i = 0; i < SamplingRate*Sec; ++i)
   {
      output.y[i] = this->y[i] * signal.y[i];
   }
   return output;
}
//sprout::array<sprout::tuple<double,double>,1000> Signal;

template <unsigned SamplingRate, unsigned Sec>
constexpr void Signal<SamplingRate, Sec>::multipleY(const double factor) const
{
   for (unsigned i = 0; i < SamplingRate*Sec; ++i)
   {
      this->y[i] = this->y[i] * factor;
   }
   return;
}

template <unsigned SamplingRate, unsigned Sec>
constexpr void Signal<SamplingRate, Sec>::generateSquare(const double tau, const double a) const
{
   const auto range = (SamplingRate * (tau / 2.0));

   for (unsigned i = 0; i < SamplingRate*Sec; ++i)
   {
      this->x[i] = (i - center_point_) / SamplingRate;
      if (center_point_ - range <= i || center_point_ + range >= i)
      {
         this->y[i] = a;
      }
   }
   return;
}

template <unsigned SamplingRate, unsigned Sec>
constexpr void Signal<SamplingRate, Sec>::generateTriangle(const double tau, const double a) const
{
   const auto range = (SamplingRate * (tau / 2.0));

   for (unsigned i = 0; i < SamplingRate*Sec; ++i)
   {
      this->x[i] = (i - center_point_) / SamplingRate;
      if (center_point_ - range <= i || center_point_ + range >= i)
      {
         this->y[i] = a - (a / range) * (i - center_point_);
      }
   }
   return;
}

template <unsigned SamplingRate, unsigned Sec>
constexpr void Signal<SamplingRate, Sec>::generateSineWave(const double tau, const double a, const double cycle) const
{
   const auto range = (SamplingRate * (tau / 2.0));

   for (unsigned i = 0; i < SamplingRate*Sec; ++i)
   {
      this->x[i] = (i - center_point_) / SamplingRate;
      if (center_point_ - range <= i || center_point_ + range >= i)
      {
         this->y[i] = a * sprout::sin(2 * cycle * pi * x[i]);
      }
   }
   return;
}

template <unsigned SamplingRate, unsigned Sec>
constexpr void Signal<SamplingRate, Sec>::generateSineUnsignedWave(const double tau, const double a, const double cycle) const
{
   const auto range = (SamplingRate * (tau / 2.0));

   for (unsigned i = 0; i < SamplingRate*Sec; ++i)
   {
      this->x[i] = (i + 1) / SamplingRate;
      if (center_point_ - range <= i || center_point_ + range >= i)
      {
         this->y[i] = a * sprout::sin(2 * cycle * pi * x[i]);
      }
   }
   return;
}

template <unsigned SamplingRate, unsigned Sec>
constexpr void Signal<SamplingRate, Sec>::generateCosineWave(const double tau, const double a, const double cycle) const
{
   const auto range = (SamplingRate * (tau / 2.0));

   for (unsigned i = 0; i < SamplingRate*Sec; ++i)
   {
      this->x[i] = (i - center_point_) / SamplingRate;
      if (center_point_ - range <= i || center_point_ + range >= i)
      {
         this->y[i] = a * sprout::cos(2 * cycle * pi * x[i]);
      }
   }
   return;
}

template <unsigned SamplingRate, unsigned Sec>
constexpr void Signal<SamplingRate, Sec>::generateCosineUnsignedWave(const double tau, const double a, const double cycle) const
{
   const auto range = (SamplingRate * (tau / 2.0));

   for (unsigned i = 0; i < SamplingRate*Sec; ++i)
   {
      this->x[i] = (i + 1) / SamplingRate;
      if (center_point_ - range <= i || center_point_ + range >= i)
      {
         this->y[i] = a * sprout::cos(2 * cycle * pi * x[i]);
      }
   }
   return;
}

template <unsigned SamplingRate, unsigned Sec>
constexpr void Signal<SamplingRate, Sec>::generateCarrierWave(const double fc, const double a) const
{
   for (unsigned i = 0; i < SamplingRate*Sec; ++i)
   {
      this->x[i] = (i - center_point_) / SamplingRate;
      this->y[i] = a * sprout::cos(2 * pi * fc * x[i]);//Cosineを乗算
   }
   return;
}

//ft = 符号1つのサンプリング周波数(2のべき乗が好ましい)
template<unsigned SamplingRate, unsigned Sec, unsigned PrbsSize>
constexpr Signal<SamplingRate, Sec * PrbsSize> generatePrbsWave(const double ft, const sprout::array<double, PrbsSize> &list, const std::function<Signal<SamplingRate, Sec>(double, double)> &fn);
