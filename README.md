# Learning2019_2020
Learning Resources

[Learning Java Project](https://github.com/cpdupuis/LearningJavaProject)

[Setting up for FRC programming](http://wpilib.screenstepslive.com/s/currentCS/m/java/c/88899)

## If your setup is not working...

You can install Visual Studio Code from here: [https://code.visualstudio.com](https://code.visualstudio.com)

The Java Development Kit is available here: [http://jdk.java.net/13/](http://jdk.java.net/13/)


## Learning Arduino

We are using Arduino to learn about electronics and how to write code for programming electronic devices. Helpful links:

### Downloading the software

https://www.arduino.cc/en/Main/Software

Try the link `Windows app Requires Win 8.1 or 10`, and see if you are allowed to install that. You may need an administrator key, or you can download the link `Windows ZIP file for non admin install`

### Simple example: Blink

Try this example to verify that everything is working. You will need an Arduino and a USB cable that fits. https://www.arduino.cc/en/Tutorial/Blink

### Arduino language reference

Arduino "Sketches" are written in a variant of C++. Language reference: https://www.arduino.cc/reference/en/

### Online tutorials about Arduino

https://learn.adafruit.com/ladyadas-learn-arduino-lesson-number-0/intro

https://learn.adafruit.com/adafruit-arduino-lesson-2-leds


### Using the distance sensor

We are using a common ultrasonic distance sensor called an HC-SR04. See this page for details: https://www.makerguides.com/hc-sr04-arduino-tutorial/

Measuring distance with this sensor works like this:

* Set the TRIG pin to LOW
* Wait 2 microseconds
* Set the TRIG pin to HIGH
* Wait 10 microseconds
* Set the TRIG pin to LOW
* Measure how long it takes for the ECHO pin to switch from high to low voltage

On the Arduino:
* you can set pins to HIGH or LOW using the `digitalWrite` command.
* you can wait for for a number of microseconds using the `delayMicroseconds` command
* you can wait for a pin to change from high to low (or low to high) using the `pulseIn` command

Here is a sample implementation that returns the measured distance in centimeters.

```
// Returns distance in cm
long getDistance() {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  long echoTime = pulseIn(echo, HIGH);
  long distance = (echoTime/2) / 29.1;
  return distance;
}
```

In order to use this, you need to include these lines in your `setup()` function:

```
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
```

### Figuring out what your Arduino is doing

Use the `Serial.print` and `Serial.println` functions to write messages to the Serial monitor.

For example:
```
int b = 123;
Serial.print("Brightness:");
Serial.println(b);
```

will print out:
`Brightness:123`

## Working with servo motors

Follow this tutorial. https://learn.adafruit.com/adafruit-arduino-lesson-14-servo-motors/overview

## About delay() and multitasking

We have used the `delay()` function to wait for a while. For example, in our initial LED project, we used a delay between lighting up different LEDs. This works fine when the Arduino has one job to do, but what happens when you want it to do different things at the same time, such as blinking LEDs while running a servo, or blinking one LED fast and another slowly.

Generally, making a computer do multiple things at once is called "multitasking", and a lot of what goes into an operating system like Windows or Linux is code to make multitasking happen automatically. On the Arduino, there is no operating system, so you need to figure out how to multitask without any automatic help.

Let's look at an example. Suppose we have a program to blink an LED on and off slowly:

```cpp
void setup() {
  pinMode(5, OUTPUT);
}
void loop() {
    digitalWrite(5, HIGH);
    delay(1000);
    digitalWrite(5, LOW);
    delay(1000);
}
```

And we have another program to blink an LED on and off quickly:

```cpp
void setup() {
  pinMode(6, OUTPUT);
}
void loop() {
    digitalWrite(6, HIGH);
    delay(111);
    digitalWrite(6, LOW);
    delay(111);
}
```

Putting together these actions in sequnce doesn't work, because what happens is that the slow LED turns on for 500 ms and turns off for 500 ms, and then the fast LED blinks once (111 ms on and 111 ms off), and then the slow LED takes its turn again.

So, how could you make both the fast-blinking and slow-blinking LEDs blink at the same time?

## What time is it?

On the Arduino, you can find out the number of milliseconds since the board started using the `millis()` function, which returns a `long` value (a 32-bit integer).

How does this help? Recall that `loop()` runs over and over again, until you turn off the power to the Arduino.

If you keep track of what time it is when you turn on an LED, you can rewrite the slow-blinking program like this:

```cpp
long lastChangeTime = 0;
bool isLit = false;

void setup() {
  pinMode(5, OUTPUT);
}
void loop() {
  long currentTime = millis();                 // what time is it?
  if (currentTime - lastChangeTime > 500) {    // is it time to change the LED state?
    if (isLit) {
      digitalWrite(5, LOW);                    // turn off the LED
    } else {
      digitialWrite(5, HIGH);                  // turn on the LED
    }
    isLit = !isLit;                            // remember if the LED is on or off
    lastChangeTime = currentTime;              // remember when we changed the LED state
  }
}
```

Now can you write code that blinks 2 or more LEDs at different rates? HINT: you will need to use different variables to keep track of the lastChangeTime and isLit for each LED.

## Keeping things organized

If you've completed the task above, look at your code. For each LED, you have different variables for `isLit`, and `lastChangeTime`, and each has a different pin number that is turned on and off with `digitalWrite`. For 2 LEDs, this isn't too much of a problem, but once you're trying to control dozens of devices, it gets very difficult to figure out how these things relate.

This is where the idea of a `class` helps. A `class` is a recipe for creating instances of the class, where an instance (also called an "object") is a container that hold variables and methods.

This sounds complicated, but looking at an example should help.

Here is a very simple class:

```cpp
class SimpleLED {
public:                    // ignore "public" for now.
    int pinNumber;
    long lastChangeTime;
    long interval;
    bool isLit;
}
```

All this does is define a recipe that lets you create instances of the class SimpleLED, where each instance has a pinNumber, a lastChangeTime, and an isLit property.

You can create instances like this:

```cpp
SimpleLED red;
SimpleLED yellow;
SimpleLED green;

void setup() {
    red.pinNumber = 1;
    red.lastChangeTime = 0;
    red.period = 1000;
    red.isLit = false;
    
    yellow.pinNumber = 2;
    yellow.lastChangeTime = 0;
    yellow.interval = 300;
    yellow.isLit = false;
    
    green.pinNumber = 3;
    green.lastChangeTime = 0;
    green.interval = 100;
    green.isLit = false;
}
```

For a complete solution of this task using classes, see https://github.com/KentridgeRobotics/Learning2019_2020/blob/master/BlinkMany/BlinkMany.ino


# FRC Robot Resources

Drivers for Talon SRX: http://www.ctr-electronics.com/talon-srx.html#product_tabs_technical_resources

# GIT

Upload a Git project to github:

1. Create the git repository on your local machine, either using `git init` or through VS Code

2. On github.com, go to the page for your own repositories. In the dropdown menu on the top-right corner where your picture is, click "Repositories"

3. Click "New" button

4. Fill in the information. Give your repository a name that you will remember.

5. Click "Create Repository", and keep this page open!

6. Open PowerShell and navigate to the base directory of your project using "cd".

7. Follow the directions on the page you kept open for "…or push an existing repository from the command line"


# Arduino Serial communication

https://www.ladyada.net/learn/arduino/lesson4.html

# Making a RoboRio talk to an Arduino over Serial connection

https://www.youtube.com/watch?v=RMHCSwLIyqg


# Sample of making an Arduino talk to a RoboRio

This example assumes that the Arduino is sending packets over USB with the format:

`$11,22\n`

That is, each line starts with a `$`, followed by an integer, followed by a comma, followed by a second integer, followed by a newline.

The idea of this program is that it will change the motor speed for the x and y direction based on the x and y values taken from the first and second integer in the packet.

https://github.com/KentridgeRobotics/SampleRioArduino2019

