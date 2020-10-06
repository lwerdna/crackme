#!/usr/bin/python
# Feb 16th, 2011 Release - With Kao's Toy Project
#------------------------------------------------------------------------------
#
#    "KGLIB" Keygenning/Math Library
#
#    Copyright 2011,2012 Andrew Lamoureux
#
#    This program is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    This program is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
#------------------------------------------------------------------------------
#    Just a collection of implementations from books, websites, papers, etc.
#    Verbosity, understanding, and fun are priorities, not optimizations.
#    Features:
#     - ???

###############################################################################
# #include
###############################################################################
import re
import sys
import math
import copy
import string
import struct
import random
import tempfile
import fractions
import itertools
import subprocess

###############################################################################
# Utils
###############################################################################
def run_get_output(cmd_and_args):
    pipe = subprocess.Popen(cmd_and_args, stdout=subprocess.PIPE, shell=True)
    text = pipe.communicate()[0]

    Output.Debug(cmd_and_args)

    return text

###############################################################################
# Bit Operations
###############################################################################

# rotate left
def bitrol(r, n, regsize=32):
    n = n % regsize
    return ((r<<n) | (r>>(regsize-n))) & (2**regsize - 1)

# rotate right
def bitror(r, n, regsize=32):
    n = n % regsize
    return ((r>>n) | (r<<(regsize-n))) & (2**regsize - 1)

# add within a register
def bitadd(a, b, regsize=32):
    return (a+b) & (2**regsize - 1)

# shifts
def bitshl(a, n, regsize=32):
    return (a<<n) & (2**regsize - 1)

def bitshr(a, n, regsize=32):
    return (a>>n) & (2**regsize - 1)

###############################################################################
# Symmetric Algorithms
###############################################################################

def xtea_encrypt_block(v, key, num_rounds=32):
    sum=0
    delta=0x9E3779B9

    [v0,v1] = struct.unpack('>II', v) 
    subkeys = struct.unpack('>IIII', key)

    for i in range(num_rounds):
        v0 = bitadd(v0, bitadd(( bitshl(v1, 4) ^ (v1 >> 5)), v1) ^ bitadd(sum, subkeys[sum & 3]))
        sum = bitadd(sum, delta)
        v1 = bitadd(v1, bitadd(( bitshl(v0, 4) ^ (v0 >> 5)), v0) ^ bitadd(sum, subkeys[(sum>>11) & 3]))

    return struct.pack('>II', v0, v1)
 
def xtea_decrypt_block(v, key, num_rounds=32):
    delta=0x9E3779B9
    sum=delta*num_rounds;
    [v0,v1] = struct.unpack('>II', v) 
    subkeys = struct.unpack('>IIII', key)

    for i in range(num_rounds):
        v1 -= (( bitshl(v0, 4) ^ (v0 >> 5)) + v0) ^ (sum + subkeys[(sum>>11) & 3])
        v1 &= 0xFFFFFFFF
        sum -= delta
        v0 -= (( bitshl(v1, 4) ^ (v1 >> 5)) + v1) ^ (sum + subkeys[sum & 3])
        v0 &= 0xFFFFFFFF

    return struct.pack('>II', v0, v1)

def xtea_encrypt_ofb(plaintext, key, iv="\x41\x42\x43\x44\x45\x46\x47\x48"):
    length = len(plaintext)

    # build stream at least as long as the plaintext
    ct = iv
    stream = []
    for i in range((length + 7) / 8):
        ct = xtea_encrypt_block(ct, key)
        stream += struct.unpack("8B", ct)
  
    #print stream
 
    # xor each byte
    ciphertext = ''
    for i in range(length):
        ciphertext += struct.pack('B', ord(plaintext[i]) ^ stream[i])

    return ciphertext 

###############################################################################
# Boolean Formulas
###############################################################################

def PicosatPipeSolve(expr):
    p = subprocess.Popen('picosat', stdin=subprocess.PIPE, stdout=subprocess.PIPE)
    
    # p cnf <NUMBER OF VARIABLES> <NUMBER OF CLAUSES>
    print "collecting var names on: ", expr
    mapVarInd = expr.collectVarNames()
    mapIndVar = {}

    varsN = len(mapVarInd)
    clausesN = len(expr.subexprs)  
 
    # create a mapping from varname -> index
    for i,v in enumerate(sorted(mapVarInd.keys())):
        # the format is 1-indexed
        mapVarInd[v] = i+1
        mapIndVar[i+1] = v
    print mapVarInd
    print mapIndVar
    
    t = 'p cnf %d %d\n' % (varsN, clausesN)
    print t,
    p.stdin.write(t)

    # enter each clause
    for se in expr.subexprs:
        # enter each [not]literal
        if isinstance(se, BoolDisj):
            for sse in se.subexprs:
                neg = ''
                name = ''
                if isinstance(sse, BoolNot):
                    neg = '-'
                    name = sse.subexprs[0].name
                else:
                    name = sse.name
    
                t = '%s%s ' % (neg, mapVarInd[name])
                print t,
                p.stdin.write(t)
        elif isinstance(se, BoolNot):
            t = '-%s ' % mapVarInd[se.subexprs[0].name]
            print t,
            p.stdin.write(t)
        elif isinstance(se, BoolLit):
            t = '%s ' % mapVarInd[se.name]
            print t,
            p.stdin.write(t)
        else:
            raise ValueError("wtf? in pipe solver")

        t = '0\n'
        print t,
        p.stdin.write(t)

    # close the pipe, ending input
    p.stdin.close()

    print "output:"

    # read from input now
    line1 = p.stdout.readline()
    print line1,
    if not re.match(r'^s SATISFIABLE', line1):
        return {}
   
    # parse out all the variables from here... 
    result = {}

    while 1:
        line2 = p.stdout.readline()
        print line2,

        if not line2:
            break

        # get rid of the 'v '
        m = re.match(r'^(v +)', line2)
        if not m:
            return {}

        line2 = string.replace(line2, m.group(1), '', 1)
        print "line (r'^v ' removed): %s" % line2

        # parse every int in this line
        while 1:
            m = re.match('^( *[+-]?\d+ *)', line2)
            if not m:
                break;

            index = int(m.group(1))
            if index == 0:
                print "got end-of-list index"
                break

            value = 1
            if index<0:
                value = 0
                index *= -1

            result[mapIndVar[index]] = value
       
            line2 = string.replace(line2, m.group(1), '', 1)

    # close
    p.stdout.close()

    #
    return result


# boolean system is a collection of boolean equations
class BoolSystem:
    def __init__(self, n):
        self.equs = [BoolEquation() for i in range(n)]

    def copy(self):
        bs = BoolSystem(len(self.equs))
        bs.equs = map(lambda x: x.copy(), self.equs)
        return bs

    def fromExprs(self, exprs):
        self.equs = [BoolEquation() for i in range(len(exprs))]
        for i in range(len(exprs)):
            self.equs.expr = exprs[i].copy()

    def loadTargetsFromArray(self, arr):
        if len(arr) > len(self.equs):
            raise ValueError("setting target of more equations than exist")

        for i,t in enumerate(arr):
            # some array slots can be "None" to mean no effect
            if t:
                self.equs[i].target = t

    def loadTargetsFromBits(self, n, mask):
        arr = []
        for i in range(n):
            arr.append(mask & 1)
            mask >>= 1

        self.loadTargetsFromArray(arr)        

    def loadEqus(self, arr):
        if len(arr) > len(self.equs):
            raise ValueError("setting equations for more equations than exist")

        for i,t in enumerate(arr):
            # some array slots can be "None" to mean no effect
            if t:
                self.equs[i].target = t

    def satSolve(self):
        # collect all Tseitin versions of equations
        cnf = BoolConst(1)

        lastName = ['gate0']

        # then collect all the per-equation cnf forms together into one cnf
        for i,equ in enumerate(self.equs):
            temp = equ.expr.TseitinTransformTargetting(equ.target, lastName).simplify()
            print "in equation %d, got: %s" % (i, temp)
            cnf = (cnf * temp).simplify()

        print "combined: ", cnf
        result = PicosatPipeSolve(cnf)

        print result

        # filter out the gate entires
        result = dict((k,v) for k,v in result.iteritems() if not re.match(r'^gate', k))

        print result

        for k in sorted(result):
            print "%s: %d" % (k, result[k])

        # print it as a hex 
        # collect all varnames
        varnames = {}
        for x in result:
            m = re.match(r'^(.*?)\d+$', x)
            if m:
                varnames[m.group(1)] = 1

        print "found varnames", varnames

        # for each varname, try to get the bits
        for vn in varnames:
            val = 0
            for i in range(len(result)):
                vnb = "%s%d" % (vn, i)
                if vnb in result:
                    val = val | (result[vnb] << i)
                else:
                    break

            print "%s: 0x%X" % (vn, val)

    def toCNF(self):
        for i,equ in enumerate(self.equs):
            self.equs[i] = equ.toCNF()

        return self

    def simplify(self):
        for i,equ in enumerate(self.equs):
            self.equs[i] = equ.simplify()

    def assign(self, varname, varvalue):
        for i,equ in enumerate(self.equs):
            self.equs[i] = equ.assign(varname, varvalue)

    # assign
    def assignBits(self, n, varname, bits):
        for i in range(n):
            self.assign("%s%d" % (varname, i), bits & 1)
            bits >>= 1

    # add stuff
    #
    def adder(self, exprs, cin=0):
        if not cin:
            cin = BoolConst(0)
        else:
            cin = BoolConst(1)

        for i,ex in enumerate(exprs): 
            a = self.equs[i].expr
            b = ex

            s = a ^ b ^ cin
            s = s.simplify()
            # lol,
            s = s.simplify()

            cin = (cin * (a^b)) + (a * b)
            cin = cin.simplify()

            self.equs[i].expr = s

    # given 8, 'a' adds to system a7,a6,...,a0 to 
    def bitAddVar(self, n, varname, where=0):
        self.adder(map(lambda x:BoolParser("%s%d" % (varname, x)), range(n)))

    # given 8, 0xA5 adds to system 10100101
    def bitAddVal(self, n, val):
        exprs = []
        for i in range(n):
            exprs.append(BoolParser("%d" % (val&1)))
            val >>= 1
        self.adder(exprs)

    # sub stuff
    #
    def subtracter(self, exprs):
        # complement all the expressions of the bits
        for i,ex in enumerate(exprs):
            exprs[i] = ex.complement()

        # attach adder with initial carry input = 1 (so 2's complemented it)
        self.adder(exprs, 1)

    # given 8, 'a' adds to system a7,a6,...,a0
    def bitSubVar(self, n, varname):
        self.subtracter(map(lambda x:BoolParser("%s%d" % (varname, x)), range(n)))

    # given 8, 0xA5 adds to system 10100101
    def bitSubVal(self, n, val):
        exprs = []
        for i in range(n):
            exprs.append(BoolParser("%d" % (val&1)))
            val >>= 1
        self.subtracter(exprs)

    # xor stuff
    #
    def xorer(self, exprs):
        print "incoming exprs: ", exprs
        for i,ex in enumerate(exprs):
            self.equs[i].expr = BoolXor([self.equs[i].expr, ex])

    def bitXorVar(self, n, varname):
        self.xorer(map(lambda x:BoolParser("%s%d" % (varname, x)), range(n)))

    def bitXorVal(self, n, val):
        exprs = []
        for i in range(n):
            exprs.append(BoolParser("%d" % (val&1)))
            val >>= 1
        print exprs
        self.xorer(exprs)
   
    # rotate stuff
    #
 
    # set each bit equal to a variable
    def bitEquVar(self, n, varname):
        for i in range(n):
            self.equs[i].expr = BoolParser("%s%d" % (varname, i))    

    def bitEquVal(self, n, v):
        for i in range(n):
            self.equs[i].expr = BoolParser("%d" % (v & 1))
            v = v >> 1

    # complement the first n equations
    def complement(self, n=0):
        if not n:
            n = len(self.equs)

        for i,equ in enumerate(self.equs[0:n]):
            self.equs[i] = equ.complement()

    def __add__(self, bs):
        a = self.copy()
        b = bs.copy()
        a.equs = a.equs + bs.equs
        return a

    def __getitem__(self, i):
        return self.equs[i]

    def __str__(self):
        rv = ''
        for equ in self.equs:
            rv += str(equ)
            rv += "\n"
        return rv

# boolean equation is an <expr> = <target>
class BoolEquation:
    # you can send it shit like "1=(a+/b) + (c*d*e*f)"
    def __init__(self, string=None):
        self.target = 0
        self.expr = None
        if string:
            m = re.match(r'^([01])=(.*)$', string)
            if not m:
                raise ValueError("invalid boolean equation: %s" % string)
            self.target = int(m.group(1))
            self.expr = BoolParser(m.group(2))
 
#    def __init__(self, expr, target):
#        self.expr = expr
#        self.target = target

    def copy(self):
        rv = BoolEquation()
        rv.target = self.target
        rv.expr = self.expr.copy()
        return rv

    def flatten(self):
        rv = self.copy()
        rv.expr =  rv.expr.flatten() 
        return rv

    def simplify(self):
        self.expr = self.expr.simplify()
        return self

    def isCNF(self):
        if isinstance(self.expr, BoolConj) and self.expr.isCNF():
            return True
        return False

    def complement(self):
        rv = BoolEquation()
        rv.target = self.target ^ 1
        rv.expr = self.expr.complement()
        return rv

    def distribute(self):
        rv = self.copy()
        rv.expr = rv.expr.distribute()
        return rv

    def assign(self, varname, varvalue):
        rv = self.copy()
        rv.expr = rv.expr.assign(varname, varvalue)
        return rv

    def countOps(self):
        return self.expr.countOps()

    # convert to conjunctive normal form
    # usual action is to flatten then complement
    def toCNF(self):
        temp = self.copy()

        if temp.target == 0:
            print "target is 0, going for the single shot..."
            temp = temp.flatten()
            temp = temp.complement()

        print "testing if in CNF..."
        if not temp.isCNF():
            print "nope, doing double flatten/complement..."
            temp = temp.flatten()
            temp = temp.complement()
            temp = temp.flatten()
            temp = temp.complement()

        if temp.isCNF():
            print "succeeded!"
        else:
            print "failed! :("
        
        return temp

    def dimacs(self):
        toCNF()

        #print "p cnf %d %d" % (

    def __str__(self):
        return '%d=%s' % (self.target, str(self.expr))


#------------------------------------------------------------------------------
# boolean expression parser
#------------------------------------------------------------------------------

def BoolParserRdDisj(s):
    #print "BoolParserRdDisj entered with s: ", s
    subexprs = []
    subexprs.append(BoolParserRdConj(s))
    if s and s[0] == '+':
        while s and s[0] == '+':
            s.pop(0)
            subexprs.append(BoolParserRdDisj(s))
        return BoolDisj(subexprs)
    else:
        return subexprs[0]

def BoolParserRdConj(s):
    #print "BoolParserRdConj entered with s: ", s
    subexprs = []
    subexprs.append(BoolParserRdXor(s))
    if s and s[0] == '*':
        while s and s[0] == '*':
            s.pop(0)
            subexprs.append(BoolParserRdConj(s))
        return BoolConj(subexprs) 
    else:
        return subexprs[0]

def BoolParserRdXor(s):
    #print "BoolParserRdXor entered with s: ", s
    subexprs = []
    subexprs.append(BoolParserRdNot(s))
    if s and s[0] == '^':
        while s and s[0] == '^':
            s.pop(0)
            subexprs.append(BoolParserRdXor(s))
        return BoolXor(subexprs) 
    else:
        return subexprs[0]

# not -> lit
#     -> '/'<disj>
def BoolParserRdNot(s):
    if s[0] == '/':
        s.pop(0)
        return BoolNot(BoolParserRdLit(s))
    else:
        return BoolParserRdLit(s)

# lit -> <identifier>
#     -> '('<disj>')'
def BoolParserRdLit(tokens):
    #print "BoolParserRdLit entered with tokens: ", tokens
    (compl, name) = (0, '')
  
    # case {'(', <expr>, ')'}
    if tokens[0] == '(':
        tokens.pop(0)
        t = BoolParserRdDisj(tokens)
        if tokens[0] != ')':
            print "missing right hand parenthesis"
            return None
        tokens.pop(0)
        return t 

    # case 0 or 1 (an assigned literal)
    m = re.match(r'^([01])$', tokens[0])
    if m:
        tokens.pop(0)
        return BoolConst(int(m.group(1)))

    name = tokens[0]
    if not re.match(r'^[0-9a-zA-Z]+$', name):
        print "invalid literal name: %s" % name
        return None

    tokens.pop(0)
    return BoolLit(name)

def BoolParser(s):
    error = 0

    # tokenize the input
    tokens = []

    # remove whitespace
    s = re.sub(r'\s', '', s)

    # go
    while s:
        # get all operators (and, or, xor, not) and parenthesis
        m = re.match(r'^[\*\+\^\/)(]', s)
        if m:
            tokens.append(m.group(0))
            s = s[1:]
            continue

        # get literal names
        m = re.match(r'^[a-zA-Z0-9]+', s)
        if m:
            tokens.append(m.group(0))
            s = s[len(m.group(0)):]
            continue

        # else wtf did we encounter?
        print "tokenizer error at \"...%s\"" % s
        error = 1
        break;

    #
    if error:
        return
        
    #print "tokens: ", tokens

    # now recursively descend over the tokens
    topnode = BoolParserRdDisj(tokens) 
    return topnode

#------------------------------------------------------------------------------
# boolean expression class
#------------------------------------------------------------------------------

class BoolExpr:
    def __init__(self):
        self.subexprs = []

    def __mul__(self, rhs):
        if not rhs:
            return self
        if type(rhs) == type("string"):
            rhs = BoolParser(rhs)
        elif isinstance(rhs, BoolLit):
            rhs = rhs.copy()
        return BoolConj([rhs, self])

    def __add__(self, rhs):
        if not rhs:
            return self
        if type(rhs) == type("string"):
            rhs = BoolParser(rhs)
        elif isinstance(rhs, BoolLit):
            rhs = rhs.copy()
        return BoolDisj([self, rhs])

    def __xor__(self, rhs):
        if not rhs:
            return self
        if type(rhs) == type("string"):
            rhs = BoolParser(rhs)
        elif isinstance(rhs, BoolLit):
            rhs = rhs.copy()
        return BoolXor([self.copy(), rhs.copy()])
        #return BoolDisj([ \
        #        BoolConj([self, rhs.complement()]), \
        #        BoolConj([self.complement(), rhs]) \
        #    ])

    def complement(self):
        return BoolNot(self.copy())

    def __invert__(self):
        return self.complement() 

    def isLeafOp(self):
        for se in self.subexprs:
            if not isinstance(se, BoolLit):
                return False

        return True

    def collectVarNames(self):
        answer = {}
        # terminal case is for BoolLits who override this method
        for se in self.subexprs:
            answer.update(se.collectVarNames())
        return answer

    def flatten(self):
        temp = self.copy()
        currops = temp.countOps()
        while 1:
            print "currops: ", currops
            temp = temp.distribute()
            temp = temp.simplify()
            c = temp.countOps()
            print " newops: ", c
            if c == currops:
                break
            else:
                currops = c
        return temp
 
    def distribute(self):
        return self
    def simplify(self, recur=0):
        return self

    # count the number of operator nodes        
    # bool lit must override this to always return 0
    def countOps(self):
        rv = 1

        for se in self.subexprs:
            rv += se.countOps()

        return rv

    def TseitinTransformGenName(self, lastName):
        m = re.match('^gate([a-fA-F0-9]+)$', lastName[0])
        ind = int(m.group(1),16)
        newName = "gate%X" % (ind+1)
        lastName[0] = newName

        #print "%s generated inside a %s" % (newName, self.__class__)
        return newName 

    # compute the Tseitin transformation of this gate
    # returns a 2-tuple [gateName, subExpr]
    def TseitinTransform(self, lastName=['gate0']):
        temp = self.copy().simplify()

        c_name = ''
        gates = []

        # each of the subgates must operate correctly
        #
        cnf = BoolConst(1)

        tcnfs = map(lambda x: x.TseitinTransform(lastName), temp.subexprs)
        for tcnf in tcnfs:
            [name, x] = tcnf
            gates.append(name)
            cnf = (cnf * x).simplify()    

        # now operate on this gate using output of subgates
        # 
        print gates
        while len(gates) >= 2:
            a = BoolLit(gates.pop(0))
            b = BoolLit(gates.pop(0))
            cName = self.TseitinTransformGenName(lastName)
            c = BoolLit(cName)

            if isinstance(self, BoolDisj):
                # c=a+b is true when (/c+b+a) * (c+/b) * (c*/a) is true
                cnf = (cnf * (c.complement()+b+a) * (c+b.complement()) * (c+a.complement())).simplify()
            elif isinstance(self, BoolConj):
                # c=(a*b) is true when (c+/b+/a)(/c+b)(/c+a) is true
                cnf = (cnf * (c + a.complement() + b.complement()) * (c.complement()+b) * (c.complement()+a)).simplify()
            elif isinstance(self, BoolXor):
                # c=(a*b) is true when (/b+/c+/a)*(a+/c+b)*(a+c+/b)*(b+c+/a) is true
                cnf = (cnf * (b.complement() + c.complement() + a.complement()) * (a + c.complement() + b) * \
                        (a + c + b.complement()) * (b + c + a.complement())).simplify()
            else:
                raise Exception("unknown gate!")

            gates.append(cName)

        # now the final guy
        return [gates[0], cnf.simplify()]

    def TseitinTransformTargetting(self, target, lastName=['gate0']):
        [tName, tExpr] = self.TseitinTransform(lastName)

        if target == 0:
            return (tExpr * BoolNot(BoolLit(tName))).simplify()
        else:
            return (tExpr * BoolLit(tName)).simplify()
            
    # this is overridden by BoolLit 
    def evaluate(self):
        return None

    # this is overridden by BoolLit to actually assign the value when name matches
    def assign(self, name, value):
        temp = self.copy()
        for i,se in enumerate(temp.subexprs):
            temp.subexprs[i] = se.assign(name, value)
        return temp

    # to valuate - assign all variables and see what comes out
    def valuate(self, values):
        temp = self.copy()
        for varname in values.keys():
            temp = temp.assign(varname, values[varname])
        temp = temp.simplify()
        return temp

    def __repr__(self):
        return str(self)

class BoolDisj(BoolExpr):
    def __init__(self, subexprs):
        self.subexprs = list(subexprs)

    def copy(self):
        temp = list(self.subexprs)
        for i,se in enumerate(temp):
            temp[i] = se.copy()
        return BoolDisj(temp)

    def distribute(self):
        copy = self.copy()

        temp = list(copy.subexprs)
        for i,se in enumerate(copy.subexprs):
            copy.subexprs[i] = se.distribute()

        if len(copy.subexprs)==1:
            return copy.subexprs[0]

        return copy

    def simplify(self, recur=1):
        copy = self.copy()

        if recur:
            for i,se in enumerate(copy.subexprs):
                copy.subexprs[i] = se.simplify(recur)

        # lift any or subexpressions into this one
        temp = list(copy.subexprs)
        for se in temp:
            #print "considering: ", se
            if isinstance(se, BoolDisj):
                #print "bringing junk up from: ", se

                for sse in se.subexprs:
                    copy.subexprs.append(sse)
                copy.subexprs.remove(se)

        # if any subexpression evaluate to 1, this whole expression is true
        if filter(lambda x: isinstance(x, BoolConst) and x.value == 1, copy.subexprs):
            return BoolConst(1)

        # remove any subexpressions that equate to 0
        for x in filter(lambda x: x.evaluate() == 0, copy.subexprs):
            copy.subexprs.remove(x)

            # if, during this process, all expressions were removed, then this disjunction is false
            if not copy.subexprs:
                return BoolConst(0)

        # do some simple simplifications
        if self.isLeafOp():
            # if any two literals are complements of one another, this whole expression is true
            for i in range(len(copy.subexprs)):
                for j in range(len(copy.subexprs)):
                    if j!=i and copy.subexprs[i] == ~(copy.subexprs[j]):
                        return BoolConst(1)
            
            # if any boolit appears twice, remove the redundent one
            while 1:
                restart = 0
                for i in range(len(copy.subexprs)):
                    for j in range(len(copy.subexprs)):
                        if j!=i and copy.subexprs[i] == copy.subexprs[j]:
                            copy.subexprs.pop(j)
                            restart = 1
                            break

                    if restart:
                        break
                if not restart:
                    break
  
        # if only one subexpr, return us up
        if len(copy.subexprs) == 1:
            return copy.subexprs[0]

        return copy

    def isCNF(self):
        # or subexpressions are in CNF if they're at the bottom of the tree
        return self.isLeafOp()        

    # operator overloading
    #
    def __str__(self):
        result = '('

        for se in self.subexprs:
            if result != '(':
                result += ('+')
            result += str(se)

        return result + ')'

    def __eq__(self, rhs):
        if not isinstance(rhs, BoolDisj):
            return False
        if not len(self.subexprs) == len(rhs.subexprs):
            return False
        temp1 = list(self.subexprs)
        temp2 = list(rhs.subexprs)
        for se in temp1:
            if se not in temp2:
                print "%s was not in %s" % (se, temp2)
                return False
            temp1.remove(se)
            temp2.remove(se)
        return True

class BoolConj(BoolExpr):
    def __init__(self, subexprs):
        self.subexprs = list(subexprs)

    def copy(self):
        temp = list(self.subexprs)
        for i,se in enumerate(temp):
            temp[i] = se.copy()
        return BoolConj(temp)

    def simplify(self, recur=1):
        copy = self.copy()

        if recur:
            for i,se in enumerate(copy.subexprs):
                copy.subexprs[i] = se.simplify(recur)

        # "lift" any and subexpressions into this one
        temp = list(copy.subexprs)
        for se in temp:
            if isinstance(se, BoolConj):
                for sse in se.subexprs:
                    copy.subexprs.append(sse)
                copy.subexprs.remove(se)

        # if any subexpression evaluate to 0, this whole expression is false
        if filter(lambda x: x.evaluate() == 0, copy.subexprs):
            return BoolConst(0)

        # remove any subexpressions that equate to 1
        for x in filter(lambda x: x.evaluate() == 1, copy.subexprs):
            copy.subexprs.remove(x)

            # if during this process, all expressions were removed, then result is true
            if not copy.subexprs:
                return BoolConst(1)

        # do some simple simplifications
        if self.isLeafOp():
            # if any two literals are complements of one another, this whole expression is false
            for i in range(len(copy.subexprs)):
                for j in range(len(copy.subexprs)):
                    if j!=i and copy.subexprs[i] == (~(copy.subexprs[j])).simplify(0):
                        return BoolConst(0)
            
            # if any boolit appears twice, remove the redundent one
            while 1:
                restart = 0
                for i in range(len(copy.subexprs)):
                    for j in range(len(copy.subexprs)):
                        if j!=i and copy.subexprs[i] == copy.subexprs[j]:
                            copy.subexprs.pop(j)
                            restart = 1
                            break

                    if restart:
                        break
                if not restart:
                    break

        # if only one subexpression remains, move it up
        if len(copy.subexprs) == 1:
            return copy.subexprs[0]

        return copy

    def distribute(self):
        copy = self.copy()

        temp = list(copy.subexprs)
        for i,se in enumerate(copy.subexprs):
            copy.subexprs[i] = se.distribute()

        # only work hard if there are disjunctions
        while 1:
            if not filter(lambda x: isinstance(x, BoolDisj), copy.subexprs):
                break

            if len(copy.subexprs) == 1:
                copy = copy.subexprs[0]
                break

            # we do 2-op cartesian products at a time
            disj = None
            other = None
            for se in copy.subexprs:
                if isinstance(se, BoolDisj):
                    if disj == None:
                        disj = se

                if se != disj and other==None:
                    other = se

                if disj and other:
                    break

            #print copy.subexprs

            # remove them
            copy.subexprs.remove(disj)
            copy.subexprs.remove(other)
          
            pargs = [[other], disj.subexprs]
            products = map(lambda x:list(x), list(itertools.product(*pargs)))
            newse = map(lambda x:BoolConj(x), products)

            # and of or's
            newguy = BoolDisj(newse)
            copy.subexprs.append(newguy)

            #print "converted: ", disj
            #print "      and: ", other
            #print "       to: ", newguy
            #print "   result: ", copy
            #print "----------"
        #print result
        return copy

    def isCNF(self):
        # and subexpressions are cnf if all children are disjunctions that are cnf
        for se in self.subexprs:
            if isinstance(se, BoolDisj):
                if not se.isLeafOp():
                    return False
            else:
                if not isinstance(se, BoolLit):
                    return False

        return True

    def __eq__(self, rhs):
        if not isinstance(rhs, BoolConj):
            return False
        if len(self.subexprs) != len(rhs.subexprs):
            return False
        temp1 = list(self.subexprs)
        temp2 = list(rhs.subexprs)
        for se in temp1:
            if se not in temp2:
                return False
            temp1.remove(se)
            temp2.remove(se)
        return True

    def __str__(self):
        result = '('

        for se in self.subexprs:
            if result != '(':
                result += '*'
            result += str(se)

        return result + ')'

class BoolXor(BoolExpr):
    def __init__(self, subexprs):
        self.subexprs = list(subexprs)

    def copy(self):
        temp = list(self.subexprs)
        for i,se in enumerate(temp):
            temp[i] = se.copy()
        return BoolXor(temp)

    def simplify(self, recur=1):
        copy = self.copy()

        if recur:
            for i,se in enumerate(copy.subexprs):
                copy.subexprs[i] = se.simplify(recur)

        # add all literals % 2, then complement one remaining subexpr if necessary
        constants = filter(lambda x: isinstance(x, BoolConst), copy.subexprs)

        if not constants:
            return copy

        val = 0
        for c in constants:
            copy.subexprs.remove(c)
            val = (val + c.value) % 2

        # if everything was a constant, return the result
        if not copy.subexprs:
            return BoolConst(val)

        # else, if the constants effectively complement a subexpression, do that
        if val:
            copy.subexprs[0] = copy.subexprs[0].complement()

        # finally, if one subexpression is remaining, return it
        if len(copy.subexprs) == 1:
            return copy.subexprs[0]

        # otherwise, return a reduced xor gate
        return copy

    def distribute(self):
        return self.copy()

    def isCNF(self):
        # xor's not allowed in CNF
        return False

    def __eq__(self, rhs):
        if not isinstance(rhs, BoolXor):
            return False
        if len(self.subexprs) != len(rhs.subexprs):
            return False
        temp1 = list(self.subexprs)
        temp2 = list(rhs.subexprs)
        for se in temp1:
            if se not in temp2:
                return False
            temp1.remove(se)
            temp2.remove(se)
        return True

    def __str__(self):
        result = '('

        for se in self.subexprs:
            if result != '(':
                result += '^'
            result += str(se)

        return result + ')'

class BoolNot(BoolExpr):
    def __init__(self, subexpr):
        self.subexprs = [subexpr]

    def copy(self):
        return BoolNot(self.subexprs[0].copy())

    def simplify(self, recur=1):
        temp = self.copy()

        if recur:
            temp.subexprs[0] = temp.subexprs[0].simplify()

        if isinstance(temp.subexprs[0], BoolNot):
            return temp.subexprs[0].subexprs[0]

        if isinstance(temp.subexprs[0], BoolConst):
            return temp.subexprs[0].complement()
    
        return temp

    def TseitinTransform(self, lastName=['gate0']):
        temp = self.copy()

        [aName, aCnf] = temp.subexprs[0].TseitinTransform(lastName)
        cName = self.TseitinTransformGenName(lastName)

        a = BoolLit(aName)
        c = BoolLit(cName)

        # c=/a is true when (/c+/a)*(a+c) is true
        cCnf = (c.complement() + a.complement()) * (c + a)

        return [cName, (cCnf * aCnf).simplify()]

    def __eq__ (self, rhs):
        return isinstance(rhs, BoolNot) and \
            self.subexprs[0] == rhs.subexprs[0]

    def __str__(self):
        return '/' + str(self.subexprs[0])


class BoolLit(BoolExpr):
    def __init__(self, name):
        self.name = name
        self.subexprs = [self]

    def copy(self):
        return BoolLit(self.name)

    def assign(self, name, value):
        if name == self.name:
            return BoolConst(value)
        else:
            return self

    def TseitinTransform(self, lastName=['gate0']):
        # we consider a literal's gate as a "buffer" which is always true
        return [self.name, BoolConst(1)]

    # these are some bottom-of-tree special overrides of BoolExpr
    #
    def countOps(self):
        return 0

    def collectVarNames(self):
        return {self.name:1}

    # operator overloading
    #
    def __eq__(self, rhs):
        return isinstance(rhs, BoolLit) and \
            self.name == rhs.name and self.value == rhs.value

    def __str__(self):
        return self.name

class BoolConst(BoolExpr):
    def __init__(self, value):
        self.value = value

    def copy(self):
        return BoolConst(self.value)

    def evaluate(self):
        return self.value

    def complement(self):
        return BoolConst(self.value ^ 1)

    def TseitinTransform(self, lastName):
        raise NotImplemented("simplify away this constant, first")

    def __eq__(self, rhs):
        return isinstance(rhs, BoolConst) and self.value == rhs.value

    def __str__(self):
        return '%d' % self.value


###############################################################################
# Primality Testing
###############################################################################

# returns 1=="probably not composite", 0=="definitely composite"
def IsPrimeMillerRabin(n):
    # reject even numbers
    if (n & 1) == 0:
        return 0

    one = ZZn(1, n)
    onel = ZZn(n-1, n)

    # now let's get into form n = 2^s * d + 1
    # s must be odd, which is automatically the case if we maximize r
    temp = n-1
    s = 0
    while temp % 2 == 0:
        s += 1
        temp /= 2
    d = temp

    #print "%d = 2^%d * %d + 1" % (n, s, d)

    # base test
    # at most N/4 bases will falsely report a likely prime
    for temp in range(32):
        #print "iteration %d" % temp
        base = random.randrange(1, n-1)

        x = ZZn(base, n)**d
        if x == one or x == onel:
            continue
        
        #print "we don't have a witness! %d^%d != 1 (mod %d)" % (base, s, n)

        # otherwise...
        passing = 0
        for r in range(0,s):
            x = x**2
            if x == one:
                #print "we don't have a pow2 witness! %d^%d == %s"
                return 0
            if x == onel:
                #print "set passing"
                passing = 1
                break
            #print "next"
           
        if not passing: 
            return 0

    return 1

def IsPrime(n):
    return IsPrimeMillerRabin(n)

def NextPrime(n):
    while not IsPrimeMillerRabin(n+1):
        n+=1

    return n+1

###############################################################################
# Factoring Algorithms
###############################################################################

# factor quickly up to 100,000,000
# most algorithms should call upon this if their target decomposes below this
# threshold
FactorSmallThreshold = 100000000
def FactorSmall(n):
    primes = [
        2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,
        73,79,83,89,97,101,103,107,109,113,127,131,137,139,149,151,157,163,167,173,
        179,181,191,193,197,199,211,223,227,229,233,239,241,251,257,263,269,271,277,281,
        283,293,307,311,313,317,331,337,347,349,353,359,367,373,379,383,389,397,401,409,
        419,421,431,433,439,443,449,457,461,463,467,479,487,491,499,503,509,521,523,541,
        547,557,563,569,571,577,587,593,599,601,607,613,617,619,631,641,643,647,653,659,
        661,673,677,683,691,701,709,719,727,733,739,743,751,757,761,769,773,787,797,809,
        811,821,823,827,829,839,853,857,859,863,877,881,883,887,907,911,919,929,937,941,
        947,953,967,971,977,983,991,997,1009,1013,1019,1021,1031,1033,1039,1049,1051,1061,1063,1069,
        1087,1091,1093,1097,1103,1109,1117,1123,1129,1151,1153,1163,1171,1181,1187,1193,1201,1213,1217,1223,
        1229,1231,1237,1249,1259,1277,1279,1283,1289,1291,1297,1301,1303,1307,1319,1321,1327,1361,1367,1373,
        1381,1399,1409,1423,1427,1429,1433,1439,1447,1451,1453,1459,1471,1481,1483,1487,1489,1493,1499,1511,
        1523,1531,1543,1549,1553,1559,1567,1571,1579,1583,1597,1601,1607,1609,1613,1619,1621,1627,1637,1657,
        1663,1667,1669,1693,1697,1699,1709,1721,1723,1733,1741,1747,1753,1759,1777,1783,1787,1789,1801,1811,
        1823,1831,1847,1861,1867,1871,1873,1877,1879,1889,1901,1907,1913,1931,1933,1949,1951,1973,1979,1987,
        1993,1997,1999,2003,2011,2017,2027,2029,2039,2053,2063,2069,2081,2083,2087,2089,2099,2111,2113,2129,
        2131,2137,2141,2143,2153,2161,2179,2203,2207,2213,2221,2237,2239,2243,2251,2267,2269,2273,2281,2287,
        2293,2297,2309,2311,2333,2339,2341,2347,2351,2357,2371,2377,2381,2383,2389,2393,2399,2411,2417,2423,
        2437,2441,2447,2459,2467,2473,2477,2503,2521,2531,2539,2543,2549,2551,2557,2579,2591,2593,2609,2617,
        2621,2633,2647,2657,2659,2663,2671,2677,2683,2687,2689,2693,2699,2707,2711,2713,2719,2729,2731,2741,
        2749,2753,2767,2777,2789,2791,2797,2801,2803,2819,2833,2837,2843,2851,2857,2861,2879,2887,2897,2903,
        2909,2917,2927,2939,2953,2957,2963,2969,2971,2999,3001,3011,3019,3023,3037,3041,3049,3061,3067,3079,
        3083,3089,3109,3119,3121,3137,3163,3167,3169,3181,3187,3191,3203,3209,3217,3221,3229,3251,3253,3257,
        3259,3271,3299,3301,3307,3313,3319,3323,3329,3331,3343,3347,3359,3361,3371,3373,3389,3391,3407,3413,
        3433,3449,3457,3461,3463,3467,3469,3491,3499,3511,3517,3527,3529,3533,3539,3541,3547,3557,3559,3571,
        3581,3583,3593,3607,3613,3617,3623,3631,3637,3643,3659,3671,3673,3677,3691,3697,3701,3709,3719,3727,
        3733,3739,3761,3767,3769,3779,3793,3797,3803,3821,3823,3833,3847,3851,3853,3863,3877,3881,3889,3907,
        3911,3917,3919,3923,3929,3931,3943,3947,3967,3989,4001,4003,4007,4013,4019,4021,4027,4049,4051,4057,
        4073,4079,4091,4093,4099,4111,4127,4129,4133,4139,4153,4157,4159,4177,4201,4211,4217,4219,4229,4231,
        4241,4243,4253,4259,4261,4271,4273,4283,4289,4297,4327,4337,4339,4349,4357,4363,4373,4391,4397,4409,
        4421,4423,4441,4447,4451,4457,4463,4481,4483,4493,4507,4513,4517,4519,4523,4547,4549,4561,4567,4583,
        4591,4597,4603,4621,4637,4639,4643,4649,4651,4657,4663,4673,4679,4691,4703,4721,4723,4729,4733,4751,
        4759,4783,4787,4789,4793,4799,4801,4813,4817,4831,4861,4871,4877,4889,4903,4909,4919,4931,4933,4937,
        4943,4951,4957,4967,4969,4973,4987,4993,4999,5003,5009,5011,5021,5023,5039,5051,5059,5077,5081,5087,
        5099,5101,5107,5113,5119,5147,5153,5167,5171,5179,5189,5197,5209,5227,5231,5233,5237,5261,5273,5279,
        5281,5297,5303,5309,5323,5333,5347,5351,5381,5387,5393,5399,5407,5413,5417,5419,5431,5437,5441,5443,
        5449,5471,5477,5479,5483,5501,5503,5507,5519,5521,5527,5531,5557,5563,5569,5573,5581,5591,5623,5639,
        5641,5647,5651,5653,5657,5659,5669,5683,5689,5693,5701,5711,5717,5737,5741,5743,5749,5779,5783,5791,
        5801,5807,5813,5821,5827,5839,5843,5849,5851,5857,5861,5867,5869,5879,5881,5897,5903,5923,5927,5939,
        5953,5981,5987,6007,6011,6029,6037,6043,6047,6053,6067,6073,6079,6089,6091,6101,6113,6121,6131,6133,
        6143,6151,6163,6173,6197,6199,6203,6211,6217,6221,6229,6247,6257,6263,6269,6271,6277,6287,6299,6301,
        6311,6317,6323,6329,6337,6343,6353,6359,6361,6367,6373,6379,6389,6397,6421,6427,6449,6451,6469,6473,
        6481,6491,6521,6529,6547,6551,6553,6563,6569,6571,6577,6581,6599,6607,6619,6637,6653,6659,6661,6673,
        6679,6689,6691,6701,6703,6709,6719,6733,6737,6761,6763,6779,6781,6791,6793,6803,6823,6827,6829,6833,
        6841,6857,6863,6869,6871,6883,6899,6907,6911,6917,6947,6949,6959,6961,6967,6971,6977,6983,6991,6997,
        7001,7013,7019,7027,7039,7043,7057,7069,7079,7103,7109,7121,7127,7129,7151,7159,7177,7187,7193,7207,
        7211,7213,7219,7229,7237,7243,7247,7253,7283,7297,7307,7309,7321,7331,7333,7349,7351,7369,7393,7411,
        7417,7433,7451,7457,7459,7477,7481,7487,7489,7499,7507,7517,7523,7529,7537,7541,7547,7549,7559,7561,
        7573,7577,7583,7589,7591,7603,7607,7621,7639,7643,7649,7669,7673,7681,7687,7691,7699,7703,7717,7723,
        7727,7741,7753,7757,7759,7789,7793,7817,7823,7829,7841,7853,7867,7873,7877,7879,7883,7901,7907,7919,
        7927,7933,7937,7949,7951,7963,7993,8009,8011,8017,8039,8053,8059,8069,8081,8087,8089,8093,8101,8111,
        8117,8123,8147,8161,8167,8171,8179,8191,8209,8219,8221,8231,8233,8237,8243,8263,8269,8273,8287,8291,
        8293,8297,8311,8317,8329,8353,8363,8369,8377,8387,8389,8419,8423,8429,8431,8443,8447,8461,8467,8501,
        8513,8521,8527,8537,8539,8543,8563,8573,8581,8597,8599,8609,8623,8627,8629,8641,8647,8663,8669,8677,
        8681,8689,8693,8699,8707,8713,8719,8731,8737,8741,8747,8753,8761,8779,8783,8803,8807,8819,8821,8831,
        8837,8839,8849,8861,8863,8867,8887,8893,8923,8929,8933,8941,8951,8963,8969,8971,8999,9001,9007,9011,
        9013,9029,9041,9043,9049,9059,9067,9091,9103,9109,9127,9133,9137,9151,9157,9161,9173,9181,9187,9199,
        9203,9209,9221,9227,9239,9241,9257,9277,9281,9283,9293,9311,9319,9323,9337,9341,9343,9349,9371,9377,
        9391,9397,9403,9413,9419,9421,9431,9433,9437,9439,9461,9463,9467,9473,9479,9491,9497,9511,9521,9533,
        9539,9547,9551,9587,9601,9613,9619,9623,9629,9631,9643,9649,9661,9677,9679,9689,9697,9719,9721,9733,
        9739,9743,9749,9767,9769,9781,9787,9791,9803,9811,9817,9829,9833,9839,9851,9857,9859,9871,9883,9887,
        9901,9907,9923,9929,9931,9941,9949,9967,9973,10007]

    factors = []
    alldone = 0

    while 1:
        s = int(math.sqrt(n))

        for p in primes:
            if p > s:
                alldone = 1
                break
            elif n % p == 0:
                factors.append(p)
                n = n / p
                break

        if alldone:
            break

    return factors + [n] 

# pollard rho factoring
#
# we imagine every integer assigned a birthday [0,p-1] via f:x -> x%p
# this p is an unkown factor
# it should take a collection of roughly sqrt(p) numbers until a birthday is shared
# between two elements, call them x,y
# x % p = y % p
# x = y (mod p)
# p|(x-y)

# of course we don't know yet p, but we can detect when the above condition has occurred
# by computing the gcd(x-y, n) since p (which we use to refer really to ANY of the factors
# that is revealed) divides both of them

# here the cycle detection is just to prevent the random walk from getting
# stuck in a loop - the point at which a cycle forms is not used in any calculation
# like in the rho DLP algorithm
# 

# attempt a single random walk searching for a factor
#
# [input]
#   start: starting point of tortoise, hare race
#       n: composite number to attempt a walk on
# [output]
#   - on fail, return n
#   - on success, return 1<d<n
#
def FactorPollardRho_Attempt(n, start, e, c):
    d = 1
    tortoise = hare = start

    while d == 1:
        # one step
        tortoise = (tortoise**e + c) % n
        # two step
        hare = (hare**e + c) % n
        hare = (hare**e + c) % n
       
        #print "(d,tortoise,hare)=(%d,%d,%d)" % (d,tortoise,hare)
        d = fractions.gcd(abs(tortoise-hare), n)
       
    # at this point, we have two cases:
    # case A) d=gcd(x-y,n)=n -> x=y (cycle detected, stop!)
    # case B) 1<d<n -> divisor found!
    return d

# try until a single factor is pulled out of a composite number
#
# [input]
#   n: composite number to pull factor from
#
def FactorPollardRho_Single(n):
    # our random mapping is f : x -> x^e + c
    # where e and c range of the below possibilities
    e_lookup = [2,3,5]
    c_lookup = [2,3,5,7,11]
    e_index = -1
    c_index = -1

    rc = n

    while rc == n:
        # increment
        e_index = (e_index + 1) % len(e_lookup)
        c_index = (c_index + 1) % len(c_lookup)
        # randomize the walk starting point
        start = random.randrange(0, n) 
        # go!
        rc = FactorPollardRho_Attempt(n, start, e_lookup[e_index], c_lookup[c_index])

    return rc

# completely factor a number using Pollard Rho method
#
# [input]
#   n: the composite number to factor
#
def FactorPollardRho(n):
    factors = []

    if IsPrime(n):
        return [n]

    if n < FactorSmallThreshold:
        return FactorSmall(n)

    f0 = FactorPollardRho_Single(n)
    f1 = n/f0
    return FactorPollardRho(f0) + FactorPollardRho(f1)

# generic factor call - point this at your favorite routine
#
def Factor(n):
    if n<FactorSmallThreshold:
        return FactorSmall(n)

    return FactorPollardRho(n)
    
#
def Subsets(x):
    answer = []

    n = len(x)

    for i in range(2**n):
        subset = []
        for j in range(n):
            if i & (1<<j):
                subset.append(x[j])

        answer.append(subset)

    return answer

# return list of distinct divisors
# [input]
#   "raw" list of factors eg: [2,2,3,3,3,5]
# [output]
#   distinct list of divisors
#
def DivisorsGivenFactors(factors):
    result = [1]

    # generate list sequential powers of the factors
    # eg: [2,2,3,3,3,5] -> [[2,4], [3,9,27], [5]]
    cartfacts = []
    while factors:
        powers = []

        f = factors[0]
        # add f^0, f^1, f^2, ...
        for e in range(factors.count(f)+1):
            powers.append(f**e)
        # remove all f's from factor
        while f in factors:
            factors.remove(f)
        # finally, add [f^1, f^2, ...] to the list
        cartfacts.append(powers)

    #print cartfacts
    # unique divisors now are the cross product of this...

    result = []
    for tuple in itertools.product(*cartfacts):
        #print "tuple: ", tuple
        # the product
        result.append(reduce(lambda x,y:x*y, tuple))

    return result

# [notes]
#  - this must factor the number each time
def Divisors(n):
    return DivisorsGivenFactors(Factor(n))
   

###############################################################################
# Number-Theoretic Algorithms
###############################################################################

# digit-by-digit (base 2) integer square root algorithm
# (since python math.sqrt() converts to float)
# returns y = f(x) s.t. y^2 < x and no z>y exists with the same property
def LongSqrt(x):
    root = 0
    res = 0    

    # position '11' mask
    mask = 3
    shift = 0
    while mask < x:
        mask <<= 2
        shift += 2 

    while shift >= 0:
        # get pair of bits
        c = (x & mask) >> shift
        # update remainder
        res = (res << 2) | c

        # append root
        prod = (root<<2) + 1

        root <<= 1
        if prod <= res:
            root |= 1
            res -= prod

        # continue
        mask >>= 2
        shift -= 2

    return root

# Pollard's rho algorithm for discrete logarithms
# calculate x in g^x = y within group G = <g>
#
# [notes]
#  - cycle detection: Floyd (one walks 2x speed as the other)
#  - random walk: the original 3-partition one

# given e = g^a * y^b, return a stepped e and calculate
# adjusted a, b to keep track of the expression
def DilogPollardRhoStep(e, g, y, a, b, order):
    bucket = e.bucketize(3)

    # elements in bucket 0 are multiplied by y
    if bucket == 0:   
        return [y.groupAction(e), a, ZZn(b+1, order).lift()]
    # elements in bucket 1 are squared
    if bucket == 1:
        return [e.groupAction(e), ZZn(2*a, order).lift(), ZZn(2*b, order).lift()]
    # elements in bucket 2 are multiplied by g
    return [g.groupAction(e), ZZn(a+1, order).lift(), b] 
 
def DilogPollardRho(g, y, init_a=1, init_b=1):
    print "derp!"
    order = g.order()
    print "g's order is: ", order
    
    # we keep track of search
    # the tortoise = g^a * y^b
    (tortoise, tortoise_a, tortoise_b) = (g**init_a * y**init_b, init_a, init_b)
    # the hare
    (hare, hare_a, hare_b) = (tortoise, init_a, init_b)

    itera = 0

    while 1:
        # tortoise takes one step
        (tortoise, tortoise_a, tortoise_b) = \
            DilogPollardRhoStep(tortoise, g, y, tortoise_a, tortoise_b, order)

        # hare takes two steps
        (hare, hare_a, hare_b) = \
            DilogPollardRhoStep(hare, g, y, hare_a, hare_b, order)
        (hare, hare_a, hare_b) = \
            DilogPollardRhoStep(hare, g, y, hare_a, hare_b, order)

        print "iter:%d (a,b,A,B)=(%d,%d,%d,%d)" % (itera, tortoise_a, tortoise_b, hare_a, hare_b)
        itera += 1

        # they match! we looped at some point!      
        if tortoise == hare:
            # tortoise = g^a * y^b
            # hare = g^A * y^B
            # equating, we have:
            # g^a * y^b = g^A * y^B
            # if the dilog exists, then y = g^x, so we substitute:
            # g^a * (g^x)^b = g^A * (g^x)^B
            # g^a * g^(bx) = g^A * g^(Bx)
            # g^(a+bx) = g^(A+Bx)
            # a+bx = A+Bx (mod ord(G))  
            # (b-B)x = A-a
            # x = (b-B)/(A-a)

            if tortoise_b == hare_b:
                raise ValueError("invalid b, B found")
            if tortoise_a == hare_a:
                raise ValueError("invalid a, A found")

            # danger, danger
            if hare_a / (1.0 * tortoise_a) == hare_b / (1.0 * tortoise_b):
                print "trival solution found - elements along walk are just multiples of one another"
                (init_a, init_b) = (random.randrange(1, order), random.randrange(1, order))
                (tortoise, tortoise_a, tortoise_b) = (g**init_a * y**init_b, init_a, init_b)
                (hare, hare_a, hare_b) = (g**init_a * y**init_b, init_a, init_b)
                continue 


            factors = Factor(order)
            print "solving equations over factors: ", factors

            # collect the equations
            mods = []
            for f in factors:
                numerator = ZZn(tortoise_b - hare_b, f)
                denominator = ZZn(hare_a - tortoise_a, f)
                print "adding to equations: %d/%d (mod %d)" % (numerator.elem, denominator.elem, f) 
                mods.append(numerator / denominator)

            # combine equations
            print "sending ", mods
            result = ChineseRemainderTheorem(mods)
            print result

#
# [input]
#  - two ZZn
# [notes]
#  - modulii are expected coprime
def ChineseRemainderTheoremPair(a1, a2):
    n1 = a1.modulus
    n2 = a2.modulus
    n1_inv_n2 = InverseMod(n1, n2)
    n2_inv_n1 = InverseMod(n2, n1)
    #print "returning ZZn(%d*%d + %d*%d, %d)" % (a1.elem, n2_inv_n1, a2.elem, n1_inv_n2, n1*n2)
    return ZZn(a1.elem * n2 * n2_inv_n1 + a2.elem * n1 * n1_inv_n2, n1*n2)

#
# [input]
#  - list of ZZn's to combine
def ChineseRemainderTheorem(l):
    answer = l.pop(0)
    while l:
        answer = ChineseRemainderTheoremPair(answer, l.pop(0))
    return answer

# Exponentiation by Squaring
# calculating b^e
# suppose e=1+2^3+2^8
# -> b^e = b^1 * b^(2^3) * b^(2^8)
# other bases would work, but e is already represented internally as base 2
#
# b can be a normal python integer, or a FieldE (field element)
# e is a normal python integer (required! else integer divison won't work)
def ExponentiationBySquaring(b, e):
    result = 1 if type(b)==type(0) else b.one()
    runner = b

    while e:
        if e & 1:
            #print "result: ", result
            #print "runner: ", runner
            result = result * runner

        # track b^(next power)
        runner = runner * runner
            
        # consider next set bit
        e = e/2

    return result

# same, but for repeated "add" operator, calculate b*e, e \in Z
def MultiplicationByDoubling(b, e):
    result = b.zero()  
    runner = b

    while e:
        if e & 1:
            result = result + runner

        # track (next double)*b
        runner = runner + runner

        # next bit
        e = e/2

    return result

# eXtended Euclidean algorithm
# given x,y yields (a,b,gcd(x,y)) s.t. ax + by = gcd(x,y)
#
# obviously gcd(x,y)|x and gcd(x,y)|y
# it's easy to see that gcd(x-y) must also divide the gap |x-y|
# algorithm essentially reduces and reduces self gap, tracking also how much
# each of x and y are used to form the smallest gap
#
def ExtendedEuclidean(x, y):
    if x-y == x:
        return [1, 0, 1]
    if y-x == y:
        return [0, 1, 1]

    # initially x = (1)x + (0)y
    ax,bx = 1, 0
    # initially y = (0)x + (1)y
    ay,by = 0, 1

    # position largest elem in x
    if x<y:
        x,ax,bx,y,ay,by = y,ay,by,x,ax,bx

    while 1:
        times = x/y

        x = x - times*y
        ax = ax - times*ay
        bx = bx - times*by

        if x==0:
            break;

        # position largest elem in x
        x,ax,bx,y,ay,by = y,ay,by,x,ax,bx
   
    return [ay, by, y]     

def InverseMod(x, p):
    xgcd = ExtendedEuclidean(x, p)
    if xgcd[2] != 1:
        raise ValueError("x is not in Z_p (%d is not in Z_%d)" % (x, p))
    if(xgcd[0] > 0):
        return xgcd[0]
    return xgcd[0] + p

###############################################################################
# Groups
###############################################################################

# abstract Group type
class Group(object):
    def __init__(self, order):
        self.m_order = order

        # delay calculating this
        self.m_order_factors = []

    def order(self):
        return self.m_order

    def order_factors(self):
        # requested! put in the work to calculate this!
        if not self.m_order_factors:
            self.m_order_factors = Factor(self.m_order)

        return self.m_order_factors

class GroupElem(object):
    def __init__(self, G):
        self.G = G
    # identity
    def one(self):
        raise NotImplemented()
    # concrete groups can choose to represent their group operation with 
    # add/sub or with mul/div
    def __add__(self, rhs):
        raise NotImplemented()
    def __sub__(self, rhs):
        raise NotImplemented()
    def __mul__(self, rhs):
        raise NotImplemented()
    def __div__(self, rhs):
        raise NotImplemented()
    # whatever is chosen, best to reference here for generic algorithms
    def groupAction(self, rhs):
        raise NotImplemented()
    # negation of the 
    def __neg__(self):          # eg: -a s.t. a + (-a) = 0
        raise NotImplemented()
    def __eq__(self, rhs):
        raise NotImplemented()
    def __ne__(self, rhs):
        raise NotImplemented()
    def __nonzero__(self):
        raise NotImplemented()
    # return containing group
    def group(self):
        raise NotImplemented()
    #
    def order(self):
        raise NotImplemented()
    # some algos (pollard rho for example) need group elements randomly assigned to n buckets,
    # return [0, n-1] the index to which bucket this element is in
    def bucketize(self, n):
        raise NotImplemented()

# multiplicative group of integers modulo n
class ZZn(GroupElem):
    def __init__(self, a, n):
        if a<0:
            a += n
        if a>n:
            a = a % n
        self.elem = a
        # BUG BUG: for now, assume n is prime because no totient calculation has occurred yet
        self.n = n
        self.modulus = n
        self.G = Group(n-1)

    def group(self):
        return self.G

    def order(self):
        for d in sorted(DivisorsGivenFactors(self.G.order_factors())):
            if self**d == ZZn(1, self.n):
                return d

        return -1

    def one(self):
        return ZZn(1, self.n)

    # we represent the group action multiplicatively
    def __mul__(self, rhs):
        return ZZn((self.elem * rhs.elem) % self.n, self.n)
    def __div__(self, rhs):
        return self * (rhs**-1)
    def __pow__(self, e):
        result = None
        # b^(-e) = (b^(-1))^e
        if e < 0:
            new_e = InverseMod(self.elem, self.n)
            e = -1*e
        else:
            new_e = self.elem

        temp = ZZn(new_e, self.n) 

        return ExponentiationBySquaring(temp, e)

    # generic group operation
    def groupAction(self, rhs):
        return self * rhs

    # other
    # equality test: compare integer element and modulus
    def __eq__(self, rhs):
        return (self.elem == rhs.elem) and (self.n == rhs.n)
    def __ne__(self, rhs):
        return not (self == rhs)
    # return the integer element
    def lift(self):
        return self.elem
    #  
    def __str__(self):
        return 'Mod(%d, %d)' % (self.elem, self.n)
    def __repr__(self):
        return self.__str__()

    # simple bucketizer
    def bucketize(self, n):
        return self.elem % n

###############################################################################
# Fields
###############################################################################

#
class Field(object):
    def __init__(self, char, deg):
        self.char = char
        self.deg = deg
    def order(self):
        return self.char ** self.deg
    def __eq__(self, rhs):
        return (self.char == rhs.char) and (self.deg == rhs.deg)
    def __ne__(self, rhs):
        return not (self == rhs)
    def __str__(self):
        return 'F_{%d^%d}' % (self.char, self.deg)
    def __repr__(self):
        return 'Field(%d, %d)' % (self.char, self.deg)

# abstract field element type
class FieldElem(object):
    def __init__(self, K):
        self.K = K
    def __add__(self, rhs):
        pass
    def __sub__(self, rhs):
        pass
    def __mul__(self, rhs):
        pass
    def __div__(self, rhs):
        pass
    def __neg__(self):          # eg: -a s.t. a + (-a) = 0
        pass
    def __pow__(self, exp):     # eg: a**(-1) == a^(-1)
        pass
    def __eq__(self, rhs):
        pass
    def __ne__(self, rhs):
        pass
    def __nonzero__(self):      # eg: if a:
        pass
    def characteristic(self):
        pass

# prime fields where elements have representation Z_p
class PFieldElem(FieldElem):
    def __init__(self, K, e):
        self.K = K
        self.e = e

        if type(self.e) != type(0) and type(self.e) != type(0L):
            raise ValueError('expected integer type for field element initializer')

    def zero(self): # we call the additive identity "0"
        return PFieldElem(self.K, 0)

    def one(self): # we call the multiplicative identity "1"
        return PFieldElem(self.K, 1)

    def __add__(self, rhs):
        new_e = (self.e + rhs.e) % self.K.char
        return PFieldElem(self.K, new_e)

    def __neg__(self):
        new_e = (self.K.char - self.e)
        return PFieldElem(self.K, new_e)

    def __sub__(self, rhs):
        return self + (-rhs)

    def __mul__(self, rhs):
        if type(rhs) == type(0):
            # allow multiplication by an int -> repeated adding
            return MultiplicationByDoubling(self, rhs)
            
        # true field multiplication by another element
        new_e = (self.e * rhs.e) % self.K.char
        return PFieldElem(self.K, new_e)

    def __div__(self, rhs):
        return self * rhs**-1

    def __pow__(self, e):
        result = None
        # b^(-e) = (b^(-1))^e
        if e < 0:
            xgcd = ExtendedEuclidean(self.e, self.K.char)
            if xgcd[2] != 1:
                raise ValueError("gcd(%d,%d) != 1" % (self.e, self.K.char))
            new_e = xgcd[0]
            if new_e < 0:
                new_e += self.K.char
            result = PFieldElem(self.K, new_e)
            e = -1*e
        else:
            result = self

        return ExponentiationBySquaring(result, e)

    def __eq__(self, rhs):
        if rhs == None:
            return False

        # convert integers to allow for comparison
        if type(rhs) == type(0):
            if rhs >= self.K.char:
                raise ValueException("comparing against a non field element")

            rhs = PFieldElem(self.K.char, rhs) 

        if (self.e == rhs.e) and (self.K == rhs.K):
            return True
        else:
            return False

    def __ne__(self, rhs):
        return not (self == rhs)

    def __str__(self):
        return '%d' % self.e

    def __repr__(self):
        return 'PFieldElem(%s, %d)' % (repr(self.K), self.e)

    def __nonzero__(self):
        return self.e != 0

    def characteristic(self):
        return self.K.char

# extension field elements
# elements represented as a polynomial ring over prime field elements
class EFieldElem(FieldElem):
    def __init__(self, K, e):
        self.K = K
        self.e = PolyRing(e)

    def zero(self): # we call the additive identity "0"
        new_e = map(lambda x: PFieldElem(x, self.K.char), [0]*self.K.deg)
        return EFieldElem(self.K, new_e)

    def one(self): # we call the multiplicative identity "1"
        new_e = map(lambda x: PFieldElem(x, self.K.char), [0]*(self.K.deg-1) \
                    + [1])
        return EFieldElem(self.K, new_e)

    # addition done by adding polynomials (no reduction needed)
    def __add__(self, rhs):
        new_e = self.e + rhs.e
        return EFieldElem(self.K, new_e)

    # negation done by subtracting polynomials (no reduction needed)
    def __neg__(self):
        new_e = (self.K.poly - self.e)
        return EFieldElem(self.K, new_e)

    # multiplication done by K[x] % primitive
    def __mul__(self, rhs):
        if type(rhs) == type(0):
            # allow multiplication by an int -> repeated adding
            return MultiplicationByDoubling(self, rhs)
            
        # true field multiplication by another element
        new_e = (self.e * rhs.e) % self.K.poly
        return EFieldElem(self.K, new_e)

    # operations that are just composed of others
    def __sub__(self, rhs):
        return self + (-rhs)

    def __div__(self, rhs):
        return self * rhs**-1

    def __pow__(self, e):
        result = None
        # b^(-e) = (b^(-1))^e
        if e < 0:
            xgcd = ExtendedEuclidean(self.e, self.K.poly)
            if xgcd[2] != 1:
                raise ValueError("gcd(%d,%d) != 1" % (self.e, self.K.char))
            new_e = xgcd[0]
            if new_e < 0:
                new_e += self.K.char
            result = EFieldElem(self.K, new_e)
            e = -1*e
        else:
            result = self

        return ExponentiationBySquaring(result, e)

    def __eq__(self, rhs):
        if rhs == None:
            return False

        if (self.e == rhs.e) and (self.K == rhs.K):
            return True
        else:
            return False

    def __ne__(self, rhs):
        return not (self == rhs)

    def __str__(self):
        return '%d' % self.e

    def __repr__(self):
        return 'EFieldElem(%s, %d)' % (repr(self.K), self.e)

    def __nonzero__(self):
        return self.e != 0

    def characteristic(self):
        return self.K.char

###############################################################################
# Elliptic Curves
###############################################################################

# abstract elliptic curve class
# curves with different representations and underlying fields or whatever can
# extend this...
class EllipticCurve(object):
    def __init__(self, field, coeffs):
        self.K = field

        # y^2 + a1*xy + a3*y = x^3 + a2*x^2 + a4*x + a6
        self.a1, self.a2, self.a3, self.a4, self.a6 = coeffs

    def HasseBound(self):
        # basically the number of points on the curve differs from the number of field
        # elements by at most 2*sqrt(#F)
        order = self.K.order()
        a_p = 2 * LongSqrt(order)
        lower = order + 1 - a_p
        upper = order + 1 + a_p
        return [lower, upper]

    def isAnomalous(self, order=0):
        '''
        anomalous curves have the same number of points as there are
        elements in their underlying field
        said differently, their trace a_p == 1 since #E = #F + 1 - a_p
        '''
        if not order:
            order = self.order()

        return self.K.order() == order

    def isSupersingular(self, order=0):
        '''
        supersingular curves have order divisible by the underlying
        field's characteristic
        '''
        if not order:
            order = self.order()

        return not (order % self.K.characteristic)

    def __str__(self):
        terms_lhs = ['y^2']
        terms_rhs = ['x^3']

        if self.a1:
            terms_lhs.append('(%s)*xy' % self.a1)
        if self.a3:
            terms_lhs.append('(%s)*y' % self.a3)
        if self.a2:
            terms_rhs.append('(%s)*x^2' % self.a2)
        if self.a4:
            terms_rhs.append('(%s)*x' % self.a4)
        if self.a6:
            terms_rhs.append('(%s)' % self.a6)

        return '%s = %s over %s' % (' + '.join(terms_lhs), ' + '.join(terms_rhs), str(self.K))

    def __repr__(self):
        return 'EllipticCurve(%s, [%s,%s,%s,%s,%s])' % \
                    (repr(self.K), repr(self.a1), repr(self.a2), repr(self.a3), \
                    repr(self.a4), repr(self.a6))

# member of the rational points (the group of points)
class ECPoint(object):
    def __add__(self, rhs): # eg: P+Q
        pass
    def __sub__(self, rhs): # eg: P-Q = P+(-Q)
        pass
    def __mul__(self, rhs): # eg: P*5
        pass
    def __inv__(self, rhs): # eg: -P
        pass
    def __eq__(self, rhs):  # eg: if P==Q
        pass
    def __neq__(self, rhs): # eg: if P!=Q
        pass
    def isId(self):         # is this point the point-at-infinity, [0]?
        pass
    def zero(self):           # return [0]
        pass

# kglib type A curves/points:
# over finite field, cartesian (non-projective) coordinates
# characteristic not 2 or not 3 (so only a4, a6 non-zero by change of variables)
# SIMPLEST CASE!
class ECurveA(EllipticCurve):
    # send [a1,a2,a3,a4,a6]
    def __init__(self, field, coeffs):
        # the underlying field
        super(ECurveA, self).__init__(field, coeffs)

        if self.a1 or self.a2 or self.a3:
            raise NotImplemented("ECurveA is for simplified Wierstrass with only a4, a6 nonzero")

        if (self.a4 and (self.a4.characteristic() <= 3)) or \
            (self.a6 and (self.a6.characteristic() <= 3)):
            raise ValueError("ECurveA must be over field of characteristic > 3")

    def isOnCurve(self, P):
        return self.isOnCurve(P.x, P.y)

    def __str__(self):
        return 'y^2 = x^3 + (%s)*x + (%s) over (%s)' % (str(self.a4), str(self.a6), str(self.K))
 
#
class ECPointA(ECPoint):
    # python None indicates [0]
    def __init__(self, E, x, y):
        self.E = E
        self.x = x
        self.y = y

        if not self.isOnCurve():
            print str(self)
            raise ValueError("point is not on curve!")

    def isOnCurve(self):
        x = self.x
        y = self.y
       
        if self.isId():
            return True
 
        if y**2 + self.E.a1*x*y + self.E.a3*y == \
            x**3 + self.E.a2*x*x + self.E.a4*x + self.E.a6:
            return True
        else:
            return False

    def __add__(self, rhs):
        if self.isId():
            return rhs
        if rhs.isId():
            return self
        # case: adding inverse points
        if self == -rhs:
            return self.zero()
        # case: point doubling
        if self == rhs:
            t = ((self.x**2)*3 + self.E.a4)/(self.y*2)
            x = t*t - self.x*2
            y = t*(self.x - x) - self.y
            return ECPointA(self.E, x, y)
        # case: normal (non-doubling)
        else: 
            m = (rhs.y - self.y)/(rhs.x - self.x)
            x = m**2 - self.x - rhs.x
            y = m*(self.x - x) - self.y
            return ECPointA(self.E, x, y)

    def isId(self):
        return (type(self.x) == type(None)) and (type(self.y) == type(None))

    def __eq__(self, rhs):
        return (self.x == rhs.x) and (self.y == rhs.y) 

    def __mul__(self, rhs):
        if self.isId():
            return copy.copy(self)
        return MultiplicationByDoubling(self, rhs)

    def __neg__(self):
        return ECPointA(self.E, self.x, -self.y)
    
    def __sub__(self, rhs):
        return self + (-rhs) 
       
    def zero(self):
        return ECPointA(E, None, None)
         
    def __str__(self): 
        if self.x == None and self.y == None:
            return '(0) on %s' % str(self.E)
        else:
            return '(%s, %s) on %s' % (str(self.x), str(self.y), str(self.E))

    def __repr__(self):
        return 'ECPointA(%s, %s, %s)' % (repr(self.E), repr(self.x), repr(self.y))



# counting points
# Shanks-Mestre (used by Pari/GP
# Baby-step Giant-step
# Schoof

###############################################################################
# main()
###############################################################################
if __name__ == '__main__':
    random.seed()
    
    print "Running some tests..."
   
    arg = None
    if len(sys.argv) >= 2:
        arg = sys.argv[1]

    if arg==None or arg=="xtea":
        # these test vectors come from http://www.freemedialibrary.com/index.php/XTEA_test_vectors
        
        print "XTEA test..."

        keys = [
            "\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f",
            "\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f",
            "\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f",
            "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00",
            "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00",
            "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        ]

        plaintexts = [
            "\x41\x42\x43\x44\x45\x46\x47\x48",
            "\x41\x41\x41\x41\x41\x41\x41\x41",
            "\x5a\x5b\x6e\x27\x89\x48\xd7\x7f",
            "\x41\x42\x43\x44\x45\x46\x47\x48",
            "\x41\x41\x41\x41\x41\x41\x41\x41",
            "\x70\xe1\x22\x5d\x6e\x4e\x76\x55"
        ]

        ciphertexts = [
            "\x49\x7d\xf3\xd0\x72\x61\x2c\xb5",
            "\xe7\x8f\x2d\x13\x74\x43\x41\xd8",
            "\x41\x41\x41\x41\x41\x41\x41\x41",
            "\xa0\x39\x05\x89\xf8\xb8\xef\xa5",
            "\xed\x23\x37\x5a\x82\x1a\x8c\x2d",
            "\x41\x41\x41\x41\x41\x41\x41\x41"
        ]

        for i in range(len(keys)):
            key = keys[i]
            plain = plaintexts[i]

            cipher = xtea_encrypt_block(plain, key)

            if cipher == ciphertexts[i]:
                print "PASS"
            else:
                print "FAIL"

            if xtea_decrypt_block(cipher, key) == plain:
                print "PASS"
            else:
                print "FAIL"

        input = "\x49\x7d\xf3\xd0\x72\x61\x2c\xb5And in front of my desk I see a little blue Android and a whiteboard, what do I write?"
        ct = xtea_encrypt_ofb(input, keys[0]) 
        if ct == input:
            print "FAIL"
        #print repr(ct)
        if input == xtea_encrypt_ofb(ct, keys[0]):
            print "PASS"
        else:
            print "FAIL"

 
    if arg==None or arg=="primefield": 
        print "Prime field tests..."
        F = Field(127, 1) # F_{127^1}
        g = PFieldElem(F, 3) # F = <g>
        
        for i in range(1024):
            a = PFieldElem(F, random.randrange(0,127)) 
            b = PFieldElem(F, random.randrange(0,127))
        
            # test inversion, multiplication
            if b != b.zero():
                q = a/b
                print "(%s)/(%s) = (%s)" % (a, b, q)
                t = q*b
                print "(%s)*(%s) = (%s)" % (q, b, t)
                if t==a:
                    print "PASS"
                else:
                    raise Exception('FAIL')
        
            # test addition, subtraction
            s = a + b
            print "(%s)+(%s) = (%s)" % (a, b, s)
            d = s - b
            print "(%s)-(%s) = (%s)" % (s, b, d)
            if d==a:
                print "PASS"
            else:
                raise Exception('FAIL')
   
    if arg==None or arg=="elliptic": 
        print "Elliptic Curve Tests..."
        
        # work over F_23
        F = Field(23,1)
        
        # elliptic curve Wierstrass parameters
        ai = map(lambda x: PFieldElem(F, x), [0, 0, 0, 1, 0])
        
        # the curve itself
        E = ECurveA(F, ai)
        print E
        
        # a point
        Px, Py = PFieldElem(F,9), PFieldElem(F,5)
        P = ECPointA(E, Px, Py)
        print P
           
        Qx, Qy = PFieldElem(F,9), PFieldElem(F,18)
        Q = ECPointA(E, Qx, Qy)
        print Q
        print Q+P
         
        for i in range(10):
            Q = P*i
            print "P*%d: %s" % (i, str(Q))
        
        # bigger parameters now
        # should print (verified with sage):
        #(0 : 1 : 0)
        #(920019632805867328128779577194949110656005543293392670030 : 247924023714148178898329740691786895218087166284853058178 : 1)
        #(1347368923186712640648783809374613834547443961974834387610 : 4112389959757745391454835779367729479686292529710684578030 : 1)
        #(5136072150299522727048713884921549466888394167843055557753 : 670759223811902288870805701970579108550537352829254733458 : 1)
        #(1523758263928574765292370494195845945669929150675275480810 : 1825086083694868727663500708139317408289339684224336360203 : 1)
        #(3225035031647916196326675568092081315499746913291130727961 : 3862609992862923384096473215341563562672049055673897245136 : 1)
        #(3033242856509374779459856267026730920528641019566242363839 : 2837374515709986657488201449785133510656808342978441386115 : 1)
        #(3525594817842830522356194144342983169660348146136984362694 : 4038421835327402660163567259258456243712931147482944846450 : 1)
        #(657723557911816259375376113617675555124843796900715252667 : 3806015207794008162697117778821888037361827943817320145382 : 1)
        #(1660669180506570899843379425665210350557400564111037059779 : 3557313439153671053486603110953622413957092959496717974886 : 1)
        F = Field(5186715201442783011196302036546738736427436330054065589317, 1)
        ai = map(lambda x: PFieldElem(F, x), [0, 0, 0, -4, 0])
        E = ECurveA(F, ai)
        print E
        Px, Py, Qx, Qy = map(lambda x: PFieldElem(F,x), [ \
            920019632805867328128779577194949110656005543293392670030, \
            247924023714148178898329740691786895218087166284853058178, \
            1655646638614857830673453525865145510699045501734303194406, \
            4260089289459941068169905641641773579714103470632308043647 \
          ])
        P = ECPointA(E, Px, Py)
        print 'P: ', P
        Q = ECPointA(E, Qx, Qy)
        print 'Q: ', Q
        for i in range(10):
            Q = P*i
            print "P*%d: %s" % (i, str(Q))

