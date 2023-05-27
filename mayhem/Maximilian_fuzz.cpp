#include <stdint.h>
#include <stdio.h>
#include <climits>
#include <math.h>
#include <stddef.h>
#include <vector>
#include <fuzzer/FuzzedDataProvider.h>

#include "maximilian.h"


extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
    // Get the bytes into a vector<uint8_t>
    FuzzedDataProvider provider(data, size);
    int bitDepth = provider.ConsumeIntegralInRange(1, 24);
    int sampleRate = provider.ConsumeIntegralInRange(44100, 48000);

    std::vector<uint8_t> audio_data = provider.ConsumeRemainingBytes<uint8_t>();
    // Create an instance of Maximilian
    maxiSample sample;

    // since this function only takes in vectors of double we'll have to cast each element
    std::vector<double> double_audio_data;
    double_audio_data.reserve(audio_data.size());
    for (const auto& value: audio_data) {
        double convertedValue = static_cast<double>(value);
        double_audio_data.push_back(convertedValue);
    }
    sample.setSampleAndRate(double_audio_data, sampleRate);



    return 0;
}