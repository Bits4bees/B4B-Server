

#include <driver/i2s.h>
#include<cmath>
#include <driver/dac.h>



#define I2S_WS 15        
#define I2S_SD 13
#define I2S_SCK 2

#define I2S_PORT I2S_NUM_0

//// Define input buffer length
#define bufferLen 1024
int16_t sBuffer[bufferLen];

void setup() {
  Serial.begin(115200);
  Serial.println("Setup I2S ...");

  delay(1000);
  i2s_install();
  i2s_setpin();
  i2s_start(I2S_PORT);
  delay(500);
}
void loop() {
 
  // Get I2S data and place in data buffer
  size_t bytesIn = 0;
  esp_err_t result = i2s_read(I2S_PORT, &sBuffer, bufferLen, &bytesIn, portMAX_DELAY);

  if (result == ESP_OK)
  {
    if (bytesIn > 0){ 
      for (int16_t i = 0; i < int16_t(bytesIn/2); ++i) {
        Serial.println(sBuffer[i]);
        }
      }
  }

  delay(10000);
}
//I2S_CHANNEL_FMT_ONLY_LEFT
//I2S_CHANNEL_FMT_ONLY_RIGHT
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

 
