# Test script for testing read_ants() function
#
from asyncio.subprocess import PIPE
import readline
import sys
import subprocess
import os

# file =  open("../test_maps/invalid_tests/invalid_ant.map")
file = os.open("../test_maps/invalid_tests/invalid_ant.map", os.O_RDWR)
# lines = file.readlines()

# print(lines[0])
# sys.stdout()
# file.readline

# r"echo 'a' | ../../lem_in"
output = subprocess.run(["../../lem-in"],
				stdin = file,
				stdout = PIPE)
print (output.stdout)
#! try to add test 
