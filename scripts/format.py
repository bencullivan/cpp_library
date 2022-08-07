import os
import sys
from argparse import ArgumentError


dir_name = os.environ['cpp_library_path']
num_spaces = 4
space_str = ' ' * num_spaces
format_extensions = ['.cc', '.cpp', '.h', '.hpp']


def is_target_file(file_path):
	return os.path.splitext(file_path)[-1] in format_extensions


def to_spaces(file_path):
	if not is_target_file(file_path):
		return
	with open(file_path, 'r') as f:
		lines = [str(s).replace('\t', space_str) for s in f.readlines()]
	with open(file_path, 'w') as f:
		f.writelines(lines)


def to_tabs(file_path):
	if not is_target_file(file_path):
		return
	with open(file_path, 'r') as f:
		lines = []
		for line in f.readlines():
			s = str(line)
			if s.find('\t') != -1:
				lines.append(s)
			else:
				i = 0
				while i < len(s) and s[i] != '\n' and s[i].isspace():
					i += 1
				lines.append(('\t' * (i // num_spaces)) + s[i:])
		for line in lines:
			print(line)
	with open(file_path, 'w') as f:
		f.writelines(lines)


def convert(fun):
	for dir in os.scandir(dir_name):
		if dir.is_dir():
			if dir.name == 'atcoder':
				print('skipping atcoder')
				continue
			for fl in os.scandir(os.path.join(dir_name, dir.name)):
				if fl.is_file():
					fun(fl.path)


if __name__ == '__main__':
	# if len(sys.argv) < 2 or sys.argv[1] not in ['tabs', 'spaces']:
	# 	raise ArgumentError('must supply "tabs" or "spaces" as an argument')
	# convert(to_tabs if sys.argv[1] == 'tabs' else to_spaces)
	print('go')
	to_tabs('/Users/benjamincullivan/documents/cpp_library/scripts/format.py')
