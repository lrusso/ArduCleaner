// DC MOTORS PINS AND SPEEDS. REGULATE THE SPEED OF EACH DC MOTOR AND THE TURNING RIGHT DELAY.
int     MOTOR_LEFT_PIN           = 11;
int     MOTOR_LEFT_SPEED         = 190;
int     MOTOR_RIGHT_PIN          = 3;
int     MOTOR_RIGHT_SPEED        = 175;
int     MOTOR_RIGHT_TURNINGDELAY = 2000;

// ULTRASONIC SENSOR PINS
int     SENSOR_PIN_TRIGGER = 22;
int     SENSOR_PIN_ECHO    = 24;

// ULTRASONIC SENSOR VARIABLES. DO NOT MODIFIY.
int     sensorMaximumRange = 15;
int     sensorMinimumRange = 0;
int     sensorCounter = 0;
long    sensorDuration = 0;
long    sensorDistance = 0;

void setup()
    {
    Serial.begin(9600);

    pinMode(SENSOR_PIN_ECHO, INPUT);
    pinMode(SENSOR_PIN_TRIGGER, OUTPUT);
    pinMode(MOTOR_LEFT_PIN, OUTPUT);
    pinMode(MOTOR_RIGHT_PIN, OUTPUT);

    // STARTING EACH DC MOTOR
    analogWrite(MOTOR_LEFT_PIN, 255);
    analogWrite(MOTOR_RIGHT_PIN, 255);
    delay(50);

    moveForward();
    }

void loop()
    {
    if (obstacleDetected()==true)
        {
        Serial.println("OBSTACLE DETECTED!");
        turnRight();
        }
        else
        {
        Serial.println("NOTHING");
        }
    }

boolean obstacleDetected()
    {
    digitalWrite(SENSOR_PIN_TRIGGER, LOW);
    delayMicroseconds(2);
    digitalWrite(SENSOR_PIN_TRIGGER, HIGH);
    delayMicroseconds(10);
    digitalWrite(SENSOR_PIN_TRIGGER, LOW);

    sensorDuration = pulseIn(SENSOR_PIN_ECHO, HIGH);
    sensorDistance = sensorDuration/58.2;

    if (sensorDistance >= sensorMaximumRange || sensorDistance <= sensorMinimumRange)
        {
        sensorCounter = 0;
        return false;
        }
        else
        {
        sensorCounter = sensorCounter +1;
        if (sensorCounter>5)
            {
            sensorCounter = 0;
            sensorDuration = 0;
            sensorDistance = 0;
            return true;
            }
            else
            {
            return false;
            }
        }
    }

void turnRight()
    {
    // SETS NO SPEED TO THE RIGHT DC MOTOR
    analogWrite(MOTOR_RIGHT_PIN, 0);

    // WAITS UNTIL THE ROBOT TURNS RIGHT
    delay(MOTOR_RIGHT_TURNINGDELAY);

    // STARTS THE RIGHT DC MOTOR
    analogWrite(MOTOR_RIGHT_PIN, 255);
    delay(50);
    
    // SETS THE DEFAULT RIGHT DC MOTOR SPEED
    analogWrite(MOTOR_RIGHT_PIN, MOTOR_RIGHT_SPEED);
    }

void moveForward()
    {
    analogWrite(MOTOR_LEFT_PIN, MOTOR_LEFT_SPEED);
    analogWrite(MOTOR_RIGHT_PIN, MOTOR_RIGHT_SPEED);
    }
