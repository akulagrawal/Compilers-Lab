import re

def class_inherit_count(filename):

	#number of inherited class declarations
	dec_inh_class=0

	#number of class declarations
	dec_class=0
	
	with open(filename, 'r') as f:
		text = f.read()
		lines = text.splitlines()
		
		pattern_ext_class = re.compile(r"[ \t]*(public[\n \t]+|private[\n \t]+)?([\n \t]+final[\n \t]+)?class[\n \t]+[a-zA-Z][<>a-zA-Z0-9_]*[\n \t]+(((extends)[\n \t]+([a-zA-Z][a-zA-Z0-9_<>]*)[\n \t]+(implements)[\n \t]+([a-zA-Z][a-zA-Z0-9_<>]*)[\n \t]*)|((extends)[\n \t]+([a-zA-Z][a-zA-Z0-9_<>]*)[\n \t]*))")
		pattern_class = re.compile(r"[ \t]*(public[\n \t]+|private[\n \t]+)?([\n \t]+final[\n \t]+)?class[<>\s\w]*{")

		eg = re.compile(r'cla[\n \t]*ss')
		flag=0
		ext_flag=0

		test = re.findall(pattern_class, text)
		c=0
		for x in test:
			# print(x)
			c+=1

		test = re.findall(pattern_ext_class, text)
		d=0
		for x in test:
			# print(x)
			d+=1

		nlines=0

		start=0
		end=0
		flag=0

		lines_set = set()

		iline=0

		for position in re.finditer(pattern_ext_class, text):
			startline = len(re.findall("\n", text[0: position.start()]))
			endline = len(re.findall("\n", text[0: position.end()]))

			for linenum in range(startline, endline + 1):
				lines_set.add(linenum)
				
			lines_in_between = len(re.findall("\n", text[position.start(): position.end()]))+1
			sme = len(re.findall("\n", text[start: position.end()]))
			start = position.end()

			if (flag==0 or sme>0):
				flag=1
				iline += lines_in_between

		# print("Inherited Lines = "+str(iline))

		start=0
		end=0
		flag=0

		for position in re.finditer(pattern_class, text):
			startline = len(re.findall("\n", text[0: position.start()]))
			endline = len(re.findall("\n", text[0: position.end()]))

			for linenum in range(startline, endline + 1):
				lines_set.add(linenum)

			lines_in_between = len(re.findall("\n", text[position.start(): position.end()]))+1

			sme = len(re.findall("\n", text[start: position.end()]))
			start = position.end()

			if (flag==0 or sme>0):
				flag=1
				nlines += lines_in_between

		# print("Normal Lines = "+str(len(lines_set)))

	# print("Number of lines with class declarations: " + str(dec_class))
	# print("Number of lines with inherited class declarations: "+str(dec_inh_class))
	dec_class = nlines
	dec_inh_class = iline
	return dec_class, dec_inh_class

if __name__ == '__main__':
	class_count, inherit_class_count = class_inherit_count('intermediate.txt')
	print(class_count)
	print(inherit_class_count)