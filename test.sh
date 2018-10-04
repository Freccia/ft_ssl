#!/bin/bash

export RED=$'\e[0;91m'
export GREEN=$'\e[0;92m'
export BLUE=$'\e[0;94m'
export WHITE=$'\e[0;97m'
export CYAN=$'\e[0;96m'
export ENDC=$'\e[0m'

FTSSL="./ft_ssl"
SSL="openssl"

if [ $# -ne 2 ]; then
	echo "Usage: $0 [ algo ] [ directory ]"
	exit 1
fi

ALGO=$1

for i in $2/*;
do
	if [ -f "$i" ] && [ ! -d "$i" ];then

		echo $i
		N=$((${#i} + ${#ALGO} + 4))
		HASH_SSL=$( $SSL $ALGO $i | sed "s/^.\{$N\}//g ")
		HASH_FTSSL=$( $FTSSL $ALGO -q $i )

		if [ "${HASH_SSL}" != "$HASH_FTSSL" ]; then
			echo $RED"File Differs"$ENDC
			echo $HASH_SSL
			echo $HASH_FTSSL
		else
			echo $GREEN"Ok"$ENDC
		fi
	fi
done
