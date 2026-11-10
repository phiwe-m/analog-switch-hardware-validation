#include <Arduino.h>

const int POT_PIN = 35;  // the manual input sumulation
const int led1 = 23; // the led output
const int SN_SEL = 21; //the select pin for SN32, pin 9,GPIO25 in real system, 21 for testing

// the manual input threshold, inputs valid above this value
const int manThreshold = 300;

// auto timing
const unsigned long autoON = 3000; //on for 3secs
const unsigned long autoOFF = 2000; // off for 2 seconds
unsigned long prevMillis = 0; // to hold the previous state value for comparison
bool autoLED_state = true; // tells you when auto mode is on and off 
bool manMODE = false;   


void setup()
{
    Serial.begin(115200); // to print to serial

    pinMode(POT_PIN, INPUT); // declare pins as I/O 
    pinMode(led1, OUTPUT);
    pinMode(SN_SEL, OUTPUT);
    digitalWrite(SN_SEL, LOW);   // Default = MANUAL
    // analog setup
    analogReadResolution(12);
    //led setup
    digitalWrite(led1,HIGH);
    prevMillis = millis();

    Serial.println("man/auto test started");
}

void loop()
{
    int potValue = analogRead(POT_PIN);

    Serial.print("POT: ");
    Serial.println(potValue);

    // =========================================
    // MANUAL MODE
    // =========================================
    if (potValue > manThreshold)
    {
        digitalWrite(SN_SEL, LOW);   // Select NC = MANUAL
        // If we just entered manual mode
        if (!manMODE)
        {
            manMODE = true;
            Serial.println("AUTO stopped --> MANUAL start");
        }

        int brightness = map(
            potValue,
            manThreshold,
            4095,
            0,
            255
        );

        brightness = constrain(brightness, 0, 255);

        analogWrite(led1, brightness);

        Serial.print("MANUAL | ADC: ");
        Serial.print(potValue);
        Serial.print(" | Brightness: ");
        Serial.println(brightness);
    }

    // =========================================
    // AUTO MODE
    // =========================================
    else
    {
         digitalWrite(SN_SEL, HIGH);
        // JUST transitioned MANUAL -> AUTO
        if (manMODE)
        {
            manMODE = false;

            // Take GPIO23 back from PWM
            pinMode(led1, OUTPUT);

            // Restart AUTO sequence
            digitalWrite(led1, HIGH);
            autoLED_state = true;
            prevMillis = millis();

            Serial.println("MANUAL stopped --> AUTO start");
        }

        unsigned long currentMillis = millis();

        // LED currently ON
        if (autoLED_state == true)
        {
            if (currentMillis - prevMillis >= autoON)
            {
                digitalWrite(led1, LOW);

                autoLED_state = false;
                prevMillis = currentMillis;

                Serial.println("AUTO: LED OFF");
            }
        }

        // LED currently OFF
        else
        {
            if (currentMillis - prevMillis >= autoOFF)
            {
                digitalWrite(led1, HIGH);

                autoLED_state = true;
                prevMillis = currentMillis;

                Serial.println("AUTO: LED ON");
            }
        }
    }

    delay(100);
    
}

extern "C" void app_main(void)
{
    initArduino();

    setup();

    while (true)
    {
        loop();
    }
}