// Important Headers
#include <WiFi.h>
#include <esp_wifi_internal.h>
#include <esp_now.h>

#define ESPNOW_WIFI_IF ESP_IF_WIFI_STA 
#define LOOP_BUFFER 16

//Important Variables
uint8_t broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

int sent = 0;
int rec = 0;
uint8_t current_buffer = 0;
unsigned long time1 = 0;
unsigned long time2 = 0;

typedef struct message {
  uint8_t type;
  uint8_t dlc;
  uint8_t xcvrID;
  uint16_t msgNum;
  uint8_t payload[240];
  uint16_t checkSum;
} message;

//FUNCTIONS
void SendSerialData();
bool BroadcastData(message* m);
void UnitTest();
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status);
//---------------------------------CODE-------------------------------------//


void setup() {
  //Serial.begin(921600);

  // Init Serial Monitor
  Serial.begin(115200);
 
  WiFi.disconnect();

  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);
  
  /*Stop wifi to change config parameters*/
  esp_wifi_stop();
  esp_wifi_deinit();
  
  /*Disabling AMPDU is necessary to set a fix rate*/
  wifi_init_config_t my_config = WIFI_INIT_CONFIG_DEFAULT(); //We use the default config ...
  my_config.ampdu_tx_enable = 0;                             //... and modify only what we want.
  esp_wifi_init(&my_config);                                 //set the new config
  
  esp_wifi_start();
  
  /*You'll see that in the next subsection ;)*/
  esp_wifi_set_channel(1, WIFI_SECOND_CHAN_NONE);
  
  /*set the rate*/
  esp_wifi_internal_set_fix_rate(ESPNOW_WIFI_IF, true, WIFI_PHY_RATE_48M);
  
  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_register_send_cb(OnDataSent);
  //esp_now_register_recv_cb(OnDataRecv);
  
  // Register peer
  esp_now_peer_info_t peerInfo;
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  
  // Add peer        
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }




  Serial.println("Starting Unit Test");
  UnitTest();
  Serial.println();
  Serial.println("Unit Test Ended");

  //delay(5000);
  //Serial.println();
  //Serial.print("rec: ");
  //Serial.print(rec);
}


void loop() {
  
}
