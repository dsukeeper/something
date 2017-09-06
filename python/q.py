import string
alphabet=string.ascii_letters


def counter(sentence):
   count_letters = {}
   for i in range (0, len(alphabet),1):
      count=0
      for j in range (len(sentence)):
         if alphabet[i]==sentence[j]:
            count+=1
      if count!=0:
         count_letters[alphabet[i]]=count
   return count_letters
   
sentence = 'Jim quickly realized that the beautiful gowns are expensive'
count_letters = {}
count_letters=counter(sentence)
print (count_letters)
maxs=0;
key=''
for i in count_letters:
    temp=count_letters[i]
    if maxs<temp:
       maxs=temp
       key=i
print(str(key)+" "+str(maxs))

    