#!/bin/bash

COMMAND=$1
IMAGE="docker_websocketpp"

if [ "${#}" -eq "0" ]; then
    echo
    echo "Usage: $(basename ${0}) <command>"
    echo
    echo "command       | description"
    echo "==============|==================================="
    echo "build         | build image"
    echo "run           | run container image"
    echo "connect_shell | connect shell to running container"
    echo
    exit 0
fi

# Build image:
if [ "$COMMAND" == "build" ]; then
    echo "Build image"
    docker build --tag=${IMAGE} .
    exit 0
fi

if [ "${COMMAND}" == "run" ]; then
    echo "Run image"
    docker run --name ${IMAGE}_1 --rm -i -t ${IMAGE}
    exit 0
fi

if [ "${COMMAND}" == "connect_shell" ]; then
    echo "Connect shell "
    docker exec -it ${IMAGE}_1 bash
    exit 0
fi

