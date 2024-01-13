#include <DHT.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Adafruit_Sensor.h>


#define DHTPIN D4     // Define the pin to which the DHT11 sensor is connected.
#define DHTTYPE DHT11 // DHT type (DHT11 or DHT22)

const char* ssid = "AnnaFredrik";
const char* password = "Mansken47";

DHT dht(DHTPIN, DHTTYPE);
ESP8266WebServer server(80);  // Create an instance of the ESP8266WebServer class on port 80

void handleRoot() {
  // Generate the HTML page to display temperature and humidity
  String html = "<html><body style=\"text-align: center; font-size: 3em;\">"; // Add style attribute to center align the content
  html += "<h1>Temperatur & Luftfuktighet</h1>";
  html += "<p>Temperatur: " + String(dht.readTemperature()) + " &#8451;</p>";
  html += "<p>Luftfuktighet: " + String(dht.readHumidity()) + " %</p>";
  html += "<p>ESP8266 IP Address: " + WiFi.localIP().toString() + "</p>";  // Display the IP address
  html += "</body></html>";

  server.send(200, "text/html", html);  // Send the HTML page as a response
}

void setup() {
  Serial.begin(9600);
  delay(10);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  dht.begin();

  // Display the ESP8266's IP address on the Serial Monitor
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Define the routes for your web server
  server.on("/", HTTP_GET, handleRoot);
  server.begin();
}

void loop() {
  server.handleClient();  // Handle incoming web server requests

  // Read temperature and humidity from the DHT11 sensor
  // You can perform actions here with the sensor data or update the web page.
  // For now, we're just reading the data and serving it via the web page.
}
