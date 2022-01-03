import re
import math

def main():

    numeric = re.compile('^(\d{13}|\d{15,16})$')
    card=input("Enter Credit Card Number\n")
    match=numeric.match(card)
    if (match==None):
        return print("INVALID")
    sum=0
    start=card[:2]
    length=match.span()[1] # len(card) possible, just emphasizing the regex indeed worked
    every_other_digit=True if length%2==0 else False #ternary in python
    for i in range(length):
        if(every_other_digit):
            sum+=(int(card[i])*2//10)+(int(card[i])*2%10) #integer division in python
            every_other_digit= not every_other_digit
        else:
            sum+=int(card[i])
            every_other_digit= not every_other_digit
    if length==13 and sum%10==0:
        print ("VISA")
    elif length==15 and sum%10==0 and (start=='37' or start=='34'):
        print("AMEX")
    elif length==16 and sum%10==0:
        if start[0]=='4':
            print("VISA")
        elif int(start)>50 and int(start)<56:
            print("MASTERCARD")
        else:
            print ("INVALID")
    else:
        print("INVALID")
#functional programming paradigm in python
if __name__ == '__main__':
    main()