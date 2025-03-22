#include <esp_now.h>
#include <Wire.h>
#include <WiFi.h>
//#include <M5StickCPlus.h>

//timer for transmission freq
unsigned long timer = 0;
// select the input pin for the potentiometer

    int id; // must be unique for each sender board     
    //gyro
    float anglex = 0; 
    float angley = 0;
    float anglez = 0; 
    //accelerometer
    float accx = 0;
    float accy = 0;
    float accz = 0;
    //pressure sensor1
    int pressSensor;
    //pressure sensor2  
     int button_a;
    //battery voltage
    float voltage = 0;
   
// REPLACE WITH THE RECEIVER'S MAC Address
uint8_t broadcastAddress[] = {0x94, 0xB9, 0x7E, 0xD2, 0x14, 0x1C};

// Structure example to send data
// Must match the receiver structure
typedef struct struct_message {
    int id; // must be unique for each sender board     
    //gyro
    float anglex; 
    float angley; 
    float anglez; 
    //accelerometer
    float accx;
    float accy;
    float accz;
    //pressure sensor
    int pressSensor;
    //button  
    int button_a;
    //battery voltage
    float voltage;
} struct_message;

// Create a struct_message called myData
struct_message myData;

// Create peer interface
esp_now_peer_info_t peerInfo;

// callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Success" : "Fail");
}

void setup() {
 

  // Init Serial Monitor
  Serial.begin(115200);

  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Register peer
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  
  // Add peer        
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
}

void loop() {
  if((millis()-timer) > 10) {

    // read the analog / millivolts value for pin 2:
  int analogValue1 = analogRead(33);
  int analogValue2 = analogRead(34);
    


    // Set values to send
    myData.id = 3; // Changed to reflect Sender 3
    myData.anglex = anglex;
    myData.angley = angley;
    myData.anglez = anglez;
    myData.accx = accx;;
    myData.accy = accy;
    myData.accz = accz;
    myData.pressSensor = analogValue1;
    myData.button_a = analogValue2;
    myData.voltage = voltage;
   



    // Send message via ESP-NOW
    esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
    if (result == ESP_OK) {
      Serial.println("Delivered");
    }
    else {
      Serial.println("Error sending the data");
      Serial.println(esp_err_to_name(result)); // Print error code
    }
    timer = millis();
  }
}





