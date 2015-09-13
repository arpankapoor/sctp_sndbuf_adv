#!/bin/bash

# very bad hack!

echo -e "secs\t\ttxq\tsndbuff"

while true
do
	assocs=$(cat /proc/net/sctp/assocs | \
		tr "\t" " " | \
		tr -s " ")

	txq=$(echo "$assocs" | \
		cut -d " " -f 9 | \
		sed "/TX_QUEUE/d")

	sndbuff=$(echo "$assocs" | \
		rev | \
		cut -d " " -f 2 | \
		rev | \
		sed "/sndbuf/d")

	secs=$(date +%s)

	if [[ -n $txq && -n $sndbuff ]]
	then
		echo -e "$secs\t$txq\t$sndbuff"
	fi
done
