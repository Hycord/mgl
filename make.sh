#!/bin/bash
clear && cmake build && cd build && make && cd ..  && cp ./build/src/mgl ./mgl