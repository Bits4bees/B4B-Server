#!/bin/bash
source /home/ec2-user/.bash_profile
sudo yum update -y

sudo usermod -a -G docker ec2-user
sudo usermod -aG docker $USER

echo "########## Cambiando a carpeta donde se copia el repositorio ##########"

cp /home/ec2-user/.env /home/ec2-user/bits4bees
cd /home/ec2-user/bits4bees

echo "------------ Carpeta actual -------------"
pwd
echo "------------ Carpeta actual -------------"

echo "------------ Contenido -------------"
ls
echo "------------ Contenido -------------"

docker-compose -f ./services/docker_compose_production.yml up -d