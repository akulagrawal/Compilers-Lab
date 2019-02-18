import re

def getname(candidate):
    classname = ""
    for letter in candidate:
        if letter.isalnum():
            classname += letter
        else:
            break
    
    return classname

def count_constructor(filename):
    with open(filename, "r") as f:
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

        # print(classnames) 

        f.seek(0)
        filestring = f.read()

        lines_count = 0
        lines_set = set()
        for classname in classnames:
            for position in re.finditer(classname + "\s*\([\s\w,]*\)\s*{", filestring):
                startline = len(re.findall("\n", filestring[0: position.start()]))
                endline = len(re.findall("\n", filestring[0: position.end()]))
                for linenum in range(startline, endline + 1):
                    lines_set.add(linenum)
                    
        return len(lines_set)
               
if __name__ == '__main__':
    constructor_count = count_constructor('intermediate.txt')
    print(constructor_count)