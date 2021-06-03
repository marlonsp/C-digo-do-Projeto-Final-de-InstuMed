#include <DHT.h>
#include <Adafruit_BMP280.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
Adafruit_BMP280 bmp; // Declara objeto do tipo BMP
DHT dht(2,DHT22); // Declara objeto do tipo DHT
int bin0, bin1; float tensao0, tensao1, umid, temp, press, res, lum; // Declara variáveis
LiquidCrystal_I2C lcd(0x27,16,2);
byte customChar0[] = { // caracter "°"
  B00111,
  B00101,
  B00111,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};
byte customChar1[] = {// caracter "ó"
  B00010,
  B00100,
  B00000,
  B01110,
  B10001,
  B10001,
  B10001,
  B01110
};
byte customChar2[] = {// caracter "ã"
  B01101,
  B10010,
  B00000,
  B01110,
  B00001,
  B01111,
  B10001,
  B01111
};
byte customChar3[] = {//caracter "ç"
  B00000,
  B01110,
  B10001,
  B10000,
  B10001,
  B01110,
  B00100,
  B01000
};


void setup()
{
Serial.begin(9600); // Inicializa serial
dht.begin(); // Inicializa objeto dht
bmp.begin(0x76); // Inicializa objeto BMP
analogReference(INTERNAL); // Fundo escala 1,1 V
lcd.init(); // Inicializa LCD
lcd.backlight(); // Liga luz do LCD
lcd.createChar(0, customChar0);
lcd.createChar(1, customChar1);
lcd.createChar(2, customChar2);
lcd.createChar(3, customChar3);
lcd.setCursor(0,0); // Move cursor no LCD
lcd.print("Esta");// Escreve no LCD
lcd.write(3);
lcd.write(2);
lcd.print("o");
lcd.setCursor(0,1);
lcd.print("Metereol");
lcd.write(1);
lcd.print("gica");
delay(3000);
lcd.setCursor(0,0); 
lcd.print("Instrumenta");
lcd.write(3);
lcd.write(2);
lcd.print("o e");
lcd.setCursor(0,1);
lcd.print("Medi");
lcd.write(3);
lcd.write(2);
lcd.print("o         ");
delay(3000);
lcd.setCursor(0,0);
lcd.print("1B Engenharia   ");
lcd.setCursor(0,1);
lcd.print("2021/1          ");
delay(3000);
lcd.setCursor(0,0);
lcd.print("Douglas Pablo   ");
lcd.setCursor(0,1);
lcd.print("B. Celestino    ");
delay(3000);
lcd.setCursor(0,0);
lcd.print("Lucas Nory      ");
lcd.setCursor(0,1);
lcd.print("Ulson           ");
delay(3000);
lcd.setCursor(0,0);
lcd.print("Marlon Silva    ");
lcd.setCursor(0,1);
lcd.print("Pereira         ");
delay(3000);
}

void loop()
{
bin0 = analogRead(A0); // Lê valor binário
tensao0 = (bin0/1023.0)*1.1; // Converte em tensão
temp = 99.62*tensao0+0.06; // Converte em temp.
umid = dht.readHumidity(); // Lê umidade
umid = 1.02*umid + 0.24; // Calibração
press = bmp.readPressure(); // Lê pressão
bin1 = analogRead(A1); // Lê binário
tensao1 = (bin1/1023.0)*1.1; // Calc. tensão
res = tensao1*100000.0/(5.0-tensao1); // Calc. resist.
lum = pow(10,6.5-1.25*log10(res)); // Calc. lumnos.
Serial.print("\n\nTemperatura [ºC]: ");
Serial.print(temp); // Exibe temperatura
Serial.print("\nUmidade [%]: ");
Serial.print(umid); // Exibe umidade
Serial.print("\nPressão [hPa]: ");
Serial.print(press/100); // Exibe pressão
Serial.print("\nLuminosidade [Lux]: ");
Serial.print(lum); // Exibe luminosidade
lcd.setCursor(0,0); // Move cursor no LCD
lcd.print("Temp: ");// Escreve no LCD
lcd.print(temp);
lcd.write(0);
lcd.print("C    ");
lcd.setCursor(0,1);
lcd.print("Umid: ");
lcd.print(umid);
lcd.print("%     ");
delay(3000);
lcd.setCursor(0,0);
lcd.print("Pres: ");
lcd.print(press/100);
lcd.print(" hPa");//
lcd.setCursor(0,1);
lcd.print("Lum: ");
lcd.print(lum);
lcd.print(" Lux");
delay(3000);
}
