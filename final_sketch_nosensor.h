
// Подключаем библиотеки:
#include <Servo.h> 
#include <Wire.h>                                               // Для работы с шиной I2C
#include <SparkFun_APDS9960.h> 
#define STEPS 4078
#include <Stepper_28BYJ.h>
SparkFun_APDS9960 apds = SparkFun_APDS9960();        // Для работы с датчиком APDS-9960
Stepper_28BYJ stepper(STEPS, 9, 10, 11, 12);

// Объявляем переменные:  
                                     
uint16_t lightAmbient = 0;                                      // Определяем переменную для хранения общей освещенности в люксах
uint16_t lightRed     = 0;                                      // Определяем переменную для хранения освещённости красного спектра в люксах
uint16_t lightGreen   = 0;                                      // Определяем переменную для хранения освещённости зелёного спектра в люксах
uint16_t lightBlue    = 0;                                      // Определяем переменную для хранения освещённости синего   спектра в люксах
int grad45 = 4075.7728395 / 8;
int leftPos = 144;
int rightPos = 30;
int storona_red = 0;
int storona_green = 0;
int storona_blue = 0;
int storona_yellow = 0;

Servo sRotate;

void setup() { 
  Serial.begin(9600);                                           // Устанавливаем скорость передачи в последовательный порт
  sRotate.attach(13);
  stepper.setSpeed(13);                                         // Установка скорости
  Serial.println("start");
  digitalWrite(2, HIGH);                                         // Включаем освещение для датчика              
} 
 
void loop() {   
// Работа блютуз модуля
int bluetooth_val = Serial.read();                              // Определяем переменную для хранения команд  
Serisl.println('bluetooth_val='+bluetooth_val);
if (bluetooth_val == 2){
  storona_red = rightPos;}
if (bluetooth_val == 3){
  storona_red = leftPos;}
if (bluetooth_val == 4){
  storona_green = rightPos;}
if (bluetooth_val == 5){
  storona_green = leftPos;}
if (bluetooth_val == 6){
  storona_blue = rightPos;}
if (bluetooth_val == 7){
  storona_blue = leftPos;}
if (bluetooth_val == 8){
  storona_yellow = rightPos;}
if (bluetooth_val == 9){
  storona_yellow = leftPos;}             
//  Читаем значения освещённости в переменные:                 
if(apds.readAmbientLight(lightAmbient)                          
  && apds.readRedLight(lightRed)
  && apds.readGreenLight(lightGreen)
  && apds.readBlueLight(lightBlue)){
    Serial.println("Red=" + lightRed + ", Green=" + lightGreen + ", Blue=" + lightBlue);
    while ((bluetooth_val == 1)
	  && (bluetooth_val != 0) ){        // движение в направлении по часовой 1 оборот пока видна конвейерная лента
	    stepper.step(grad45);}  
// работа датчика цвета
if ((55 < apds.readRedLight(lightRed) < 59)
   && (55 < apds.readGreenLight(lightGreen) < 58)
   && (44 < apds.readBlueLight(lightBlue) < 48)){            // rgb для красного кубика
     digitalWrite(9, LOW);
     digitalWrite(10, LOW);
     digitalWrite(11, LOW);
     digitalWrite(12, LOW);
     delay(500);
     sRotate.write(storona_red); 
     delay(1000);
     sRotate.write(storona_red*-1); 
     delay(500);
     digitalWrite(9, HIGH);
     digitalWrite(10, HIGH);
     digitalWrite(11, HIGH);
     digitalWrite(12, HIGH);}
if ((33 < apds.readRedLight(lightRed) < 38) 
   && (36 < apds.readGreenLight(lightGreen) < 41)
   && (44 < apds.readBlueLight(lightBlue) < 48)){            // rgb для зеленого кубика
     digitalWrite(9, LOW);
     digitalWrite(10, LOW);
     digitalWrite(11, LOW);
     digitalWrite(12, LOW);
     delay(500);
     sRotate.write(storona_green); 
     delay(1000);
     sRotate.write(storona_green*-1); 
     delay(500);
     digitalWrite(9, HIGH);
     digitalWrite(10, HIGH);
     digitalWrite(11, HIGH);
     digitalWrite(12, HIGH);}
if ((20 < apds.readRedLight(lightRed) < 26)
   && (25 < apds.readGreenLight(lightGreen) < 31)
   && (34 < apds.readBlueLight(lightBlue) < 37)){            // rgb для синего кубика
     digitalWrite(9, LOW);
     digitalWrite(10, LOW);
     digitalWrite(11, LOW);
     digitalWrite(12, LOW);
     delay(500);
     sRotate.write(storona_blue); 
     delay(1000);
     sRotate.write(storona_blue*-1); 
     delay(500);
     digitalWrite(9, HIGH);
     digitalWrite(10, HIGH);
     digitalWrite(11, HIGH);
     digitalWrite(12, HIGH);}
if ((55 < apds.readRedLight(lightRed) < 60)
   && (45 < apds.readGreenLight(lightGreen) < 50)
   && (54 < apds.readBlueLight(lightBlue) < 58)){   // rgb для желтого кубика
     digitalWrite(9, LOW);
     digitalWrite(10, LOW);
     digitalWrite(11, LOW);
     digitalWrite(12, LOW);
     delay(500);
     sRotate.write(storona_yellow); 
     delay(1000);
     sRotate.write(storona_yellow*-1); 
     delay(500);
     digitalWrite(9, HIGH);
     digitalWrite(10, HIGH);
     digitalWrite(11, HIGH);
     digitalWrite(12, HIGH);}
}                                                       
//  Приостанавливаем выполнение скетча на 1 секунду, чтобы не перегружать шину I2C постоянными запросами:       
     delay(1000);                                                
}                                                          


