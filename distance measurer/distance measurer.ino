
#define buton A7
#include <LiquidCrystal.h> 
LiquidCrystal LCD(9, 8, 5, 4, 3, 2); 

#define trigPin 6 //Sensörün Echo pini Arduinonun 6. pinine bağlanır
#define echoPin 7 //Sensorün Trig pini Arduinonun 7. pinine bağlanır

int turn = 0;
int butonFlag = 0;
unsigned long ilkDeger;
void setup()
{
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT); //6. yani trigpini çıkış olarak ayarlıyoruz
  pinMode(echoPin, INPUT); //7. yani echoPini giriş olarak ayarlıyoruz

  LCD.begin(16, 2); 
  LCD.setCursor(0, 0); 
  LCD.print("   ULTRASONIK    "); 
  LCD.setCursor(0, 1); 
  LCD.print("  MESAFE OLCER   "); 
  delay(1000);
  LCD.clear();
}

void loop() {
tekrar:
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  ilkDeger = millis();
  duration = pulseIn(echoPin, HIGH );
  distance = (duration / 2) / 28.75; 

  if ((millis() - ilkDeger) >= 600)
  {
    LCD.setCursor(0, 0); 
    LCD.print("MENZIL DISI VEYA"); 
    LCD.setCursor(0, 1); 
    LCD.print("  ZAMAN ASIMI   ");
    delay(1000);
    LCD.clear();
    goto tekrar;
  }

  if (butonFlag == 0 )
  {

    if (distance > 500)
    {
      LCD.setCursor(0, 0); 
      LCD.print("  OLCUM ACISI   "); 
      LCD.setCursor(0, 1); 
      LCD.print("  UYGUN DEGIL   ");
      delay(1000);
      LCD.clear();
      goto tekrar;
    }

  }


  if (!digitalRead(buton) && turn == 0)
  {
    butonFlag = 1;
    turn = 1;
    Serial.println("butona basıldı");
    while (!digitalRead(buton)) {}
  }
  
  if (!digitalRead(buton) && turn == 1)
  {
    butonFlag = 0;
    turn = 0;
    Serial.println("buton bırakıldı");
  }



  if (butonFlag == 0)
  {
    LCD.setCursor(0, 0); 
    LCD.print("     MESAFE     ");
    LCD.setCursor(0, 1); 
    LCD.setCursor(5, 1); 
    LCD.print(distance); 
    LCD.print("    ");
    LCD.setCursor(9, 1);
    LCD.print("cm   ");
    Serial.println(distance);
    delay(250); 
  }

  if (butonFlag == 1 )
  {
    LCD.setCursor(0, 0); 
    LCD.print("   DONDURULDU   ");
    LCD.setCursor(0, 1); 
     LCD.print("         ");
    LCD.setCursor(5, 1); 
    LCD.print(distance); 
    LCD.print("      ");
    LCD.setCursor(9, 1);
    LCD.print("cm   ");
    Serial.println(distance);
    while (digitalRead(buton)) {

    }
  }

}
