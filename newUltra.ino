/*
 * Copyright (c) 2021, Micropolis
 * All rights reserved.
 
 * Created on Sun Aug 22 10:30:17 2021
 * @author: Khaled Gabr
 
 * Redistribution and use in source and binary forms, with or without 
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, 
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice, 
 *    this list of conditions and the following disclaimer in the documentation 
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, 
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR 
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR 
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; 
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR 
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, 
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
/*
 *  ULTRASONIC ROSSERIAL Node PUBLISHER test app
 *
 *  Copyright 2021  Micropolis Team
 *  http://www.micropolis.ae
 * 
 */
 #include <ros.h>
 #include <ros/time.h>
 #include <sensor_msgs/Range.h>
 
 ros::NodeHandle  nh;
 sensor_msgs::Range sonar_msg;
 ros::Publisher pub_sonar( "rangeSonar", &sonar_msg);
 float sensoReading = 0;
   
// this constant won't change. It's the pin number of the sensor's output:
const int trigPin = 7;
const int echoPin= 5;

char frameid[] ="/sonar_ranger";
void setup() {
  nh.getHardware()->setBaud(9600);

  // initialize serial communication:
//  Serial.begin(9600);
    nh.initNode();
    nh.advertise(pub_sonar);
    pinMode(trigPin,OUTPUT);
    pinMode(echoPin,INPUT);
    sonar_msg.radiation_type = sensor_msgs::Range::ULTRASOUND;
    sonar_msg.header.frame_id =  frameid;
    sonar_msg.field_of_view = (10.0/180.0) * 3.14;
    sonar_msg.min_range = 0.0;
    sonar_msg.max_range = 10.0;
    
}
int duration;
unsigned long publisher_timer;
void loop() {
    sensoReading = 0 ;
    
  // establish variables for duration of the ping, and the distance result
  // in inches and centimeters:


if ((millis() - publisher_timer)> 50 ) 
   {
    digitalWrite(trigPin,LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin,HIGH);
    delayMicroseconds(10);
    
   duration = pulseIn(echoPin, HIGH);
   sensoReading = duration *0.342/2000;
   //sensoReading = getDistance;
   sonar_msg.range = sensoReading;
   //Serial.println(sensoReading);
   sonar_msg.header.stamp = nh.now();
   pub_sonar.publish(&sonar_msg);
   publisher_timer = millis(); //publish once a second
   
   }
   
  nh.spinOnce();
    
}
