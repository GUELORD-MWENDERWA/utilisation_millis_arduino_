#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define BP1 8
#define BP2 9
#define BP3 10

bool lastStateBP1 = HIGH;
bool lastStateBP2 = HIGH;
bool lastStateBP3 = HIGH;

unsigned long lastDebounceTime1 = 0;
unsigned long lastDebounceTime2 = 0;
unsigned long lastDebounceTime3 = 0;
const unsigned long debounceDelay = 50;

unsigned long messageStartTime = 0;
const unsigned long messageDuration = 20000;
bool messageVisible = false;

void setup() {
  Serial.begin(9600); // Initialisation du moniteur série

  lcd.init();
  lcd.backlight();
  lcd.clear();

  pinMode(BP1, INPUT_PULLUP);
  pinMode(BP2, INPUT_PULLUP);
  pinMode(BP3, INPUT_PULLUP);

  Serial.println("Systeme pret");
}

void afficherMessage(String l1, String l2) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(l1);
  lcd.setCursor(0, 1);
  lcd.print(l2);

  // Affichage dans le moniteur série
  Serial.print("Message affiche : ");
  Serial.println(l1 + " " + l2);

  messageStartTime = millis();
  messageVisible = true;
}

void loop() {
  // --- Bouton 1 ---
  bool lectureBP1 = digitalRead(BP1);
  if (lectureBP1 == LOW && lastStateBP1 == HIGH && (millis() - lastDebounceTime1) > debounceDelay) {
    afficherMessage("PATIENTEZ", "Mr(Mme)");
    lastDebounceTime1 = millis();
  }
  lastStateBP1 = lectureBP1;

  // --- Bouton 2 ---
  bool lectureBP2 = digitalRead(BP2);
  if (lectureBP2 == LOW && lastStateBP2 == HIGH && (millis() - lastDebounceTime2) > debounceDelay) {
    afficherMessage("ENTREZ", "Mr(Mme)");
    lastDebounceTime2 = millis();
  }
  lastStateBP2 = lectureBP2;

  // --- Bouton 3 ---
  bool lectureBP3 = digitalRead(BP3);
  if (lectureBP3 == LOW && lastStateBP3 == HIGH && (millis() - lastDebounceTime3) > debounceDelay) {
    afficherMessage("JE SUIS", "ABSENT");
    lastDebounceTime3 = millis();
  }
  lastStateBP3 = lectureBP3;

  // --- Timer 20s ---
  if (messageVisible && (millis() - messageStartTime >= messageDuration)) {
    lcd.clear();
    messageVisible = false;
    Serial.println("Effacement automatique du message");
  }
}