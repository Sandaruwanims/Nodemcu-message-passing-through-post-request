#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>

const String ROBOT_ID = "robot_1";
const String LINK = "http://192.168.8.101:8084/Robot_Debug_Monitor/RobotSerialData";
const char* USER_NAME = "Dialog 4G";
const char* PASSWORD = "EJ4735D2Q83";

int sensorValue = 0;

void setup() {

  Serial.begin(115200);                                  //Serial connection
  WiFi.begin(USER_NAME, PASSWORD);   //WiFi connection

  while (WiFi.status() != WL_CONNECTED) {  //Wait for the WiFI connection completion

    delay(500);
    Serial.println("Waiting for connection");

  }

}

void loop() {

  String message = "motorSpeed = " + String(sensorValue);
  printSerial(message);
  sensorValue = sensorValue+1;
  delay(10000);  //Send a request every 10 seconds

}

void printSerial(String message){
  
     String payload = "message=" + ROBOT_ID +":" + message; //message format robot_id:message
     if(WiFi.status()== WL_CONNECTED){   //Check WiFi connection status
    
       HTTPClient http;    //Declare object of class HTTPClient
       http.setReuse(false);
       http.begin(LINK);      //Specify request destination
       http.addHeader("Content-Type", "application/x-www-form-urlencoded");  //Specify content-type header
       http.addHeader("Connection", "close");
    
       int httpCode = http.POST(payload);   //Send the request
    
       String reply = http.getString();   //Get the response payload
       
       Serial.println(httpCode);   //Print HTTP return code
       Serial.println(reply);    //Print request response payload
    
       http.end();  //Close connection
    
     }else{
    
        Serial.println("Error in WiFi connection");   
    
     }
  }
