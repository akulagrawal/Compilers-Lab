import re

def count_object(filename):
	#number of class declarations
	decobj=0

	with open(filename, 'r') as f:
		text = f.read()
		lines = text.splitlines()

		for x in lines:
			line = []
			flag = 0
			for word in x.split():
				try:
					if re.search(word + r"[\s]*([a-zA-Z][a-zA-Z0-9_]*)[\s]*(\s=\s)[\s]*(new)[\s]*" + word + r"(\()",x):
						flag = 1
						# print(x)
						break
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