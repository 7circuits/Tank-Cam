bool ap = 1;

//AP Settings
int channel = 11; // WIfi Channel for AP Mode
int hidden = 0; // 0=not hidden, 1=hidden
int maxconnection = 1; // Connections at a time

#include "esp_camera.h"
#include <WiFi.h>
#include "esp_wifi.h"
#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"

const char* ssid = "TankCam02";
const char* password = ""; //Password. Blank for open network.
WiFiServer server(80);

// AIThinker ESP32Cam Pin Definitions
#define PWDN_GPIO_NUM     32
#define RESET_GPIO_NUM    -1
#define XCLK_GPIO_NUM      0
#define SIOD_GPIO_NUM     26
#define SIOC_GPIO_NUM     27

#define Y9_GPIO_NUM       35
#define Y8_GPIO_NUM       34
#define Y7_GPIO_NUM       39
#define Y6_GPIO_NUM       36
#define Y5_GPIO_NUM       21
#define Y4_GPIO_NUM       19
#define Y3_GPIO_NUM       18
#define Y2_GPIO_NUM        5
#define VSYNC_GPIO_NUM    25
#define HREF_GPIO_NUM     23
#define PCLK_GPIO_NUM     22

// GPIO Setting
extern int gpLed =  4; // Light
extern String WiFiAddr ="";

void startCameraServer();

void setup() {
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0); // Prevent brownouts by silencing them. You probably want to keep this.
  
  Serial.begin(115200);
  Serial.setDebugOutput(true);

  pinMode(gpLed, OUTPUT); //Light
  
  //initialize
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;
  //init with high specs to pre-allocate larger buffers
  if(psramFound()){
    config.frame_size = FRAMESIZE_UXGA; //UXGA
    config.jpeg_quality = 10; //10
    config.fb_count = 2; //2
  } else {
    config.frame_size = FRAMESIZE_SVGA;
    config.jpeg_quality = 12;
    config.fb_count = 1;
  }

  // camera init
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    return;
  }

  //drop down frame size for higher initial frame rate
  sensor_t * s = esp_camera_sensor_get();
  s->set_framesize(s, FRAMESIZE_CIF);

  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid,password,channel,hidden,maxconnection);
  WiFiAddr = WiFi.softAPIP().toString();
      
  //Start Webserver
  startCameraServer();
    
}

void loop() {
  // put your main code here, to run repeatedly:

}
