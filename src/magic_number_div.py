import math
import sys

def magicgu(nmax, d):
	nc = (nmax +1 //d) *d -1
	nbits = int(math.log(nmax, 2)) +1
	for p in range(0, 2*nbits +1):
		if 2**p > nc*(d -1 -(2**p -1)%d):
			m = (2**p +d -1 -(2**p -1)%d)//d
			print ('%d\n,%d',(m,p))
			return (m,p)
		print ("Can't find p, something is wrong.")
		sys.exit(1)

magicgu(300,10)