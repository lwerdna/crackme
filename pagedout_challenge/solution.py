#!/usr/bin/env python

import sys
import gzip
import base64

alphabet = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/'

# this is the text from the image
code = \
	'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'

# will deleting columns from the right work?
N_ROWS = 24
N_COLS = 79
N_CHARS = N_ROWS * N_COLS
lines = [code[i:i+N_COLS] for i in range(0, N_CHARS, N_COLS)]
#print('\n'.join(lines))
for i in range(1,50):
	lines2 = []
	for line in lines:
		#lines2.append(line[0:-i]) # from the right
		lines2.append(line[i:]) # from the left
	#print('trying:')
	#print('\n'.join(lines2))
	code2 = ''.join(lines2)
	try:
		data = base64.b64decode(code2)
		data2 = gzip.decompress(data)
		print('truncating %d sized column worked' % i)
	except Exception as e:
		pass

# will a truncation result in a succesful decode and decompress?
#for i in range(1,500):
#	try:
#		data = base64.b64decode(code[0:-i])
#		data2 = gzip.decompress(data)
#		print('truncating %d characters worked' % i)
#	except Exception as e:
#		pass
#
# will a 1-character change result in a successful decode and decompress?
#for i in range(len(code)):
#	for a in alphabet:
#		tmp = list(code)
#		tmp[i] = a
#		tmp = ''.join(tmp)
#
#		try:
#			print('trying code[%d]=%s' % (i, a))
#			data = base64.b64decode(tmp)
#			data2 = gzip.decompress(data)
#			print('code[%d]=%s worked' % (i, a))
#		except Exception as e:
#			pass

# will a 2-character change result in a successful decode and decompress?
#for i in range(len(code)):
#	for j in range(i+1, len(code)):
#		for a in alphabet:
#			for b in alphabet:
#				tmp = list(code)
#				tmp[i] = a
#				tmp[j] = b
#				tmp = ''.join(tmp)
#	
#				try:
#					#print('trying code[%d]=%s and code[%d]=%s' % (i, a, j, b))
#					data = base64.b64decode(tmp)
#					data2 = gzip.decompress(data)
#					print('code[%d]=%s and code[%d]=%s worked' % (i, a, j, b))
#				except Exception as e:
#					pass

