#!/bin/bash
source /home/ec2-user/.bash_profile

#sudo yum update -y

#sudo usermod -a -G docker ec2-user
#sudo usermod -aG docker $USER

#echo "########## Cambiando a carpeta donde se copia el repositorio ##########"

echo "########## Copiando .envo a services ##########"
cp /home/ec2-user/credentials/.env ./services

echo "########## Copiando .envo a /app ##########"
cp /home/ec2-user/credentials/.env ./app

#cd /home/ec2-user/bits4bees

echo "########## Entrando a /services ##########"
cd /services

#echo "------------ Carpeta actual -------------"
#pwd
#echo "------------ Carpeta actual -------------"

#echo "------------ Contenido -------------"
#ls
#echo "------------ Contenido -------------"

echo "########## Ejecutando docker compose ##########"


sudo docker build -t nuxt_app app/
docker-compose -f ./services/docker_compose_production.yml up -d