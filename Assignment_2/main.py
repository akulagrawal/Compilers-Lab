import sys

from object_count import count_object
from constructor_count import count_constructor
from remove_comments import remove_comments
from class_inherit_count import class_inherit_count

def main(filename = 'input.txt'):
    out_file = 'output.txt'
    intermediate_file = 'intermediate.txt'
    
    # remove comments from input.txt and write to intermediate.txt
    remove_comments(filename, intermediate_file)

    # get object count
    # object_count = count_object(intermediate_file)

    # get the constructor count
    constructor_count = count_constructor(intermediate_file)

    # get the class count and inherited class count
    class_count, inherit_class_count = class_inherit_count(intermediate_file)

    with open(out_file, 'w') as f:
        f.write('Number of Class Definitions: ' + str(class_count) + '\n')
        f.write('Number of Inherited Class Definitions:' + str(inherit_class_count) + '\n')
        f.write('Number of Constructor Definitions: ' + str(constructor_count) + '\n')
        # f.write('Number of Object Declarations: ' + str(object_count) + '\n')
    

if __name__ == '__main__':
    main(sys.argv[1])