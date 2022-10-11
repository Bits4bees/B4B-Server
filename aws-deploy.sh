#!/bin/bash
source /home/ec2-user/.bash_profile

echo "------------THIS IS THE USER-------------"

echo "$USER"

docker-compose -f services/docker_compose_production.yml up -d