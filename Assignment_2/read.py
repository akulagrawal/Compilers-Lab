import re, sys

f = open(sys.argv[1]).read()
lines = f.splitlines()

#number of class declarations
decobj=0

for x in lines:
	line = []
	flag = 0
	for word in x.split():
		if re.search(word + r"[\s]*([a-zA-Z][a-zA-Z0-9_]*)[\s]*(\s=\s)[\s]*(new)[\s]*" + word + r"(\()",x):
			flag = 1
			print(x)
			break
	if re.search(r"(.newInstance\()",x) or re.search(r"(.readObject\()",x):
		print(x)
		flag = 1
	decobj += flag

print(decobj)