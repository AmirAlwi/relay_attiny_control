#include <Arduino.h>
#include <DigiUSB.h>
enum of_relay
{
  relay1,
  relay2,
  relay3,
  res1,
  relay4,
  relay5
};

void setup()
{
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  pinMode(relay5, OUTPUT);

  DigiUSB.begin();
}

void relay_op(int relay_sel, int relay_conf)
{
  switch (relay_sel)
  {
  case 0x61:
    if (relay_conf == 0x31)
      digitalWrite(relay1, HIGH);
    else
      digitalWrite(relay1, LOW);
    break;
  case 0x62:
    if (relay_conf == 0x31)
      digitalWrite(relay2, HIGH);
    else
      digitalWrite(relay2, LOW);
    break;
  case 0x63:
    if (relay_conf == 0x31)
      digitalWrite(relay3, HIGH);
    else
      digitalWrite(relay3, LOW);
    break;
  case 0x64:
    if (relay_conf == 0x31)
      digitalWrite(relay5, HIGH);
    else
      digitalWrite(relay5, LOW);
    break;

  default:
    break;
  }
}

void get_input()
{
  int lastRead = -1;
  int sec_read, temp = -1;
  // when there are no characters to read, or the character isn't a newline
  while (true)
  { // loop forever
    if (DigiUSB.available())
    {
      // something to read
      lastRead = DigiUSB.read(); // hold the last data , com
      if (temp != lastRead)
        sec_read = temp; // take first data , sel
      temp = lastRead;

      relay_op(sec_read, lastRead);

      if (lastRead == '\n')
      {
        break; // when we get a newline, break out of loop
      }
    }

    // refresh the usb port for 10 milliseconds
    DigiUSB.delay(10);
  }
}

void loop()
{
  // print output
  DigiUSB.println("Waiting for input...");
  // get input
  get_input();
}