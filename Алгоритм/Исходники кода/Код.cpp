код по state machin
#include "AsyncMqttClient"
#include "ESPAsyncTCP"
#include "Arduino ESP8266 Core"
#include "ESP8622MQTTMesh"

ESP8266MQTTMesh mesh = ESP8266MQTTMesh::Builder(networks, mqtt_server, mqtt_port).build();
					//.setVersion(firmware_ver, firmware_id)
                    .setMeshPassword(password)
					.setMqttAuth(username, password)
                    .build();

wifi_conn networks[]
const char mqtt.by //server
int mqtt_port 1883
const char ququpi //username
const char 2zucerch5 //password (username)
const char 123456789 //пароль для подключению к другому узлу сетки

setMeshSSID(ssid)
const char *ssid // по умолчанию `esp8266_mqtt_mesh

setMeshPort(port)
int port 1884

setTopic(in_topic, out_topic)
const char user/ququpi/  //in_topic
const char *out_topic //по умолчанию esp8266-out/

//setMeshSSL(cert, cert_len, key, key_len, fingerprint)


publish(topic, payload, msgCmd)
publish_node(topic, payload, msgCmd)
////

int getCommand();
Watering userWatering;
void sendMessage();
	void receivedCallback( uint32_t from, String &msg ){
		Serial.printf("startHere: Received from user/ququpi msg=%s\n", from, msg.c_str());
		waterringTimeoutInSec = msg; 
	
////

#define NO_CONNECTION_STATE 0
#define WAITING_STATE 1
#define SENSOR_ANALISYS_STATE 2
#define CHECK_WATER_STATE 3
#define WATERING_ON_STATE 4
#define ERROR_STATE 5

#define CONNECT_CMD '0'
#define GET_MST_CMD '1'
#define WTR_ON_CMD '2'
#define WTR_OFF_CMD '3'
#define WAT_LEV_OK_CMD '4'
#define WAT_LEV_BAD_CMD '5'
#define WAIT_WTR_CMD '6'
#define DIS'CONNECT'_CMD '7'

	
int watering  
int state = SENSOR_ANALISYS_STATE;

void setup(){
}
int getCommand(){
	int cmd = Serial.read();
	return cmd;
}
void loop(){
		int cmd = getCommand();
		switch(state){
			case SENSOR_ANALISYS_STATE:{
				senAnSt_handler(cmd);
				break;
			}
			case WAITING_STATE:{
				waitSt_handler(cmd);
				break;
			}
			case CHECK_WATER_STATE:{
				ChWtSt_handler(cmd);
				break;
			}
			case WATERING_ON_STATE:{
				WtOnSt_handler(cmd);
				break;
			}
			case ERROR_STATE:{
				ErrorSt_handler();
				break;
			}
			case NO_CONNECTION_STATE:{
				noConSt_handler();
				break;
			}
			


void chWtSt_handler(){

 bool waterLevel = checkWaterLevel();
 if (waterLevel){
  waterring_start_time = millis();
  state = WATERING_ON_STATE; 
 }
 else{
  state = ERROR_STATE;
 }
}


#define MSEC_IN_SEC 1000
int waterringTimeoutInSec = 10;



void wtOnSt_handler(int cmd){
 uint32_t now = millis();
 pump_turn_on();
 
 if (abs(now - waterring_start_time) >= waterringTimeoutInSec*MSEC_IN_SEC){
  pump_turn_off();
  state = WAITING_STATE;
 }
 else{
  bool waterLevel = checkWaterLevel();
  if (!waterLevel){
   pump_turn_off();
   state = ERROR_STATE;
  }
 }
}