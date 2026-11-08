#include <Arduino.h>

/*
// v1 - работает ----------------------------------------------------------------------------------------

// Подключаем библиотеку для работы с HTTP-протоколом
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

// Вводим имя и пароль точки доступа
//const char *ssid =     "linksystve";     // Put your SSID here
//const char *password = "x93k6kq6wf";     // Put your PASSWORD here

const char *ssid =     "TP-Link_B394";     // Put your SSID here
const char *password = "18009217";     // Put your PASSWORD here

//const char* ssid     = "OPPO A9 2020";
//const char* password = "b277a4ee84e8";

void setup() 
{
  Serial.begin(115200);
  // делаем небольшую задержку на открытие монитора порта
  delay(5000);
  Serial.println("Через 5 секунд соединяемся с Wi-Fi..");
  delay(5000);
  // подключаемся к Wi-Fi сети
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(1000);
    Serial.println("Соединяемся с Wi-Fi..");
  }
  Serial.println("Соединение с Wi-Fi установлено");
}

void loop() 
{
  // выполняем проверку подключения к беспроводной сети
  if ((WiFi.status() == WL_CONNECTED)) 
  {
    // создаем объект для работы с HTTP
    HTTPClient http;
    WiFiClient client;
// подключаемся к веб-странице
    // http.begin("http://developer.alexanderklimov.ru/arduino/");
    //http.begin("https://doortry.ru/stihi/sorevnovanie-s-hakerami");
    // http.begin("https://kwinflat.ru/svanidze/");
    http.begin(client,"http://kwinflat.ru/Vid17b/");
    
    // делаем GET запрос
    int httpCode = http.GET();
    // проверяем успешность запроса
    if (httpCode > 0) 
    {
      // выводим ответ сервера
      String payload = http.getString();
      Serial.println("\n-------------------------------------------------------------------");
      Serial.println(httpCode);
      Serial.println(payload);
      Serial.println("-------------------------------------------------------------------");
    }
    else 
    {
      Serial.println("Ошибка HTTP-запроса");
    }
    // освобождаем ресурсы микроконтроллера
    http.end();
  }
  delay(10000);
}
// E1 - работает ----------------------------------------------------------------------------------------
*/

/*
// v2 - работает ----------------------------------------------------------------------------------------
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <ESP8266HTTPClient.h>

#include <WiFiClient.h>

ESP8266WiFiMulti WiFiMulti;

void setup() 
{

  Serial.begin(115200);
  delay(10000);
  // Serial.setDebugOutput(true);

  Serial.println();
  Serial.println();
  Serial.println();

  for (uint8_t t = 4; t > 0; t--) {
    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }

  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP("TP-Link_B394", "18009217");
}

void loop() 
{
  // wait for WiFi connection
  if ((WiFiMulti.run() == WL_CONNECTED)) 
  {

    WiFiClient client;

    HTTPClient http;

    Serial.print("[HTTP] begin...\n");
    if (http.begin(client, "http://kwinflat.ru/Vid17b/")) 
    {  // HTTP


      Serial.print("[HTTP] GET...\n");
      // start connection and send HTTP header
      int httpCode = http.GET();

      // httpCode will be negative on error
      if (httpCode > 0) 
      {
        // HTTP header has been send and Server response header has been handled
        Serial.printf("[HTTP] GET... code: %d\n", httpCode);

        // file found at server
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) 
        {
          String payload = http.getString();
          Serial.println(payload);
        }
      } else {
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }

      http.end();
    } 
    else 
    {
      Serial.println("[HTTP] Unable to connect");
    }
  }

  delay(10000);
}
// E2 - работает ----------------------------------------------------------------------------------------
*/

/*
// v3 - работает ----------------------------------------------------------------------------------------

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

// Ваши учётные данные
const char *ssid = "TP-Link_B394";                        // Название точки доступа
const char *password = "18009217";                        // Пароль точки доступа 

// Целевой URL (замените на свой)
const char* serverUrl = "http://kwinflat.ru/Vid17b/"; // Для POST
// Или для GET: const char* serverUrl = "http://example.com/get.php";

void setup() 
{
  Serial.begin(115200);
  delay(10000);
  // Подключение к Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("WiFi connected");
  Serial.println("");                                     // Если удачно подключились
  Serial.print("Connected to ");                          // Пишем в UART:
  Serial.println(ssid);                                   // Название точки доступа
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());                         // IP адрес назначенный нашему ESP

}

void sendData() 
{
  // Собираем данные (например, с датчика)
  String temperature = "25.5";
  String humidity = "60";

  // Для POST формируем тело запроса
  String requestBody = "api_key=YOUR_API_KEY&temperature=" + temperature + "&humidity=" + humidity;

  // Создаём объекты для запроса
  WiFiClient client;
  HTTPClient http;

  // Начинаем запрос
  http.begin(client, serverUrl);

  // Указываем тип контента для POST
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");

  // Отправляем данные
  int httpResponseCode = http.POST(requestBody);

  // Проверяем ответ сервера
  if (httpResponseCode > 0) 
  {
    Serial.println("POST successful. Code: " + String(httpResponseCode));
    String payload = http.getString();
    Serial.println("Response: " + payload);
  } 
  else 
  {
    Serial.println("POST failed. Error: " + String(httpResponseCode));
  }

  // Обязательно закрываем соединение
  http.end();
}

void loop() 
{
  // Периодически вызываем отправку (например, каждые 10 секунд)
  if (millis() % 10000 == 0) 
  {
    Serial.println("sendData()");
    sendData();
    delay(100);
  }
}
// E3 - работает ----------------------------------------------------------------------------------------
*/



#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h> 
boolean recievedFlag;
String strData, Link;

//Вводим параметры своей точки доступа WIFI 
const char *ssid = "TP-Link_B394";                        // Название точки доступа
const char *password = "18009217";                        // Пароль точки доступа 
//const char *host = "www.kwinflat.ru";                     // Адрес нашего веб сервера
const char *host = "http://kwinflat.ru/Vid17b";         // Адрес нашего веб сервера
const int httpsPort = 443;                                // Адрес порта для HTTPS= 443 или HTTP = 80
//const char fingerprint[] PROGMEM = "5B:FB:D1:D4:49:D3:0F:A9:C6:40:03:34:BA:E0:24:05:AA:D2:E2:01";    //ключ для шифрования
const char fingerprint[] PROGMEM = "15:5D:DF:F0:1C:A8:FB:88:61:83:AF:20:7D:E7:95:E0:37:44:C0:D5";    //ключ для шифрования

// Обьявление функции подключения к точкt доступа WIFI 
void setup() 
{
  Serial.begin(115200);                                   // Настройка скорости UART
  Serial.println("");
  delay(10000);                                           
  Serial.println("\nПодключение к WiFi");
  WiFi.mode(WIFI_OFF);                                    // Перезапуск точки доступа
  delay(1000);                                            // Ждем
  WiFi.mode(WIFI_STA);                                    // Настраиваем ESP в режиме клиента
  WiFi.begin(ssid, password);                             // Подключаемся к точке доступа
  // Ждем соединения
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }                                          
  Serial.println("");                                     // Если удачно подключились
  Serial.print("Connected to ");                          // Пишем в UART:
  Serial.println(ssid);                                   // Название точки доступа
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());                         // IP адрес назначенный нашему ESP
}

// Обьявление функции передачи данных
void transmit() 
{
  WiFiClientSecure httpsClient;                                //Обьявляем обьект класса WiFiClient
  Serial.println(host);                                        //Пишем в UART: адрес нашего веб сервера,
  Serial.printf("Using fingerprint '%s'\n", fingerprint);      //Ключ для шифрования.
  httpsClient.setFingerprint(fingerprint);                     //Присваиваем значения ключа для шифрования
  httpsClient.setTimeout(15000);                               //Присваиваем значение паузы (15 секунд)
  delay(1000);                                                 //Ждем                                     
  Serial.print("HTTPS Connecting");                            //Пишем в UART: Соединяемся с нашим веб сервером
  int r=0;                                                     //Обьявляем переменную счетчика попыток подключения
  while((!httpsClient.connect(host, httpsPort)) && (r < 30))
  {
    delay(100);Serial.print(".");r++;
  }                          //Пока пытаемся соединиться с веб сервером отправляем в UART точки
  if(r==30) 
    {Serial.println("Connection failed");}             //Если не получилось соединиться пишем в UART, что не получилось  
  else 
    {Serial.println("Connected to web");}                   //Если получилось соединиться пишем в UART, что получилось  
  Link = "/get.php?" + strData;                                //Формируем строку для GET запроса
  Serial.print("requesting URL: ");                            //Пишем в UART что отправляем GET запрос
  Serial.println(host+Link);                                   //Пишем в UART GET запрос
  httpsClient.print(String("GET ") + Link + " HTTP/1.1\r\n" +  
    "Host: " + host + "\r\n" + 
    "Connection: close\r\n\r\n");                                //Отправляем GET запрос через ESP
  Serial.println("request sent");                              //Пишем в UART что GET запрос отправлен
  while (httpsClient.connected())                              //Ловим ответ веб сервера
  {
    String line = httpsClient.readStringUntil('\n');
    if (line == "\r") 
    {
      Serial.println("headers received");break;
    }
  }
  Serial.println("reply was:");                                //Пишем в UART что веб сервер ответил
  Serial.println("==========");                                //Для красоты выводим в UART разграничивающую линию
  String line;                                                 //Формируем строку для ответа веб сервера
  while(httpsClient.available())
  {                              //Ловим строку от веб сервера
    line = httpsClient.readStringUntil('\n');                    
    Serial.println(line);
  }                                       //Пишем в UART строку от веб сервера
  Serial.println("==========");                                //Для красоты выводим в UART разграничивающую линию
  Serial.println("closing connection");
}                       //Пишем в UART, что закрыли соединение с веб сервером
 
//Основная функция
void loop() 
{
  while (Serial.available() > 0)                              // Прием данных из UART для передачи на  веб сервер
  { 
    strData +=(char)Serial.read();                            // Забиваем строку принятыми данными
    recievedFlag = true; delay(2); 
  };                         // Поднимаем флаг что получили данные
  if (recievedFlag)                                           // Если данные получены   
  { 
    Serial.println(strData);                                  // Пишем в UART строку для передачи на  веб сервер
    transmit();                                               // Запускаем функцию передачи данных
    strData ="";                                              // Очищаем строку от принятых данных
    recievedFlag = false;
  }                                    // Опускаем флаг
  delay(100);
}
