/**************************************************************************************

This is example for ClosedCube HDC1080 Humidity and Temperature Sensor breakout booard

**************************************************************************************/
#include <arduinoFFT.h>

#define SAMPLES         1024          // Must be a power of 2
#define SAMPLING_FREQ   44100         // Hz, must be 40000 or less due to ADC conversion time. Determines maximum frequency that can be analysed by the FFT Fmax=sampleF/2.

double vReal[SAMPLES];
double vImag[SAMPLES];

arduinoFFT FFT = arduinoFFT(vReal, vImag, SAMPLES, SAMPLING_FREQ);

//####INMP411#####
#include <driver/i2s.h>

#define I2S_WS 15        
#define I2S_SD 13
#define I2S_SCK 2
#define I2S_PORT I2S_NUM_0
#define bufferLen 1024

int16_t sBuffer[bufferLen];
//*************************************************************************************

#include <Wire.h>
#include "ClosedCube_HDC1080.h"

ClosedCube_HDC1080 sensor01;
ClosedCube_HDC1080 sensor02;

#define ADD1 0x40
#define SDA1 23
#define SCL1 22

#define ADD2 0x40
#define SDA2 33
#define SCL2 32

TwoWire I2C1 = TwoWire(0); //I2C1 bus
TwoWire I2C2 = TwoWire(1); //I2C2 bus

//**************************************************************************************

void setup()
{
  Serial.begin(115200);
  Serial.println('\n');
  Serial.println("Bits4bits Beehive");
  delay(1000);

  i2s_install();
  i2s_install();
  i2s_install();
  i2s_setpin();
  i2s_start(I2S_PORT);
  delay(500);

  I2C1.begin(SDA1, SCL1, 100000); // Start I2C1 on pins 23 and 22
  I2C2.begin(SDA2, SCL2, 100000); // Start I2C2 on pins 33 and 32
  delay(500);

  sensor01.begin(ADD1,&I2C1);
  sensor02.begin(ADD2,&I2C2);

  sensor01.setResolution(HDC1080_RESOLUTION_14BIT, HDC1080_RESOLUTION_14BIT);
  sensor02.setResolution(HDC1080_RESOLUTION_14BIT, HDC1080_RESOLUTION_14BIT);
  delay(1000);
}

void loop()
{ 
  // Get I2S data and place in data buffer
  size_t bytesIn = 0;
  esp_err_t result = i2s_read(I2S_PORT, &sBuffer, bufferLen, &bytesIn, portMAX_DELAY); 

  if ((result == ESP_OK) & (bytesIn > 0) ){
    for (int i = 0; i < SAMPLES; ++i) {
          vReal[i] = double(sBuffer[i]);
          vImag[i] = 0;  
     }
  }

  // Compute FFT
  FFT.DCRemoval();
  FFT.Windowing(FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  FFT.Compute(FFT_FORWARD);
  FFT.ComplexToMagnitude();
  
//########################################
  double Frec_MajorPeak = FFT.MajorPeak();

  double T_int = sensor01.readTemperature();
  double H_int = sensor01.readHumidity();
  
  double T_ext = sensor02.readTemperature();
  double H_ext = sensor02.readHumidity();

  delay(100);
//########################################
  Serial.print("T=");
  Serial.print(T_int);
  Serial.print("C, RH=");
  Serial.print(H_int);
  Serial.print("% ");
  Serial.print(" T=");
  Serial.print(T_ext);
  Serial.print("C, RH=");
  Serial.print(H_ext);
  Serial.print("% ");
  Serial.print(" Major Peak: ");
  Serial.print(Frec_MajorPeak);
  Serial.println("Hz ");
  
  delay(1000);
}

void i2s_install(){
  const i2s_config_t i2s_config = {
    .mode = i2s_mode_t(I2S_MODE_MASTER | I2S_MODE_RX),
    .sample_rate = 44100,
    .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
    .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
    .communication_format = i2s_comm_format_t(I2S_COMM_FORMAT_I2S | I2S_COMM_FORMAT_I2S_MSB),
    .intr_alloc_flags = 0, // default interrupt priority
    .dma_buf_count = 8,
    .dma_buf_len = bufferLen,
    .use_apll = false
  };

  i2s_driver_install(I2S_PORT, &i2s_config, 0, NULL);
}

void i2s_setpin(){
  const i2s_pin_config_t pin_config = {
    .bck_io_num = I2S_SCK,
    .ws_io_num = I2S_WS,
    .data_out_num = -1,
    .data_in_num = I2S_SD
  };

  i2s_set_pin(I2S_PORT, &pin_config);
}
