#define PIN_1 13
#define PIN_2 12

void setup() {
  // put your setup code here, to run once:
    pinMode( PIN_1, OUTPUT);
    pinMode( PIN_2, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
    digitalWrite( PIN_1, HIGH);
    digitalWrite( PIN_2, HIGH);
    delay(30);
    digitalWrite( PIN_1, LOW);
    delayMicroseconds(5000);
    digitalWrite( PIN_1, HIGH);
    delay(0);                      //ここでかえる
    digitalWrite( PIN_2, LOW);
    delayMicroseconds(5000);
    digitalWrite( PIN_1, HIGH);
    
}
