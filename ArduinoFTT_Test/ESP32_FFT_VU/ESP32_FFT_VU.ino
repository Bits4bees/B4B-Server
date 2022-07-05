// (Heavily) adapted from https://github.com/G6EJD/ESP32-8266-Audio-Spectrum-Display/blob/master/ESP32_Spectrum_Display_02.ino
// Adjusted to allow brightness changes on press+hold, Auto-cycle for 3 button presses within 2 seconds
// Edited to add Neomatrix support for easier compatibility with different layouts.

#include <arduinoFFT.h>

#define SAMPLES         1024          // Must be a power of 2
#define SAMPLING_FREQ   15000         // Hz, must be 40000 or less due to ADC conversion time. Determines maximum frequency that can be analysed by the FFT Fmax=sampleF/2.
#define AMPLITUDE       1000          // Depending on your audio source level, you may need to alter this value. Can be used as a 'sensitivity' control.
#define AUDIO_IN_PIN    35            // Signal in on this pin
#define NUM_BANDS       8            // To change this, you will need to change the bunch of if statements describing the mapping from bins to bands
#define NOISE           500           // Used as a crude noise filter, values below this are ignored

// Sampling and FFT stuff
unsigned int sampling_period_us;
double vReal[SAMPLES];
double vImag[SAMPLES];
unsigned long newTime;
int bandValues[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
arduinoFFT FFT = arduinoFFT(vReal, vImag, SAMPLES, SAMPLING_FREQ);
double highestBandValue = 60000;

void setup() {
  Serial.begin(1000000);
  sampling_period_us = round(1000000 * (1.0 / SAMPLING_FREQ));
}

void loop() {

  // Sample the audio pin
  for (int i = 0; i < SAMPLES; i++) {
    newTime = micros();
    vReal[i] = analogRead(AUDIO_IN_PIN); // A conversion takes about 9.7uS on an ESP32
    vImag[i] = 0;
//    Serial.println(vReal[i]);
    while ((micros() - newTime) < sampling_period_us) { /* chill */ }
  }
//  memcpy(vRealCopy, vReal, sizeof(vReal));
  
//  for (int i = 0; i < SAMPLES; i++) {
//    Serial.println(vRealCopy[i]);
//  }
 
  // Compute FFT
  FFT.DCRemoval();
  FFT.Windowing(FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  FFT.Compute(FFT_FORWARD);
  FFT.ComplexToMagnitude();
  FFT.MajorPeak();

  Serial.println(FFT.MajorPeak());

//  for (int i = 0; i<NUM_BANDS; i++){
//    bandValues[i] = 0;
//  }
//
//  for (int i = 2; i < (SAMPLES/2); i++){       // Don't use sample 0 and only first SAMPLES/2 are usable. Each array element represents a frequency bin and its value the amplitude.
//   if (vReal[i] > NOISE) {                    // Add a crude noise filter
//    //16 bands, 12kHz top band
//      if (i<=8 )           bandValues[0]  += (int)vReal[i];
//      if (i>8   && i<=15  ) bandValues[1]  += (int)vReal[i];
//      if (i>15  && i<=29  ) bandValues[2]  += (int)vReal[i];
//      if (i>29  && i<=56  ) bandValues[3]  += (int)vReal[i];
//      if (i>56  && i<=107 ) bandValues[4]  += (int)vReal[i];
//      if (i>107 && i<=204 ) bandValues[5]  += (int)vReal[i];
//      if (i>204 && i<=390 ) bandValues[6]  += (int)vReal[i];
//      if (i>390           ) bandValues[7]  += (int)vReal[i];
//    }
//  }
//  
//  int val = 0;
//  for (int i = 0; i < NUM_BANDS; i++) {
//    if (bandValues[i]>highestBandValue){highestBandValue = bandValues[i];}
//    
//    val = map(bandValues[i],0,highestBandValue,0,1000);
//    Serial.println(val); 
//  }
  

//  for (int i = 0; i < SAMPLES; i++) {
//    Serial.println(vReal[i]); 
//  }
//  Serial.println("*********************"); 
//  delay(10);
}
