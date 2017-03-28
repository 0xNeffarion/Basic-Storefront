#!bin/bash
gcc "src/server/main.c" -O -o "bin/sv.out";
gcc "src/client/main.c" -O -o "bin/cl.out";
exit