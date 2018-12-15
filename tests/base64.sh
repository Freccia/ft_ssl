#!/bin/bash

export RED=$'\e[0;91m'
export GREEN=$'\e[0;92m'
export BLUE=$'\e[0;94m'
export WHITE=$'\e[0;97m'
export CYAN=$'\e[0;96m'
export ENDC=$'\e[0m'

FTSSL="./ft_ssl base64"
SSL="openssl base64"

TMP_TEST1="/tmp/test1"
TMP_TEST2="/tmp/test2"

function Usage ()
{
	echo "Usage: $0 [ -d | -e ] [ directory ]"
	exit 1
}

if [ $# -ne 2 ]; then
	Usage
fi

MODE=$1

if [ "$MODE" != "-e" ] && [ "$MODE" != "-d" ];then
	Usage
fi

if [ "$MODE" == "-d" ]; then
	OSSLMODE=$MODE
fi

for i in $2/*;
do
	if [ -f "$i" ] && [ ! -d "$i" ];then

		echo $i
		cat $i | $FTSSL $MODE > $TMP_TEST1
		cat $i | $SSL $OSSLMODE > $TMP_TEST2

		diff $TMP_TEST1 $TMP_TEST2 1>/dev/null 2>/dev/null
		if [ "$?" -ne 0 ]; then
			echo $RED"File Differs"$ENDC
			echo $HASH_SSL
			echo $HASH_FTSSL
		else
			echo $GREEN"Ok"$ENDC
		fi
	fi
done
