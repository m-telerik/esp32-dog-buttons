#include <Arduino.h>
#include "driver/i2s.h"
#include <math.h>

const int I2S_BCLK = 9;   // ESP32-C3 -> MAX98357 BCLK
const int I2S_LRC  = 10;  // ESP32-C3 -> MAX98357 LRC/WS
const int I2S_DIN  = 8;   // ESP32-C3 -> MAX98357 DIN

void i2sInit() {
  i2s_config_t cfg = {
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX),
    .sample_rate = 22050,
    .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
    .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
    .communication_format = I2S_COMM_FORMAT_STAND_I2S,
    .intr_alloc_flags = 0,
    .dma_buf_count = 6,
    .dma_buf_len = 256,
    .use_apll = false,
    .tx_desc_auto_clear = true,
    .fixed_mclk = 0
  };
  i2s_pin_config_t pins = {
    .bck_io_num = I2S_BCLK,
    .ws_io_num  = I2S_LRC,
    .data_out_num = I2S_DIN,
    .data_in_num  = I2S_PIN_NO_CHANGE
  };
  i2s_driver_install((i2s_port_t)0, &cfg, 0, NULL);
  i2s_set_pin((i2s_port_t)0, &pins);
  i2s_zero_dma_buffer((i2s_port_t)0);
}

void beep(uint32_t f=1200, uint32_t ms=250, uint32_t sr=22050) {
  const size_t N=256; int16_t buf[N];
  double ph=0, step=2.0*M_PI*f/sr;
  size_t total=(sr*ms)/1000, sent=0;
  while(sent<total){
    size_t n = min(N, total-sent);
    for(size_t i=0;i<n;i++){ buf[i]=(int16_t)(sin(ph)*16000); ph+=step; if(ph>2*M_PI) ph-=2*M_PI; }
    size_t w=0; i2s_write((i2s_port_t)0, buf, n*sizeof(int16_t), &w, portMAX_DELAY);
    sent+=n;
  }
}

void setup(){
  Serial.begin(115200);
  Serial.println("I2S init");
  i2sInit();
  Serial.println("Beep");
  beep(1000, 300);   // 1 kHz, 300 ms
  delay(400);
  beep(600, 300);    // второй тон – для уверенности
  Serial.println("Done");
}

void loop(){}
