![SU Logo](/SU_Logo/SU_logo.png "Stockholm University")

# Design for Emerging Technologies (DET), Stockholm University VT25 Lab Session 4: Unity-Esp32 Communication

## Unity Instructions

### Before you start...

 - Make sure you have the [Unity Game Engine](https://www.arduino.cc/en/software) version 2022.3.53f1 or above
 - Make sure you have installed the Android modules (Tip: On Unity Hub go to "Installs", select the Gear icon on the correct install and then "Add Modules". If "Android Build Support" does not say "Installed" under the "Download Size" column, tick the box on the left and click the "Install" button)
 - On the "Projects" tab, click the "Add" button on the top right corner, and then "Add project from disk". Choose the "SU_ESP32-Unity_Communication" folder inside this repository. The project should now be added to your 

### Once Unity is installed and the project opened...

- If you get prompted to restart the Unity Editor select "Ignore"
- If you get prompted to choose the OVR hand, select either "Remind me later" or "Keep using OVR Hand"
- Go to "File"-> "Build Settings". Once a new window opens, locate and click on "Android" under "Platform" on the left side of the window. Once that is done click on "Switch Platform". Once that is done you can close the "Build Settings" window.
  - ***Note: If the "Android" option is greyed out, it means you don't have the required modules installed. Refer back to the "Before you start" section to solve this***
- Once you have done finished these steps, open either the "WebSocket Client Example" or "WebSocket Client Example XR" scenes.

### Setting up the project

- Once you have one of the scenes open, locate the "WebSocketClient Manager" GameObject. It should have a "Web Socket Client" script attached to it.
- Replace the "IP Address" and "Port" with the right values from the ESP32
  - ***Note: You can get the "IP Address" using the Serial Monitor in the Arduino IDE and the "Port" from the "ESP32_Server.ino" file***

![Project Files](/DET_Lab4_Unity/rsc/ClientScript.png "Stockholm University")

- Assuming your ESP32 is correctly setup, you can now either hit the "Play" button in Unity (if you are using the "WebSocket Client Example" scene) or build a new apk and deploy it to your device (if you are using the "WebSocket Client Example XR")

### Highlights of the project

The "DET Lab Files" folder contains all the required files for this demo.

![Project Files](/DET_Lab4_Unity/rsc/UnityFolder.png "Stockholm University")

There is only 1 script that truly matters and that is the "WebSocketClient.cs" script inside the "Scripts" folder. This is responsible for the communication between the device running Unity and the ESP32. Examine it to better understand how it works.

There are 2 Unity Scenes created for this project.

- "WebSocket Client Example" can be ran without a VR headset and does the exact same thing as the other Scene
- "WebSocket Client Example XR" can only be run with a Meta Quest device (or with a simulator).

---
Made by: António Pinheiro Braga - antonio.braga@dsv.su.se