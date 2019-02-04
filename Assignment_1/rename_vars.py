# sys package for command-line arguments
import sys

# Path for the IR code text file that has to have renamed variables - default is IR.txt in the same directory.
try:
    IR_file_path = sys.argv[1]
except IndexError:
    IR_file_path = "IRvars.txt"

# Path for the file with renamed variables.
IR_output_path = "IRfinal.txt"

# List containing new tokens.
newtokens = []

with open(IR_file_path, "r") as f:
    # Read all lines from the file.
    lines = f.readlines()

    # Count number of variables.
    # Variables start with _t.
    var_set = set()
    for line in lines:
        tokens = line.split()
        for token in tokens:
            if token[0:2] == '_t':
                var_set.add(token)

    var_count = len(var_set)

    # Code-variables start with $.
    codevar_offset = var_count
    renamed_codevars = {}
    for line in lines:
        tokens = line.split()

        # Replace in the new format.
        for index, token in enumerate(tokens):
            if token[0] == '$':
                if token not in renamed_codevars:
                    renamed_codevars[token] = '_t' + str(codevar_offset)
                    codevar_offset += 1

                tokens[index] = renamed_codevars[token]

        newtokens.append(tokens)

# Write to the output file
with open(IR_output_path, "w") as f:
    # Print the new tokens on one line.
    for tokens in newtokens:
        line = ""
        for token in tokens:
            line += token
            line += " "

        line += "\n"
        f.write(line)

