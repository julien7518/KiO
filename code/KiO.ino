#define TRIG_PIN A4
#define ECHO_PIN A0

#define LED_R_PIN A3
#define LED_G_PIN A1
#define LED_B_PIN A2
#define INPUT_1 A5
#define INPUT_2 A10

long duration;
float distanceCm;

void setup() {
  Serial.begin(115200);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  pinMode(INPUT_1, OUTPUT);
  pinMode(INPUT_2, OUTPUT);

  // Nouvelle API (Arduino-ESP32 v3+)
  // ledcAttach(pin, freq, resolution) -> channel auto-assigné
  ledcAttach(LED_R_PIN, 5000, 8); // 5 kHz, 8 bits (0..255)
  ledcAttach(LED_G_PIN, 5000, 8);
  ledcAttach(LED_B_PIN, 5000, 8);

  ledcWrite(LED_R_PIN, 0);
  ledcWrite(LED_G_PIN, 0);
  ledcWrite(LED_B_PIN, 0);
}

void loop() {
  // Trigger
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Lecture echo (timeout 30 ms pour sécurité)
  duration = pulseIn(ECHO_PIN, HIGH, 30000);
  if (duration == 0) {
    distanceCm = -1; // hors portée / timeout
  } else {
    distanceCm = (duration * 0.034) / 2.0;
  }

  Serial.print("Distance: ");
  if (distanceCm < 0) Serial.println("timeout");
  else {
    Serial.print(distanceCm);
    Serial.println(" cm");
  }

  // Mappage simple en paliers (tu peux remplacer par un dégradé)
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