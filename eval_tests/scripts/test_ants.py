# Test script for testing read_ants() function
# New tests and be added to "tests" array

from asyncio.subprocess import PIPE
import subprocess
import time
import os

# Path to lem-in executable
lem_in_path = "../../lem-in"

# New tests can be added here
tests = 	[" 42",
				"42 ",
				"	42",
				"42		",
				"42",
				]

# Loop for testing all numbers
for line in tests:
	proc = subprocess.run(["../../lem-in", line],
	stdin=subprocess.PIPE)
	# stdout=subprocess.PIPE)
	print(proc)
	if proc.returncode == 1:
		print("ok")
	else:
		print("ko")
