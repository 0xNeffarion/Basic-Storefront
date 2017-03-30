#!/bin/bash
echo -e "\n   |=================== SERVER =======================|\n"
sudo gcc "src/server/main.c" -O -o "bin/sv.out"
echo -e "\n   |================= END SERVER =====================|\n"
echo -e "\n   |=================== CLIENT=======================|\n"
sudo gcc "src/client/main.c" -O -o "bin/cl.out"
echo -e "\n   |================= END CLIENT =====================|\n"
