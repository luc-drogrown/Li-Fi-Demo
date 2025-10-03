#define LED_PIN 52
#define PERIOD 100

void setup() 
{
  // put your setup code here, to run once:
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);
  Serial.begin(9600);
}

void loop() 
{
  // put your main code here, to run repeatedly;
  Serial.println("Enter data: ");
  while (Serial.available() == 0)
  {
    String data_string = Serial.readString();
    data_string.trim();
    unsigned int data_string_length = data_string.length();
    if (data_string == "calibrate")
      calibrate();
    else
    {
      for (int i = 0; i < data_string_length; i++)
      {
        digitalWrite(LED_PIN, LOW);
        if (i == 0)
          delay(PERIOD-15);
        else
          delay(PERIOD-15);
        send_byte(data_string[i]);
        digitalWrite(LED_PIN, HIGH);
        delay(PERIOD-10);
      }
    }
  }
}

void send_byte(char my_byte)
{
  //transmission of bits
  for(int i = 0; i < 8; i++)
  {
    digitalWrite(LED_PIN, (my_byte&(0x01 << i))!=0);
    delay(PERIOD);
  }
}

void calibrate()
{
    digitalWrite(LED_PIN, LOW);
    delay(PERIOD);
    digitalWrite(LED_PIN, HIGH);
    delay(PERIOD);
}