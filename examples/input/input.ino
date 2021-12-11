/**
 * @file input.ino
 * @author Phil Schatzmann
 * @brief Input of audio data from the AudioKit microphones
 * @version 0.1
 * @date 2021-12-10
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "AudioKit.h"

AudioKit kit;
const int BUFFER_SIZE = 1024;
uint8_t buffer[BUFFER_SIZE];

void printBuffer(int len){
  // by default we get int16_t values on 2 channels = 4 bytes per frame
  int16_t *value_ptr = (int16_t*) buffer;
  for (int j=0;j<len/4;j++){
    Serial.print(*value_ptr++);
    Serial.print(", ");
    Serial.println(*value_ptr++);
  }
}

void setup() {
  Serial.begin(115200);
  // open in write mode
  auto cfg = kit.defaultConfig(false);
  cfg.adc_input = AUDIO_HAL_ADC_INPUT_LINE1; // microphone
  kit.begin(cfg);
}

void loop() {
  size_t len = kit.read(buffer, BUFFER_SIZE);
  printBuffer(len);
}