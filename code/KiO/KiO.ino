#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define TRIG_PIN A10
#define ECHO_PIN A9

#define LED_R_PIN A2
#define LED_G_PIN A1
#define LED_B_PIN A0

#define INPUT_1 A8
#define INPUT_2 A3

#define SCREEN_SCL 6
#define SCREEN_SDA 5

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// Création de l’objet écran (adresse 0x3C = standard SSD1306 en I2C)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

long duration;
float distanceCm;

void setup() {
  Serial.begin(115200);

  // Initialisation capteur ultrasons
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Contrôle moteur
  pinMode(INPUT_1, OUTPUT);
  pinMode(INPUT_2, OUTPUT);

  // Initialisation LED RGB
  ledcAttach(LED_R_PIN, 5000, 8);
  ledcAttach(LED_G_PIN, 5000, 8);
  ledcAttach(LED_B_PIN, 5000, 8);

  ledcWrite(LED_R_PIN, 0);
  ledcWrite(LED_G_PIN, 0);
  ledcWrite(LED_B_PIN, 0);

  // Initialisation écran OLED
  Wire.begin(SCREEN_SDA, SCREEN_SCL);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 non détecté"));
    for (;;);
  }
  display.clearDisplay();
  display.setTextSize(2);      // Taille du texte
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Init...");
  display.display();
  delay(1000);
}

void loop() {
  // Trigger ultrason
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Lecture echo
  duration = pulseIn(ECHO_PIN, HIGH, 30000);
  if (duration == 0) {
    distanceCm = -1; // hors portée / timeout
  } else {
    distanceCm = (duration * 0.034) / 2.0;
  }

  // Affichage série
  Serial.print("Distance: ");
  if (distanceCm < 0) Serial.println("timeout");
  else {
    Serial.print(distanceCm);
    Serial.println(" cm");
  }

  // Affichage OLED
  display.clearDisplay();
  display.setCursor(0, 0);
  if (distanceCm < 0) {
    display.println("Hors-champ");
  } else {
    display.print("Distance: ");
    display.print(distanceCm, 1);
    display.println(" cm");
  }
  display.display();

  // Indicateurs LED + moteurs
  if (distanceCm > 0 && distanceCm < 10) {
    ledcWrite(LED_R_PIN, 255); ledcWrite(LED_G_PIN, 0);   ledcWrite(LED_B_PIN, 0);   // rouge
    digitalWrite(INPUT_1, HIGH);
    digitalWrite(INPUT_2, LOW);
  } else if (distanceCm >= 10 && distanceCm < 15) {
    ledcWrite(LED_R_PIN, 255); ledcWrite(LED_G_PIN, 255); ledcWrite(LED_B_PIN, 0);   // jaune
    digitalWrite(INPUT_1, LOW);
    digitalWrite(INPUT_2, LOW);
  } else if (distanceCm >= 15 && distanceCm < 30) {
    ledcWrite(LED_R_PIN, 0);   ledcWrite(LED_G_PIN, 255); ledcWrite(LED_B_PIN, 0);   // vert
    digitalWrite(INPUT_1, LOW);
    digitalWrite(INPUT_2, HIGH);
  } else {
    ledcWrite(LED_R_PIN, 0);   ledcWrite(LED_G_PIN, 0);   ledcWrite(LED_B_PIN, 255); // bleu
    digitalWrite(INPUT_1, LOW);
    digitalWrite(INPUT_2, HIGH);
  }

  delay(150);
}