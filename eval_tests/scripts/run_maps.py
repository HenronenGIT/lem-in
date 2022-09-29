from pathlib import Path
import os
import glob

# PATHS
cwd = os.getcwd()

lem_in = cwd + "/lem-in"
files_arr = glob.glob("eval_tests/test_maps/*.map")

for file in files_arr:
	print("===== " + file +" =====")
	os.system(lem_in + "<" + file)