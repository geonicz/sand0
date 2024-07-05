// Created by GeoNicZ
// mailto:geonicz@gmail.com

#include "Arduino.h"

int digital_pins[] = {0 - 13};
int analog_pins[] = {14 - 19};
String command = "";

void print_command(String command)
{
	for (unsigned int i = 0; i < command.length(); i++)
	{
		Serial.print(i);
		Serial.print(":\t");
		Serial.print(command[i]);
		Serial.print('\t');
		Serial.println(command[i], HEX);
	}
}
bool check_command(String command)
{
	command.toLowerCase();
	if (!isdigit(command[0]))
		return false;

	for (unsigned int i = 1; command[i] != 0x0d && command[i] != 0x0a; i++)
	{
		switch (command[i])
		{
		case '+':
			if (!isdigit(command[i - 1]))
				return false;
			break;
		case '-':
			if (!isdigit(command[i - 1]))
				return false;
			break;
		case '!':
			if (!isdigit(command[i - 1]))
				return false;
			break;
		case '?':
			if (!isdigit(command[i - 1]))
				return false;
			break;
		default:
			if (!isDigit(command[i]))
				return false;
		}
	}
	Serial.println(command);
	return true;
}
void execute()
{
	String port = "";
	command.toLowerCase();

	for (unsigned int i = 0; command[i] != 0x0d && command[i] != 0x0a; i++)
	{
		if (isDigit(command[i]))
		{
			port += command[i];
			continue;
			;
		}
		pinMode(port.toInt(), OUTPUT);

		switch (command[i])
		{
		case '+':
		{
			digitalWrite(port.toInt(), HIGH);
			break;
		}
		case '-':
		{
			digitalWrite(port.toInt(), LOW);
			break;
		}
		case '!':
		{
			if (digitalRead(port.toInt()) == HIGH)
				digitalWrite(port.toInt(), LOW);
			else
				digitalWrite(port.toInt(), HIGH);
			break;
		}
		case '?':
		{

			Serial.println(analogRead(port.toInt()));
			break;
		}
		}
		port = "";
	}
}
void setup()
{
	Serial.begin(9600);
}
void loop()
{
	command = Serial.readString();
	if (check_command(command))
		execute();
}
