#!/bin/bash
SCRIPT_DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"


cd "$SCRIPT_DIR"
colcon build --cmake-args -DCMAKE_BUILD_TYPE=Debug