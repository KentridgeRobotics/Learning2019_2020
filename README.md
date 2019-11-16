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
void loop() {
    digitalWrite(5, HIGH);
    delay(1000);
    digitalWrite(5, LOW);
    delay(1000);
}
```

And we have another program to blink an LED on and off quickly:

```cpp
void loop() {
    digitalWrite(6, HIGH);
    delay(111);
    digitalWrite(6, LOW);
    delay(111);
}
```

Putting together these actions in sequnce doesn't work, because what happens is that the slow LED turns on for 500 ms and turns off for 500 ms, and then the fast LED blinks once (111 ms on and 111 ms off), and then the slow LED takes its turn again.

So, how could you make both the fast-blinking and slow-blinking LEDs blink at the same time?
