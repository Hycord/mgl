#!/bin/bash
clear && cmake build && cd build && make && cd .. && clear && cp ./build/src/mgl ./mgl