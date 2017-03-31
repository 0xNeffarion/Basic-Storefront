#!/bin/bash
rm -rf bin
mkdir bin
chmod 777 bin
clear
printf "\n   |=================== SERVER =======================|\n"
if gcc src/server/main.c -O -o bin/sv.out; then 
	printf "\n                        COMPLETE                       \n"
fi
printf "\n   |================= END SERVER =====================|\n"
printf "\n   |=================== CLIENT========================|\n"
if gcc src/client/main.c -O -o bin/cl.out; then 
	printf "\n                        COMPLETE                       \n"
fi
printf "\n   |================= END CLIENT =====================|\n"
