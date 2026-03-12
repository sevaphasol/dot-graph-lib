#!/bin/bash

cmake -B build
cmake --build build -j
cmake --install build --prefix install
ln -sf build/compile_commands.json
