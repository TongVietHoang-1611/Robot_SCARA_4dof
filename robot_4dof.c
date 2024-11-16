// Định nghĩa chân pin
const int stepxPin = 2;
const int dirxPin = 5;
const int enPin = 8;
const int stepyPin = 3;
const int diryPin = 6;
const int stepzPin = 4;
const int dirzPin = 7;
const int stepsPerRevolution = 200; // Số bước cho một vòng quay

// Biến để theo dõi vị trí hiện tại
long currentX = 0;
long currentY = 0;
long currentZ = 0;

void setup() {
  // Thiết lập các chân pin output
  pinMode(stepxPin, OUTPUT);
  pinMode(dirxPin, OUTPUT);
  pinMode(stepyPin, OUTPUT);
  pinMode(diryPin, OUTPUT);
  pinMode(stepzPin, OUTPUT);
  pinMode(dirzPin, OUTPUT);
  pinMode(enPin, OUTPUT);
  
  digitalWrite(enPin, LOW); // Enable động cơ
}

// Hàm di chuyển đồng bộ 3 trục theo thuật toán Bresenham
void moveSync(long x, long y, long z, int stepDelay) {
  long dx = abs(x - currentX);
  long dy = abs(y - currentY);
  long dz = abs(z - currentZ);
  
  // Xác định hướng cho mỗi trục
  digitalWrite(dirxPin, x > currentX ? HIGH : LOW);
  digitalWrite(diryPin, y > currentY ? HIGH : LOW);
  digitalWrite(dirzPin, z > currentZ ? HIGH : LOW);
  
  // Tìm khoảng cách lớn nhất để làm trục chính
  long maxDist = max(dx, max(dy, dz));
  
  // Các biến lỗi cho thuật toán Bresenham
  long errorY = maxDist / 2;
  long errorZ = maxDist / 2;
  long errorX = maxDist / 2;
  
  // Đếm số bước đã di chuyển
  long stepCount = 0;
  
  while (stepCount < maxDist) {
    // Reset tất cả step pin
    digitalWrite(stepxPin, LOW);
    digitalWrite(stepyPin, LOW);
    digitalWrite(stepzPin, LOW);
    
    // Tính toán xem trục nào cần bước
    if (stepCount < dx) {
      errorX -= dx;
      if (errorX < 0) {
        digitalWrite(stepxPin, HIGH);
        errorX += maxDist;
      }
    }
    
    if (stepCount < dy) {
      errorY -= dy;
      if (errorY < 0) {
        digitalWrite(stepyPin, HIGH);
        errorY += maxDist;
      }
    }
    
    if (stepCount < dz) {
      errorZ -= dz;
      if (errorZ < 0) {
        digitalWrite(stepzPin, HIGH);
        errorZ += maxDist;
      }
    }
    
    delayMicroseconds(stepDelay);  // Điều chỉnh tốc độ bằng cách thay đổi thời gian delay
    stepCount++;
  }
  
  // Cập nhật vị trí hiện tại
  currentX = x;
  currentY = y;
  currentZ = z;
}

void loop() {
  // Di chuyển theo mẫu như code gốc nhưng đồng bộ

  // Di chuyển X
  moveSync(50 * stepsPerRevolution, 0, 0, 700);
  delay(200);

  // Di chuyển Y
  moveSync(50 * stepsPerRevolution, stepsPerRevolution, 0, 700);
  delay(200);

  // Di chuyển Z
  moveSync(50 * stepsPerRevolution, stepsPerRevolution, stepsPerRevolution, 700);
  delay(200);

  // Di chuyển Y ngược lại
  moveSync(50 * stepsPerRevolution, 0, stepsPerRevolution, 700);
  delay(200);

  // Di chuyển Z ngược lại
  moveSync(50 * stepsPerRevolution, 0, 0, 700);
  delay(200);

  // Di chuyển X ngược về vị trí ban đầu
  moveSync(0, 0, 0, 700);
  delay(200);
}
