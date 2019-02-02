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

    # Deallocate all busy registers.
    def return_all_registers(self):
        for register_name in self.busy_registers:
            self.return_register(register_name)

    # Assign the second operand to the first.
    def assign(self, operand1, operand2):
        # Load into accumulator.
        if operand2 in virtual_registers:
            print("; Assigning to " + memory_map[operand1] + " the value at " + memory_map[operand2])
            print("LDA " + memory_map[operand2])
        else:
            print("; Assigning to " + memory_map[operand1] + " the value " + to_hex(operand2))
            print("MVI " + "A" + ", " + to_hex(operand2))

        # Store into memory location,
        print("STA " + memory_map[operand1])

    # Add 8-bit operands, storing in the first operand.
    def add(self, operand1, operand2):
        # Load into accumulator.
        print("LDA " + memory_map[operand1])

        # Add to accumulator, using a free register if not immediate data.
        if operand2 in virtual_registers:
            print("; Adding " + memory_map[operand1] + " and the value at " + memory_map[operand2])
            free_register = self.get_free_register()
            print("MOV " + free_register + ", " + "A")
            print("LDA " + memory_map[operand2])
            print("ADD " + free_register)
            self.return_register(free_register)
        else:
            print("; Adding " + memory_map[operand1] + " and " + to_hex(operand2))
            print("ADI " + to_hex(operand2))

        # Store into memory location.
        print("STA " + memory_map[operand1])

    # Subtract with 8-bit operands.
    def sub(self, operand1, operand2):
        # Load into accumulator.
        if operand2 in virtual_registers:
            print("; Subtracting " + memory_map[operand1] + " by the value at " + memory_map[operand2])
            print("LDA " + memory_map[operand2])
        else:
            print("; Subtracting " + memory_map[operand1] + " by " + to_hex(operand2))
            print("MVI " + to_hex(operand2))

        # Subtract from accumulator, using a free register.
        free_register = self.get_free_register()
        print("MOV " + free_register + ", " + "A")
        print("LDA " + memory_map[operand1])
        print("SUB " + free_register)
        self.return_register(free_register)

        # Store into memory location.
        print("STA " + memory_map[operand1])

    # Multiply 4-bit operands.
    def mul(self, operand1, operand2):
        # Load into accumulator.
        if operand2 in virtual_registers:
            print("; Multiplying " + memory_map[operand1] + " and the value at " + memory_map[operand2])
            print("LDA " + memory_map[operand2])
        else:
            print("; Multiplying " + memory_map[operand1] + " and " + to_hex(operand2))
            print("MVI " + "A" + ", " + to_hex(operand2))

        # Check if second operand is 0.
        self.curr_loop += 1
        print("CPI 0H")
        print("JNZ " + "NZINP" + str(self.curr_loop))
        print("STA " + memory_map[operand1])
        print("JMP " + "MULTEND" + str(self.curr_loop))

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

        # Load the running sum into another register, initially with value of operand1.
        runningsum_register = self.get_free_register()
        print("MOV " + runningsum_register + ", " + "A")

        # Addition loop - multiplication by repeated addition.
        print("LOOP" + str(self.curr_loop) + ": NOP")
        print("MOV " + "A" + ", " + runningsum_register)
        print("ADD " + operand1_register)
        print("MOV " + runningsum_register + ", " + "A")

        # Check the value of the second operand, after decrementing.
        print("DCR " + operand2_register)
        print("MOV " + "A" + ", " + operand2_register)

        # Loop while the second operand is still non-zero.
        print("JNZ " + "LOOP" + str(self.curr_loop))

        # Store in memory.
        print("MOV " + "A" + ", " + runningsum_register)
        print("STA " + memory_map[operand1])

        # Ending label.
        print("MULTEND" + str(self.curr_loop) + ": NOP")

        # Free registers.
        self.return_all_registers()

    # Divides the value of operand1 by operand2, both 8 bits, storing the quotient in operand1.
    def div(self, operand1, operand2):
        # Load into accumulator.
        if operand2 in virtual_registers:
            print("; Dividing " + memory_map[operand1] + " by the value at " + memory_map[operand2])
            print("LDA " + memory_map[operand2])
        else:
            print("; Dividing " + memory_map[operand1] + " by " + to_hex(operand2))
            print("MVI " + "A" + ", " + to_hex(operand2))

        # Check if second operand is 0. Halt if it is.
        self.curr_loop += 1
        print("CPI 0H")
        print("JNZ " + "NZINP" + str(self.curr_loop))
        print("HLT")
        print("JMP " + "DIVEND" + str(self.curr_loop))

        # If the second operand isn't zero, continue.
        print("NZINP" + str(self.curr_loop) + ": NOP")

        # Move second operand into a register.
        operand2_register = self.get_free_register()
        print("MOV " + operand2_register + ", " + "A")

        # Load first operand and move to a free register.
        print("LDA " + memory_map[operand1])
        operand1_register = self.get_free_register()
        print("MOV " + operand1_register + ", " + "A")

        # Initialize quotient to 0.
        print("MVI A, 0H")
        quotient_register = self.get_free_register()
        print("MOV " + quotient_register + ", " + "A")

        # Subtraction loop - division by repeated subtraction.
        print("LOOP" + str(self.curr_loop) + ": NOP")
        print("MOV " + "A" + ", " + operand1_register)

        # Check the value of the first operand, compared to the second operand.
        print("CMP " + operand2_register)
        print("JC " + "LOOPEND" + str(self.curr_loop))

        # Subtraction is alright - first operand is big enough.
        print("SUB " + operand2_register)
        print("MOV " + operand1_register + ", " + "A")

        # Increment quotient.
        print("INR " + quotient_register)
        print("MOV " + "A" + ", " + operand1_register)

        # Loop while the second operand is still non-zero.
        print("CMP " + operand2_register)
        print("JNC " + "LOOP" + str(self.curr_loop))

        # Ending label.
        print("LOOPEND" + str(self.curr_loop) + ": NOP")

        # Store in memory.
        print("MOV " + "A" + ", " + quotient_register)
        print("STA " + memory_map[operand1])

        # Ending label.
        print("DIVEND" + str(self.curr_loop) + ": NOP")

        # Free registers.
        self.return_all_registers()

    # Logical OR of two 8-bit operands.
    def logical_or(self, operand1, operand2):
        # Load into accumulator.
        print("LDA " + memory_map[operand1])

        # Load second operand, using a free register if not immediate data, and perform the OR.
        if operand2 in virtual_registers:
            print("; Logical OR with " + memory_map[operand1] + " and the value at " + memory_map[operand2])
            free_register = self.get_free_register()
            print("MOV " + free_register + ", " + "A")
            print("LDA " + memory_map[operand2])
            print("ORA " + free_register)
            self.return_register(free_register)
        else:
            print("; Logical OR with " + memory_map[operand1] + " and " + to_hex(operand2))
            print("OR " + to_hex(operand2))

        # Store into memory location.
        print("STA " + memory_map[operand1])

    # Logical AND of two 8-bit operands.
    def logical_and(self, operand1, operand2):
        # Load into accumulator.
        print("LDA " + memory_map[operand1])

        # Load second operand, using a free register if not immediate data, and perform the AND.
        if operand2 in virtual_registers:
            print("; Logical AND with " + memory_map[operand1] + " and the value at " + memory_map[operand2])
            free_register = self.get_free_register()
            print("MOV " + free_register + ", " + "A")
            print("LDA " + memory_map[operand2])
            print("ANA " + free_register)
            self.return_register(free_register)
        else:
            print("; Logical AND with " + memory_map[operand1] + " and " + to_hex(operand2))
            print("ANI " + to_hex(operand2))

        # Store into memory location.
        print("STA " + memory_map[operand1])

    # Assigns the Logical NOT of the second operand to the first operand.
    def logical_not(self, operand1, operand2):
        # Load second operand into accumulator, and perform the XOR for a NOT.
        if operand2 in virtual_registers:
            print("; Assigning " + memory_map[operand1] + " to the logical NOT of the value at " + memory_map[operand2])
            print("LDA " + memory_map[operand2])
            print("XRI " + "0FFH")
        else:
            print("; Assigning " + memory_map[operand1] + " to the logical NOT of " + to_hex(operand2))
            print("MVI " + to_hex(operand2))
            print("XRI " + "0FFH")

        # Store into memory location.
        print("STA " + memory_map[operand1])


# Instruction Class.
class Instruction:
    @staticmethod
    def is_assignment(tokenlist):
        return tokenlist[1] == "="

    @staticmethod
    def is_addition(tokenlist):
        return tokenlist[1] == "+="

    @staticmethod
    def is_subtraction(tokenlist):
        return tokenlist[1] == "-="

    @staticmethod
    def is_multiplication(tokenlist):
        return tokenlist[1] == "*="

    @staticmethod
    def is_division(tokenlist):
        return tokenlist[1] == "/="

    @staticmethod
    def is_logical_or(tokenlist):
        return tokenlist[1] == "|="

    @staticmethod
    def is_logical_and(tokenlist):
        return tokenlist[1] == "&="

    @staticmethod
    def is_logical_not(tokenlist):
        return tokenlist[1] == "!="


if __name__ == "__main__":
    # Create Processor instance.
    processor = Processor()

    with open(IR_file_path, "r") as f:
        # Read all lines from the file.
        lines = f.readlines()

        for line in lines:
            # Extract tokens.
            tokens = line.split()

            # Check operation, based on tokens.
            # Assignment.
            if Instruction.is_assignment(tokens):
                processor.assign(tokens[0], tokens[2])

            # Addition.
            elif Instruction.is_addition(tokens):
                processor.add(tokens[0], tokens[2])

            # Subtraction.
            elif Instruction.is_subtraction(tokens):
                processor.sub(tokens[0], tokens[2])

            # Multiplication.
            elif Instruction.is_multiplication(tokens):
                processor.mul(tokens[0], tokens[2])

            # Division.
            elif Instruction.is_division(tokens):
                processor.div(tokens[0], tokens[2])

            # Logical OR.
            elif Instruction.is_logical_or(tokens):
                processor.logical_or(tokens[0], tokens[2])

            # Logical AND.
            elif Instruction.is_logical_and(tokens):
                processor.logical_and(tokens[0], tokens[2])

            # Logical NOT.
            elif Instruction.is_logical_not(tokens):
                processor.logical_not(tokens[0], tokens[2])