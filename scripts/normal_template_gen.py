import sys
import os

folder_path = sys.argv[1]
template_path = '/Users/bencullivan/documents/CppLibrary/templates/normal.cc'

for i in range(2, len(sys.argv)):
  with open(template_path, 'r') as template_file:
    with open(os.path.join(folder_path, sys.argv[i] + '.cc'), 'w') as destination_file:
      for line in template_file:
        destination_file.write(line)
