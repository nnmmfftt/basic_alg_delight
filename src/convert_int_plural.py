import sys
import cmath


# convert -1 + i decimal int to plural

num = sys.argv[1:]
if len(num) == 0:
	print ("Converts a base -1 + 1j number, given in decimal")
	print ("of hex, to the form a + bj, with a, b real.")
	sys.exit()
num = eval(num[0])
r = 0
weight = 1
while num > 0:
	if num & 1:
		r = r + weight;
	weight = (-1 + 1j)*weight
	num = num >> 1;
print ("r = %d",r) 