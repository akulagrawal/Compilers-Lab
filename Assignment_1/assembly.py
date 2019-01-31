'''
Assembly Code Generation
30th January, 2019
'''

# The maximum number of 8-bit variables (ie, memory locations) we will use.
max_variables = 100

# Memory start location
memory_start = 8000

# Path for the IR code text file that has to be translated.
IR_file_path = "IR.txt"

# Define virtual registers, real memory locations and the mapping between them.
virtual_registers = ["_t" + chr(num + ord('0')) for num in range(max_variables)]
memory_locations = [str(8000 + num) + 'H' for num in range(max_variables)]
memory_map = dict(zip(virtual_registers, memory_locations))


# Returns the hexadecimal equivalent of num (possibly, a string) in Assembly format.
def to_hex(num):
    return hex(int(num))[2:].upper() + 'H'


# Processor Class.
class Processor:
    def __init__(self):
        self.num_registers = 6
        self.registers = ['B', 'C', 'D', 'E', 'H', 'L']
        self.free_registers = self.registers.copy()
        self.busy_registers = []
        self.curr_loop = 0

    # Assign a free register.
    def get_free_register(self):
        # No free registers available.
        if len(self.free_registers) == 0:
            raise IndexError('No free registers left.')

        free_register = self.free_registers.pop(0)
        self.busy_registers.append(free_register)
        return free_register

    # Deallocate a previously busy register.
    def return_register(self, register_name):
        if register_name not in self.busy_registers:
            raise NameError('Incorrect register name.')

        self.busy_registers.remove(register_name)
        self.free_registers.append(register_name)

    @staticmethod
    def assign(operand1, operand2):
        # Load into accumulator.
        if operand2 in virtual_registers:
            print("LDA " + memory_map[operand2])
        else:
            print("MVI " + "A" + ", " + to_hex(operand2))

        # Store into memory location,
        print("STA " + memory_map[operand1])

    @staticmethod
    def is_assignment(tokenlist):
        return tokenlist[1] == "="

    # Add 8-bit operands.
    def add(self, operand1, operand2):
        # Load into accumulator.
        print("LDA " + memory_map[operand1])

        # Add to accumulator, using a free register if not immediate data.
        if operand2 in virtual_registers:
            free_register = self.get_free_register()
            print("MOV " + free_register + ", " + "A")
            print("LDA " + memory_map[operand2])
            print("ADD " + free_register)
            self.return_register(free_register)
        else:
            print("ADI " + to_hex(operand2))

        # Store into memory location.
        print("STA " + memory_map[operand1])

    @staticmethod
    def is_addition(tokenlist):
        return tokenlist[1] == "+="

    # Subtract with 8-bit operands.
    def sub(self, operand1, operand2):
        # Load into accumulator.
        if operand2 in virtual_registers:
            print("LDA " + memory_map[operand2])
        else:
            print("MVI " + to_hex(operand2))

        # Subtract from accumulator, using a free register.
        free_register = self.get_free_register()
        print("MOV " + free_register + ", " + "A")
        print("LDA " + memory_map[operand1])
        print("SUB " + free_register)
        self.return_register(free_register)

        # Store into memory location.
        print("STA " + memory_map[operand1])

    @staticmethod
    def is_subtraction(tokenlist):
        return tokenlist[1] == "-="

    # Multiply 4-bit operands.
    def mul(self, operand1, operand2):
        # Load into accumulator.
        if operand2 in virtual_registers:
            print("LDA " + memory_map[operand2])
        else:
            print("MVI " + "A" + ", " + to_hex(operand2))

        # Check if second operand is 0.
        self.curr_loop += 1
        print("CPI 0H")
        print("JNZ " + "NZINP" + str(self.curr_loop))
        print("STA " + memory_map[operand1])

        # If the second operand isn't zero, continue.
        print("NZINP" + str(self.curr_loop) + ": NOP")

        # Move the second operand to a free register, after decrementing.
        print("DCR A")
        operand2_register = self.get_free_register()
        print("MOV " + operand2_register + ", " + "A")

        # Load first operand and move to a free register.
        print("LDA " + memory_map[operand1])
        operand1_register = self.get_free_register()
        print("MOV " + operand1_register + ", " + "A")

        # Addition loop - multiplication by repeated addition.
        print("LOOP" + str(self.curr_loop) + ": NOP")
        print("LDA " + memory_map[operand1])
        print("ADD " + operand1_register)
        print("STA " + memory_map[operand1])

        # Check the value of the second operand, after decrementing.
        print("DCR " + operand2_register)
        print("MOV " + "A" + ", " + operand2_register)

        # Loop while the second operand is still non-zero.
        print("JNZ " + "LOOP" + str(self.curr_loop))

    @staticmethod
    def is_multiplication(tokenlist):
        return tokenlist[1] == "*="

    @staticmethod
    def is_division(tokenlist):
        return tokenlist[1] == "/="


if __name__ == "__main__":

    # Create processor object.
    processor = Processor()

    with open(IR_file_path, "r") as f:
        # Read all lines from the file.
        lines = f.readlines()

        for line in lines:
            # Extract tokens.
            tokens = line.split()

            # Check operation.
            if processor.is_assignment(tokens):
                processor.assign(tokens[0], tokens[2])

            elif processor.is_addition(tokens):
                processor.add(tokens[0], tokens[2])

            elif processor.is_subtraction(tokens):
                processor.sub(tokens[0], tokens[2])

            elif processor.is_multiplication(tokens):
                processor.mul(tokens[0], tokens[2])

            elif processor.is_division(tokens):
                processor.div(tokens[0], tokens[2])
