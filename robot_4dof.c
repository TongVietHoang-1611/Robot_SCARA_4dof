// Defines pin numbers
const int stepxPin = 2; 
const int dirxPin = 5; 
const int stepyPin = 3; 
const int diryPin = 6; 
const int stepzPin = 4; 
const int dirzPin = 7; 
const int enPin = 8; 

const int stepsPerRevolution = 200; // Number of steps per revolution

void setup() {
  // Set pin modes
  pinMode(stepxPin, OUTPUT);
  pinMode(dirxPin, OUTPUT);
  pinMode(stepyPin, OUTPUT);
  pinMode(diryPin, OUTPUT);
  pinMode(stepzPin, OUTPUT);
  pinMode(dirzPin, OUTPUT);
  pinMode(enPin, OUTPUT);

  // Enable the driver
  digitalWrite(enPin, LOW);
}

void loop() {
  // Move to (1000, 500, 300) steps
  moveTo(1000, 500, 300);
  delay(1000); // Wait 1 second

  // Move back to the origin (-1000, -500, -300) steps
  moveTo(-1000, -500, -300);
  delay(1000); // Wait 1 second
}

// Function to move the motor to the target position using Bresenham's algorithm
void moveTo(int dx, int dy, int dz) {
  // Determine the direction for each axis
  digitalWrite(dirxPin, dx > 0 ? HIGH : LOW);
  digitalWrite(diryPin, dy > 0 ? HIGH : LOW);
  digitalWrite(dirzPin, dz > 0 ? HIGH : LOW);

  // Take the absolute value of each displacement
  dx = abs(dx);
  dy = abs(dy);
  dz = abs(dz);

  // Determine the maximum number of steps (for Bresenham)
  int stepsMax = max(dx, max(dy, dz));

  // Initialize errors for each axis
  int errorX = 0;
  int errorY = 0;
  int errorZ = 0;

  // Calculate deltas for each axis (errors are multiplied by 2)
  int deltaX = dx * 2;
  int deltaY = dy * 2;
  int deltaZ = dz * 2;

  // Iterate over the number of steps
  for (int step = 0; step < stepsMax; step++) {
    // Move on the X axis
    errorX += deltaX;
    if (errorX >= stepsMax) {
      digitalWrite(stepxPin, HIGH);
      delayMicroseconds(700);  // Adjust speed by modifying delay time
      digitalWrite(stepxPin, LOW);
      delayMicroseconds(700);
      errorX -= stepsMax * 2; // Reset error
    }

    // Move on the Y axis
    errorY += deltaY;
    if (errorY >= stepsMax) {
      digitalWrite(stepyPin, HIGH);
      delayMicroseconds(700);
      digitalWrite(stepyPin, LOW);
      delayMicroseconds(700);
      errorY -= stepsMax * 2; // Reset error
    }

    // Move on the Z axis
    errorZ += deltaZ;
    if (errorZ >= stepsMax) {
      digitalWrite(stepzPin, HIGH);
      delayMicroseconds(700);
      digitalWrite(stepzPin, LOW);
      delayMicroseconds(700);
      errorZ -= stepsMax * 2; // Reset error
    }
  }
}
