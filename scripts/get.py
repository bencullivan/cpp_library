import sys
import os

folder_path = sys.argv[1]
data_structure_path = f'/Users/bencullivan/documents/CppLibrary/{sys.argv[2]}/{sys.argv[3]}.cc'
target_line = 'const char df ='

if not os.path.isfile(data_structure_path):
    print(f'{sys.argv[2]}/{sys.argv[3]}.cc does not exist.')
    exit(0)

with open(os.path.join(folder_path, sys.argv[4] + '.cc'), 'r') as destination_file:
    buf = destination_file.readlines()

with open(os.path.join(folder_path, sys.argv[4] + '.cc'), 'w') as destination_file:
    for line in buf:
        if line.find(target_line) != -1:
            with open(data_structure_path, 'r') as source_file:
                for source_line in source_file:
                    line += source_line
            line += '\n'
        destination_file.write(line)
