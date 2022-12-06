
#include <Arduino.h>
#include "DHT.h"
#include "Colors.h"
#include "IoTicosSplitter.h"
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <PubSubClient.h>

// IoT Device
String dId = "123456";
String webhook_pass = "tK8qXCCzdW";
String webhook_endpoint = "http://192.168.100.7:3001/api/getdevicecredentials";
const char *mqtt_server = "192.168.100.7";

//PINS
#define led LED_BUILTIN
#define DHTPIN 13     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
#define DHTPENABLE 12     // Digital pin connected to the DHT GND sensor

// WiFi
const char *wifi_ssid = "Jasson";
const char *wifi_password = "telerin1234";

//Functions definitions
bool get_mqtt_credentials();
void check_mqtt_connection();
bool reconnect();
void process_sensors();
void process_actuators();
void send_data_to_broker();
void callback(char *topic, byte *payload, unsigned int length);
void process_incoming_msg(String topic, String incoming);
void print_stats();
void clear();

// Global Vars
WiFiClient espclient;
PubSubClient client(espclient);
DHT dht(DHTPIN, DHTTYPE);
IoTicosSplitter splitter;
long lastReconnectAttemp = 0;
long varsLastSend[20];
long varsLastRead[20];
String last_received_msg = "";
String last_received_topic = "";


float prev_temp_in  = 37;
float prev_hum_in   = random(40, 60);


DynamicJsonDocument mqtt_data_doc(2048);


// the setup function runs once when you press reset or power the board
void setup() {

  Serial.begin(115200);
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(led, OUTPUT);
  delay(100);

  clear();

  Serial.println();
  Serial.println("Set up ready ...");
  delay(2000); 

  clear();

  Serial.print(underlinePurple + "\n\n\nWiFi Connection in Progress" + fontReset + Purple);

  int counter = 0;
  // WiFi.begin(ssid, pass);
  WiFi.begin(wifi_ssid, wifi_password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
    counter++;

    if (counter > 10)
    {
      Serial.print("  ⤵" + fontReset);
      Serial.print(Red + "\n\n         Ups WiFi Connection Failed :( ");
      Serial.println(" -> Restarting..." + fontReset);
      delay(2000);
      ESP.restart();
    }
  }
  
  // Printing local ip
  Serial.print("  ⤵" + fontReset);
  Serial.println(boldGreen + "\n\n         WiFi Connection -> SUCCESS :)" + fontReset);
  Serial.print("\n         Local IP -> ");
  Serial.print(boldBlue);
  Serial.print(WiFi.localIP());
  Serial.println(fontReset);

  client.setCallback(callback);

  digitalWrite(led, HIGH);
  delay(100);
  digitalWrite(led, LOW);

}

// the loop function runs over and over again forever

int count = 0;
void loop() {
  check_mqtt_connection();
}

//USER FUNTIONS ⤵
void process_sensors()
{
  long now = millis();

// ##########TEMPERATURA INTERNA##################v
  if (now - varsLastRead[0] >= 5 * 1000) //Read the sensor each 5 seconds
  {

    varsLastRead[0] = millis();

    // SIMULATOR
    long temp_in = prev_temp_in + random(0, 2) - random(0, 2);
    // READ SENSOR
    // float temp_in = dht.readTemperature();
    if (isnan(temp_in)){
      mqtt_data_doc["variables"][0]["last"]["save"] = 0;
    }
    else{
      //save temp?
      float dif = temp_in - prev_temp_in;
      if (dif < 0)
      {
        dif *= -1;
      }

      if (dif >= 0.01)
      {
        mqtt_data_doc["variables"][0]["last"]["save"] = 1;
      }
      else
      {
        mqtt_data_doc["variables"][0]["last"]["save"] = 0;
      }
    
      mqtt_data_doc["variables"][0]["last"]["value"] = temp_in;
      prev_temp_in = temp_in;
    }
  }

// ##########HUMEDAD INTERNA##################
  if (now - varsLastRead[1] >= 5 * 1000) //Read the sensor each 5 seconds
  {
    digitalWrite(led, HIGH);
    digitalWrite(DHTPENABLE, LOW);
    delay(100);

    varsLastRead[1] = millis();

    float hum_in = prev_hum_in +  + random(0, 2) - random(0, 2);
    // float hum_in = dht.readHumidity();

    if (isnan(hum_in)){
      mqtt_data_doc["variables"][1]["last"]["save"] = 0;
    }
    else{
      //save hum?
      float dif = hum_in - prev_hum_in;
      if (dif < 0)
      {
        dif *= -1;
      }

      if (dif >= 0.01)
      {
        mqtt_data_doc["variables"][1]["last"]["save"] = 1;
      }
      else
      {
        mqtt_data_doc["variables"][1]["last"]["save"] = 0;
      }
    
      mqtt_data_doc["variables"][1]["last"]["value"] = hum_in;
      prev_hum_in = hum_in;
    }
  }
}


// ACTUATORS
// void process_actuators()
// {
//   if (mqtt_data_doc["variables"][2]["last"]["value"] == "true")
//   {
//     digitalWrite(led, HIGH);
//     mqtt_data_doc["variables"][2]["last"]["value"] = "";
//     varsLastSend[4] = 0;
//   }
//   else if (mqtt_data_doc["variables"][3]["last"]["value"] == "false")
//   {
//     digitalWrite(led, LOW);
//     mqtt_data_doc["variables"][3]["last"]["value"] = "";
//     varsLastSend[4] = 0;
//   }
// }


// TEMPLATE
void process_incoming_msg(String topic, String incoming){

  last_received_topic = topic;
  last_received_msg = incoming;

  String variable = splitter.split(topic, '/', 2);

  for (int i = 0; i < mqtt_data_doc["variables"].size(); i++ ){

    if (mqtt_data_doc["variables"][i]["variable"] == variable){
      
      DynamicJsonDocument doc(256);
      deserializeJson(doc, incoming);
      mqtt_data_doc["variables"][i]["last"] = doc;

      long counter = mqtt_data_doc["variables"][i]["counter"];
      counter++;
      mqtt_data_doc["variables"][i]["counter"] = counter;

    }

  }

  // process_actuators();

}

void callback(char *topic, byte *payload, unsigned int length)
{

  String incoming = "";

  for (int i = 0; i < length; i++)
  {
    incoming += (char)payload[i];
  }

  incoming.trim();

  // process_incoming_msg(String(topic), incoming);

}

void send_data_to_broker()
{

  long now = millis();

  for (int i = 0; i < mqtt_data_doc["variables"].size(); i++)
  {

    if (mqtt_data_doc["variables"][i]["variableType"] == "output")
    {
      continue;
    }

    int freq = mqtt_data_doc["variables"][i]["variableSendFreq"];

    if (now - varsLastSend[i] > freq * 1000)
    {
      varsLastSend[i] = millis();

      String str_root_topic = mqtt_data_doc["topic"];
      String str_variable = mqtt_data_doc["variables"][i]["variable"];
      String topic = str_root_topic + str_variable + "/sdata";

      String toSend = "";

      serializeJson(mqtt_data_doc["variables"][i]["last"], toSend);

      client.publish(topic.c_str(), toSend.c_str());


      //STATS
      long counter = mqtt_data_doc["variables"][i]["counter"];
      counter++;
      mqtt_data_doc["variables"][i]["counter"] = counter;

      // digitalWrite(led, HIGH);
      // delay(500);
      // digitalWrite(led, LOW);

    }
  }
}

bool reconnect()
{

  if (!get_mqtt_credentials())
  {
    Serial.println(boldRed + "\n\n      Error getting mqtt credentials :( \n\n RESTARTING IN 10 SECONDS");
    Serial.println(fontReset);
    delay(10000);
    ESP.restart();
  }

  //Setting up Mqtt Server
  client.setServer(mqtt_server, 1883);

  Serial.print(underlinePurple + "\n\n\nTrying MQTT Connection" + fontReset + Purple + "  ⤵");

  String str_client_id = "device_" + dId + "_" + random(1, 9999);
  const char *username = mqtt_data_doc["username"];
  const char *password = mqtt_data_doc["password"];
  String str_topic = mqtt_data_doc["topic"];

  if (client.connect(str_client_id.c_str(), username, password))
  {
    Serial.print(boldGreen + "\n\n         Mqtt Client Connected :) " + fontReset);
    delay(2000);

    client.subscribe((str_topic + "+/actdata").c_str());

    return true;
  }
  else
  {
    Serial.print(boldRed + "\n\n         Mqtt Client Connection Failed :( " + fontReset);
    return false;
  }
}

void check_mqtt_connection()
{

  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(Red + "\n\n         Ups WiFi Connection Failed :( ");
    Serial.println(" -> Restarting..." + fontReset);
    delay(15000);
    ESP.restart();
  }

  if (!client.connected())
  {

    long now = millis();

    if (now - lastReconnectAttemp > 5000)
    {
      lastReconnectAttemp = millis();
      if (reconnect())
      {
        lastReconnectAttemp = 0;
      }
    }
  }
  else
  {
    client.loop();
    process_sensors();
    send_data_to_broker();
    print_stats();
  }
}

bool get_mqtt_credentials()
{

  Serial.print(underlinePurple + "\n\n\nGetting MQTT Credentials from WebHook" + fontReset + Purple + "  ⤵");
  delay(1000);

  String toSend = "dId=" + dId + "&password=" + webhook_pass;

  HTTPClient http;
  http.begin(webhook_endpoint);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");

  int response_code = http.POST(toSend);

  if (response_code < 0)
  {
    Serial.print(boldRed + "\n\n         Error Sending Post Request :( " + fontReset);
    http.end();
    return false;
  }

  if (response_code != 200)
  {
    Serial.print(boldRed + "\n\n         Error in response :(   e-> " + fontReset + " " + response_code);
    http.end();
    return false;
  }

  if (response_code == 200)
  {
    String responseBody = http.getString();

    Serial.print(boldGreen + "\n\n         Mqtt Credentials Obtained Successfully :) " + fontReset);

    deserializeJson(mqtt_data_doc, responseBody);
    http.end();
    delay(1000);
  }

  return true;
}

void clear()
{
  Serial.write(27);    // ESC command
  Serial.print("[2J"); // clear screen command
  Serial.write(27);
  Serial.print("[H"); // cursor to home command
}

long lastStats = 0;

void print_stats()
{
  long now = millis();

  if (now - lastStats > 1000)
  {
    lastStats = millis();
    clear();

    Serial.print("\n");
    Serial.print(Purple + "\n╔══════════════════════════╗" + fontReset);
    Serial.print(Purple + "\n║       SYSTEM STATS       ║" + fontReset);
    Serial.print(Purple + "\n╚══════════════════════════╝" + fontReset);
    Serial.print("\n\n");
    Serial.print("\n\n");

    Serial.print(boldCyan + "#" + " \t Name" + " \t\t Var" + " \t\t Type" + " \t\t Count" + " \t\t Last V" + fontReset + "\n\n");

    for (int i = 0; i < mqtt_data_doc["variables"].size(); i++)
    {

      String variableFullName = mqtt_data_doc["variables"][i]["variableFullName"];
      String variable = mqtt_data_doc["variables"][i]["variable"];
      String variableType = mqtt_data_doc["variables"][i]["variableType"];
      String lastMsg = mqtt_data_doc["variables"][i]["last"];
      long counter = mqtt_data_doc["variables"][i]["counter"];

      Serial.println(String(i) + " \t " + variableFullName.substring(0,5) + " \t\t " + variable.substring(0,10) + " \t " + variableType.substring(0,5) + " \t\t " + String(counter).substring(0,10) + " \t\t " + lastMsg);
    }

    Serial.print(boldGreen + "\n\n Free RAM -> " + fontReset + ESP.getFreeHeap() + " Bytes");

    Serial.print(boldGreen + "\n\n Last Incomming Msg -> " + fontReset + last_received_msg);
  }
}

