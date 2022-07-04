# app

## Build Setup

```bash
# install dependencies
Install the PlatformIO IDE VSCode plugin

# serve with hot reload at localhost:3000
Open the DEVICE project on a single windows
In the left menu you should see the PlatformIO ICON
You should see the PlatformIO Menu on the botton
# build for production and launch server

In main.cpp you should modify the follow values


String dId = "deviceID";
String webhook_pass = "webhookpass";
String webhook_endpoint = "http://put_here_an_ip:3001/api/getdevicecredentials";
const char *mqtt_server = "put_here_an_ip";


Connect the esp32 to the computer

Helping by the PlatformIO Menu, compile and upload the firmware

Press the Serial Monitor to see the Device Stats

