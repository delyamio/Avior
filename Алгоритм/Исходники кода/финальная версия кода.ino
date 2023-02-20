#include <Arducam_Mega.h> 
 
#include <AsyncPrinter.h> 
#include <DebugPrintMacros.h> 
#include <ESPAsyncTCP.h> 
#include <ESPAsyncTCPbuffer.h> 
#include <SyncClient.h> 
#include <async_config.h> 
#include <tcp_axtls.h> 
 
#include <ESP8266MQTTMesh.h> 
 
 
 
ESP8266MQTTMesh mesh = ESP8266MQTTMesh::Builder(networks, mqtt_server, mqtt_port).build(); 
             //.setVersion(firmware_ver, firmware_id) 
                    .setMeshPassword(password) 
               .setMqttAuth(username, password) 
                    .build(); 
 
wifi_conn networks[] 
const char mqtt_server mqtt.by  
int mqtt_port 1883 
const char *username ququpi  
const char *password 2zucerch5 
 
setMeshPassword(password) 
const char *password 123456789 //пароль для подключению к другому узлу сетки 
 
setMeshSSID(ssid) 
const char *ssid `esp8266_mqtt_mesh 
 
setMeshPort(port) 
int port 1884 
 
setTopic(in_topic, out_topic, in_topic_time, out_topic_time) 
const char *in_topic user/ququpi/in/   
const char *out_topic user/ququpi/out/ 
const char *in_topic_time user/ququpi/in/time/ 
const char *out_topic_time user/ququpi/out/time/ 
 
//setMeshSSL(cert, cert_len, key, key_len, fingerprint) 
 
void callback(const char *topic, const char *payload) 
 
publish(topic, payload, msgCmd) 
publish_node(topic, payload, msgCmd) 
const char *topic SENSOR_MST_INDICATORS 
const char *payload REAL_MST_INDICATORS 
 
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
#define DIS_CONNECT_CMD '7' 
 
  
int watering = D5; 
int state = SENSOR_ANALISYS_STATE; 
int get_mst_cmd_1= A0; 
int get_mst_cmd_2= A0; 
int get_mst_cmd = (get_mst_cmd_1 + get_mst_cmd_2)/2; 
 
void setup(){ 
} 
pinMode(watering, OUTPUT); 
 
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
  int get_mst_cmd_1= A0; 
  int get_mst_cmd_2= A0; 
  int get_mst_cmd = (get_mst_cmd_1 + get_mst_cmd_2)/2; 
}   
 
int waterringTimeoutInSec 
 
int getCommand(){ 
  if int cmd = (in_topic_time):{ 
    waterringTimeoutInSec = in_topic_time; 
  } 
  else{ 
    waterringTimeoutInSec = 10; 
  } 
return; 
} 
 
void chWtSt_handler(){ 
 int waterLevel = A0; 
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
  
void wtOnSt_handler(int cmd){ 
 uint32_t now = millis(); 
 pump_turn_on(); 
 digitalWrite(watering, HIGH); 
 delay(1000); 
  
 if (abs(now - waterring_start_time) >= waterringTimeoutInSec*MSEC_IN_SEC){ 
  pump_turn_off(); 
  digitalWrite(watering, LOW); 
  state = WAITING_STATE; 
 } 
 else{ 
  bool waterLevel = checkWaterLevel(); 
  if (!waterLevel){ 
    digitalWrite(watering, LOW); 
   pump_turn_off(); 
   state = ERROR_STATE; 
  }