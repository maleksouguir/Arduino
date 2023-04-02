#include <WiFi.h> // Utilisation de la bibliothèque WiFi à la place de esp32-hal-adc.h

// Remplacez avec les informations de votre réseau
const char* ssid = "NomDeMonWifi";
const char* password = "MotDePasseDeMonWifi";

// Définition du serveur web sur le port 80
WiFiServer server(80);

void setup() {
// Initialisation de la broche LED en tant que sortie
pinMode(13, OUTPUT);

// Connexion au réseau WiFi avec l'identifiant (SSID) et le mot de passe
Serial.begin(115200); // Utilisation de la majuscule S pour Serial
delay(10);

Serial.println();
Serial.println();
Serial.print("Connexion au réseau ");
Serial.println(ssid);

WiFi.begin(ssid, password);

while (WiFi.status() != WL_CONNECTED) {
delay(500);
Serial.print(".");
}

Serial.println("");
Serial.println("WiFi connecté");

// Démarrage du serveur web
server.begin();
Serial.println("Serveur démarré");
}

void loop() {
// Vérification des requêtes client entrantes
WiFiClient client = server.available();

if (!client) {
return;
}

Serial.println("Nouveau client");

while (!client.available()) {
delay(1);
}

// Lecture de la requête HTTP du client
String request = client.readStringUntil('\r');
Serial.println(request);
client.flush();

// Réponse au client en fonction de la requête
if (request.indexOf("/LED=ON") != -1) {
digitalWrite(13, HIGH); // Allumer la LED
} else if (request.indexOf("/LED=OFF") != -1) {
digitalWrite(13, LOW); // Éteindre la LED
}

// Envoi d'une réponse HTTP au client
client.println("HTTP/1.1 200 OK");
client.println("Content-Type: text/html");
client.println("");
client.println("<!DOCTYPE HTML>");
client.println("<html>");
client.println("<head><title>Serveur Web ESP32</title></head>");
client.println("<body>");
client.println("<h1>Contrôle de la LED</h1>");
client.println("<p>Cliquez <a href='/LED=ON'>ici</a> pour allumer la LED.</p>");
client.println("<p>Cliquez <a href='/LED=OFF'>ici</a> pour éteindre la LED.</p>");
client.println("</body>");
client.println("</html>");
}
