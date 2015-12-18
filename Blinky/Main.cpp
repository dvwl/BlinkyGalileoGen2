// Main.cpp : Defines the entry point for the console application.
//

#include <cpprest/http_client.h>

#include "stdafx.h"
#include "arduino.h"

using namespace utility;                    // Common utilities like string conversions
using namespace web;                        // Common features like URIs.
using namespace web::http;                  // Common HTTP functionality
using namespace web::http::client;          // HTTP client features
using namespace concurrency::streams;       // Asynchronous streams

int led = 13;  // This is the pin the LED is attached to.

void led_status()
{
	http_client client(L"http://swingalileo.azurewebsites.net/api/galileo/ledstate/1");

	client.request(methods::GET).then([](http_response response)
	{
		if (response.status_code() == status_codes::OK)
		{
			// the output from the server
			auto body = response.extract_string().get();
			std::wstring str = body.c_str();

			std::wstring on = L"true";
			std::wstring off = L"false";

			if (str.compare(on) == 0)
			{
				// is ON
				digitalWrite(led, HIGH);   // turn the LED on by making the voltage HIGH
				Log(L"LED ON\n");
				delay(1000);               // wait for a second
			}
			else if (str.compare(off) == 0)
			{
				// is OFF
				digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
				Log(L"LED OFF\n");
				delay(1000);               // wait for a second
			}
		}
	});
}

int _tmain(int argc, _TCHAR* argv[])
{
    return RunArduinoSketch();
}

void setup()
{
    // TODO: Add your code here
    
    pinMode(led, OUTPUT);       // Configure the pin for OUTPUT so you can turn on the LED.
}

// the loop routine runs over and over again forever:
void loop()
{
    // TODO: Add your code here
	led_status();
	delay(5000);				// wait for 5 second before next HTTP GET
}
