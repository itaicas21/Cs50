def main():
    print("How many blocks?")
    height = get_num()
    while height<1 or height>8:
        print("Insert a number between one and eight inclusive")
        height = get_num()
    for i in range(height):
        half = False
        for j in range(height*2):
            if half==False:
                if j>=height-(i+1):
                    print("#", end="")
                else:
                   print(" ", end="")
            elif j<=height+(i):
                print("#", end="")
            if (j==height-1):
                half=True
                print("  ", end="")
        print()


def get_num():
    num = None
    while num is None:
        input_value = input()
        try:
            # try and convert the string input to a number
            num = int(input_value)
        except ValueError:
            # tell the user off
            print(f"{input_value} is not a number, please enter a number only")
    return num
if __name__ == '__main__':
    main()