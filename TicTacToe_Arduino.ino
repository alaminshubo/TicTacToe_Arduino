#include <LiquidCrystal.h>
#include <Keypad.h>
// LCD Connections: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const byte ROWS = 3; 
const byte COLS = 3; 
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'}
};
// Keypad Pins: Rows to 10, 9, 8 | Cols to 7, 6, 13
byte rowPins[ROWS] = {10, 9, 8}; 
byte colPins[COLS] = {7, 6, 13}; 

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

const int blueLED = A1; // Player X
const int redLED = A0;  // Player O

char board[9];
bool playerX = true;
int moves = 0;
bool gameOver = false;
bool vsComputer = false;
bool gameStarted = false;

void setup() {
  lcd.begin(16, 2);
  pinMode(blueLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  randomSeed(analogRead(A5));// Use noise for random AI moves
  
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("TIC-TAC-TOE"); 
  lcd.setCursor(4, 1);
  lcd.print("WELCOME!");
  delay(2000);
  selectMode();
}

void selectMode() {
  digitalWrite(blueLED, LOW);
  digitalWrite(redLED, LOW);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Select Mode:");
  lcd.setCursor(0, 1);
  lcd.print("1:P V P  2:P V C");
  gameStarted = false;
}

void resetGame() {
  // Fill board with numbers 1-9
  for(int i=0; i<9; i++) board[i] = (char)(i + '1');
  playerX = true;
  moves = 0;
  gameOver = false;
  gameStarted = true;
  updateDisplay();
}

void updateDisplay() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(board[0]); lcd.print("|"); lcd.print(board[1]); lcd.print("|"); lcd.print(board[2]);
  lcd.print("  Turn: ");
  lcd.print(playerX ? 'X' : 'O');

  lcd.setCursor(0, 1);
  lcd.print(board[3]); lcd.print("|"); lcd.print(board[4]); lcd.print("|"); lcd.print(board[5]);
  lcd.print("  "); lcd.print(board[6]); lcd.print("|"); lcd.print(board[7]); lcd.print("|"); lcd.print(board[8]);
  // Toggle LEDs based on turn
  if (playerX) {
    digitalWrite(blueLED, HIGH);
    digitalWrite(redLED, LOW);
  } else {
    digitalWrite(blueLED, LOW);
    digitalWrite(redLED, HIGH);
  }
}

void blinkLEDs() {
  for(int i=0; i<5; i++) {
    digitalWrite(blueLED, HIGH); digitalWrite(redLED, HIGH);
    delay(200);
    digitalWrite(blueLED, LOW); digitalWrite(redLED, LOW);
    delay(200);
  }
}

void computerMove() {
  if (gameOver) return;
  
  // AI: Win
  for(int i=0; i<9; i++) {
    if(board[i] != 'X' && board[i] != 'O') {
      char temp = board[i]; board[i] = 'O';
      if(checkWinner()) { moves++; return; }
      board[i] = temp;
    }
  }
  // AI: Block
  for(int i=0; i<9; i++) {
    if(board[i] != 'X' && board[i] != 'O') {
      char temp = board[i]; board[i] = 'X';
      if(checkWinner()) { board[i] = 'O'; moves++; return; }
      board[i] = temp;
    }
  }
  // AI: Random
  int r;
  do { r = random(0, 9); } while(board[r] == 'X' || board[r] == 'O');
  board[r] = 'O';
  moves++;
}

void loop() {
  char key = keypad.getKey();

  if (!gameStarted) {
    if (key == '1') { vsComputer = false; resetGame(); }
    if (key == '2') { vsComputer = true; resetGame(); }
    return;
  }

  if (gameOver) {
    if (key) { selectMode(); }
    return;
  }

  if (key) {
    int index = key - '1';// Convert char key to index 0-8
    if (index >= 0 && index < 9 && board[index] != 'X' && board[index] != 'O') {
      board[index] = (playerX) ? 'X' : 'O';
      moves++;
      
      if (checkWinProcess()) return;

      if (vsComputer) {
        playerX = false; 
        updateDisplay();
        delay(600); 
        computerMove();
        if (checkWinProcess()) return;
        playerX = true;
      } else {
        playerX = !playerX; 
      }
      updateDisplay();
    }
  }
}

bool checkWinProcess() {
  if (checkWinner()) {
    updateDisplay();
    blinkLEDs();
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Winner is: "); 
    // Logic: If checkWinner is true, the current player is the winner
    lcd.print(playerX ? 'X' : 'O'); 
    lcd.setCursor(0,1);
    lcd.print("Key to Restart");
    gameOver = true;
    return true;
  }
  if (moves == 9) {
    updateDisplay();
    lcd.clear();
    lcd.print("Game Draw!");
    lcd.setCursor(0,1);
    lcd.print("Key to Restart");
    gameOver = true;
    return true;
  }
  return false;
}

bool checkWinner() {
  // Check all 8 possible winning combinations
  int winCases[8][3] = {{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};
  for(int i=0; i<8; i++) {
    if(board[winCases[i][0]] == board[winCases[i][1]] && board[winCases[i][1]] == board[winCases[i][2]]) return true;
  }
  return false;
}
