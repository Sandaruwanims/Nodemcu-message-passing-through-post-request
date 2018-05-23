#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>

String message;
int sensorValue = 0;
String robotId="robot_3";

void setup() {

  Serial.begin(115200);                                  //Serial connection
  WiFi.begin("Kaushal", "Oy5@s221");   //WiFi connection

  while (WiFi.status() != WL_CONNECTED) {  //Wait for the WiFI connection completion

    delay(500);
    Serial.println("Waiting for connection");

  }

}

void loop() {

 message = "motor speed= " + String(sensorValue);
 Serial.println(message);
 if(WiFi.status()== WL_CONNECTED){   //Check WiFi connection status

   HTTPClient http;    //Declare object of class HTTPClient
   http.setReuse(true);
   http.begin("http://192.168.8.103:8084/Robot_Debug_Monitor/RobotSerialData");      //Specify request destination
   http.addHeader("Content-Type", "application/x-www-form-urlencoded");  //Specify content-type header
   http.addHeader("Connection", "keep-alive");

   int httpCode = http.POST("message="+robotId+":"+message);   //Send the request

   String payload = http.getString();                  //Get the response payload
   
   Serial.println(httpCode);   //Print HTTP return code
   Serial.println(payload);    //Print request response payload

   http.end();  //Close connection

 }else{

    Serial.println("Error in WiFi connection");   

 }
  sensorValue = sensorValue+1;
  delay(10000);  //Send a request every 30 seconds

}
