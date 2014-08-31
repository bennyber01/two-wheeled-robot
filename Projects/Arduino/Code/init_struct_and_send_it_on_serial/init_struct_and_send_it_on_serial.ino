struct Numbers
{
  char c;
  long l;
  float f;
  double d;
};

char str[100];
char double_str[100];

void setup()
{
  Serial.begin(9600);
  
  Numbers n = {0};
  n.c = 100;
  n.l = 876543210;
  n.d = 123.321;
  n.f = n.d;
 

//  sprintf(str, "numbers.c = %02x : n.c = %02x", numbers.c, n.c);
//  Serial.println(str);
//  sprintf(str, "numbers.l = %08lx : n.l = %08lx", numbers.l, n.l);
//  Serial.println(str);  
//  sprintf(str, "numbers.d = %08lx : n.d = %08lx", (long)*((long*)&numbers.d), (long)*((long*)&n.d));
//  Serial.println(str);

  sprintf(str, "n.c = %02x : n.c = %d", n.c, n.c);
  Serial.println(str);
  sprintf(str, "n.l = %08lx : n.l = %ld", n.l, n.l);
  Serial.println(str);  
  
  long intpart;
  long fractpart;

//dtostrf(n.d, 0, 0, str);
  sprintf(str, "n.d = %08lx : n.d = %s", (long)*((long*)&n.d), dtostrf(n.d, 0, 3, double_str));
  Serial.println(str);
  sprintf(str, "n.f = %08lx : n.f = %s", (long)*((long*)&n.f), dtostrf(n.f, 0, 3, double_str));
  Serial.println(str);
  
  sprintf(str, "sizeof(Numbers) = %d", sizeof(Numbers));
  Serial.println(str);
}

void loop()
{
  delay(100);
}


