// DC MOTORS SPEEDS. REGULATE THE SPEED OF EACH DC MOTOR.
int     MOTOR_LEFT_SPEED  = 255;
int     MOTOR_RIGHT_SPEED = 240;

// DC MOTORS PINS
int     MOTOR_1_PIN = 3;
int     MOTOR_1_DIRECTION = 12;
int     MOTOR_2_PIN = 11;

// ULTRASONIC SENSOR PINS
int     SENSOR_PIN_TRIG = 22;
int     SENSOR_PIN_ECHO = 24;

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
    pinMode(SENSOR_PIN_TRIG, OUTPUT);

    pinMode(MOTOR_1_DIRECTION, OUTPUT);

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
    digitalWrite(SENSOR_PIN_TRIG, LOW);
    delayMicroseconds(2);
    digitalWrite(SENSOR_PIN_TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(SENSOR_PIN_TRIG, LOW);

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
    // THE RIGHT MOTOR GOES BACKWARD
    digitalWrite(MOTOR_1_DIRECTION, HIGH);

    // WAITS FOR THE ROBOT TO TURN RIGHT. REGULATE THIS VALUE.
    delay(3000);

    // THE RIGHT MOTOR GOES FORWARD
    digitalWrite(MOTOR_1_DIRECTION, LOW);
    }

void moveForward()
    {
    // THE RIGHT MOTOR GOES FORWARD
    digitalWrite(MOTOR_1_DIRECTION, LOW);

    analogWrite(MOTOR_1_PIN, MOTOR_LEFT_SPEED);
    analogWrite(MOTOR_2_PIN, MOTOR_RIGHT_SPEED);
    }
