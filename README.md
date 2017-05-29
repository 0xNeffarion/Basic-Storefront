# Project Title

Storefront back-end (server) & front-end (client) applications

### Prerequisites

- Linux based OS. Ubuntu, Debian, Fedora, etc..
- GCC installed for compiling the source code

### Installing

Clone or download a zip file with source code and extract to a folder.

If you dont have GCC installed type the following in the terminal:

```
sudo apt-get install gcc
```

You can use the provided .sh files to build and run the client/server.

Make sure they have permission to execute.

Build server and client:
```
sh build.sh
```

Run client or/and server
```
sh client_run.sh
sh server_run.sh
```
Any compiled files will be in the bin folder

## Authors

* **Vasco Serrano** - [0xNeffarion](https://github.com/0xNeffarion)
* **André Moreira Pacheco** - [AndreMP97](https://github.com/AndreMP97)

## Acknowledgments

This was a simple university project written in C.

All information is stored locally on same machine (users, stats and items) @ ~\labc_sm_data

It is possible to reset the stock, stats and registered users info by running the server with the following arguments (in-case something goes wrong unnexpectedly)

```
.\sv.out reset target
```

Target can be either:
users, stats or stocks

