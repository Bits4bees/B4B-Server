# app

## Build Setup

```bash
Install the PlatformIO IDE VSCode plugin

Open the DEVICE project on a single windows
In the left menu you should see the PlatformIO ICON
You should see the PlatformIO Menu on the botton

In main.cpp you should modify the follow values

String dId = "deviceID";
String webhook_pass = "webhookpass";
String webhook_endpoint = "http://put_here_an_ip:3001/api/getdevicecredentials";
const char *mqtt_server = "put_here_an_ip";

Connect the esp32 to the computer

Helping by the PlatformIO Menu, compile and upload the firmware

Press the Serial Monitor to see the Device Stats


Ejecutar proyecto

- Borrar docker containers
- Borrar docker volumes:
 docker volume rm $(docker volume ls -q) -f   (puede no funcionar, usar tool de docker en vs code)
- Borrar carpeta mongodata en carpeta /services:  sudo rm -rf services/mongodata/
- Borrar imagenes de docker: docker rmi -f iddeimagen

