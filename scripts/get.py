import sys
import os


folder_path = sys.argv[1]
data_structure_path = f'{os.environ["cpp_library_path"]}/{sys.argv[2]}/{sys.argv[3]}.cc'

if not os.path.isfile(data_structure_path):
	print(f'{sys.argv[2]}/{sys.argv[3]}.cc does not exist.')
	exit(0)

with open(os.path.join(folder_path, sys.argv[4] + '.cc'), 'r') as destination_file:
	buf = destination_file.readlines()

target_line = ''
targs = ['// end of template', 'using ll = long long;', 'using ll=long long', 'using namespace std;']
for targ in targs:
	has_line = False
	for line in buf:
		if line.find(targ) != -1:
			has_line = True
			break
	if has_line:
		target_line = targ
		break

with open(os.path.join(folder_path, sys.argv[4] + '.cc'), 'w') as destination_file:
	for line in buf:
		if line.find(target_line) != -1:
			line += '\n'
			with open(data_structure_path, 'r') as source_file:
				for source_line in source_file:
					line += source_line
			line += '\n'
		destination_file.write(line)
