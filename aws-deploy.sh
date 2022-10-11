#!/bin/bash
source /home/ec2-user/.bash_profile
sudo apt-get update

wget https://github.com/docker/compose/releases/latest/download/docker-compose-$(uname -s)-$(uname -m) 
sudo mv docker-compose-$(uname -s)-$(uname -m) /usr/local/bin/docker-compose
sudo chmod -v +x /usr/local/bin/docker-compose
sudo chmod +x /usr/local/bin/docker-compose-Linux-x86_64;

sudo usermod -a -G docker ec2-user
sudo usermod -aG docker $USER


docker-compose -f services/docker_compose_production.yml up -d