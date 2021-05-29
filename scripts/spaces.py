import sys
import os

base_dir = '/Users/bencullivan/documents/CppLibrary'
num_spaces = 2
to_tabs = False

def spaces_to_tabs(file_path):
	buf = None
	with open(file_path, 'r') as f:
		buf = f.readlines()
	with open(file_path, 'w') as f:
		for line in buf:
			i = 0
			while line[i] == ' ':
				i += 1
			nl = line if line[i] == '\n' else ('\t' * (i // num_spaces)) + line[i:]
			f.write(nl)

def tabs_to_spaces(file_path):
	buf = None
	with open(file_path, 'r') as f:
		buf = f.readlines()
	with open(file_path, 'w') as f:
		for line in buf:
			i = 0
			while line[i] == '\t':
				i += 1
			nl = line if line[i] == '\n' else (' ' * (i * num_spaces)) + line[i:]
			f.write(nl)

for path in os.listdir(base_dir):
	actual_path = os.path.join(base_dir, path)
	if not os.path.isdir(actual_path) or path[0] == '.':
		continue
	for file in os.listdir(actual_path):
		ext = os.path.splitext(file)[1]
		if ext != '.cc' and ext != '.cpp' and ext != '.h' and ext != '.hpp':
			continue
		if to_tabs:
			spaces_to_tabs(os.path.join(actual_path, file))
		else:
			tabs_to_spaces(os.path.join(actual_path, file))
