#!/bin/bash

SERVER_PID=$$
SERVER_PORT=60000

start_sctp_server() {
	local ip=$1
	local port=$2

	sctp_test -H $ip -P $port -l -d 0 &
	SERVER_PID=$!
}

main() {
	local ip=$(./getip.sh)

	start_sctp_server $ip $SERVER_PORT
	echo "IP: $ip"
	echo "PID: $SERVER_PID"
	trap "kill $SERVER_PID" SIGTERM SIGINT
	wait
}

main
