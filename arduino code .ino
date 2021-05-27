#include <SD.h>
#include <SoftwareSerial.h>
#include <EEPROM.h>
#include <SPI.h>
#include "RTClib.h"
#include <Wire.h>
#include <Separador.h>
#include <epd2in9.h>
#include <epdpaint.h>
#define DEBUG true

Separador s;
RTC_DS3231 rtc;

#define COLORED     0
#define UNCOLORED   1
volatile int ISRenter = 0;
volatile int ISRatras = 0;
volatile int ISRabajo = 0;
volatile int ISRarriba = 0;
const int  ENTER = 2;    // the pin that the pushbutton is attached to
const int  ATRAS = 3;
const int  ABAJO = 18;
const int  ARRIBA = 19;
const int  DERECHA = 5;
const int  IZQUIERDA = 6;
long timeCounter = 0;
const int timeThreshold = 250;

boolean Flaginicio = false;
boolean Flagtar = false;
boolean Flagtar1 = false;
boolean Flag = false;
boolean Flagparameters = false;
boolean Flagviewtar1 = false;
boolean Flagviewtar2 = false;
boolean Flagoptionselect = false;
boolean Flagselect = false;
boolean Flagselect1 = false;
boolean Flagpantalla3 = false;
boolean Flagpantalla2 = false;
boolean Flagpantalla1 = false;
boolean Flagpantalla = false;
boolean Flaginfo = false;
boolean Flagtarifa=false;
boolean Flagdisplay=false;
boolean Flagocupado=false;

int enter = 0;   // enter for the number of button presses
int atras = 0;
int abajo = 0;
int derecha = 1;
int izquierda = 0;
int arriba = 0;
int buttonState = 0;         // current state of the button
int buttonState1 = 0;
int buttonState2 = 0;
int buttonState3 = 0;
int buttonState4 = 0;
int buttonState5 = 0;
int lastButtonState = 0;     // previous state of the button
int lastButtonState1 = 0;
int lastButtonState2 = 0;
int lastButtonState3 = 0;
int lastButtonState4 = 0;
int lastButtonState5 = 0;
int Decena1, Unidad1;
int Decena2, Unidad2;
int Decena3, Unidad3;
unsigned char image[0];
Paint paint(image, 0, 0);    // width should be the multiple of 8
Epd epd;
int a;

char cc[20];
const char parametros[] PROGMEM = "Parametros";
const char tari[] PROGMEM = "Tarifas";
const char info[] PROGMEM = "Informacion";
const char impr[] PROGMEM = "Modo Configuracion";
const char tard[] PROGMEM = "Tarifa Diurna";
const char tarn[] PROGMEM = "Tarifa Nocturna";

const char tarm[] PROGMEM = "Tarifa minima:";
const char arranque[] PROGMEM = "Arranque:";
const char porkm[] PROGMEM = "Por Km:";
const char minu[] PROGMEM = "Min espera:";

const char nums[] PROGMEM = "Num Serie:";
const char constk[] PROGMEM = "Constante K:";
const char pla[] PROGMEM = "Placa:";
const char numre[] PROGMEM = "Num Registro:";

const char comp[] PROGMEM = "Compania:";
const char ciudad[] PROGMEM = "Ciudad:";
const char rucs[] PROGMEM = "Ruc:";
const char auts[] PROGMEM = "Aut.SRI:";
const char tit[] PROGMEM = "Titular:";

const char print1[] PROGMEM = "Parametros";
const char print2[] PROGMEM = "Reporte mensual";
const char print3[] PROGMEM = "Reporte total";
const char print4[] PROGMEM = "Reporte diario";

const char * const string_table[] PROGMEM =     // change "string_table" name to suit
{
  parametros, tari, info, impr, tard, tarn, tarm, arranque, porkm, minu,
  nums, constk, pla, numre,
  comp, ciudad, rucs, auts, tit,
  print1, print2, print3, print4
};

int eeAddress = 1; 
int eeAddress1 = 51; 
int eeAddress2 = 81; 
int eeAddress3 = 95; 
int eeAddress4 = 106; 

int eeAddress5 = 150; 
int eeAddress6 = 165; 
int eeAddress7 = 170; 
int eeAddress8 = 172; 
int eeAddress9 = 174; 
int eeAddress10 = 184; 

int eeAddress11 = 200; 
int eeAddress12 = 205; 
int eeAddress13 = 210; 
int eeAddress14 = 215; 
int eeAddress15 = 220; 

int eeAddress16 = 225; 
int eeAddress17 = 230; 
int eeAddress18 = 235; 
int eeAddress19 = 240; 
int eeAddress20 = 245; 

int eeAddress21 = 250; 
int eeAddress22 = 255; 
int eeAddress23 = 275; 
int eeAddress24 = 280; 
int eeAddress25 = 300; 

int eeAddress26 = 310; 
int eeAddress27 = 314; 
int eeAddress28 = 318; 
int eeAddress29 = 322; 

//float td;//ck
char tarifas [5];
int vlc;// vlm;
int aa, mes, dia, hora, minuto, segundo;
int dr;//mr,ar;
int connectionId;
char compania[50];
char ciu[30];
char ruc[15];
char placa[10];
char master[5]; 
char chofer1[20];

void setup()
{

  pinMode(ENTER, INPUT_PULLUP);
  pinMode(ATRAS, INPUT_PULLUP);
  pinMode(ABAJO, INPUT_PULLUP);
  pinMode(DERECHA, INPUT_PULLUP);
  pinMode(IZQUIERDA, INPUT_PULLUP);
  pinMode(ARRIBA, INPUT_PULLUP);

  Serial.begin(9600);    ///////For Serial monitor
  if (! rtc.begin())
  {
    while (1);
  }

  Serial2.begin(9600); ///////ESP Baud rate

    Serial2.write("AT+CWMODE=3\r\n");
    delay(200);
    Serial2.write("AT+CIPMUX=1\r\n");
    delay(200);
    Serial2.write("AT+CIPSERVER=1,80\r\n");
    delay(200);

  if (epd.Init(lut_full_update) != 0)
  {
    return;
  }
  epd.ClearFrameMemory(0xFF);   // bit set = white, bit reset = black
  epd.DisplayFrame();
  epd.ClearFrameMemory(0xFF);   // bit set = white, bit reset = black
  epd.DisplayFrame();

  if (epd.Init(lut_partial_update) != 0)
  {
    return;
  }
  attachInterrupt(digitalPinToInterrupt(ENTER), interruptCount, FALLING);
  attachInterrupt(digitalPinToInterrupt(ATRAS), interruptCount1, FALLING);
  attachInterrupt(digitalPinToInterrupt(ABAJO), interruptCount2, FALLING);
  attachInterrupt(digitalPinToInterrupt(ARRIBA), interruptCount3, FALLING);
}
void loop()
{
  left();
  right();
  if (Serial2.available())
  {
    /////////////////////Recieving from client
    if (Serial2.find("+IPD,"))
    {
      delay(300);
      connectionId = Serial2.read() - 48;
      String cadena = "";
      String elemento1, elemento2, elemento3, elemento4, elemento5, elemento6, elemento7, elemento8, elemento9;
      String elemento10, elemento11, elemento12;

      while (Serial2.available())
      {
        cadena = Serial2.readString();
        elemento1 = s.separa(cadena, ':', 0);
        elemento2 = s.separa(cadena, ':', 1);
        int variable = elemento2.toInt();

        if (variable == 2)
         {
          String enviar1 = String(EEPROM.get(eeAddress, compania));
          espsend(enviar1);
          String enviar2 = String(EEPROM.get(eeAddress1, ciu));
          espsend(enviar2);
          String enviar3 = String(EEPROM.get(eeAddress2, ruc));
          espsend(enviar3);
          String enviar4 = String(EEPROM.get(eeAddress3, ruc));
          espsend(enviar4);
          String enviar5 = String(EEPROM.get(eeAddress4, compania));
          espsend(enviar5);
        }
        if (variable == 3)
        {
          String enviar1 = String(EEPROM.get(eeAddress5, ruc));
          espsend(enviar1);
          String enviar2 = String(EEPROM.get(eeAddress6, tarifas));
          espsend(enviar2);
          String enviar3 = String(EEPROM.get(eeAddress7, vlc));
          espsend(enviar3);
          String enviar4 = String(EEPROM.get(eeAddress8, vlc));
          espsend(enviar4);
          String enviar5 = String(EEPROM.get(eeAddress9, placa));
          espsend(enviar5);
          String enviar6 = String(EEPROM.get(eeAddress10, placa));
          espsend(enviar6);
        }
        if (variable == 4)
        {
          String enviar1 = String(EEPROM.get(eeAddress21, master));
          espsend(enviar1);
          String enviar2 = String(EEPROM.get(eeAddress22, chofer1));
          espsend(enviar2);
          String enviar3 = String(EEPROM.get(eeAddress23, master));
          espsend(enviar3);
          String enviar4 = String(EEPROM.get(eeAddress24, chofer1));
          espsend(enviar4);
          String enviar5 = String(EEPROM.get(eeAddress25, master));
          espsend(enviar5);
        }
        if (variable == 5)
        {
          String enviar1 = String(EEPROM.get(eeAddress11, tarifas));
          espsend(enviar1);
          String enviar2 = String(EEPROM.get(eeAddress12, tarifas));
          espsend(enviar2);
          String enviar3 = String(EEPROM.get(eeAddress13, tarifas));
          espsend(enviar3);
          String enviar4 = String(EEPROM.get(eeAddress14, tarifas));
          espsend(enviar4);
          String enviar5 = String(EEPROM.get(eeAddress15, tarifas));
          espsend(enviar5);
          String enviar6 = String(EEPROM.get(eeAddress16, tarifas));
          espsend(enviar6);
          String enviar7 = String(EEPROM.get(eeAddress17, tarifas));
          espsend(enviar7);
          String enviar8 = String(EEPROM.get(eeAddress18, tarifas));
          espsend(enviar8);
          String enviar9 = String(EEPROM.get(eeAddress19, tarifas));
          espsend(enviar9);
          String enviar10 = String(EEPROM.get(eeAddress20, tarifas));
          espsend(enviar10);
        }

        if (variable == 6)
        {
          String enviar1 = String(EEPROM.get(eeAddress26, dr));
          espsend(enviar1);
          String enviar2 = String(EEPROM.get(eeAddress27, dr));
          espsend(enviar2);
          String enviar3 = String(EEPROM.get(eeAddress28, dr));
          espsend(enviar3);
          String enviar4 = String(EEPROM.get(eeAddress29, ruc));
          espsend(enviar4);
        }


        ////////////////////////////data receive////////////////////////////////
        if (variable == 7)
        {
          elemento3 = s.separa(cadena, ':', 2);
          elemento4 = s.separa(cadena, ':', 3);
          elemento5 = s.separa(cadena, ':', 4);
          elemento6 = s.separa(cadena, ':', 5);
          elemento7 = s.separa(cadena, ':', 6);

          elemento3.toCharArray(compania, 50);
          EEPROM.put(eeAddress, compania);
          Serial.println(compania);
          elemento4.toCharArray(ciu, 30);
          EEPROM.put(eeAddress1, ciu);
          elemento5.toCharArray(ruc, 15);
          EEPROM.put(eeAddress2, ruc);
          elemento6.toCharArray(ruc, 15);
          EEPROM.put(eeAddress3, ruc); 
          elemento7.toCharArray(compania, 50); 
          EEPROM.put(eeAddress4, compania);

        }
        if (variable == 8)
        {
          elemento3 = s.separa(cadena, ':', 2);
          elemento4 = s.separa(cadena, ':', 3);
          elemento5 = s.separa(cadena, ':', 4);
          elemento6 = s.separa(cadena, ':', 5);
          elemento7 = s.separa(cadena, ':', 6);
          elemento8 = s.separa(cadena, ':', 7);

          elemento3.toCharArray(ruc, 15);
          EEPROM.put(eeAddress5, ruc);
          elemento4.toCharArray(tarifas, 5);
          EEPROM.put(eeAddress6, tarifas);
          vlc = elemento5.toInt();
          EEPROM.put(eeAddress7, vlc);
          vlc = elemento6.toInt();
          EEPROM.put(eeAddress8, vlc);
          elemento7.toCharArray(placa, 10);
          EEPROM.put(eeAddress9, placa);
          elemento8.toCharArray(placa, 10);
          EEPROM.put(eeAddress10, placa);

        }
        if (variable == 9)
        {
          elemento3 = s.separa(cadena, ':', 2);
          elemento4 = s.separa(cadena, ':', 3);
          elemento5 = s.separa(cadena, ':', 4);
          elemento6 = s.separa(cadena, ':', 5);
          elemento7 = s.separa(cadena, ':', 6);

          elemento3.toCharArray(master, 5);
          EEPROM.put(eeAddress21, master);
          elemento4.toCharArray(chofer1, 20);
          EEPROM.put(eeAddress22, chofer1);
          elemento5.toCharArray(master, 5);
          EEPROM.put(eeAddress23, master);
          elemento6.toCharArray(chofer1, 20);
          EEPROM.put(eeAddress24, chofer1);
          elemento7.toCharArray(master, 5);
          EEPROM.put(eeAddress25, master);


        }
        if (variable == 10)
        {
          elemento3 = s.separa(cadena, ':', 2);
          elemento4 = s.separa(cadena, ':', 3);
          elemento5 = s.separa(cadena, ':', 4);
          elemento6 = s.separa(cadena, ':', 5);
          elemento7 = s.separa(cadena, ':', 6);
          elemento8 = s.separa(cadena, ':', 7);
          elemento9 = s.separa(cadena, ':', 8);
          elemento10 = s.separa(cadena, ':', 9);
          elemento11 = s.separa(cadena, ':', 10);
          elemento12 = s.separa(cadena, ':', 11);

          elemento3.toCharArray(tarifas, 5);
          EEPROM.put(eeAddress11, tarifas);
          elemento4.toCharArray(tarifas, 5);
          EEPROM.put(eeAddress12, tarifas);
          elemento5.toCharArray(tarifas, 5);
          EEPROM.put(eeAddress13, tarifas);
          elemento6.toCharArray(tarifas, 5);
          EEPROM.put(eeAddress14, tarifas);
          elemento7.toCharArray(tarifas, 5);
          EEPROM.put(eeAddress15, tarifas);
          elemento8.toCharArray(tarifas, 5);
          EEPROM.put(eeAddress16, tarifas);
          elemento9.toCharArray(tarifas, 5);
          EEPROM.put(eeAddress17, tarifas);
          elemento10.toCharArray(tarifas, 5);
          EEPROM.put(eeAddress18, tarifas);
          elemento11.toCharArray(tarifas, 5);
          EEPROM.put(eeAddress19, tarifas);
          elemento12.toCharArray(tarifas, 5);
          EEPROM.put(eeAddress20, tarifas);

        }
        if (variable == 11)
        {
          elemento3 = s.separa(cadena, ':', 2);
          elemento4 = s.separa(cadena, ':', 3);
          elemento5 = s.separa(cadena, ':', 4);
          elemento6 = s.separa(cadena, ':', 5);
          elemento7 = s.separa(cadena, ':', 6);
          elemento8 = s.separa(cadena, ':', 7);
          elemento9 = s.separa(cadena, ':', 8);
          elemento10 = s.separa(cadena, ':', 9);
          elemento11 = s.separa(cadena, ':', 10);
          elemento12 = s.separa(cadena, ':', 11);

          dia = elemento3.toInt();
          mes = elemento4.toInt();
          aa = elemento5.toInt();
          hora = elemento6.toInt();
          minuto = elemento7.toInt();
          segundo = elemento8.toInt();
          dr = elemento9.toInt();
          EEPROM.put(eeAddress26, dr);
          dr = elemento10.toInt();
          EEPROM.put(eeAddress27, dr);
          dr = elemento11.toInt();
          EEPROM.put(eeAddress28, dr);
          elemento12.toCharArray(ruc, 15);
          EEPROM.put(eeAddress29, ruc);
          rtc.adjust(DateTime(aa, mes, dia, hora, minuto, segundo));

        }
      }
    }
  }
  if (Flag == true)
  {
    epd.ClearFrameMemory(0xFF);   // bit set = white, bit reset = black
    epd.DisplayFrame();
    epd.ClearFrameMemory(0xFF);   // bit set = white, bit reset = black
    epd.DisplayFrame();
    Flag = false;
  }

  if (Flaginicio == true)
  {
    if (izquierda == 1)
    {
      izquierda = 0;
    }
      if (derecha == -1 || derecha == 0)
      {
        derecha = 1;
      }
  }
  if (Flagpantalla == true)
  {
    if (ISRabajo == -1 || ISRabajo == 7)
    {
      ISRabajo = 0;
    }
    if (ISRarriba >= 1)
    {
      ISRarriba = 0;
    }
    if (derecha == -1 || derecha == 0||derecha==2)
    {
      derecha = 1;
    }
    if (izquierda >= 0)
    {
      izquierda = 0;
    }
  }
  if (Flagpantalla1 == true)
  {
    if (ISRarriba == 1)
    {
      ISRabajo = 0;
    }
    if (derecha == -1 || derecha == 0||derecha==2)
    {
      derecha = 1;
    }
    if (izquierda >= 0)
    {
      izquierda = 1;
    }
  }

  if (Flagpantalla2 == true)
  {
    if (ISRarriba == 1)
    {
      ISRabajo = 1;
    }
    if (derecha == -1 || derecha == 0||derecha==2)
    {
      derecha = 1;
    }
    if (izquierda >= 0)
    {
      izquierda = 0;
    }
  }

  if (Flagpantalla3 == true)
  {
    if (ISRarriba == 1)
    {
      ISRabajo = 2;
    }
    if (derecha == -1 || derecha == 0||derecha==2)
    {
      derecha = 1;
    }
    if (izquierda >= 0)
    {
      izquierda = 0;
    }
  }
  if (Flagparameters == true)
  {
    if (derecha == -1 || derecha == 0||derecha==2)
    {
      derecha = 1;
    }
    if (izquierda >= 0)
    {
      izquierda = 0;
    }
  }
  if (Flagtar == true)
  {
    if (izquierda >= 1)
    {
      izquierda = 1;
    }
    if (ISRabajo == -1 || ISRabajo == 0)
    {
      ISRabajo = 1;
    }
    if (derecha == -1 || derecha == 0)
    {
      derecha = 1;
    }
  }
  if (Flagtar1 == true)
  {
    if (derecha == -1 || derecha == 0||derecha==2)
    {
      derecha = 1;
    }
    if (izquierda >= 1)
    {
      izquierda = 1;
    }
  }
  if (Flagviewtar1 == true)
  {
    if (derecha == -1 || derecha == 0||derecha==2)
    {
      derecha = 1;
    }
    if (izquierda >= 0)
    {
      izquierda = 1;
    }
  }
  
  if (Flagviewtar2 == true)
  {
    if (derecha == -1 || derecha == 0||derecha==2)
    {
      derecha = 1;
    }
    if (izquierda >= 0)
    {
      izquierda = 1;
    }
    if(ISRabajo>=3)
    {
      ISRabajo=2;
    }
  }

  if (Flagoptionselect == true)
  {
    if (izquierda >= 0)
    {
      izquierda = 1;
    }
    if (ISRabajo == -1 || ISRabajo == 0)
    {
      ISRabajo = 1;
    }
    if(derecha==3)
    {
      derecha=1;
    }
  }
    if (Flaginfo == true)
    {
       if (izquierda >= 0)
      {
        izquierda = 0;
      }
      if (ISRabajo == -1 || ISRabajo == 0)
      {
        ISRabajo = 1;
      }
      if (derecha == -1 || derecha == 0||derecha==2)
      {
        derecha = 1;
      }
    }
    if (Flagocupado == true)
    {
       if (izquierda >= 0)
      {
        izquierda = 0;
      }
    }

  if (ISRenter == 0 && derecha == 1 || ISRenter == 0 && derecha == 4)
  {
    inicio1();
  }
  if (ISRenter == 0 && derecha == 2)
  {
    inicio2();
  }
  if (ISRenter == 0 && derecha == 3)
  {
    inicio3();
  }

  if (ISRenter == 1 && derecha == 1 && ISRabajo == 0 || ISRenter == 1 && derecha == 1 && ISRabajo == 4)
  {
    pantalla();
  }
  if (ISRenter == 1 && derecha == 1 && ISRabajo == 1|| ISRenter == 1 && derecha == 2 && ISRabajo ==1|| ISRenter == 1 && derecha == 2 && ISRabajo == 2)
  {
    pantalla1();
  }
  if (ISRenter == 1 && derecha == 1 && ISRabajo == 2 || ISRenter == 1 && derecha == 1 && ISRabajo == 5)
  {
    pantalla2();
  }
  if (ISRenter == 1 && derecha == 1 && ISRabajo == 3)
  {
    pantalla3();
  }
  if (ISRenter == 2 && derecha == 1 && ISRabajo == 0)
  {
    parameters();

  }
  if (ISRenter == 2 && derecha == 1 && ISRabajo == 1 && izquierda==1|| ISRenter == 2 && derecha == 1 && ISRabajo == 3 &&izquierda==1)
  {
    tariffs();
  }
  if (ISRenter == 2 && derecha == 1 && ISRabajo == 2 && izquierda==1|| ISRenter == 2 && derecha == 3 && ISRabajo == 2&&izquierda==1)
  {
    tariffs1();
  }
  if (ISRenter == 3 && derecha == 1 && ISRabajo == 1&& izquierda==1)
  {
    viewtariff1();
  }
  if (ISRenter == 3 && derecha == 1 && ISRabajo == 2&& izquierda==1)

  {
    viewtariff2();
  }
     if (ISRenter == 2 && derecha == 1 && ISRabajo == 2 && izquierda==0)
    {
      informacion();
    }

    if (ISRenter == 1 && derecha == 2 && ISRabajo == 0&&izquierda==0)
    {
      ocupado();
    }

    if (ISRenter == 1 && derecha == 3 && ISRabajo == 0)
    {
      impresion();
    }  
  if (enter != ISRenter)
  {
    enter = ISRenter;
  }
  if (atras != ISRatras)
  {
    atras = ISRatras;
  }
  if (abajo != ISRabajo)
  {
    abajo = ISRabajo;
  }
  if (arriba != ISRarriba)
  {
    arriba = ISRarriba;
  }
 }
void interruptCount()
{  
  if (millis() > timeCounter + timeThreshold)
  {
    ISRenter++;
    Flag=true;
    timeCounter = millis();
  }
}
void interruptCount1()
{
   if (millis() > timeCounter + timeThreshold)
  {
    ISRatras++;
    ISRenter--;
    Flag=true;
    timeCounter = millis();
  }
}
void interruptCount2()
{
  if (millis() > timeCounter + timeThreshold)
  {
    ISRabajo++;
    timeCounter = millis();
  }
}
void interruptCount3()
{
  if (millis() > timeCounter + timeThreshold)
  {
    ISRarriba++;
    ISRabajo--;
    timeCounter = millis();
  }
}
void right()
{
  buttonState3 = digitalRead(DERECHA);
  if (buttonState3 != lastButtonState3)
  {
    if (buttonState3 == LOW)
    {
      derecha++;
      Serial.print("derecha");
      Serial.println(derecha);
    }
  }
  lastButtonState3 = buttonState3;
}
void left()
{
  buttonState4 = digitalRead(IZQUIERDA);
  if (buttonState4 != lastButtonState4)
  {
    if (buttonState4 == LOW)
    {
      izquierda++;
      derecha--;
      if (izquierda == -1)
      {
        izquierda = 0;
      }
      Serial.print("izquierda");
      Serial.println(izquierda);
    }
  }
  lastButtonState4 = buttonState4;
}
void reloj()
{
  char retc[] = {'0', '\0'};
  char retc1[] = {'0', '\0'};
  char retc2[] = {'0', '\0'};
  char retc3[] = {'0', '\0'};

  retc[0] = Decena1 + '0';
  retc1[0] = Unidad1 + '0';
  retc2[0] = Decena2 + '0';
  retc3[0] = Unidad2 + '0';
  paint.SetRotate(ROTATE_180);
  paint.SetWidth(80);
  paint.SetHeight(60);

  paint.Clear(UNCOLORED);
  paint.DrawStringAt(0, 4, retc, &Font96, COLORED);
  epd.SetFrameMemory(paint.GetImage(), 40, 10, paint.GetWidth(), paint.GetHeight());

  paint.Clear(UNCOLORED);
  paint.DrawStringAt(0, 4, retc1, &Font96, COLORED);
  epd.SetFrameMemory(paint.GetImage(), 40, 70, paint.GetWidth(), paint.GetHeight());

  paint.Clear(UNCOLORED);
  paint.DrawStringAt(0, 4, ":", &Font96, COLORED);
  epd.SetFrameMemory(paint.GetImage(), 40, 115, paint.GetWidth(), paint.GetHeight());

  paint.Clear(UNCOLORED);
  paint.DrawStringAt(0, 4, retc2, &Font96, COLORED);
  epd.SetFrameMemory(paint.GetImage(), 40, 176, paint.GetWidth(), paint.GetHeight());

  paint.Clear(UNCOLORED);
  paint.DrawStringAt(0, 4, retc3, &Font96, COLORED);
  epd.SetFrameMemory(paint.GetImage(), 40, 236, paint.GetWidth(), paint.GetHeight());
}
void horario()
{
  DateTime now = rtc.now();
  int h = now.hour();
  int m = now.minute();
  Decena1 = h / 10;
  Unidad1 = (h - Decena1 * 10);
  Decena2 = m / 10;
  Unidad2 = (m - Decena2 * 10);
}

void letranegra()
{
  paint.SetRotate(ROTATE_90);
  paint.SetWidth(20);
  paint.SetHeight(296);
  paint.Clear(COLORED);
}
void letranormal()
{
  paint.SetRotate(ROTATE_90);
  paint.SetWidth(20);
  paint.SetHeight(296);
  paint.Clear(UNCOLORED);
}
void inicio()
{
  horario();
  reloj();
  Flaginicio = false;
  Flagpantalla = false;
  Flagpantalla1 = false;
  Flagpantalla2 = false;
  Flagpantalla3 = false;
  Flaginfo = false;
  Flagtar1 = false;
  Flagtar = false;
  Flagocupado = false;
  ISRabajo = 0;
  ISRarriba = 0;
  izquierda = 0;
  derecha=0;
}
void inicio1()
{
  horario();
  reloj();
  paint.SetRotate(ROTATE_90);
  paint.SetWidth(20);
  paint.SetHeight(80);
  paint.Clear(COLORED);
  paint.DrawStringAt(5, 4, "Libre", &Font20, UNCOLORED);
  epd.SetFrameMemory(paint.GetImage(), 0, 0, paint.GetWidth(), paint.GetHeight());
  paint.SetRotate(ROTATE_90);
  paint.SetWidth(20);
  paint.SetHeight(120);
  paint.Clear(UNCOLORED);
  paint.DrawStringAt(7, 4, "Ocupado", &Font20, COLORED);
  epd.SetFrameMemory(paint.GetImage(), 0, 80, paint.GetWidth(), paint.GetHeight());
  paint.Clear(UNCOLORED);
  paint.DrawStringAt(12, 4, "Imprim", &Font20, COLORED);
  epd.SetFrameMemory(paint.GetImage(), 0, 190, paint.GetWidth(), paint.GetHeight());
  epd.DisplayFrame();
  Flaginicio = true;
  Flagpantalla = false;
  Flagpantalla1 = false;
  Flagpantalla2 = false;
  Flagpantalla3 = false;
  Flaginfo = false;
  Flagtar1 = false;
  Flagtar = false;
  Flagocupado = false;
  ISRabajo = 0;
  ISRarriba = 0;
  izquierda = 0;
  if (derecha == 4)
  {
    derecha = 1;
  }
  }
void inicio2()
{
  horario();
  reloj();
  paint.SetRotate(ROTATE_90);
  paint.SetWidth(20);
  paint.SetHeight(80);
  paint.Clear(UNCOLORED);
  paint.DrawStringAt(5, 4, "Libre", &Font20, COLORED);
  epd.SetFrameMemory(paint.GetImage(), 0, 0, paint.GetWidth(), paint.GetHeight());
  paint.SetRotate(ROTATE_90);
  paint.SetWidth(20);
  paint.SetHeight(120);
  paint.Clear(COLORED);
  paint.DrawStringAt(7, 4, "Ocupado", &Font20, UNCOLORED);
  epd.SetFrameMemory(paint.GetImage(), 0, 80, paint.GetWidth(), paint.GetHeight());
  paint.Clear(UNCOLORED);
  paint.DrawStringAt(12, 4, "Imprim", &Font20, COLORED);
  epd.SetFrameMemory(paint.GetImage(), 0, 190, paint.GetWidth(), paint.GetHeight());
  epd.DisplayFrame();
  ISRabajo = 0;
  ISRarriba = 0;
  Flaginicio = false;
  Flagpantalla = false;
  Flagpantalla1 = false;
  Flagpantalla2 = false;
  Flagpantalla3 = false;  
  Flagtar1 = false;
  Flagtar = false;
  Flaginfo = false;
  Flagocupado = true;
}
void inicio3()
{
  horario();
  reloj();
  paint.SetRotate(ROTATE_90);
  paint.SetWidth(20);
  paint.SetHeight(80);
  paint.Clear(UNCOLORED);
  paint.DrawStringAt(5, 4, "Libre", &Font20, COLORED);
  epd.SetFrameMemory(paint.GetImage(), 0, 0, paint.GetWidth(), paint.GetHeight());
  paint.SetRotate(ROTATE_90);
  paint.SetWidth(20);
  paint.SetHeight(120);
  paint.Clear(UNCOLORED);
  paint.DrawStringAt(7, 4, "Ocupado", &Font20, COLORED);
  epd.SetFrameMemory(paint.GetImage(), 0, 80, paint.GetWidth(), paint.GetHeight());
  paint.Clear(COLORED);
  paint.DrawStringAt(12, 4, "Imprim", &Font20, UNCOLORED);
  epd.SetFrameMemory(paint.GetImage(), 0, 190, paint.GetWidth(), paint.GetHeight());
  epd.DisplayFrame();
  ISRabajo = 0;
  ISRarriba = 0;
  Flaginicio = false;
  Flagpantalla = false;
  Flagpantalla1 = false;
  Flagpantalla2 = false;
  Flagpantalla3 = false;  
  Flagtar1 = false;
  Flagtar = false;
  Flaginfo = false;
  Flagocupado = true;
  if (derecha == 4)
  {
    derecha = 1;
  }
}
void pantalla()
{
  letranegra();
  strcpy_P(cc, (char*)pgm_read_word(&(string_table[0])));
  paint.DrawStringAt(0, 4, cc, &Font20, UNCOLORED);
  epd.SetFrameMemory(paint.GetImage(), 100, 10, paint.GetWidth(), paint.GetHeight());

  letranormal();
  strcpy_P(cc, (char*)pgm_read_word(&(string_table[1])));
  paint.DrawStringAt(0, 4, cc, &Font20, COLORED);
  epd.SetFrameMemory(paint.GetImage(), 70, 10, paint.GetWidth(), paint.GetHeight());

  letranormal();
  strcpy_P(cc, (char*)pgm_read_word(&(string_table[2])));
  paint.DrawStringAt(0, 4, cc, &Font20, COLORED);
  epd.SetFrameMemory(paint.GetImage(), 35, 10, paint.GetWidth(), paint.GetHeight());

  letranormal();
  strcpy_P(cc, (char*)pgm_read_word(&(string_table[3])));
  paint.DrawStringAt(0, 4, cc, &Font20, COLORED);
  epd.SetFrameMemory(paint.GetImage(), 5, 10, paint.GetWidth(), paint.GetHeight());
  epd.DisplayFrame();
  Flaginicio = false;
  Flagpantalla = true;
  Flagpantalla1 = false;
  Flagpantalla2 = false;
  Flagpantalla3 = false;
  Flagparameters = false;  
  Flagtar1 = false;
  Flagtar = false;
  Flaginfo = false;
  ISRarriba = 0;
  ISRatras = 0;
  izquierda = 0;
  if (ISRabajo == 4)
  {
    ISRabajo = 0;
  }
}
void pantalla1()
{
  letranormal();
  strcpy_P(cc, (char*)pgm_read_word(&(string_table[0])));
  paint.DrawStringAt(0, 4, cc, &Font20, COLORED);
  epd.SetFrameMemory(paint.GetImage(), 100, 10, paint.GetWidth(), paint.GetHeight());

  letranegra();
  strcpy_P(cc, (char*)pgm_read_word(&(string_table[1])));
  paint.DrawStringAt(0, 4, cc, &Font20, UNCOLORED);
  epd.SetFrameMemory(paint.GetImage(), 70, 10, paint.GetWidth(), paint.GetHeight());

  letranormal();
  strcpy_P(cc, (char*)pgm_read_word(&(string_table[2])));
  paint.DrawStringAt(0, 4, cc, &Font20, COLORED);
  epd.SetFrameMemory(paint.GetImage(), 35, 10, paint.GetWidth(), paint.GetHeight());

  letranormal();
  strcpy_P(cc, (char*)pgm_read_word(&(string_table[3])));
  paint.DrawStringAt(0, 4, cc, &Font20, COLORED);
  epd.SetFrameMemory(paint.GetImage(), 5, 10, paint.GetWidth(), paint.GetHeight());
  epd.DisplayFrame();
  Flaginicio = false;
  Flagpantalla = false;
  Flagpantalla1 = true;
  Flagpantalla2 = false;
  Flagpantalla3 = false;
  Flagtar1 = false;
  Flagtar = false;
  Flaginfo = false;
  ISRarriba = 0;
  ISRatras = 0;
  izquierda = 1;
}
void pantalla2()
{
  letranormal();
  strcpy_P(cc, (char*)pgm_read_word(&(string_table[0])));
  paint.DrawStringAt(0, 4, cc, &Font20, COLORED);
  epd.SetFrameMemory(paint.GetImage(), 100, 10, paint.GetWidth(), paint.GetHeight());

  letranormal();
  strcpy_P(cc, (char*)pgm_read_word(&(string_table[1])));
  paint.DrawStringAt(0, 4, cc, &Font20, COLORED);
  epd.SetFrameMemory(paint.GetImage(), 70, 10, paint.GetWidth(), paint.GetHeight());

  letranegra();
  strcpy_P(cc, (char*)pgm_read_word(&(string_table[2])));
  paint.DrawStringAt(0, 4, cc, &Font20, UNCOLORED);
  epd.SetFrameMemory(paint.GetImage(), 35, 10, paint.GetWidth(), paint.GetHeight());

  letranormal();
  strcpy_P(cc, (char*)pgm_read_word(&(string_table[3])));
  paint.DrawStringAt(0, 4, cc, &Font20, COLORED);
  epd.SetFrameMemory(paint.GetImage(), 5, 10, paint.GetWidth(), paint.GetHeight());
  epd.DisplayFrame();
  Flaginicio = false;
  Flagpantalla = false;
  Flagpantalla1 = false;
  Flagpantalla2 = true;
  Flagpantalla3 == false;
  Flaginfo = false;
  Flaginfo = false;
  ISRarriba = 0;
  ISRatras = 0;
  izquierda = 0;
}
void pantalla3()
{
  letranormal();
  strcpy_P(cc, (char*)pgm_read_word(&(string_table[0])));
  paint.DrawStringAt(0, 4, cc, &Font20, COLORED);
  epd.SetFrameMemory(paint.GetImage(), 100, 10, paint.GetWidth(), paint.GetHeight());

  letranormal();
  strcpy_P(cc, (char*)pgm_read_word(&(string_table[1])));
  paint.DrawStringAt(0, 4, cc, &Font20, COLORED);
  epd.SetFrameMemory(paint.GetImage(), 70, 10, paint.GetWidth(), paint.GetHeight());

  letranormal();
  strcpy_P(cc, (char*)pgm_read_word(&(string_table[2])));
  paint.DrawStringAt(0, 4, cc, &Font20, COLORED);
  epd.SetFrameMemory(paint.GetImage(), 35, 10, paint.GetWidth(), paint.GetHeight());

  letranegra();
  strcpy_P(cc, (char*)pgm_read_word(&(string_table[3])));
  paint.DrawStringAt(0, 4, cc, &Font20, UNCOLORED);
  epd.SetFrameMemory(paint.GetImage(), 5, 10, paint.GetWidth(), paint.GetHeight());
  epd.DisplayFrame();
  Flaginicio = false;
  Flagpantalla = false;
  Flagpantalla1 = false;
  Flagpantalla2 = false;
  Flagpantalla3 = true;
  Flaginfo = false;
  ISRatras = 0;
  izquierda = 0;
  ISRarriba = 0;
}

void parameters()
{
  letranormal();
  strcpy_P(cc, (char*)pgm_read_word(&(string_table[10])));
  paint.DrawStringAt(0, 0, cc, &Font20, COLORED);
  ruc[15] = (EEPROM.get(eeAddress5, ruc));
  paint.DrawStringAt(145, 0, ruc, &Font20, COLORED);
  epd.SetFrameMemory(paint.GetImage(), 100, 10, paint.GetWidth(), paint.GetHeight());

  letranormal();
  strcpy_P(cc, (char*)pgm_read_word(&(string_table[11])));
  paint.DrawStringAt(0, 0, cc, &Font20, COLORED);
  tarifas[5] = (EEPROM.get(eeAddress6, tarifas));
  paint.DrawStringAt(175, 0, tarifas, &Font20, COLORED);
  epd.SetFrameMemory(paint.GetImage(), 70, 10, paint.GetWidth(), paint.GetHeight());

  letranormal();
  strcpy_P(cc, (char*)pgm_read_word(&(string_table[12])));
  paint.DrawStringAt(0, 0, cc, &Font20, COLORED);
  placa[10] = (EEPROM.get(eeAddress9, placa));
  paint.DrawStringAt(90, 0, placa, &Font20 , COLORED);
  epd.SetFrameMemory(paint.GetImage(), 35, 10, paint.GetWidth(), paint.GetHeight());

  letranormal();
  strcpy_P(cc, (char*)pgm_read_word(&(string_table[13])));
  paint.DrawStringAt(0, 0, cc, &Font20, COLORED);
  placa[10] = (EEPROM.get(eeAddress10, placa));
  paint.DrawStringAt(190, 0, placa, &Font20 , COLORED);
  epd.SetFrameMemory(paint.GetImage(), 0, 10, paint.GetWidth(), paint.GetHeight());
  epd.DisplayFrame();
  Flaginicio = false;
  Flagparameters = true;
  Flagpantalla = false;
  Flagpantalla1 = false;
  Flagpantalla2 = false;
  Flagpantalla3 = false;
  Flaginfo = false;
  ISRabajo = 0;
  ISRarriba = 0;
  izquierda = 0;
  ISRatras = 0;
}
void tariffs()
{
  letranegra();
  strcpy_P(cc, (char*)pgm_read_word(&(string_table[4])));
  paint.DrawStringAt(0, 4, cc, &Font20, UNCOLORED);
  epd.SetFrameMemory(paint.GetImage(), 100, 10, paint.GetWidth(), paint.GetHeight());

  letranormal();
  strcpy_P(cc, (char*)pgm_read_word(&(string_table[5])));
  paint.DrawStringAt(0, 4, cc, &Font20, COLORED);
  epd.SetFrameMemory(paint.GetImage(), 50, 10, paint.GetWidth(), paint.GetHeight());
  epd.DisplayFrame();

  Flaginicio = false;
  Flagtar = true;
  Flagtar1 = false;
  Flagviewtar1 = false;
  Flagpantalla1 = false;
  Flagpantalla2 = false;
  Flagpantalla3 = false;
  Flaginfo = false;
  izquierda = 1;
  ISRarriba = 0;
  ISRatras = 0;
  if (ISRabajo == 3)
  {
    ISRabajo = 1;
  }
}
void tariffs1()
{
  letranormal();
  strcpy_P(cc, (char*)pgm_read_word(&(string_table[4])));
  paint.DrawStringAt(0, 4, cc, &Font20, COLORED);
  epd.SetFrameMemory(paint.GetImage(), 100, 10, paint.GetWidth(), paint.GetHeight());

  letranegra();
  strcpy_P(cc, (char*)pgm_read_word(&(string_table[5])));
  paint.DrawStringAt(0, 4, cc, &Font20, UNCOLORED);
  epd.SetFrameMemory(paint.GetImage(), 50, 10, paint.GetWidth(), paint.GetHeight());
  
  epd.DisplayFrame();

  Flaginicio = false;
  Flagpantalla = false;
  Flagpantalla1 = false;
  Flagpantalla2 = false;
  Flagpantalla3 = false;
  Flagtar = false;
  Flagtar1 = true;
  Flagviewtar2 = false;
  Flaginfo = false;
  izquierda = 1;
  ISRarriba = 0;
  ISRatras = 0;
  derecha=1;
}
void informacion()
{
    letranormal();
    strcpy_P(cc, (char*)pgm_read_word(&(string_table[14])));
    paint.DrawStringAt(0, 0, cc, &Font20, COLORED);
    compania[50] = (EEPROM.get(eeAddress, compania));
    paint.DrawStringAt(125, 0, compania, &Font20, COLORED);
    epd.SetFrameMemory(paint.GetImage(), 100, 10, paint.GetWidth(), paint.GetHeight());
  
    letranormal();
    strcpy_P(cc, (char*)pgm_read_word(&(string_table[15])));
    paint.DrawStringAt(0, 0, cc, &Font20, COLORED);
    ciu[30] = (EEPROM.get(eeAddress1, ciu));
    paint.DrawStringAt(100, 0, ciu, &Font20 , COLORED);
    epd.SetFrameMemory(paint.GetImage(), 75, 10, paint.GetWidth(), paint.GetHeight());
  
    letranormal();
    strcpy_P(cc, (char*)pgm_read_word(&(string_table[16])));
    paint.DrawStringAt(0, 0, cc, &Font20, COLORED);
    ruc[15] = (EEPROM.get(eeAddress2, ruc));
    paint.DrawStringAt(60, 0, ruc, &Font20 , COLORED);
    epd.SetFrameMemory(paint.GetImage(), 50, 10, paint.GetWidth(), paint.GetHeight());
  
    letranormal();
    strcpy_P(cc, (char*)pgm_read_word(&(string_table[17])));
    paint.DrawStringAt(0, 0, cc, &Font20, COLORED);
    ruc[15] = (EEPROM.get(eeAddress3, ruc));
    paint.DrawStringAt(115, 0, ruc, &Font20 , COLORED);
    epd.SetFrameMemory(paint.GetImage(), 25, 10, paint.GetWidth(), paint.GetHeight());
  
    letranormal();
    strcpy_P(cc, (char*)pgm_read_word(&(string_table[18])));
    paint.DrawStringAt(0, 0, cc, &Font20 , COLORED);
    compania[50] = (EEPROM.get(eeAddress4, compania));
    paint.DrawStringAt(115, 0, compania, &Font20 , COLORED);
    epd.SetFrameMemory(paint.GetImage(), 0, 10, paint.GetWidth(), paint.GetHeight());
    epd.DisplayFrame();       
    Flagpantalla = false;
    Flagpantalla1 = false;
    Flagpantalla2 = false;
    Flagpantalla3 = false;
    Flagocupado = false;
    Flaginfo = true;
    ISRarriba = 0;
    izquierda = 0;
    ISRatras = 0;
    ISRabajo = 2;
}
void ocupado()
{
  paint.SetRotate(ROTATE_180);
  paint.SetWidth(80);
  paint.SetHeight(60);
  
  paint.Clear(UNCOLORED);
  paint.DrawStringAt(0, 4, "0", &Font96, COLORED);
  epd.SetFrameMemory(paint.GetImage(), 30, 10, paint.GetWidth(), paint.GetHeight());

      paint.SetWidth(80);
      paint.SetHeight(50);
      paint.Clear(UNCOLORED);
      paint.DrawStringAt(0, 4, ",", &Font96, COLORED);
      epd.SetFrameMemory(paint.GetImage(), 30, 60, paint.GetWidth(), paint.GetHeight());

      paint.SetWidth(80);
      paint.SetHeight(60);
      paint.Clear(UNCOLORED);
      paint.DrawStringAt(0, 4, "4", &Font96, COLORED);
      epd.SetFrameMemory(paint.GetImage(), 30, 90, paint.GetWidth(), paint.GetHeight());
  
      paint.Clear(UNCOLORED);
      paint.DrawStringAt(0, 4, "0", &Font96, COLORED);
      epd.SetFrameMemory(paint.GetImage(), 30, 140, paint.GetWidth(), paint.GetHeight());

      paint.Clear(COLORED);
      char b[2];
      String str;
      str = String(a);
      str.toCharArray(b, 2);
      paint.DrawStringAt(0, 0, b, &Font96, UNCOLORED);
      epd.SetFrameMemory(paint.GetImage(), 30, 220, paint.GetWidth(), paint.GetHeight());
    
      paint.SetRotate(ROTATE_90);
      paint.SetWidth(20);
      paint.SetHeight(90);
  
      paint.Clear(UNCOLORED);
      paint.DrawStringAt(0, 4, "Tarifa", &Font20, COLORED);
      epd.SetFrameMemory(paint.GetImage(), 110, 210, paint.GetWidth(), paint.GetHeight());

      paint.Clear(UNCOLORED);
      paint.DrawStringAt(0, 4, "Valor", &Font20, COLORED);
      epd.SetFrameMemory(paint.GetImage(), 110, 70, paint.GetWidth(), paint.GetHeight());

      paint.Clear(UNCOLORED);
      paint.DrawStringAt(12, 4, "Pausa", &Font20, COLORED);
      epd.SetFrameMemory(paint.GetImage(), 0, 30, paint.GetWidth(), paint.GetHeight());
      
      paint.Clear(UNCOLORED);
      paint.DrawStringAt(4, 4, "Pagar", &Font20, COLORED);
      epd.SetFrameMemory(paint.GetImage(), 0, 150, paint.GetWidth(), paint.GetHeight());
      epd.DisplayFrame();
      
  Flaginicio = false;
  Flagpantalla = false;
  Flagpantalla1 = false;
  Flagpantalla2 = false;
  Flagpantalla3 = false;
  Flagocupado = true;
  Flaginfo = false;
  Flagtar1 = false;
  Flagtar = false;
  ISRabajo = 0;
  ISRarriba = 0;
  izquierda = 0;
}
void impresion()
{
  letranegra();
  strcpy_P(cc, (char*)pgm_read_word(&(string_table[19])));
  paint.DrawStringAt(0, 4, cc, &Font20, UNCOLORED);
  epd.SetFrameMemory(paint.GetImage(), 100, 10, paint.GetWidth(), paint.GetHeight());
  letranormal();
  strcpy_P(cc, (char*)pgm_read_word(&(string_table[20])));
  paint.DrawStringAt(0, 4, cc, &Font20, COLORED);
  epd.SetFrameMemory(paint.GetImage(), 70, 10, paint.GetWidth(), paint.GetHeight());

  letranormal();
  strcpy_P(cc, (char*)pgm_read_word(&(string_table[21])));
  paint.DrawStringAt(0, 4, cc, &Font20, COLORED);
  epd.SetFrameMemory(paint.GetImage(), 35, 10, paint.GetWidth(), paint.GetHeight());

  letranormal();
  strcpy_P(cc, (char*)pgm_read_word(&(string_table[22])));
  paint.DrawStringAt(0, 4, cc, &Font20, COLORED);
  epd.SetFrameMemory(paint.GetImage(), 5, 10, paint.GetWidth(), paint.GetHeight());//Texto 100 desplaza arriba,10 desplaza derecha
  epd.DisplayFrame();
  Flaginicio = false;
  Flagpantalla = false;
  Flagpantalla1 = false;
  Flagpantalla2 = false;
  Flagpantalla3 = false;
  Flaginfo = false;
  Flagtar1 = false;
  Flagtar = false;
  Flagocupado = true;
  ISRabajo = 0;
  ISRarriba = 0;
  izquierda = 0;
}
void espsend(String d)
{
  String cipSend = "AT+CIPSEND=";
  cipSend += connectionId;
  cipSend += ",";
  cipSend += d.length();
  cipSend += "\r\n";
  sendData(cipSend, 100, DEBUG);
  sendData(d, 100, DEBUG);
}
//////////////gets the data from esp and displays in serial monitor///////////////////////
String sendData(String command, const int timeout, boolean debug)
{
  String response = "";
  Serial2.print(command);
  long int time = millis();
  while ( (time + timeout) > millis())
  {
    while (Serial2.available() > 0)
    {
      char c = Serial2.read(); // read the next character.
      response += c;
    }
  }
  if (debug)
  {
    Serial.print(response); //displays the esp response messages in arduino Serial monitor
  }
  return response;
}
