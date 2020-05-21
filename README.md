# Advanced Blind Stick Using Adruino Nano

The people who use ordinary stick as a tool for direction, when they walk they are not able to identify that there is any obstacle in their way without the contact of the object and the stick.


So with the power of Arduino and different sensors, here we develop a tool which can serve as blind stick being more efficient and helpful than the conventional one.This will assist the blind person during the walk and provides an alarm if any hurdle is detected within the set range.


The blind stick is integrated with ultrasonic sensor along with LDR and water sensor. Ultrasonic sensor is used to detect obstacles ahead using ultrasonic waves. On sensing obstacle, the sensor passes this data to Arduino nano. The Arduino nano then processes this data and calculates if the obstacle is close enough. If the circuit is close the Arduino nano sends the warning in form of voice. If the obstacle is not that close the circuit does nothing. A buzzer is also used so that if the water sensor detects water the buzzer will alert the person. The stick also includes a vibrator. If any obstacle is detected, so along with the two sensors this vibrator is also used to alert the blind. The system has one more advanced feature integrated to help the blind find their stick if the stick is lost by using IR remote.
