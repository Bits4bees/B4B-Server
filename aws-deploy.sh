#!/bin/bash
source /home/ec2-user/.bash_profile
sudo yum update -y

sudo usermod -a -G docker ec2-user
sudo usermod -aG docker $USER

echo "------------ USUARIO -------------"
echo "$USER"

docker-compose -f ~/services/docker_compose_production.yml up -d