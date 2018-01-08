#include <Servo.h> 
#include <Wire.h>

Servo motor;

int mot_pin = D6;    //Подключаем мотор к пину D6

int js_position = 1000;  //Начальная позиция
int max_position = 2000; //Максимальное значение ШИМ 2 мс
int min_position = 1000;  //Минимальное значени ШИМ 1 мс

int i = 0; // Counter
int j = 0; // направление измерения 0-рост, 1 - уменьшение

int ledState = LOW;                 // переменная состояния лампочки
unsigned long previousMillis = 0;   // счетчик
unsigned long currentMillis = 0;    // счетчик
const long interval = 1000;         // полу-период счетчика

void setup() 
{
 pinMode(LED_BUILTIN, OUTPUT);    // насраиваем вывод встроенной лампочки на выход
 Serial.begin(115200); // Initialize serial port
 while(!Serial); // wait for serial
 
 delay(3000); // Waits 3 seconds
 Serial.println("Serial start"); // Sends preamble and Cr+Lf
 delay(3000); // Waits 3 seconds

 motor.attach(mot_pin, min_position, max_position);    //Инициальзация мотора (порт, минимальная позиция, максимальная позиция)       !!!
 Serial.println("Servo init"); // Sends preamble and Cr+Lf
 delay(1000);
 
 motor.detach();    //Остановка мотора  чтобы контроллер вошел в режим полета    !!!
 Serial.println("Servo Stop"); // Sends preamble and Cr+Lf
 delay(10000);
 
 motor.attach(mot_pin, min_position, max_position);    //Инициальзация мотора (порт, начальная позиция, максимальная позиция)       !!!
 motor.writeMicroseconds(js_position);
 Serial.println("Servo start at 1 ms"); // Sends preamble and Cr+Lf
 i = 0;

} 

void loop() 
{
 
   unsigned long currentMillis = millis();            // объявляем переменную и считываем текущее время
  if(currentMillis - previousMillis >= interval) {    // проверяем не вышло ли время цикла
    previousMillis = currentMillis;   
    if (ledState == LOW)
      ledState = HIGH;  // Note that this switches the LED *off*
    else
     { ledState = LOW;   // Note that this switches the LED *on*
      if (j==0)
      {i = i +1;
      if (i==10) j=1;
      }
      else 
      {i = i - 1;
      if (i==0) j=0;
      }
      
      js_position = min_position + 100*i;
      motor.writeMicroseconds(js_position);
      Serial.print("Speed = "); // send Start
      Serial.println(js_position); // send Start
      }  
    digitalWrite(LED_BUILTIN, ledState);
  }

}
