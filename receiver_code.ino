#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define LDR_PIN A2

#define OLED_MOSI 9
#define OLED_CLK 10
#define OLED_DC 11
#define OLED_CS 12
#define OLED_RESET 13

#define BUTTON_PIN 8

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

bool previous_state;
bool current_state;

unsigned long PERIOD;
unsigned int THRESHOLD;

void setup() 
{
    Serial.begin(9600);
    display.begin(SSD1306_SWITCHCAPVCC);
    display.display();
    display.clearDisplay();
    display.setTextSize(2.5);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);

    pinMode(BUTTON_PIN, INPUT);
    
}

void loop() 
{
  if (digitalRead(BUTTON_PIN) == HIGH)
  {
    calibrate();
    display.setCursor(0, 0);
  }
  else
  {
    current_state = get_ldr();
    if(!current_state)
    {
      delay(PERIOD);   
      print_byte(get_byte());
    }
  }
}

bool get_ldr()
{
  int voltage = analogRead(LDR_PIN);
  return voltage > THRESHOLD ? true : false;
}

char get_byte()
{
  char ret = 0;
  for(int i = 0; i < 8; i++)
  {   ret = ret | get_ldr() << i; 
   Serial.print((ret&(0x01 << i))!=0);
   delay(PERIOD);
  }
  return ret;
}
void print_byte(char my_byte)
{
  char buff[2];
  sprintf(buff, "%c", my_byte);
  if (my_byte != '~'){
    display.print(buff);
  }
  else
  {
    display.clearDisplay();
    display.setCursor(0, 0);
  }
  Serial.print(buff);
  display.display();
}

void calibrate()
{
  unsigned long start_time, end_time;
  THRESHOLD = analogRead(LDR_PIN) - 20;
  display.clearDisplay();
  display.setCursor(0,0);
  display.println("calibrate");
  display.display();
  while (true)
  {
      previous_state = get_ldr();
      if (previous_state == false)
      {
        start_time = millis();
        while (true)
        {
          current_state = get_ldr();
          if (current_state == true)
          {
            end_time = millis();
            break;
          }
        }
        break;
      }
  }
  PERIOD = end_time - start_time - 5;
  display.setTextSize(1.5);
  display.print("PERIOD: ");
  display.println(PERIOD);
  display.println("THRESHOLD: ");
  display.print(THRESHOLD);
  display.display();
  delay(2000);
  display.clearDisplay();
  display.setTextSize(2.5);
}