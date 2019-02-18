import re

def class_inherit_count(filename):

	#number of inherited class declarations
	dec_inh_class=0

	#number of class declarations
	dec_class=0
	
	with open(filename, 'r') as f:
		text = f.read()
		lines = text.splitlines()
		
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

	# print("Number of lines with class declarations: " + str(dec_class))
	# print("Number of lines with inherited class declarations: "+str(dec_inh_class))
	return dec_class, dec_inh_class

if __name__ == '__main__':
	class_count, inherit_class_count = class_inherit_count('intermediate.txt')
	print(class_count)
	print(inherit_class_count)