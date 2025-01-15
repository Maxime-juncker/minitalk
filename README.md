minitalk project of 42

## Goals
creating a server and a client:
- the server need to print is pid
- using the server pid the client can send a message of any size to the server (message can includes utf8 characters 😨)
- the server need to print the received message and reply to the client

## Compile it yourself
first clone the repo
```
git clone https://github.com/Maxime-juncker/minitalk.git
cd minitalk
```
then build it using make
```
make
```

## How to run
after building it

go to the bin directory
```
cd bin/
```

run the server
```
./server
```

the server will print it's pid
you can now run the client
```
./client <server_pid> <message>
```

