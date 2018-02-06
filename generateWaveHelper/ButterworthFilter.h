#pragma once
#include "generateWave.h"
void applyIirLowPassFilter(const std::vector<std::complex<double>> &input, std::vector<std::complex<double>> &output, const double sampling_rate, const double cutoff_frequency, const double q = 1);
