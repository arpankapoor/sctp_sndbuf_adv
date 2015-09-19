#!/bin/bash

addnums() {
	local sum=0
	while read -r val
	do
		if [[ -n $val ]]
		then
			sum=$(($sum+$val))
		fi
	done
	echo $sum
}

main() {
	echo -e "secs\t\ttxq\t\trxq\t\tsndbuff"

	while true
	do
		assocs=$(tail -n +2 /proc/net/sctp/assocs | \
			tr "\t" " " | \
			tr -s " ")

		txq=$(echo "$assocs" | \
<<<<<<< HEAD
			cut -d " " -f 8 | \
||||||| merged common ancestors
			cut -d " " -f 9 | \
=======
			cut -d " " -f 8 | \
			addnums)

		rxq=$(echo "$assocs" | \
			cut -d " " -f 9 | \
>>>>>>> d4c904a028bf868c17f69fd06a305685f31c7bd0
			addnums)

		sndbuff=$(echo "$assocs" | \
			rev | \
			cut -d " " -f 2 | \
			rev | \
			addnums)

		secs=$(date +%s)

		if [[ !($txq -eq 0 && $sndbuff -eq 0) ]]
		then
			echo -e "$secs\t$txq\t\t$rxq\t\t$sndbuff"
		fi
	done
}

main
