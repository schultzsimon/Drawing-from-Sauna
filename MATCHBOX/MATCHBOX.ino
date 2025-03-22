#include <esp_now.h>
#include <Wire.h>
#include <WiFi.h>
#include <M5StickCPlus.h>

//timer for transmission freq
unsigned long timer = 0;
// select the input pin for the potentiometer

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
  // Init M5StickC Plus.
  M5.begin();           
  M5.Imu.Init();
  M5.Lcd.setRotation(3);     // Rotate the screen.
  M5.Lcd.setCursor(50, 15);  // set the cursor location.
  M5.Lcd.setCursor(30, 30);
  M5.Lcd.println("SENDER MATCHBOX #1"); // Changed to reflect MATCHBOX

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
    
    //read gyro and Accelerometer data
    M5.Imu.getGyroData(&anglex, &angley, &anglez);
    M5.Imu.getAccelData(&accx, &accy, &accz);
    //read the pressure sensor
    int sensorValue = (analogRead(36)); 
    Serial.println(sensorValue); 
    //read Battery Voltage
    float charge = M5.Axp.GetVBusVoltage();
    Serial.println(charge);

    // Set values to send
    myData.id = 1; // Changed to reflect Sender 1
    myData.anglex = anglex;
    myData.angley = angley;
    myData.anglez = anglez;
    myData.accx = accx;;
    myData.accy = accy;
    myData.accz = accz;
    myData.pressSensor = sensorValue;
    myData.button_a = button_a;
    myData.voltage = charge;
   


    M5.update();  // Read the press state of the key.
    if (M5.BtnA.wasPressed()) {  // If the button A is pressed.
        button_a = 1;
    }
    if (M5.BtnA.wasReleased()) {
        button_a = 0;
    }

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





