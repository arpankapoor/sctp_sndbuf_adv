#!/bin/bash

SERVER_PORT=60000
CLIENT_PORT=60001
REPEAT_COUNT=1000000
TIMEOUT=30

SCTP_PROBE="/proc/net/sctpprobe"

start_test() {
	local client_ip=$1
	local client_port=$2

	local server_ip=$3
	local server_port=$4

	local test_case=$5
	local max_stream=$6
	local order_pattern=$7
	local stream_pattern=$8

	local outfile="c${test_case}.dat"

	echo -e "c=$test_case\t\
		o=$order_pattern\t\
		t=$stream_pattern\t\
		M=$max_stream"

	mkdir -p data

	parallel --timeout $TIMEOUT ::: \
		"sctp_test \
			-H $client_ip \
			-P $client_port \
			-h $server_ip \
			-p $server_port \
			-s \
			-c $test_case \
			-d 0 \
			-x $REPEAT_COUNT \
			-o $order_pattern \
			-t $stream_pattern \
			-M $max_stream > /dev/null" \
		"cat $SCTP_PROBE > data/$outfile"
}

main() {
	if [[ $# -ne 1 ]]
	then
		echo "usage: $0 SERVER_IP"
		exit 1
	fi

	if [[ ! -f "$SCTP_PROBE" ]]
	then
		echo "Load the sctp_probe module"
		exit 1
	fi

	if [[ $EUID -ne 0 ]]
	then
		echo "Run as root"
		exit 1
	fi

	local ip
	ip=$(./getip.sh)

	for test_case in {0..6}
	do
		start_test \
			$ip "$CLIENT_PORT" \
			$1 "$SERVER_PORT" \
			$test_case \
			0 0 0
	done
}

main "$@"
