# IoT-based-traffic-light-control-and-monitoring-system-using-esp32-AWS-and-Blynk-IoT
IoT based Traffic light control system using ESP32, AWS/Blynk Iot.

There are three different variations to yhis project. the are :

# AWS Integration :

The esp32 controller sends ultrasonic signal counts to AWS server throught publish/subscribe protocol.

here is a youtube video link to set up your **"Thing"** in AWS:

https://youtu.be/sPVCXR9bWJQ

As you can see in the code for AWS open both files(two tabs) in a Sketch in Arduino IDE and select ESP32 Developer kit to upload the code into esp32.

<img width="937" height="368" alt="image" src="https://github.com/user-attachments/assets/386333bf-46b4-4ecf-9edb-d365728dcd61" />

paste the necessary details that are blanck in the code before uploading( certificates, Thing name, publish, subbscribe, wifi credentials, ect,.)

To store the data in AWS you have to create a database and add pipelines. refer youtube videos.

# Blynk Iot:

signals are send to Blynk IoT app which is available even in mobile phones(play store, app store).

here is a video:

https://youtu.be/W1xG_XJb0FU

you can add four different counters in the app for ultrasonic sensors.

Fill all the required details and upload to esp32.

# Only Hardware

Just paste the code in Arduino Ide and upload it. there is no cloud integration in this variation

# Circuit:

![Circuit-for-Density-Based-Traffic-Light-Controller-with-ESP32](https://github.com/user-attachments/assets/41ee6f12-9d6b-430d-959f-5d42503d58dd)

# Working video:

https://github.com/user-attachments/assets/702e0f9f-165a-4449-acf8-807891c4f7b4



