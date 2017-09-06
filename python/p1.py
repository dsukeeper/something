import cs50
s = 'bsbrgnooq'

indexstart=0
indexend=1
ist=0;
ite=0;
lmax=0
ltemp=0
flag=0
for i in range(1,len(s),1):
    #print(i)
    if ((ord(s[i])>ord(s[i-1]) or ord(s[i])==(ord(s[i-1]))) and flag==0):
        ist=i-1
        flag=1
        #print(s[i-1]+" "+str(i+1))
   # if (ord(s[i])==ord(s[i-1]) and flag==1):
       # continue
    if ((ord(s[i])<(ord(s[i-1])) or i==len(s)-1) and flag==1):   
        if i==len(s)-1 and ord(s[i])>(ord(s[i-1])):
            ite=i+1
        else: 
            ite=i
        flag=0
        ltemp=ite-ist
        #print(i)
#    print("lmax="+str(lmax))
 #   print("ltemp="+str(ltemp))
    if (lmax<ltemp and flag==0):
        #print("замена индексов " + s[indexstart:indexend])
        #print(i)
        lmax=ltemp
        ltemp=0
        indexstart=ist
        indexend=ite

print("Longest substring in alphabetical order is: "+ s[indexstart:indexend])
