#!/bin/bash

# Get the main IP address

getip() {
	hostname -i | cut -d ' ' -f 1
}

getip
