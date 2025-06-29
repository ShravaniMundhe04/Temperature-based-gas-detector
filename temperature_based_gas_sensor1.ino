#define TMP_PIN A0   // Temperature sensor pin
#define LED_PIN 7    // LED connected to pin 7
#define BUZZER_PIN 6 // Buzzer connected to pin 6
#define BUTTON_PIN 12 // Button connected to pin 12

float prevTemperature = 0; // Stores previous temperature
bool tempLow = false; // Flag to track low temperature condition

void setup() {
    pinMode(LED_PIN, OUTPUT);
    pinMode(BUZZER_PIN, OUTPUT);
    pinMode(BUTTON_PIN, INPUT_PULLUP); // Internal pull-up for button
    Serial.begin(9600);
}

void loop() {
    int tempValue = analogRead(TMP_PIN);
    float voltage = (tempValue / 1024.0) * 5.0;
    float temperatureC = (voltage - 0.5) * 100.0; // Convert to Celsius

    bool buttonState = digitalRead(BUTTON_PIN); // Reads button state
    bool tempDropping = (temperatureC < prevTemperature - 2.0); // Detect sudden drop

    Serial.print("Temperature: ");
    Serial.print(temperatureC);
    Serial.println(" C");

    // Condition 1: If temperature drops suddenly
    if (tempDropping) {
        tempLow = true; // Mark temp as low
    }

    // Condition 2: If button is pressed AND temp is low, buzzer goes ON
    if (buttonState == LOW && tempLow) {
        digitalWrite(LED_PIN, HIGH);
        digitalWrite(BUZZER_PIN, HIGH);
    } else {
        digitalWrite(LED_PIN, LOW);
        digitalWrite(BUZZER_PIN, LOW);
    }

    // If temp rises again, reset tempLow flag
    if (temperatureC > prevTemperature) {
        tempLow = false;
    }

    prevTemperature = temperatureC; // Update previous temperature
    delay(500);
}
