#!/usr/bin/env bash

cd ..
docker run --rm -it --shm-size=1g -p 8765:8765 carcontrol-sim
