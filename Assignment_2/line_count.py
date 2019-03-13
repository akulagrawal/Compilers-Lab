def count_lines(filename):
	with open(filename, "r") as f:
		filestring = f.read()
		totalline_count = len(filestring.split('\n'))
		blankline_count = len([token for token in filestring.split('\n') if len(token.lstrip()) == 0])

		#print(filestring.split('\n')[:20])

		#return totalline_count - blankline_count, blankline_count
		# blankline_count = 0
		# lines = filestring.splitlines()
		# for line in lines:
		# 	line = line.lstrip()
		# 	if (len(line) == 0):
		# 		blankline_count += 1
	return totalline_count - blankline_count, blankline_count
