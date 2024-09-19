
#include <SPI.h>
#include <WiFi.h>
#include <HTTPClient.h>
#define redled 22
#define greenled 23
#define blueled 2

char ssid[] = "Galaxy A20s6686";  //  your network SSID (name)
char pass[] = "keilusaaaaaa";     // your network password
const char* serverUrl = "http://192.168.27.149:8080/parol/getdata2.php";
const char* green = "http://192.168.27.149:8080/parol/green.php";
const char* red = "http://192.168.27.149:8080/parol/red.php";
WiFiServer server(80);

void setup() {
  Serial.begin(9600);
  pinMode(redled, OUTPUT);
  pinMode(blueled, OUTPUT);
  pinMode(greenled, OUTPUT);
  delay(50);

  Serial.println("");
  Serial.println("");
  Serial.print("Connecting to ");
  Serial.println(ssid);


  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(redled, !digitalRead(greenled));

    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP Address ");
  Serial.println(WiFi.localIP());
  digitalWrite(redled, LOW);
  digitalWrite(greenled, HIGH);

  server.begin();
}

int val = 0;

void loop() {
  WiFiClient client = server.available();  // listen for incoming clients

  if (client) {                    // if you get a client,
    Serial.println("new client");  // print a message out the serial port
    String currentLine = "";       // make a String to hold incoming data from the client
    while (client.connected()) {   // loop while the client's connected
      if (client.available()) {    // if there's bytes to read from the client,
        char c = client.read();    // read a byte, then
        Serial.write(c);           // print it out the serial monitor
        if (c == '\n') {           // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // the content of the HTTP response follows the header:
            client.print("Click <a href=\"/H\">here</a> turn the BlueLED on pin 2 on<br>");
            client.print("Click <a href=\"/L\">here</a> turn the BlueLED on pin 2 off<br>");

            // The HTTP response ends with another blank line:
            client.println();


            HTTPClient http;

            Serial.print("Requesting data from server...");
            http.begin(serverUrl);

            int httpCode = http.GET();

            if (httpCode > 0) {
              String blue = http.getString();
              Serial.println(blue);

              client.print(blue);
              int blueValue = blue.substring(2, blue.length() - 2).toInt();
              // Debugging: Print the received payload value
              Serial.print("Payload value: ");
              Serial.println(blueValue);
              client.print(blueValue);
              // Check if the payload is equal to 4
              if (blueValue == 0) {
                Serial.println("Payload is 4!");  // Debugging statement
                digitalWrite(blueled, LOW);      // Turn on the blue LED
              } else if (blueValue == 1) {
                digitalWrite(blueled, HIGH);  // Turn off the blue LED (optional)
              } else if (blueValue == 2) {
                for (int x=0; x<15; x++){
                digitalWrite(blueled, HIGH);
                delay(500);
                digitalWrite(blueled, LOW);
                 delay(500);
                digitalWrite(blueled, HIGH);
                }  // Turn off the blue LED (optional)
              }

            } else {
              Serial.println("Error on HTTP request");
            }





            Serial.print("Requesting data from server...");
            http.begin(green);

            int httpCod = http.GET();

            if (httpCod > 0) {
              String green = http.getString();
              Serial.println(green);

              client.print(green);
              int greenValue = green.substring(2, green.length() - 2).toInt();
              // Debugging: Print the received payload value
              Serial.print("Payload value: ");
              Serial.println(greenValue);
              client.print(greenValue);
              // Check if the payload is equal to 4
              if (greenValue == 1) {
                Serial.println("Payload is 4!");  // Debugging statement
                digitalWrite(greenled, HIGH);     // Turn on the blue LED
              } else {
                digitalWrite(greenled, LOW);  // Turn off the blue LED (optional)
              }
            } else {
              Serial.println("Error on HTTP request");
            }




            Serial.print("Requesting data from server...");
            http.begin(red);

            int httpCo = http.GET();

            if (httpCo > 0) {
              String red = http.getString();
              Serial.println(red);

              client.print(red);
              int redValue = red.substring(2, red.length() - 2).toInt();
              // Debugging: Print the received payload value
              Serial.print("Payload value: ");
              Serial.println(redValue);
              client.print(redValue);
              // Check if the payload is equal to 4
              if (redValue == 1) {
                  digitalWrite(redled, HIGH);   // Turn on the red LED
                  delay(500);                   // Adjust the delay as needed
                  digitalWrite(redled, LOW);    // Turn off the red LED
                  delay(500);                   // Adjust the delay as needed
              } else {
                digitalWrite(redled, LOW);  // Turn off the blue LED (optional)
              }
            } else {
              Serial.println("Error on HTTP request");
            }







            // break out of the while loop:
            break;
          } else {  // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

        // Check to see if the client request was "GET /H" or "GET /L":
        if (currentLine.endsWith("GET /H")) {
          digitalWrite(blueled, HIGH);  // GET /H turns the LED on
        }
        if (currentLine.endsWith("GET /L")) {
          digitalWrite(blueled, LOW);  // GET /L turns the LED off
        }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("client disonnected");
  }
}



// void printWifiStatus() {
//   // print the SSID of the network you're attached to:
//   Serial.print("SSID: ");
//   Serial.println(WiFi.SSID());

//   // print your WiFi shield's IP address:
//   IPAddress ip = WiFi.localIP();
//   Serial.print("IP Address: ");
//   Serial.println(ip);

//   // print the received signal strength:
//   long rssi = WiFi.RSSI();
//   Serial.print("signal strength (RSSI):");
//   Serial.print(rssi);
//   Serial.println(" dBm");
//   // print where to go in a browser:
//   Serial.print("To see this page in action, open a browser to http://");
//   Serial.println(ip);
// }
