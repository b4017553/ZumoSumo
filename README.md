# ZumoSumo

## GUI

The GUI was build in processing using the G4P library. The UI shows the score of the sumo match currently running.
The GUI will have to be restart to restart a match.

## How To Build and Run
### Upload to the Zumo Robot
1. Extract the sumoZumoProject folder and open the sumoZumoProject.ino file in the Arduino IDE.
2. Ensure the Board is set to Pololu A-Star 32U4 board.
3. Plug the robot in via USB
4. Drop down the board name and select the COM port the Zumo is connected to
5. Select upload on the sketch to upload it to the Zumo 
Once completed unplug the robot
### Connecting the Xbee module
Please ensure the xbee module is connected via usb, this is so the GUI can detect it on the specified COM port.
### Running the GUI
1. find the sumoGUI.pde in the sumoGUI folder and open it in processing.
2. Check the COM port is set to the correct port for the xbee on line 14 of the sketch.

`String portName = "COM6";`

This can be checked by opening XCTU and checking the COM the port the xbee is connected to.

3. Press the play button the save the GUI.
## Sumo ring
The sumo ring is made with black electrical tape on a white surface.
Ensure there are no objects other than the opponent in the immediate vacinity of the sumo ring.
## Starting a match
To start a match put the Zumo in the center of the ring and press the c button on the Zumo.
## During the match
The Zumo will search the sumo ring for its opponent, once found it will drive towards the opponent adjusting from left to right if they move. Once an opponent is pushed over the line the score will be updated in the GUI.
The Zumo will then turn around and drive to the centre before attempting to go again.
## Seeing the Score
The score will be shown in the GUI.
## Demonstration Videos
This demos shows how the Zumo can find and push an object out of the ring and the score will be updated on th GUI.
It also shows how the Zumo can follow the object.

https://user-images.githubusercontent.com/72078518/236359038-75b1fd8c-777a-4818-86cf-07dba45e9cf9.mp4

https://user-images.githubusercontent.com/72078518/236359282-15f71ef2-3e32-4a5d-bdd6-76df9591575d.mp4


# References
1. LiquidCrystal - Arduino Reference. (n.d.). Arduino. Retrieved May 5, 2023, from http://arduino.cc/en/Reference/LiquidCrystal
2. Staff, M. (2022, June 6). Create Custom Characters using a 16x2 Liquid Crystal Display. Digi-Key Electronics. Retrieved May 5, 2023, from https://www.digikey.co.uk/en/maker/blogs/2022/create-custom-characters-using-a-common-16x2-liquid-crystal-display
3. Brown, A. (2016, October 16). Zumo 32U4 – Using the Proximity Sensors to Point Towards the Closest Object | A. Brown Design. A. Brown Design. Retrieved May 5, 2023, from http://www.abrowndesign.com/2016/10/16/zumo-32u4-using-the-proximity-sensors-to-point-towards-the-closest-object/
4. Pololu - 3.d. Inertial sensors (accelerometer, magnetometer, and gyro). (n.d.). Pololu. Retrieved May 5, 2023, from https://www.pololu.com/docs/0J57/3.d
5. Pololu Zumo 32U4 Robot User’s Guide. (n.d.). Pololu. Retrieved May 5, 2023, from https://www.pololu.com/docs/0J63/all#3
