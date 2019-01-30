'''
Assembly Code Generation
30th January, 2019
'''

# Path for the IR code text file that has to be translated.
IR_file_path = "IR.txt"

# Define virtual registers, real registers and the mapping between them.
virtual_registers = ["_t" + chr(num + ord('0')) for num in range(7)]
registers = [chr(ord('A') + 1 + num) for num in range(7)]
register_map = dict(zip(virtual_registers, registers))


# Returns the hexadecimal equivalent of num (possibly, a string) in Assembly format.
def to_hex(num):
    return hex(int(num))[2:].upper() + 'H'


# Instructions Class.
class Instruction:
    @staticmethod
    def assign(operand1, operand2):
        if operand2 in virtual_registers:
            print("MOV " + register_map[operand1] + ", " + register_map[operand2])
        else:
            print("MVI " + register_map[operand1] + ", " + to_hex(operand2))

    @staticmethod
    def is_assignment(tokenlist):
        return tokenlist[1] == "="

    @staticmethod
    def add(operand1, operand2):
        # Move to accumulator
        print("MOV " + "A" + ", " + register_map[operand1])

        # Add to accumulator
        if operand2 in virtual_registers:
            print("ADD " + register_map[operand2])
        else:
            print("ADI " + to_hex(operand2))

        # Shift back to register
        print("MOV " + register_map[operand1] + ", " + "A")

    @staticmethod
    def is_addition(tokenlist):
        return tokenlist[1] == "+="

    @staticmethod
    def sub(operand1, operand2):
        # Move to accumulator
        print("MOV " + "A" + ", " + register_map[operand1])

        # Add to accumulator
        if operand2 in virtual_registers:
            print("SUB " + register_map[operand2])
        else:
            print("SUI " + to_hex(operand2))

        # Shift back to register.
        print("MOV " + register_map[operand1] + ", " + "A")

    @staticmethod
    def is_subtraction(tokenlist):
        return tokenlist[1] == "-="

    @staticmethod
    def is_multiplication(tokenlist):
        return tokenlist[1] == "*="

    @staticmethod
    def is_division(tokenlist):
        return tokenlist[1] == "/="


if __name__ == "__main__":
    with open(IR_file_path, "r") as f:
        # Read all lines from the file.
        lines = f.readlines()

        for line in lines:
            # Extract tokens.
            tokens = line.split()

            # Check operation.
            if Instruction.is_assignment(tokens):
                Instruction.assign(tokens[0], tokens[2])

            elif Instruction.is_addition(tokens):
                Instruction.add(tokens[0], tokens[2])

            elif Instruction.is_subtraction(tokens):
                Instruction.sub(tokens[0], tokens[2])

            elif Instruction.is_multiplication(tokens):
                Instruction.mul(tokens[0], tokens[1])

            elif Instruction.is_division(tokens):
                Instruction.div(tokens[0], tokens[1])
