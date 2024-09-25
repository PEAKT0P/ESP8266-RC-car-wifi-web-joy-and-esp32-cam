#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WebSocketsServer_Generic.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Servo.h>
#include "index.h"
//#include "play.h"
#include "about.h"
#include "systemstat.h"

#define CMD_STOP 0
#define CMD_FORWARD 1
#define CMD_BACKWARD 2
#define CMD_LEFT 4
#define CMD_RIGHT 8
#define CMD_LED1 16
#define CMD_LED2 32
#define CMD_SERVO_MOVE 64
#define CMD_SERVO_LEFT 128
#define CMD_SERVO_RIGHT 256

#define IN1_PIN D5
#define IN2_PIN D3
#define IN3_PIN D8
#define IN4_PIN D7
#define SERVO_PIN D6

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const char* ssid = "DriverPack";
const char* password = "Streamer12345679";

IPAddress local_ip(192,168,3,1);
IPAddress gateway(192,168,3,1);
IPAddress subnet(255,255,255,0);

ESP8266WebServer server(80);
WebSocketsServer webSocket = WebSocketsServer(81);

uint8_t LED1pin = D4;
bool LED1status = HIGH;

uint8_t LED2pin = D0;
bool LED2status = HIGH;

int motorSpeed = 255;
unsigned long startTime;

Servo cameraServo;
int servoPosition = 90;
int targetServoPosition = 90;
unsigned long lastServoUpdate = 0;
const int servoUpdateInterval = 15; // миллисекунды между обновлениями положения

unsigned long lastClientActivity = 0;
const unsigned long CLIENT_TIMEOUT = 5000; // 5 секунд таймаут
bool clientConnected = false;
int currentCommand = CMD_STOP;

void setup() {
  Serial.begin(9600);

  pinMode(IN1_PIN, OUTPUT);
  pinMode(IN2_PIN, OUTPUT);
  pinMode(IN3_PIN, OUTPUT);
  pinMode(IN4_PIN, OUTPUT);
  
  pinMode(LED1pin, OUTPUT);
  pinMode(LED2pin, OUTPUT);
  digitalWrite(LED1pin, LED1status);
  digitalWrite(LED2pin, HIGH);

  cameraServo.attach(SERVO_PIN);
  cameraServo.write(servoPosition);
// Initialize OLED display
  Wire.begin(D1, D2);  // SDA = GPIO5 (D1), SCL = GPIO4 (D2)
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  
  startTime = millis();

    // Connect to Wi-Fi
  WiFi.softAP(ssid, password, 7);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  // Дополнительные настройки Wi-Fi для оптимизации видеопотока
  WiFi.setOutputPower(20.5);  // Устанавливаем максимальную мощность передатчика (20.5 дБм)
  WiFi.setPhyMode(WIFI_PHY_MODE_11N);  // Используем режим 802.11n для повышения пропускной способности
  // Настройка ширины канала (если поддерживается вашей версией ESP8266)
  system_phy_set_max_tpw(82);  // Устанавливаем максимальную мощность передачи (82 * 0.25 = 20.5 дБм)
  system_phy_set_tpw_via_vdd33(0);  // Отключаем автоматическую регулировку мощности
  delay(100);

  // Initialize WebSocket server
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);

  // Serve the HTML page
  server.on("/", HTTP_GET, []() {
    Serial.println("Web Server: received a web page request");
    server.send(200, "text/html", HTML_CONTENT);
  });
  // Serve the play.html page
//server.on("/play.html", HTTP_GET, []() {
//  Serial.println("Web Server: received a web page request for /play.html");
//  server.send(200, "text/html", PLAY_HTML_CONTENT);
//});
  // Serve the about.html page
server.on("/about.html", HTTP_GET, []() {
  Serial.println("Web Server: received a web page request for /play.html");
  server.send(200, "text/html", ABOUT_HTML_CONTENT);
});
  // Serve the about.html page
server.on("/system.html", HTTP_GET, []() {
  Serial.println("Web Server: received a web page request for /play.html");
  server.send(200, "text/html", SYSTEMSTAT_HTML_CONTENT);
});

  server.begin();
  Serial.print("ESP8266 Web Server's IP address: ");
  Serial.println(WiFi.softAPIP());
  playStartupMelody();
}
void smoothServoControl() {
  if (millis() - lastServoUpdate >= servoUpdateInterval) {
    if (servoPosition < targetServoPosition) {
      servoPosition++;
    } else if (servoPosition > targetServoPosition) {
      servoPosition--;
    }
    cameraServo.write(servoPosition);
    lastServoUpdate = millis();
  }
}

void loop() {
  server.handleClient();
  webSocket.loop();
  updateDisplay();
  smoothServoControl();
  executeCurrentCommand();
  checkConnection();
}
void executeCurrentCommand() {
  if (clientConnected) {
    switch (currentCommand) {
      case CMD_FORWARD:
        CAR_moveForward();
        break;
      case CMD_BACKWARD:
        CAR_moveBackward();
        break;
      case CMD_LEFT:
        CAR_turnLeft();
        break;
      case CMD_RIGHT:
        CAR_turnRight();
        break;
      default:
        CAR_stop();
    }
  } else {
    CAR_stop();
  }
}
void updateDisplay() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("IP: " + WiFi.softAPIP().toString());
  
  unsigned long currentTime = millis();
  unsigned long runTime = currentTime - startTime;
  int hours = runTime / 3600000;
  int minutes = (runTime % 3600000) / 60000;
  int seconds = (runTime % 60000) / 1000;
  
  display.print("Uptime: ");
  display.print(hours);
  display.print(":");
  if(minutes < 10) display.print("0");
  display.print(minutes);
  display.print(":");
  if(seconds < 10) display.print("0");
  display.println(seconds);
  
  display.println("+79998993123");
  display.println("Yana i love u");
  display.println("Nikol i love u");
  display.println("Powered by Denjik");
  
  // Добавляем логотип (сердечко)
  int16_t heart_x = 100;
  int16_t heart_y = 45;
  int16_t heart_size = 10;

  display.fillTriangle(
    heart_x, heart_y + heart_size, 
    heart_x + heart_size, heart_y, 
    heart_x + heart_size * 2, heart_y + heart_size, 
    WHITE);
  display.fillCircle(heart_x + heart_size / 2, heart_y, heart_size / 2, WHITE);
  display.fillCircle(heart_x + heart_size * 3 / 2, heart_y, heart_size / 2, WHITE);
  
  display.display();
}

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
  switch(type) {
    case WStype_DISCONNECTED:
      Serial.printf("[%u] Disconnected!\n", num);
      clientConnected = false;
      currentCommand = CMD_STOP;
      break;
    case WStype_CONNECTED:
      {
        IPAddress ip = webSocket.remoteIP(num);
        Serial.printf("[%u] Connected from %d.%d.%d.%d\n", num, ip[0], ip[1], ip[2], ip[3]);
        clientConnected = true;
        lastClientActivity = millis();
      }
      break;
    case WStype_TEXT:
      lastClientActivity = millis();
      {
        String message = String((char*)payload);
        if(message.startsWith("SPEED:")) {
          motorSpeed = message.substring(6).toInt();
          Serial.print("Motor speed set to: ");
          Serial.println(motorSpeed);
        } else if(message.startsWith("SERVO:")) {
          targetServoPosition = constrain(message.substring(6).toInt(), 0, 180);
          Serial.print("Target servo position set to: ");
          Serial.println(targetServoPosition);
        } else if(message == "PING") {
          // Обновляем lastClientActivity, но не меняем текущую команду
        } else {
          int command = message.toInt();
          Serial.print("Command received: ");
          Serial.println(command);

          switch (command) {
            case CMD_STOP:
            case CMD_FORWARD:
            case CMD_BACKWARD:
            case CMD_LEFT:
            case CMD_RIGHT:
              currentCommand = command;
              break;
            case CMD_LED1:
              LED1status = !LED1status;
              digitalWrite(LED1pin, LED1status);
              Serial.println(LED1status ? "LED1 ON" : "LED1 OFF");
              break;
            case CMD_LED2:
              LED2status = !LED2status;
              digitalWrite(LED2pin, LED2status);
              Serial.println(LED2status ? "LED2 OFF" : "LED2 ON");
              break;
            case CMD_SERVO_LEFT:
              targetServoPosition = max(0, targetServoPosition - 10);
              Serial.print("Servo Left: ");
              Serial.println(targetServoPosition);
              break;
            case CMD_SERVO_RIGHT:
              targetServoPosition = min(180, targetServoPosition + 10);
              Serial.print("Servo Right: ");
              Serial.println(targetServoPosition);
              break;
            default:
              Serial.println("Unknown command");
          }
        }
      }
      break;
  }
}
void checkConnection() {
  if (clientConnected && millis() - lastClientActivity > CLIENT_TIMEOUT) {
    Serial.println("Client timeout, stopping car");
    clientConnected = false;
    currentCommand = CMD_STOP;
  }
}

void CAR_moveForward() {
  if (clientConnected) {
    analogWrite(IN1_PIN, motorSpeed);
    analogWrite(IN2_PIN, 0);
    analogWrite(IN3_PIN, motorSpeed);
    analogWrite(IN4_PIN, 0);
  }
}

void CAR_moveBackward() {
  if (clientConnected) {
    analogWrite(IN1_PIN, 0);
    analogWrite(IN2_PIN, motorSpeed);
    analogWrite(IN3_PIN, 0);
    analogWrite(IN4_PIN, motorSpeed);
  }
}

void CAR_turnLeft() {
  if (clientConnected) {
    analogWrite(IN1_PIN, motorSpeed);
    analogWrite(IN2_PIN, 0);
    analogWrite(IN3_PIN, 0);
    analogWrite(IN4_PIN, 0);
  }
}

void CAR_turnRight() {
  if (clientConnected) {
    analogWrite(IN1_PIN, 0);
    analogWrite(IN2_PIN, 0);
    analogWrite(IN3_PIN, motorSpeed);
    analogWrite(IN4_PIN, 0);
  }
}

void CAR_stop() {
  digitalWrite(IN1_PIN, LOW);
  digitalWrite(IN2_PIN, LOW);
  digitalWrite(IN3_PIN, LOW);
  digitalWrite(IN4_PIN, LOW);
}

void playStartupMelody() {
  int melody[] = {262, 294, 330, 349, 392, 440, 494, 523};
  int durations[] = {200, 200, 200, 200, 200, 200, 200, 400};
  int lowPower = 25;  // Примерно 10% от максимальной мощности (255)
  
  for (int repeat = 0; repeat < 2; repeat++) {  // Повторяем дважды
    for (int i = 0; i < 8; i++) {
      int noteDuration = durations[i];
      
      // Вращение вперёд с низкой мощностью
      analogWrite(IN1_PIN, lowPower);
      analogWrite(IN2_PIN, 0);
      analogWrite(IN3_PIN, lowPower);
      analogWrite(IN4_PIN, 0);
      
      delay(noteDuration / 2);
      
      // Вращение назад с низкой мощностью
      analogWrite(IN1_PIN, 0);
      analogWrite(IN2_PIN, lowPower);
      analogWrite(IN3_PIN, 0);
      analogWrite(IN4_PIN, lowPower);
      
      delay(noteDuration / 2);
      
      // Остановка моторов
      analogWrite(IN1_PIN, 0);
      analogWrite(IN2_PIN, 0);
      analogWrite(IN3_PIN, 0);
      analogWrite(IN4_PIN, 0);
      
      delay(50);  // Небольшая пауза между нотами
    }
    delay(500);  // Пауза между повторениями
  }
}
