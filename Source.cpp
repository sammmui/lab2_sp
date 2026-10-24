#include <iostream>
#include <vector>
#include <cmath>

const size_t SIGNAL_LENGTH = 20000000;
const int PIPELINE_CYCLES = 6;

void calibrate_sensor_readings(const std::vector<float>& raw_input, std::vector<float>& calibrated_output) {
    for (size_t i = 0; i < raw_input.size(); ++i) {
        float val = raw_input[i];
        calibrated_output[i] = (val * 1.085f + 0.312f) * (1.0f - val * 0.004f);
    }
}

void apply_noise_reduction(std::vector<float>& buffer) {
    for (size_t i = 1; i < buffer.size() - 1; ++i) {
        buffer[i] = 0.2f * buffer[i - 1] + 0.6f * buffer[i] + 0.2f * buffer[i + 1];
    }
}

void stage_calibration(const std::vector<float>& input, std::vector<float>& output) {
    calibrate_sensor_readings(input, output);
}

void stage_filtering(std::vector<float>& buffer) {
    apply_noise_reduction(buffer);
}

void run_telemetry_pipeline(const std::vector<float>& raw_data, std::vector<float>& final_output) {
    std::vector<float> temp_buffer(raw_data.size(), 0.0f);

    stage_calibration(raw_data, temp_buffer);
    stage_filtering(temp_buffer);

    for (size_t i = 0; i < final_output.size(); ++i) {
        final_output[i] += temp_buffer[i];
    }
}

int main() {
    std::cout << "[Telemetry System] Initializing data buffer..." << std::endl;

    std::vector<float> raw_signals(SIGNAL_LENGTH);
    std::vector<float> processed_signals(SIGNAL_LENGTH, 0.0f);

    for (size_t i = 0; i < SIGNAL_LENGTH; ++i) {
        raw_signals[i] = static_cast<float>(i % 360) * 0.05f;
    }

    std::cout << "[Telemetry System] Executing processing loops..." << std::endl;

    for (int cycle = 0; cycle < PIPELINE_CYCLES; ++cycle) {
        run_telemetry_pipeline(raw_signals, processed_signals);
    }

    std::cout << "[Telemetry System] Done! Checksum: " << processed_signals[1024] << std::endl;

    return 0;
}