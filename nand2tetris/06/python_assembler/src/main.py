from parser import Parser
from code import Code
from symboltable import SymbolTable
import os

# Getting path of assembly file to be assembled
file_path = input('path of assembly file:')

# opening file, and storing file name for output file
assembly_code_unfiltered = open(file_path, 'r')
file_name = assembly_code_unfiltered.name


# initializing vars
assembly_code = []
number_commands = 0
output_name = os.path.splitext(file_name)[0] + ".hack"

#initializing symbol table object
sym_tbl = SymbolTable()

# Initial clean - eliminates white space, comments
for line in assembly_code_unfiltered:
    if not line.isspace() and line[0:2] != '//':
        number_commands = number_commands + 1
        line_cleaned = str()
        for char in line:
            if char == '' or char == '/':
                break
            else:
                line_cleaned = line_cleaned + char
        assembly_code.append(line_cleaned.strip())
assembly_code_unfiltered.close()

#PASS FUNCTIONS
def first_pass(assembly_code, number_commands):
    #initializing parser and symbol table
    assembly = Parser(assembly_code, number_commands)

    # Storing lines of assembly code without labels
    n=[]
    ROM_line = 0

    #looping through each line of the asm program
    while assembly.has_more_commands():
        assembly.advance()
        symbol = assembly.symbol()
        current_command = assembly.current_command
        if assembly.command_type() == 'L_COMMAND':
            if not sym_tbl.contains(symbol):
                sym_tbl.add_entry(symbol, ROM_line)
        elif assembly.command_type() == 'C_COMMAND':
            ROM_line = ROM_line + 1
            n.append(current_command)
        elif assembly.command_type() == 'A_COMMAND':
            ROM_line = ROM_line + 1
            n.append(current_command)

    return n, ROM_line



# takes in assembly code with no labels and codes into hack language
def second_pass(assembly_code, number_commands, output_name):
    assembly = Parser(assembly_code, number_commands)
    coder = Code()

    # Storing lines to write to .hack file in var
    n=[]
    next_avail_RAM = 16

    # SECOND PASS
    while assembly.has_more_commands():
        assembly.advance()
        if assembly.command_type() == 'C_COMMAND':
            # access to symbols
            symbol_c=assembly.comp()
            symbol_d=assembly.dest()
            symbol_j=assembly.jump()

            #convert symbols to binary
            e = coder.comp(symbol_c)
            f = coder.dest(symbol_d)
            g = coder.jump(symbol_j)

            out = '111'+ e + f + g
            n.append(out +'\n')

        elif assembly.command_type() == 'A_COMMAND':
            symbol = assembly.symbol()
            if not symbol.isdigit():
                if not sym_tbl.contains(symbol):
                    sym_tbl.add_entry(symbol, next_avail_RAM)
                    next_avail_RAM = next_avail_RAM + 1
                out = '0' + '{0:015b}'.format(sym_tbl.get_address(symbol))
            else:
                out = '0' + "{0:015b}".format(int(symbol))
            n.append(out +'\n')

    # writing to .hack file
    with open(output_name, "w") as binary_output:
        binary_output.writelines(n)
    binary_output.close()


# RUN FIRST PASS - asm to asm
assembly_code, number_commands = first_pass(assembly_code, number_commands)
# RUN SECOND PASS - asm to hack
hack_output = second_pass(assembly_code, number_commands, output_name)
