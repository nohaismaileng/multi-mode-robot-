#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(4, 3);
#define trig 10
#define echo 2
long duration, distance;

#define IN1 6
#define IN2 7
#define IN3 8
#define IN4 9

char Reading;
const byte address[6] = "00001";

void setup() {
    for(int i = 5; i <= 11; i++) {
        pinMode(i, OUTPUT);
    }
    pinMode(echo, INPUT);
    Serial.begin(9600);
    radio.begin();
    radio.openReadingPipe(0, address);
    radio.setPALevel(RF24_PA_HIGH);
    radio.startListening();
}

void Ultrasonic() {
    digitalWrite(trig, LOW);
    delayMicroseconds(2);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);
    duration = pulseIn(echo, HIGH);
    distance = (duration / 2) * 0.0343;
    Serial.print("Distance: ");
    Serial.println(distance);
}

void forword() {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
}

void backword() {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
}

void left() {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
}

void right() {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
}

void stopp() {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
}

void loop() {


   

    if (radio.available()) {
        radio.read(&Reading, sizeof(Reading));
        Serial.println(Reading);

        switch (Reading) {
            case 'F': forword(); Serial.println("Slave"); break;
            case 'B': backword(); break;
            case 'R': right(); break;
            case 'L': left(); break;
            case 'S': stopp(); break;
        }
    }
   
    }
}
