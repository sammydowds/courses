
class Parser:
    # Encapsualtes access to the input code.
    # Reads an assembly language command, parses it, and provides convenient access to the command's components.
    # Remove all white space and comments.

    def __init__(self, assembly_code, number_commands):
        # filtering and reading file
        self.current_command = None
        self.number_commands = number_commands
        self.current_line = 0
        self.assembly_code = assembly_code

    def has_more_commands(self):
        if self.current_line < self.number_commands:
            return True
        else:
            return False

    def advance(self):
        if self.has_more_commands() == True:
            self.current_command = self.assembly_code[self.current_line]
            self.current_line = self.current_line + 1

    def command_type(self):
        if self.current_command[0] == '@':
            return 'A_COMMAND'
        elif self.current_command[0] == '(':
            return 'L_COMMAND'
        else:
            return 'C_COMMAND'

    def symbol(self):
        if self.command_type() == 'A_COMMAND':
            return self.current_command[1:]
        elif self.command_type() == 'L_COMMAND':
            return self.current_command[1:-1]

    def dest(self):
        if self.command_type() =='C_COMMAND' and self.jmp_cond() == False:
            return self.current_command[0:self.dest_range()]
        else:
            return None

    def comp(self):
        if self.command_type() =='C_COMMAND' and self.jmp_cond() == False:
            return self.current_command[self.dest_range()+1:]
        elif self.command_type() == 'C_COMMAND' and self.jmp_cond() == True:
            return self.current_command[:self.jmp_comp_range()]
        else:
            return None

    def jump(self):
        if self.command_type() =='C_COMMAND' and self.jmp_cond() == True:
            return self.current_command[-3:]
        else:
            return None

    def jmp_cond(self):
        for character in self.current_command:
            if character == ';':
                return True #true if jump condition present
            elif character == '=':
                return False #false if equation is present

    def dest_range(self):
        dest_range = 0
        for character in self.current_command:
            if character == '=': #dest range is everything before the equal sign
                return dest_range
            else:
                dest_range = dest_range + 1

    def jmp_comp_range(self):
        comp_range = 0
        for character in self.current_command:
            if character == ';': #comp range for jump statements
                return comp_range
            else:
                comp_range = comp_range + 1
