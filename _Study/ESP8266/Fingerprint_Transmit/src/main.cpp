#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h> 
boolean recievedFlag;
String strData, Link;

//Вводим параметры своей точки доступа WIFI 
const char *ssid = "TP-Link_B394";                        // Название точки доступа
const char *password = "18009217";                        // Пароль точки доступа 
//const char *host = "www.kwinflat.ru";                     // Адрес нашего веб сервера
//const char *host = "https://kwinflat.ru/Vid17b";         // Адрес нашего веб сервера
const char *host = "www.kwinflat.ru/Vid17b";                     // Адрес нашего веб сервера
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
