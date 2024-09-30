#include "esp_camera.h"
#include <WiFi.h>
#include <HTTPClient.h>

#define CAMERA_MODEL_AI_THINKER // Has PSRAM
#include "camera_pins.h"

// WiFi your credentials
const char *ssid = "*****";
const char *password = "@******";

// Server URL
const char* serverUrl = "http://10.128.0.13:5000/upload"; // Atualize o IP para o do seu servidor Flask

void setup() {
  Serial.begin(115200);
  Serial.println();

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
  config.pin_sccb_sda = SIOD_GPIO_NUM;
  config.pin_sccb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.frame_size = FRAMESIZE_QVGA;  
  config.pixel_format = PIXFORMAT_JPEG; 
  config.fb_location = CAMERA_FB_IN_DRAM;
  config.jpeg_quality = 12;
  config.fb_count = 1;


  // Inicializa a câmera
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Falha ao inicializar a câmera, erro 0x%x", err);
    return;
  }

  // Conectar ao WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi conectado");

  Serial.print("Camera pronta! Use 'http://");
  Serial.print(WiFi.localIP());
  Serial.println("' para conectar.");
}

// Função para capturar e enviar a imagem
void captureAndSendImage() {
  camera_fb_t *fb = esp_camera_fb_get();  // Captura a imagem
  if (!fb) {
    Serial.println("Falha ao capturar a imagem");
    return;
  }

  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverUrl);  
    http.addHeader("Content-Type", "image/jpeg");

    int httpResponseCode = http.POST(fb->buf, fb->len);
    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println(httpResponseCode);  
      Serial.println(response);         
    } else {
      Serial.print("Erro no envio da imagem: ");
      Serial.println(httpResponseCode);
    }

    http.end(); 
  } else {
    Serial.println("Erro de conexão WiFi");
  }

  esp_camera_fb_return(fb);  
}

void loop() {
  captureAndSendImage();
  delay(1000);  // Intervalo de 10 segundos entre capturas
}
