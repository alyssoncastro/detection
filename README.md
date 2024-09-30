# DETECÇÃO DE FACES COM ESP32 CAM

###### AUTOR: ALYSSON C. C. CORDEIRO

Este projeto utiliza um microcontrolador ESP32 e uma câmera para capturar imagens, enviá-las para um servidor Flask, que por sua vez processa as imagens e realiza a detecção de faces utilizando o OpenCV. O sistema exibe as imagens com a detecção de faces e também informa quando não há faces detectadas.

### Estrutura de pastas:

```python
detection/
├── CameraWebServer/
│   ├── app_httpd.cpp
│   ├── camera_index.h
│   ├── camera_pins.h
│   ├── CameraWebServer.ino
├── servidor_post/
│   ├── models/
│   │   └── haarcascade_frontalface_default.xml
│   ├── imagem_processada.jpg
│   ├── main.py
└── README.md
```

### Requisitos:

```python
- ESP32
- Câmera compatível com ESP32 (ex: AI-Thinker)
- Flask
- OpenCV
- NumPy
```

### Instrução de uso

1. Clonar: 

```python
git clone https://github.com/alyssoncastro/detection.git
```

2. Configuração

```python
Dentro da pasta CameraWebServer, você encontrará o arquivo CameraWebServer.ino, que deve ser carregado no ESP32 utilizando o Arduino IDE.

- Configure sua rede Wi-Fi no código, alterando as variáveis ssid e password.
- Compile e faça o upload do código para o ESP32
```

3. Servidor:

Após instalar as independencias, inicie o servidor Flask executando o seguinte comando:

```python
python main.py
```

```python
OBS: Na captura e processamento de imagens, uma vez que o ESP32 estiver conectado à rede Wi-Fi e o servidor Flask estiver em execução, o ESP32 irá capturar imagens e enviá-las para o servidor, que processará as imagens e detectará as faces.

Se uma face for detectada, um retângulo será desenhado ao redor da face e a imagem será exibida.
Caso não haja faces na imagem, o servidor exibirá uma mensagem informando que "Nenhuma face foi encontrada".

O servidor também abrirá uma janela no seu computador para exibir as imagens com os resultados da detecção de faces.

além disso, deve ter um arquivo importante que é o "haarcascade_frontalface_default.xml", que é um modelo de detecção de faces pré-treinado do OpenCV.
```

### vídeo demonstrativo:

(https://drive.google.com/file/d/1LjB3pkKYZCJ6-QHGQZG8KjujXwSSo4LC/view?usp=sharing)
