from pathlib import Path
import os
import glob

YELLOW = "\x1b[1;33;40m" 
WHITE = '\033[93m'

# PATHS
cwd = os.getcwd()

lem_in = cwd + "/lem-in"
files_arr = glob.glob("eval_tests/test_maps/*.map")

for file in files_arr:
	print("===== " + file +" =====")
	input("Press Enter to continue...")
	os.system(lem_in + "<" + file)