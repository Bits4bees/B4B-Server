#!/bin/bash
source /home/ec2-user/.bash_profile
docker-compose -f services/docker_compose_production.yml up -d