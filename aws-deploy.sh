#!/bin/bash
source /home/ec2-user/.bash_profile
sudo yum update -y

echo "------------ USUARIO -------------"
echo "$USER"

docker-compose -f services/docker_compose_production.yml up -d