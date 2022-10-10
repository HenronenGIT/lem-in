# Test script what asks path to folder.
import os
import readline, glob
import glob

cwd = os.getcwd()
lem_in = cwd + "/lem-in"

path = "eval_tests/maps/"
path += input("Give path for test_files\n")
path += '/*.map'
print(path)
# files_arr = glob.glob("eval_tests/test_maps/*.map")
files_arr = glob.glob(path)
# print (folder)
print (files_arr)


# for file in folder:
# 	path_array = file.split("/")
# 	print("===== " + path_array[2] +" =====", flush=True)
# 	# input("Press Enter to continue...")
# 	os.system(lem_in + "<" + file)