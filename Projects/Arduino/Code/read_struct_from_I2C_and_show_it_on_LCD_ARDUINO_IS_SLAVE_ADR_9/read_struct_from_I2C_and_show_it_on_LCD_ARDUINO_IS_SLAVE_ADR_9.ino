#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#define I2C_ADDRESS 0x09

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

struct Numbers
{
  char c;
  long l;
  double d;
};

Numbers numbers = {0};
int isNewData = 0;
int bytes_to_read;
int buf_size;
char str[100];
char double_str[100];

void setup()
{
  lcd.init();                      // initialize the lcd 
  lcd.backlight();
  lcd.clear();
  
  Wire.begin(I2C_ADDRESS);                // Start I2C Bus as a Slave (Device Number 9)
  Wire.onReceive(receiveEvent); // register event
  Wire.onRequest(requestEvent); // register event
}

void loop()
{
  if (isNewData)
  {
    lcd.clear();
    lcd.setCursor(0,0);
    sprintf(str, "%02x : %d", numbers.c, numbers.c);
    lcd.printstr(str);
    lcd.setCursor(0,1);
    sprintf(str, "%08lx : %ld", numbers.l, numbers.l);
    lcd.printstr(str);
    lcd.setCursor(0,2);
    sprintf(str, "%08lx : %s", (long)*((long*)&numbers.d), dtostrf(numbers.d, 0, 3, double_str));
    lcd.printstr(str);
    lcd.setCursor(0,3);
    sprintf(str, "%d : %d", buf_size, bytes_to_read);
    lcd.printstr(str);
    isNewData = 0;
  }
  delay(100);
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany)
{
  byte * buf = (byte*)&numbers;
  buf_size = sizeof(numbers);
  for (int i = 0; i < buf_size; ++i)
    buf[i] = Wire.read();
  bytes_to_read = howMany;
  isNewData = 1;
}

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent()
{
  //byte * buf = (byte*)&numbers;
  //int buf_size = sizeof(numbers);
  //for (int i = 0; i < buf_size; ++i)
  //  Wire.write(buf[i]);
  Wire.write((byte*)&numbers, sizeof(numbers));
}

