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
    double onOff = provider.ConsumeIntegralInRange(0, 1);
    double newSample = provider.ConsumeIntegralInRange(0, 10);
    double start = provider.ConsumeIntegralInRange(1, 10);
    double end = provider.ConsumeIntegralInRange(10, 20);
    double freq = provider.ConsumeIntegralInRange(44100, 48000);
    int bitDepth = provider.ConsumeIntegralInRange(1, 24);
    int sampleRate = provider.ConsumeIntegralInRange(44100, 48000);
    std::vector<uint8_t> audio_data = provider.ConsumeRemainingBytes<uint8_t>();
    if (audio_data.size() < 12) {
        return 0;
    }

    // Prepend a valid header the target is expecting
    std::string header = "RIFF";
    // Convert the string to a vector of uint8_t
    std::vector<uint8_t> strVec(header.begin(), header.end());

    // Prepend the string vector to the original vector
    audio_data.insert(audio_data.begin(), strVec.begin(), strVec.end());

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
    sample.playOnce();
    sample.trigger();
    sample.setSample(double_audio_data);
    const bool enable = true;
    #sample.loopRecord(newSample, enable, enable, start, end);
    sample.setPosition(onOff);
    sample.normalise(onOff);
    sample.play4(freq, start, end);



    return 0;
}
