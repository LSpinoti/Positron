// The size of the board is 60cm
#define BOARD_SIZE 60
#define BOARD_SQUARES 10

#define SENSOR1_PIN 3
#define SENSOR2_PIN 8

float dist1;
float dist2;

bool board[BOARD_SQUARES][BOARD_SQUARES];

void setup() {
  // Initiate serial communication
  Serial.begin(9600);
}

void loop() {
  // Ping the sensors
  dist1 = ping(SENSOR1_PIN);
  dist2 = ping(SENSOR2_PIN);

  // Loop to detect every square
  for (int i = 0; i < BOARD_SQUARES; ++i) {
    for (int j = 0; j < BOARD_SQUARES; ++j) {
      detectSquare(i, j);
    }
  }

  // Print, wait, and repeat
  printBoard();
  delay(500);
}

void detectSquare(int x, int y) {
  // See the flowchart in the report to understand this
  if ((int) (dist1 / BOARD_SQUARES) == (int) sqrt(x * x + y * y)) {
    if ((int) (dist2 / BOARD_SQUARES) == (int) sqrt((BOARD_SQUARES - x - 1) * (BOARD_SQUARES - x - 1) + y * y)) {
      board[y][x] = true;
      return;
    }
  }
  
  board[y][x] = false;
}

// This method can be used instead of detectSquare to see the whole circle detected
void detectSquareDebug(int x, int y) {
  if ((int) (dist1 / BOARD_SQUARES) == (int) sqrt(x * x + y * y)) {
    board[y][x] = true;
    return;
  }
  if ((int) (dist2 / BOARD_SQUARES) == (int) sqrt((BOARD_SQUARES - x - 1) * (BOARD_SQUARES - x - 1) + y * y)) {
    board[y][x] = true;
    return;
  }
  board[y][x] = false;
}

void printBoard() {
  // Print the top
  for (int i = 0; i < 3 * BOARD_SQUARES + 1; ++i) {
    Serial.print("—");
  }
  Serial.println();

  // Print the boxes
  for (int i = 0; i < BOARD_SQUARES; ++i) {
    for (int j = 0; j < BOARD_SQUARES; ++j) {
      if (board[i][j])
        Serial.print("|██");
      else
        Serial.print("|  ");
    }
    Serial.println("|");
  }

  // Print the bottom
  for (int i = 0; i < 3 * BOARD_SQUARES + 1; ++i) {
    Serial.print("—");
  }
  
  Serial.println("\n");
}

// This code was copied from this course's D2L page
float ping(int pingPin) {
  long duration;
  long cm;
  
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);
  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);
  
  return duration / 29.0 / 2.0;
}
