#include <WiFi.h> // Use WiFi library instead of esp32-hal-adc.h
// Replace with your network credentials
const char* ssid = "TOPNET5321C94F";
const char* password = "LmT7RMU3bkJwjKX";
// Define web server on port 80
WiFiServer server(80);

void setup() {
  // Initialize LED pin as an output
  pinMode(13, OUTPUT);
  // Connect to WiFi network with SSID and password
  Serial.begin(115200); // Use capital S in Serial
  delay(10);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  // Start the server
  server.begin();
  Serial.println("Server started");
  
  // Print ESP32 IP address
  Serial.println(WiFi.localIP());
}

void loop() {
  // Check for incoming client requests
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  Serial.println("New client");
  while (!client.available()) {
    delay(1);
  }
  // Read the HTTP request from the client
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
  // Respond to the client based on the request
  if (request.indexOf("/LED=ON") != -1) {
    digitalWrite(13, HIGH); // Turn LED ON
  } else if (request.indexOf("/LED=OFF") != -1) {
    digitalWrite(13, LOW); // Turn LED OFF
  }
  // Send an HTTP response back to the client
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("");
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<head><title>ESP32 Web Server</title></head>");
  client.println("<body>");
  client.println("<h1>LED Control</h1>");
  client.println("<p>Click <a href="/LED=ON">here</a> to turn LED on.</p>");
  client.println("<p>Click <a href="/LED=OFF">here</a> to turn LED off.</p>");
  client.println("</body>");
  client.println("</html>");
}