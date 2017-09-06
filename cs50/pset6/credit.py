import cs50

def get_num():
    while True:
        print("enter a cardnumber: ", end="")
        num = cs50.get_string()
        if num.isdigit():
            return num

number = get_num()
leng = len(number)
summ=0
namecard = 0
if leng<13 or leng >16:
    print("INVALID")

if  number[0] == '3' and (number[1] == '4' or number[1] == '7') and (leng == 15):
    namecard = 1 
if (number[0] == '5' and (number[1] >'0' and number[1] < '6')) and leng == 16:
    namecard = 2 
if (number[0] == '4') and (leng == 13 or leng == 16):
    namecard = 3 
i=leng-2
while i >= 0: 
    if (int(number[i])>=5):
        summ=summ+(int(number[i])*2-10)+1
    else:
        summ=summ+int(number[i])*2
    i=i-2
    
i=leng-1
while i >= 0:
    summ=summ+int(number[i])
    i=i-2

if (summ % 10)==0: 
    if namecard == 1:
        print ("AMEX")
    if namecard == 2:
        print ("MASTERCARD")
    if namecard == 3:
        print ("VISA")
else:
    print("INVALID")
    
print(namecard)
print(summ)
     

     
    
