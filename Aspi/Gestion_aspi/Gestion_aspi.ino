// Définition des broches pour les relais
#define RELAY_PIN_1 2
#define RELAY_PIN_2 3

// Temporisation en millisecondes
#define DELAY_TIME 5000

void setup() 
{
  // Initialisation des broches des relais en sortie
  pinMode(RELAY_PIN_1, OUTPUT);
  pinMode(RELAY_PIN_2, OUTPUT);

  // Initialisation des relais
  digitalWrite(RELAY_PIN_1, HIGH);
  digitalWrite(RELAY_PIN_2, HIGH);
}

void loop() {
  // Activation des relais
  digitalWrite(RELAY_PIN_1, LOW);
  digitalWrite(RELAY_PIN_2, LOW);

  // Attente de la temporisation
  delay(DELAY_TIME);

  // Désactivation des relais
  digitalWrite(RELAY_PIN_1, HIGH);
  digitalWrite(RELAY_PIN_2, HIGH);

  // Attente de la temporisation avant de recommencer
  delay(DELAY_TIME);
}
