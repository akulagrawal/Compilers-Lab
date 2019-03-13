import re, sys


def getname(candidate):
    classname = ""
    for letter in candidate:
        if letter.isalnum():
            classname += letter
        else:
            break
    
    return classname

def count_constructor():
    with open("input.txt", "r") as f:
        lines = f.readlines()
    
        classnames = []
        for linenum, line in enumerate(lines):
            tokens = line.split()

            if 'class' in tokens:
                if tokens[-1] == 'class':
                    tokens = lines[linenum + 1].split()
                    candidate = tokens[0]
                    classnames.append(getname(candidate))
                else:
                    for index, token in enumerate(tokens):
                        if token == 'class':
                            candidate = tokens[index + 1]
                            classnames.append(getname(candidate))

        print(classnames) 

        f.seek(0)
        filestring = f.read()

        lines_count = 0
        for classname in classnames:
            start = 0
            for position in re.finditer(classname + "\s*\([\s\w,]*\)\s*{", filestring):
                lines_in_between = len(re.findall("\n", filestring[start: position.end()]))
                start = position.end()

                if lines_in_between > 0:
                    lines_count += 1

        print("Number of lines with constructor definitions:", lines_count)
        
def comment_remover(text):
    def replacer(match):
        s = match.group(0)
        if s.startswith('/'):
            return " " # note: a space and not an empty string
        else:
            return s
    pattern = re.compile(
        r'//.*?$|/\*.*?\*/|\'(?:\\.|[^\\\'])*\'|"(?:\\.|[^\\"])*"',
        re.DOTALL | re.MULTILINE
    )
    return re.sub(pattern, replacer, text)

try:
    f = open(sys.argv[1]).read()
except IndexError:
    f = open("fd.txt").read()

# Remove all comments
stripped = comment_remover(f)

print(stripped)
exit(0)

# Filter for removing \ns 
filtered = "\n".join([ll.rstrip() for ll in stripped.splitlines() if ll.strip()])
lines = filtered.splitlines()

#number of inherited class declarations
dec_inh_class=0

#number of class declarations
dec_class=0

pattern_class = re.compile(r"[ \t]*(public[ \t]+|private[ \t]+)?class[ \t]+[a-zA-Z][a-zA-Z0-9_]*([ \t]+(implements)[ \t]+([a-zA-Z][a-zA-Z0-9_]*))?[ \t]*")
pattern_ext_class = re.compile(r"[ \t]*(public[ \t]+|private[ \t]+)?class[ \t]+[a-zA-Z][a-zA-Z0-9_]*[ \t]+(((extends)[ \t]+([a-zA-Z][a-zA-Z0-9_]*)[ \t]+(implements)[ \t]+([a-zA-Z][a-zA-Z0-9_]*)[ \t]*)|((extends)[ \t]+([a-zA-Z][a-zA-Z0-9_]*)[ \t]*))")


flag=0
ext_flag=0

for x in lines:
	test = re.findall(pattern_ext_class, x);
	for y in test:
		ext_flag=1
	
	if(ext_flag==1):
		dec_class+=1
		dec_inh_class+=1
		ext_flag=0
	else:
		test = re.findall(pattern_class, x);
		for p in test:
			flag=1

		if(flag==1):
			flag=0
			dec_class+=1

print("Number of lines with class declarations: " + str(dec_class))
print("Number of lines with inherited class declarations: "+str(dec_inh_class))
