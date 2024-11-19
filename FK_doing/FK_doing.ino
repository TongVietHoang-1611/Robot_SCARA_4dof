// Định nghĩa chân
const int stepxPin = 2;
const int dirxPin = 5;
const int enPin = 8;
const int stepyPin = 3;
const int diryPin = 6;
const int stepzPin = 4;
const int dirzPin = 7;

// Hằng số chuyển đổi
const float MM_PER_REV_X = 2.0;
const float DEG_PER_REV_Y = 80.0;
const float DEG_PER_REV_Z = 49.6;
const float DEG_PER_REV_YZ = 92.9;
const int STEPS_PER_REV = 200;

bool executed = false;

void setup() {
  pinMode(stepxPin, OUTPUT);
  pinMode(dirxPin, OUTPUT);
  pinMode(stepyPin, OUTPUT);
  pinMode(diryPin, OUTPUT);
  pinMode(stepzPin, OUTPUT);
  pinMode(dirzPin, OUTPUT);
  pinMode(enPin, OUTPUT);
  digitalWrite(enPin, LOW);
}

void moveRobotSync(float x_mm, float y_deg, float z_deg) {
   // Tính số bước
   int x_steps = (x_mm / MM_PER_REV_X) * STEPS_PER_REV;
   int y_steps = (y_deg / DEG_PER_REV_Y) * STEPS_PER_REV;
   int yz_steps = (y_deg / DEG_PER_REV_YZ) * STEPS_PER_REV;
   int z_steps = (z_deg / DEG_PER_REV_Z) * STEPS_PER_REV;
   
   // Xác định hướng
   bool x_dir = (x_mm >= 0) ? LOW : HIGH;
   bool y_dir = (y_deg >= 0) ? LOW : HIGH;
   bool z_dir = (z_deg >= 0) ? LOW : HIGH;
   
   // Thiết lập hướng ban đầu
   digitalWrite(dirxPin, x_dir);
   
   // X chạy riêng trước
   for (int i = 0; i < abs(x_steps); i++) {
     digitalWrite(stepxPin, HIGH);
     delayMicroseconds(700);
     digitalWrite(stepxPin, LOW);
     delayMicroseconds(700);
   }
   delay(200);
   
   // Sau đó mới đồng bộ Y và YZ
   digitalWrite(diryPin, y_dir);
   digitalWrite(dirzPin, y_dir);
   
   int max_steps = max(abs(y_steps), abs(yz_steps));
   
   for (int i = 0; i < max_steps; i++) {
     // Y
     if (i < abs(y_steps)) digitalWrite(stepyPin, HIGH);
     
     // YZ đồng bộ
     if (i < abs(yz_steps)) digitalWrite(stepzPin, HIGH);
     
     delayMicroseconds(700);
     
     // Hạ xuống
     digitalWrite(stepyPin, LOW);
     digitalWrite(stepzPin, LOW);
     
     delayMicroseconds(700);
   }
   
   // Thêm phần di chuyển riêng của Z
   digitalWrite(dirzPin, z_dir);
   
   for (int i = 0; i < abs(z_steps); i++) {
     digitalWrite(stepzPin, HIGH);
     delayMicroseconds(700);
     digitalWrite(stepzPin, LOW);
     delayMicroseconds(700);
   }
}

void loop() {
  if (!executed) {
    moveRobotSync(0, 0, 60);  // Ví dụ: Thay đổi giá trị theo nhu cầu
    executed = true;
  }
}