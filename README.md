# Introduction to Robotics (2021 - 2022)
Introduction to Robotics laboratory homeworks, taken in the 3rd year at the Faculty of Mathematics and Computer Science, University of Bucharest. Each homework includes requirements, implementation details, code and image files.
  
## Homework 1 ✔️

**Components**: RBG led (1 minimum), potentiometers (3 minimum), resistors and wires (per logic)  

**Technical Task**: Use a separate potentiometer in controlling each of the
color of the RGB led (Red, Green and Blue). The control must be done
with digital electronics (aka you must read the value of the potentiometer with Arduino, and write a mapped value to each of the pins connected
to the led.

**Solution:**
![WhatsApp Image 2021-10-27 at 9 18 30 AM](https://user-images.githubusercontent.com/60759315/139013667-1509cace-229a-4d52-894d-f3c2f922ce4f.jpeg)
https://youtu.be/06yYPAwsBjg

## Homework 2 ✔️

**Components**: 5 LEDs, 1 button, 1 buzzer, resistors and wires (per logic)

**General  description**: Building the traffic lights for a crosswalk. You will use 2 LEDs to represent the traffic lights for people (red and green)and 3 LEDs to represent the traffic lights for cars (red, yellow and green). See the states it needs to go through. If anything is not clear, ask. Also,see the uploaded video (the intervals are different, but the states flow isthe same). It’s a traffic lights system for people and cars - don’t overthink it.

**Solution:**
![WhatsApp Image 2021-11-04 at 2 49 37 PM](https://user-images.githubusercontent.com/60759315/140316640-a8abae61-3d24-4605-8acb-6803dff5a421.jpeg)
https://youtu.be/n8lKOH2N9yY

## Homework 3 ✔️

**Components**: a buzzer and a 7-segment display (or a led bar / or 8 leds in a row that simulate a led bar)

**Task**: should detect EMF (check body and near outlets.  DO NOT IN-SERT INTO OUTLET). It should print the value on the 7-segment display (or light the led bar) and should make a sound based on the intensity.

**Solution:**
![1636628459160](https://user-images.githubusercontent.com/60759315/141287188-9761d1a1-453c-40aa-89b6-fd98ca2b75ef.jpg)
https://youtu.be/yYH_rGTicU8 

## Homework 4 ✔️

**Components**: a  joystick,  a  4  digit  7-segment  display,  a  74hc595  shiftregister

**Task**: First  state:   you  can  use  a  joystick  axis  to  cycle  through  the  4digits; using the other axis does nothing.  A blinking decimal point showsthe current digit position.  When pressing the button (must use interruptfor  maximum  points!),  you  lock  in  on  the  selected  digit  and  enter  thesecond state.  In this state, the decimal point stays always on, no longerblinking and you can no longer use the axis to cycle through the 4 digits.Instead, using the other axis, you can increment on decrement the numberon the current digit.  Pressing the button again returns you to the previousstate.  For bonus, save the last value in eeprom and load it when startingarduino.  Also, keep in mind that when changing the number, you mustincrement it for each joystick movement - it should not work continuoslyincrement if you keep the joystick in one position.

**Solution**: 
![WhatsApp Image 2021-12-01 at 10 22 03 PM](https://user-images.githubusercontent.com/60759315/144308461-8387ffc2-31bd-4f5c-bd48-bd0a712d9d6e.jpeg)
https://youtu.be/vmq76rrw_zk

## Homework 5 - Matrix project ✔️

**Task Requirements**: Create a game. It must be fun and intuitive, and also remember that it is your game! Pick something that you like and have fun creating it.

**Components**: 16 Segment Led Display, 8x8 Led Matrix, MAX7219 Driver, Joystick, Buzzer, 10k Potentiometer, Capacitors, Resistors and Wires.

**Solution**:  
![WhatsApp Image 2021-12-23 at 2 43 47 PM](https://user-images.githubusercontent.com/60759315/147242427-0460abba-9f7e-4c8b-aaa5-0e18c946136d.jpeg)
https://youtu.be/DOaoat5Dq_A

