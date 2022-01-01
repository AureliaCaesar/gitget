#!/bin/bash
[ ! -d "bin" ] && mkdir bin
gcc -O2 main.c -o ./bin/gitget && chmod +x ./bin/gitget
