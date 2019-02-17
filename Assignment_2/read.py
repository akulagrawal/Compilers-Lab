import re, sys

f = open(sys.argv[1]).read()
lines = f.splitlines()

#number of class declarations
decclass=0

for x in lines:
	if(re.match(r"[ \t]*(public[ \t]+|private[ \t]+)?class[ \t]+((extends)[ \t]+([a-zA-Z][a-zA-Z0-9_]*)[ \t]+(implements)[ \t]+([a-zA-Z][a-zA-Z0-9_]*)[ \t]*|(implements)[ \t]+([a-zA-Z][a-zA-Z0-9_]*)[ \t]*|(extends)[ \t]+([a-zA-Z][a-zA-Z0-9_]*)[ \t]*|([a-zA-Z][a-zA-Z0-9_]*)[ \t]*)",x)):
		decclass += 1
		print(x)

print(decclass)