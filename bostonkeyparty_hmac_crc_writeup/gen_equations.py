#!/usr/bin/env python

import sys

def simplify(expr):
    lookup = {}

    for p in expr.split('^'):
        if p in lookup:
            lookup[p] += 1
        else:
            lookup[p] = 1

    parts = []
    for key, count in lookup.iteritems():
        if key == '1' and count % 2:
            parts.append(key)
            continue
        if key == '0':
            continue
        if count % 2:
            parts.append(key)

    return '^'.join(sorted(parts))

#######
# INNER
#######
# key bits k63,k62,...,k0
expr = map(lambda x: 'k%d'%x, [k for k in xrange(63,-1,-1)])
# xor with inner padding 0x363636...
for (i,x) in enumerate([0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0]):
    expr[i] = '%s^%d' % (expr[i], x)
# bits of 'zupe zecret'
expr += map(str, [0,1,1,1,1,0,1,0,0,1,1,1,0,1,0,1,0,1,1,1,0,0,0,0,0,1,1,0,0,1,0,1,0,0,1,0,0,0,0,0,0,1,1,1,1,0,1,0,0,1,1,0,0,1,0,1,0,1,1,0,0,0,1,1,0,1,1,1,0,0,1,0,0,1,1,0,0,1,0,1,0,1,1,1,0,1,0,0])
# temp bits start with abaddeadbeef1dea
expr += map(str, [1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 0])
# as the polynomial moves across, collect expressions for the crc result
poly = [1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1]
for i in range(len(expr)-64):
    src = expr[i]

    for (j,p) in enumerate(poly):
        if p:
            expr[i+1+j] += '^%s' % src
            expr[i+1+j] = simplify(expr[i+1+j])

temp = expr[-64:]
print '\n'.join(temp)
print len(temp)
print '--'

#######
# OUTER
#######
# key bits k63,k62,...,k0
expr = map(lambda x: 'k%d'%x, [k for k in xrange(63,-1,-1)])
# outer padding 0x5c5c...
for (i,x) in enumerate([0, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0]):
    expr[i] = '%s^%d' % (expr[i], x)
# temp (output of inner crc)
expr += temp
# and the initial crc const val
expr += map(str, [1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 0])
# as the polynomial moves across, collect expressions for the crc result
poly = [1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1]
for i in range(len(expr)-64):
    src = expr[i]

    for (j,p) in enumerate(poly):
        if p:
            expr[i+1+j] += '^%s' % src
            expr[i+1+j] = simplify(expr[i+1+j])

#>>> bin(0xA57D43A032FeB286)
#'0b1010010101111101010000111010000000110010111111101011001010000110'
target = list('1010010101111101010000111010000000110010111111101011001010000110')

hmac = expr[-64:]

equations = map(lambda k: '%s=%s' % k, zip(hmac, target))

print '\n'.join(equations)
print '--'

# print out pari/gp form
matrows = []
for (i,e) in enumerate(hmac):
    rowElems = []
    compl = False
    parts = e.split('^')

    for k in xrange(63,-1,-1):
        if 'k%d'%k in parts:
            rowElems.append('1')
        else:
            rowElems.append('0')

    if '1' in parts:
        target[i] = {'0':'1','1':'0'}[target[i]]

    matrows.append(','.join(rowElems))

print 'A=[', ';'.join(matrows), ']*Mod(1,p)'
print 'B=[', ';'.join(target), ']'
print 'lift(A^-1 * B)'




