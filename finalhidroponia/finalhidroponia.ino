#include <EtherCard.h>
#include "RTClib.h"
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2); 
static byte mymac[] = { 0x74,0x69,0x69,0x2D,0x30,0x31 };
byte Ethernet::buffer[1000];
static byte myip[] = {192,168,1,25};
const int llave1 = 4;
const int llave2 = 5;
const int llave3 = 6;
const int bomba = 7;
char* Estadollave1="OFF";
char* Estadollave2="OFF";
char* Estadollave3="OFF";
char modo='a';
#include "DHT.h"
#define DHTPIN 2
#define hidro1 A0
#define hidro2 A1
#define hidro3 A2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
RTC_DS1307 RTC;
int t;
long hum1=0;
long tem1=0;
long h1hum=0;
long h2hum=0;
long h3hum=0;
long hu=0;
int pos = 0;
void setup() {
  Serial.begin(9600);
  lcd.init();                      // initialize the lcd
  lcd.backlight();
  dht.begin();
  RTC.begin();
 //RTC.adjust(DateTime(__DATE__, __TIME__)); // Establece la fecha y hora (Comentar una vez establecida la hora)
  pinMode(hidro1, INPUT);
  pinMode(hidro2, INPUT);
  pinMode(hidro3, INPUT);
   pinMode(bomba, OUTPUT);
  pinMode(llave1, OUTPUT);
  pinMode(llave2, OUTPUT);
  pinMode(llave3, OUTPUT);
   digitalWrite(llave1, LOW);
    digitalWrite(llave2, LOW);
    digitalWrite(llave3, LOW);
  Serial.println("Test del Modulo  ENC28J60");
  digitalWrite(bomba, HIGH);
  // mostrarhumedad();
  if (!ether.begin(sizeof Ethernet::buffer, mymac, SS))
    Serial.println( "No se ha podido acceder a la controlador Ethernet");
 else
   Serial.println("Controlador Ethernet inicializado");
 
  if (!ether.staticSetup(myip))
    Serial.println("No se pudo establecer la dirección IP");

  Serial.println();
}
void loop() {
 pagina();
  mostrarhumedad();
   delay(100); 
}
void mostrarhumedad() {
hum1 = dht.readHumidity();
tem1 = dht.readTemperature();
  h1hum = map(analogRead(hidro1), 0, 1023, 100, 0);
  h2hum = map(analogRead(hidro2), 0, 1023, 100, 0);
  h3hum = map(analogRead(hidro3), 0, 1023, 100, 0);
  DateTime now = RTC.now(); 
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("|Hum:");
    lcd.print(hum1);
    lcd.print("%|");
    lcd.print("Tem:");
    lcd.print(tem1);
    lcd.print("C|");
    lcd.setCursor(0, 1);
    lcd.print(now.day(), DEC);
    lcd.print("/");
    lcd.print(now.month(), DEC);
    lcd.print("/");
    lcd.print(now.year() - 2000);
 lcd.print("|");
    lcd.print(now.hour(), DEC);
    lcd.print(":");
    lcd.print(now.minute(), DEC);
    lcd.print(":");
    lcd.print(now.second(), DEC);  
int hora=(now.hour());
int minu=(now.minute());
int segu=(now.second());
Serial.print(hora);
Serial.print(':');
Serial.print(minu);
Serial.print(':');
Serial.println(segu);
if(hora>7 && hora<18){
  if(modo=='a'){
  if(minu==0 && segu==0){
    digitalWrite(llave1, HIGH);
    digitalWrite(llave2, HIGH);
    digitalWrite(llave3, HIGH);
      digitalWrite(bomba, LOW);
      Estadollave1="ON";Estadollave2="ON"; Estadollave3="ON";
      }
      modo='b';
      }
    if(modo=='b'){
  if(minu==0 && segu==10){
    digitalWrite(llave1, LOW);
    digitalWrite(llave2, LOW);
    digitalWrite(llave3, LOW);
      digitalWrite(bomba, HIGH);
      Estadollave1="OFF";Estadollave2="OFF"; Estadollave3="OFF";}
  } modo='a';}
    
}

static word homePage() {

 BufferFiller bfill = ether.tcpOffset();
 bfill.emit_p(PSTR("<!DOCTYPE html>\n"
      "<html><head><title>Hidroponia Unu</title>"
      "<meta http-equiv='refresh' content='3000;url=http://192.168.1.38:81/hidro/subir.php?h=$L&&t=$L&&h1=$L&&h2=$L&&h3=$L'>"
       "<meta charset='utf-8'></head><body style='background-color:red;'>"
      "<center>"
      "<h1>Area de control hidroponia unu 2019</h1>" 
      "<a href='http://192.168.1.34:81/hidroponiamovil/'>volver al sistema de reportes</a><center/>"
      "<br>Llave 1: $S<a href=\"/?llave1=ON\"><input type=\"button\" value=\"ON\"></a><a href=\"/?llave1=OFF\"><input type=\"button\" value=\"OFF\"></a> <br>"      
      "<br>Llave 2: $S<a href=\"/?llave2=ON\"><input type=\"button\" value=\"ON\"></a><a href=\"/?llave2=OFF\"><input type=\"button\" value=\"OFF\"></a> <br>"
      "<br>Llave 3: $S<a href=\"/?llave3=ON\"><input type=\"button\" value=\"ON\"></a><a href=\"/?llave3=OFF\"><input type=\"button\" value=\"OFF\"></a> <br>"
      "</body></html>"      
      ),hum1,tem1,h1hum,h2hum,h3hum,Estadollave1,Estadollave2,Estadollave3);
     
  return bfill.position();
}
void pagina(){word len = ether.packetReceive();
  word pos = ether.packetLoop(len);
   
  if(Estadollave1=="ON"|| Estadollave2=="ON"|| Estadollave3=="ON") {digitalWrite(bomba, LOW);}else{digitalWrite(bomba, HIGH);}
  
  if(pos) {
    
    if(strstr((char *)Ethernet::buffer + pos, "GET /?llave1=ON") != 0) {
      Serial.println("Comando ON recivido");
      digitalWrite(llave1, HIGH);
      Estadollave1 = "ON";
    }

    if(strstr((char *)Ethernet::buffer + pos, "GET /?llave1=OFF") != 0) {
   
      digitalWrite(llave1, LOW);
       Estadollave1= "OFF";
    }
    if(strstr((char *)Ethernet::buffer + pos, "GET /?llave2=ON") != 0) {
    
      digitalWrite(llave2, HIGH);
      Estadollave2 = "ON";
    }

    if(strstr((char *)Ethernet::buffer + pos, "GET /?llave2=OFF") != 0) {
    
      digitalWrite(llave2, LOW);
       Estadollave2= "OFF";
    }
    if(strstr((char *)Ethernet::buffer + pos, "GET /?llave3=ON") != 0) {
 
      digitalWrite(llave3, HIGH);
      Estadollave3 = "ON";
    }
    if(strstr((char *)Ethernet::buffer + pos, "GET /?llave3=OFF") != 0) {
   
      digitalWrite(llave3, LOW);
       Estadollave3= "OFF";
    }      
    ether.httpServerReply(homePage()); // se envia página Web
  }}
