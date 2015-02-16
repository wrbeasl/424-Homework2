#!/bin/bash

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
declare -A OwnerArray
declare -A FileCount

if (( ScriptMode == 1 )); then
	FILES="$(find $Starting_Directory -mtime $TargetTime)"

	for f in "${FILES[@]}"; do
		Owner=$(ls -ld $f | awk '{print $3}')
		
		containsElement $Owner "${OwnerArray[@]}"
		if(($?==0)); then
			OwnerArray["$Owner"]="$Owner"
		fi
		((FileCount["$Owner"]++))

		printf "%s\n" "${OwnerArray[@]}"
		printf "%s\n" "${FILES[@]}"
		printf "%s\n" "${FileCount[@]}"

	done



else
	echo "Mode 2"
fi

