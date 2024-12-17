#!bin/bash/

make
./bin/server &
SERVER_PID=$!
TEST_TXT=$(cat ./test.txt)

gnome-terminal -- bash -c "./bin/client $SERVER_PID $TEST_TXT; exec bash"
