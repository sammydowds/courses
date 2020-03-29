import cs50
import sys

key = int(sys.argv[1])

encrypt = cs50.get_string("What would you like to encrypt?\n")

encrypted = ""

for letter in encrypt:
    if letter.isalpha():

        if letter.isupper():
            charact = (ord(letter) - 65 +  key) % 26
            encrypted_char = chr(charact+65)
            encrypted += (encrypted_char)

        elif letter.islower():
            charact = (ord(letter) - 97 +  key) % 26
            encrypted_char = chr(charact+97)
            encrypted += (encrypted_char)
    else:

        encrypted += (letter)


print(encrypted)




