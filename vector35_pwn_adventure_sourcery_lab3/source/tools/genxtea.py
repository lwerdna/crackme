#!/usr/bin/env python

import sys

rounds = int(sys.argv[1])

print '#include <stdint.h>'
print 'void decipher3(uint32_t v[2]) {'
print '\tunsigned int i;'
print '\tuint32_t v0=v[0], v1=v[1];'

delta = 0x9e3779b9
sum_ = (delta*rounds)&0xFFFFFFFF

key = [0xDEADBEEF, 0xCAFEBABE, 0x8BADF00D, 0xC0D3D00D]

for i in range(rounds):
	#print 'key[%d]' % ((sum_>>11)&3)
	print '\tv1 -= (((v0 << 4) ^ (v0 >> 5)) + v0) ^ 0x%08X;' % (sum_ + key[(sum_>>11)&3])
	sum_ = (sum_ + (delta ^ 0xFFFFFFFF) + 1) & 0xFFFFFFFF
	#print 'key[%d]' % (sum_&3)
	print '\tv0 -= (((v1 << 4) ^ (v1 >> 5)) + v1) ^ 0x%08X;' % (sum_ + key[sum_&3])

print '\tv[0]=v0; v[1]=v1;'
print '}'
