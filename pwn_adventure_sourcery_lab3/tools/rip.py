#!/usr/bin/env python

# to be used like:
#
# objdump -M intel -d ./xtea_wb.o | ./rip.py xtea > ~/Downloads/challenge/xtea.s

import re
import sys

label = 'label_'
if sys.argv[1:]:
	label = sys.argv[1]

for line in sys.stdin:
	#if re.match(r'^\s+$', line):
	#	continue

	line = re.sub(r'DWORD PTR', 'dword', line)
	line = re.sub(r'WORD PTR', 'word', line)
	line = re.sub(r'BYTE PTR', 'byte', line)

	if re.match(r'^Disassembly.*', line):
		continue

	if re.match(r'^\.\/.*file format.*', line):
		continue

	m = re.match(r'^[0-9a-f]+ <(.*)>:$', line)
	if m:
		func_name = m.group(1)
		print func_name + ':'
		continue

	m = re.match(r'\s+([0-9a-f]+):\t.*\t(.*)', line)
	if m:
		(addr, instr) = m.group(1,2)

		toks = instr.split()
		if len(toks)==3 and re.match(r'[a-fA-F0-9]',toks[1]) and re.match(r'<.*>', toks[2]):
			instr = '%s    %s_%s' % (toks[0], label, toks[1])

		print '%s_%s: %s' % (label, addr, instr)
		continue

	print line,
