import re
import re, sys

def count_object(filename):
	#number of class declarations
	decobj=0

	datatypes = ['boolean', 'byte', 'char', 'short', 'int', 'long', 'float', 'double']
	keywords = ['abstract', 'continue', 'for',	'new',	'switch',
	'assert',	'default',	'goto',	'package',	'synchronized',
	'boolean',	'do',	'if',	'private',	'this',
	'break',	'double',	'implements',	'protected',	'throw',
	'byte',	'else',	'import',	'public',	'throws',
	'case',	'enum',	'instanceof',	'return',	'transient',
	'catch',	'extends',	'int',	'short',	'try',
	'char',	'final',	'interface',	'static',	'void',
	'class',	'finally',	'long',	'strictfp',	'volatile',
	'const',	'float',	'native',	'super',	'while']

	with open(filename, 'r') as f:
		text = f.read()
		lines = text.splitlines()

		for x in lines:
			line = []
			flag = 0
			x = x.strip()
			words = re.findall(r"[a-zA-Z][a-zA-Z0-9_\[\]]*",x)
			for i in range(len(words)):
				try:
					word = words[i]
					if re.search(word + r"[\s]*([a-zA-Z][a-zA-Z0-9_]*)[\s]*(\s=\s)[\s]*(new)[\s]*" + word + r"(\()",x):
						flag = 1
						# print(x)
						break
					if word not in datatypes and word not in keywords:
						if x.startswith(word):
							y = x[len(word):]
							y = y.lstrip()
							if y.startswith(words[i+1]):
								flag = 1
								# print(x)
				except:
					pass
			try:
				if re.search(r"(.newInstance\()",x) or re.search(r"(.readObject\()",x):
					# print(x)
					flag = 1
			except:
				pass

			decobj += flag

	return decobj

if __name__ == '__main__':
	object_count = count_object('intermediate.txt')
	print(object_count)