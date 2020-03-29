import cs50

while True:
    height = cs50.get_int("Number of rows: ")
    bool1 = height <= 0
    bool2 = height > 32
    if bool1 or bool2:
        break
    else:
        for i in range(height):
            spaces = height - i - 1
            hashes = height - spaces
            print(" " * spaces, end = "")
            print("#" * hashes)


