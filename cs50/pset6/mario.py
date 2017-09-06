import cs50

def get_level():
    while True:
        print("height is ",end="")
        level=cs50.get_int()
        if level >=4 and level<=23:
                break
    return level
    
level = get_level()
for i in range (level):
    for j in range (level - i -1):
        print(" ", end="")
    for j in range (i+1):
        print("#", end="")
    print("  ", end="")
    for j in range (i+1):
        print("#", end="")
    print("")

    

