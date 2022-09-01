#!/bin/bash
#
# Test script for testing hoe lem-in program handles invalid ant intput

# Colors for echos
RED='\033[0;31m'
BGREEN='\033[1;32m' 
GREEN='\033[0;32m'
CYAN='\033[0;36m'
PURPLE='\033[0;35m' 
YELLOW='\033[0;33m'
OFF='\033[0m'

lem_in="../../lem_in"
# file="../test_maps/invalid_tests/invalid_ant.map"
file="/Users/hmaronen/workspace/github/lem-in/eval_tests/test_maps/invalid_tests/invalid_ant.map"
# invalid_test="../test_ma"

# echo "${PURPLE}Testing with invalid ant syntax${OFF}"

while IFS= read -r line;
	# do printf "$line";
	do output=$(echo "$line" | $lem_in);
	
		# printf "$line"
		# printf "$line"
		# operation_count=$(../push_swap "$line" | wc -l | xargs);
	# if [ $output == "KO" ]; then
		# echo "${RED}[FAIL] -> ARRAY NOT SORTED${OFF}"
	# elif [ $operation_count -le $max_3 ]; then
		# echo "${GREEN}${PASS_MSG} -> ${OFF}$operation_count"
	# else
		# echo "${RED} ${FAIL_MSG} -> ${OFF}$operation_count"
	# fi
done < $file