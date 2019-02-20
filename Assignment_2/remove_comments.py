import re

lines_set = set()
def comment_remover(text):
    def replacer(match):
        s = match.group(0)
        if s.startswith('/'):
            return " " # note: a space and not an empty string
        else:
            return s
    pattern = re.compile(
        r'//.*?$|/\*.*?\*/|\'(?:\\.|[^\\\'])*\'"',
        re.DOTALL | re.MULTILINE
    )

    for position in re.finditer(pattern, text):
        #print(position.group(0))
        startline = len(re.findall("\n", text[0: position.start()]))
        endline = len(re.findall("\n", text[0: position.end()]))
        for linenum in range(startline, endline + 1):
            lines_set.add(linenum)

    # for line in lines_set:
    #     print(line + 1)

    commentline_count = len(lines_set)

    return commentline_count, re.sub(pattern, replacer, text)

def remove_comments(filename1, filename2):
    with open(filename1, 'r') as f:
        text = f.read()

        # Remove all comments and count comment lines.
        commentline_count, stripped = comment_remover(text)
       #print(stripped)
        # Filter for removing empty lines
        # filtered = "\n".join([ll.rstrip() for ll in stripped.splitlines() if ll.strip()])

        with open(filename2, 'w') as f:
            f.write(stripped)

        return commentline_count

if __name__ == '__main__':
    remove_comments('input.txt', 'intermediate.txt')