import cs50
import sys  

if len(sys.argv)!=2:
    print("Usage: python caesar k")
    exit 

key =int(sys.argv[1])
print ("plaintext: ", end="")
s=cs50.get_string()
leng=len(s)
print ("ciphertext: ", end="")
i=0
while i<leng:
    Ci=0
    if s[i].isalpha():
        if s[i].isupper():
            alph=65
        else:
            alph=97
        Ci=((ord(s[i])-alph)+key) % 26+alph
        print (chr(Ci), end="")
    else:
        print (s[i])
    i=i+1
print ()

