#!/bin/bash

sudo sh -c " echo 'SSLREDIRECT=${SSLREDIRECT}' >> $filename"
cd ..

docker-compose -f services/docker_compose_production.yml up -d