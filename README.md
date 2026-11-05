# PlatformIO_Lib

Слабоизменяемая прикладная коллекция библиотек для проектов на Arduino/ESP (PlatformIO)

### [Adаfruit Unified Sensor Driver, v1.1.15](https://github.com/adafruit/Adafruit_Sensor)

Библиотека‑абстракция от Adafruit, которая задаёт единый интерфейс для работы с разными датчиками в Arduino и совместимых платформах.

Главная цель — сделать код универсальным: если вы поменяете датчик на другой с тем же типом данных, менять логику скетча почти не придётся. Библиотека гарантирует:

- единые типы данных для всех датчиков;
- стандартные единицы измерения (СИ) — например, температура всегда в °C, освещённость в люксах, давление в гПа и т. д.;
- одинаковый способ чтения и получения характеристик датчика.

Это особенно удобно в проектах с несколькими датчиками или когда вы хотите сделать код переносимым между разными платами (в том числе ESP32/ESP8266).

### [DHT sensor library, v1.4.7](https://github.com/adafruit/DHT-sensor-library?ysclid=mvumra4gob712999909)

Библиотека для работы с датчиками серии DHT (DHT11, DHT22, DHT21 и другими совместимыми моделями). Она значительно упрощает считывание данных о температуре и влажности с этих датчиков.

Важное условие: для работы этой библиотеки требуется зависимость — ***Adafruit Unified Sensor Driver***.


### [GyverWDT, v2.3.1](https://github.com/GyverLibs/GyverWDT)

Библиотека для управления watchdog таймером, список поддерживаемых МК ниже.

>         ВНИМАНИЕ! Использование watchdog с Arduino-загрузчиком версии 'OLD' НЕДОСТУПНО

    Документация: https://alexgyver.ru/gyverwdt/
    GitHub: https://github.com/GyverLibs/GyverWDT

    Возможности:
    - Настройка режима работы watchdog
    - Настройка прерываний
    Поддержка МК:
        > AVR ATmega48p/88p/168p/328p (Arduino UNO/NANO/MINI/PRO MINI)
        > AVR ATmega32u4			  (Arduino LEONARDO/PRO MICRO)
        > AVR ATmega1280/2560		  (Arduino MEGA)
        > AVR ATtiny87/167			  (Naked chip)
        > AVR ATtiny45/85			  (Naked chip)
        > AVR ATtiny44/84			  (Naked chip)
        > AVR ATtiny13				  (Naked chip)
        Доступные режимы:
        > RST_MODE (RESET_MODE) 				- Сброс МК при тайм-ауте
        > ISR_MODE (INTERRUPT_MODE) 		 	- Прерывание при тайм-ауте
        > ISR_RST_MODE (INTERRUPT_RESET_MODE) 	- Прерывание при тайм-ауте и переключение в RST_MODE (RESET_MODE)

    Egor 'Nich1con' Zaharov for AlexGyver, alex@alexgyver.ru
    https://alexgyver.ru/
    MIT License

    Версии:
    v2.3 ~ 08.11.2021


### [iarduino_VCC, v1.0.2](https://github.com/tremaru/iarduino_VCC/tree/main)

Библиотека чтения напряжения питания Arduino UNO, UNO R4, MINI, NANO, MEGA, ULTRA, LEONARDO, MICRO, Версия: 1.0.2

Последнюю версию библиотеки Вы можете скачать по ссылке: [https://iarduino.ru/file/568.html](https://iarduino.ru/file/568.html)

Подробное описание функций бибилиотеки доступно по ссылке: [https://wiki.iarduino.ru/page/arduino-vcc/](https://wiki.iarduino.ru/page/arduino-vcc/)

Библиотека является собственностью интернет магазина iarduino.ru и может свободно использоваться и распространяться!  При публикации устройств или скетчей с использованием данной библиотеки, как целиком, так и её частей, в том числе и в некоммерческих целях, просим Вас опубликовать ссылку: http://iarduino.ru

Автор библиотеки: Панькин Павел.

