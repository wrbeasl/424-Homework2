#!/bin/bash

#####################################################################
#					William Beasley									#
#						wrbeasl										#
#						CPSC 424									#
#					Homework 2 Question #2							#
#####################################################################

containsElement () {
  local e
  for e in "${@:2}"; do [[ "$e" == "$1" ]] && return 0; done
  return 1
}


if(( $# != 3 )); then
	echo "ERROR: Missing required param"
	usage
	exit -1
fi

Starting_Directory=$1
TargetTime=$2
ScriptMode=$3
index=0
declare -A Array
declare -A FileArray

#####################################################################
#					Check the mode type 							#
#####################################################################

if (( ScriptMode == 1 )); then
	FILES="$(find $Starting_Directory -type f -mtime $TargetTime)"
	shopt -s globstar

	for f in $FILES; do
		Owner=$(ls -ld $f | awk '{printf $3}')
		if [ ${Array[$Owner]+_} ]; then
			((Array[$Owner]++))	
		else
			((Array[$Owner]=1))
		fi
	done

	printf "Owner\tNumber of files changed\n"

	for i in "${!Array[@]}"; 
	do
		printf "%s\t %s\n" "$i" "${Array[$i]}"
	done | sort -rn -k3

else
	FILES="$(find $Starting_Directory -type f -mtime $TargetTime)"
	shopt -s globstar

	for f in $FILES; do
		Owner=$(ls -ld $f | awk '{printf $3}')
		if [ ${Array[$Owner]+_} ]; then
			((Array[$Owner]++))	
		else
			((Array[$Owner]=1))
		fi
	done

	for i in "${!Array[@]}"; 
	do
		printf "%s\t\n" "$i"
		echo "$i"
		USER_FILES="$(find $Starting_Directory -type f -user "$i" -mtime $TargetTime)"
		for f in $USER_FILES;
		do
			ls -lt $f
		done

	done | sort -rn -k3
fi

