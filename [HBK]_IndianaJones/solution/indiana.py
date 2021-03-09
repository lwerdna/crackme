# key searcher for [HBK]'s "Indiana Jones and the Wizard of Oz" crackme
# 2011 andrewl

from itertools import *

def xor_state(a,b):
    result = a
    for i in range(16):
        result[i] = (result[i] + b[i]) % 2
    return result

button_masks = [ \
    [0,1,1,0,0,0,1,0,0,0,0,0,0,0,0,0], # b_01 "D" 0
    [0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0], # b_03 "B" 1
    [1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0], # b_04 "A" 2
    [0,0,1,0,0,1,0,0,0,1,0,0,0,0,0,0], # b_05 "C" 3
    [0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0], # b_07 "R" 4
    [0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0], # b_09 "R" 5
    [0,0,0,0,0,0,0,0,0,1,1,1,0,0,1,0], # b_10 "A" 6
    [0,0,0,0,0,0,1,0,0,0,1,1,0,0,0,0], # b_11 "A" 7
    [0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0], # b_12 "B" 8
    [0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0], # b_13 "A" 9
    [0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1]  # b_15 "A" 10
]

button_indices = [ 1, 3, 4, 5, 7, 9, 10, 11, 12, 13, 15 ];

index_to_letter = { 1:'D', 3:'B', 4:'A', 5:'C', 7:'R', 9:'R', \
    10:'A', 11:'A', 12:'B', 13:'A', 15:'A' }

a_indices = [2,6,7,9,10]
b_indices = [1,8]
r_indices = [4,5]
c_indices = [3]
d_indices = [0]

count = 0

for p in product( a_indices, \
                    b_indices, \
                    r_indices, \
                    a_indices, \
                    c_indices, \
                    a_indices, \
                    d_indices, \
                    a_indices, \
                    b_indices, \
                    r_indices, \
                    a_indices, \
                    a_indices, \
                    a_indices):

    ok = 1
    string = ''
    state = [0]*16
    for i in range(13):
        if state[button_indices[p[i]]] == 1:
            ok = 0
            break
        state = xor_state(state, button_masks[p[i]])
        #print "state is now: ", state
        string = string + index_to_letter[button_indices[p[i]]]
    if not ok:
        continue
    if state != [1]*16:
        continue

    if string == 'ABRACADABRAAA':
        for i in p:
            print '[%d,%d]' % (button_indices[i]/4+1, button_indices[i]%4+1),
        print ''
        count+=1



print "total solutions: %d" % count
