import re

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

def remove_comments(filename1, filename2):
    with open(filename1, 'r') as f:
        text = f.read()
        # Remove all comments
        stripped = comment_remover(text)

        # Filter for removing empty lines
        # filtered = "\n".join([ll.rstrip() for ll in stripped.splitlines() if ll.strip()])

        with open(filename2, 'w') as f:
            f.write(stripped)

if __name__ == '__main__':
    remove_comments('input.txt', 'intermediate.txt')