#!/bin/bash
declare -a times
export BC_LINE_LENGTH=0
BDIR=scratch

books=(GreenEggsAndHam Macbeth Genesis HoundOfTheBaskervilles TheWarOfTheWorlds TreasureIsland TheSecretGarden TheCountOfMonteCristo TwentyThousandLeagues Bible)

for type in unique bincount parity; do
		echo "$type"
		echo "--------"
		echo
		echo -e "\t\ttable"
	for book in "${books[@]}"; do
		printf "$book.txt\t";
		for foo in table; do
			for count in 1 2 3; do
				times[$count]=$( TIMEFORMAT="%R"; { time ./$type-$foo $BDIR/$book.txt 1>/dev/null; } 2>&1 )
			done
			AVG=`echo "(${times[1]} + ${times[2]} + ${times[3]})/3" | bc -l`
			printf "$(printf %.3f << echo $AVG)\t"
		done
		printf "\n"
	done
	printf "\n"
done
