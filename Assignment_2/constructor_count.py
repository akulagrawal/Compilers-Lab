import re

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
               
if __name__ == '__main__':
    count_constructor()
    