const int ledPin1 = 19;
const int ledPin2 = 26;
const int ledPin3 = 33;
const int ledPin4 = 17;
const int buttonPin1 = 14;
const int buttonPin2 = 27;
const int buttonPin3 = 25;
const int buttonPin4 = 16;
const int buttonReset = 18;
bool resetButtonPressed = false;

int buttons[5] = {buttonPin1, buttonPin2, buttonPin3, buttonPin4, buttonReset};
int leds[4] = {ledPin1, ledPin2, ledPin3, ledPin4};

int sequence[16] = {};
int currentRound = 0;
int step = 0;
bool losing = false;

void setup() {
  setupButtons();
  setupLeds();
}

void loop() {
  if (digitalRead(buttonReset) == LOW) {
    resetButtonPressed = false;
    gameOver();
  }
  nextRound();
  playSequence();
  waitingPlayer();

  if (losing) {
    gameOverAnimation();
    resetGame();
  }
  if (currentRound >= 4){
    winAnimation();
    resetGame();
  }
  delay(1000);
}

void setupButtons() {
  for (int i = 0; i < 4; i++) {
    pinMode(buttons[i], INPUT_PULLUP);
  }
  pinMode(buttonReset, INPUT_PULLUP);
}

void setupLeds() {
  for (int i = 0; i < 4; i++) {
    pinMode(leds[i], OUTPUT);
  }
}

void playSequence() {
  for (int i = 0; i < currentRound; i++) {
    digitalWrite(leds[sequence[i]], HIGH);
    delay(500);
    digitalWrite(leds[sequence[i]], LOW);
    delay(100);
  }
}

void waitingPlayer() {
  int buttonPressed = 0;
  for (int i = 0; i < currentRound; i++) {
    bool moveMade = false;
    while (!moveMade) {
      for (int j = 0; j < 4; j++) {
        if (digitalRead(buttons[j]) == HIGH) {
          buttonPressed = j;
          digitalWrite(leds[j], HIGH);
          delay(300);
          digitalWrite(leds[j], LOW);
          moveMade = true;
        }
      }
    }
    if (sequence[step] != buttonPressed) {
      gameOverAnimation();
      losing = true;
      break;
    }
    step++;
  }
  step = 0;
}

void nextRound() {
  if (currentRound < 4) {
    sequence[currentRound] = random(4);
    currentRound++;
  }
}

void gameOver() {
  if (resetButtonPressed) {
    losing = true;
    resetGame();
    resetButtonPressed = false;
  }
}

void resetGame() {
  for (int i = 0; i < 16; i++) {
    sequence[i] = 0;
  }
  currentRound = 0;
  step = 0;
  losing = false;
}

void gameOverAnimation() {
  for (int i = 0; i < 4; i++) {
    digitalWrite(ledPin1, HIGH);
    digitalWrite(ledPin2, HIGH);
    digitalWrite(ledPin3, HIGH);
    digitalWrite(ledPin4, HIGH);
    delay(250);
    digitalWrite(ledPin1, LOW);
    digitalWrite(ledPin2, LOW);
    digitalWrite(ledPin3, LOW);
    digitalWrite(ledPin4, LOW);
    delay(250);
  }
}

void winAnimation() {
  for (int i = 0; i < 2; i++) {
    for(int j = 0; i < 4; j++){
      digitalWrite(leds[j], HIGH);
      delay(250);
      digitalWrite(leds[j], LOW);
      delay(250);
    }
  }
}
