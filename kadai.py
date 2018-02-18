#coding:utf-8
PURPLE  = '\033[35m'
RED     = '\033[31m'
CYAN    = '\033[36m'
OKBLUE  = '\033[94m'
OKGREEN = '\033[92m'
WARNING = '\033[93m'
FAIL    = '\033[91m'
ENDC    = '\033[0m'
import csv
import sys
import codecs
import math
from urlparse import urlparse #URL --> Domain
from time import sleep

text =[]
with open('neko.num','r') as  a:
	for line in a:
		text.append(line.rstrip())

text = ' '.join(text).split()
N = len(text)


#initialize values as 0
dict_lib = {}
for num in text:
	dict_lib[num] = 0
#count word 
for num in text:
	count = int(dict_lib[num])
	count = count + 1
	dict_lib[num] = count
#print dict_lib["28"]
Keys = dict_lib.keys()



# get indexes of '28'
indexes = [i for i, x in enumerate(text) if x == '28']


next_indexes = []
next_words   = []
for num in indexes:
	num = num + 1 
	#num is index number of '28' in text[], 
	next_indexes.append(num)
	next_words.append(text[num])


dict_next_28 = {}
for num in Keys:
	dict_next_28[num] = 0
for num in next_words:
	count = int(dict_next_28[num])
	count = count + 1
	dict_next_28[num] = count


# bigram
count = 0
sum_Pwb = 0.0
dict_bigram = {}
for key in Keys:
	count = count + 1
	Cbw = dict_next_28[key] - 0.5 #absolute discount
	if Cbw < 0:
		Cbw = 0
	Cb  = dict_lib['28']
	Pwb = float(Cbw) / float(Cb)
	math.floor(Pwb)	
	dict_bigram[key] = Pwb
	sum_Pwb = float(sum_Pwb) + float(Pwb)

diff_bigram = abs(1 - float(sum_Pwb))

# Sort by word number and Save
b = open('bigram.model','w')
count_keys =  len(Keys)
# equally distribute diff_bigram to all words
add_bigram = diff_bigram / count_keys
sum_after_added_bi = 0.0
for i in range(1,count_keys+1):
	bigram_added = float(dict_bigram[str(i)]) + float(add_bigram)
	#print "{0:20.17e}".format(float(bigram_added))
	b.write("{0:20.17e}".format(float(bigram_added)) + '\n')
	sum_after_added_bi = sum_after_added_bi + bigram_added
b.close()









# 24 -> 28
indexes = [i for i, x in enumerate(text) if x == '24']
next_24indexes = []
next_24words   = []
next_24_28words = []
for num in indexes:
	num = num + 1
	next_24indexes.append(num)
	next_24words.append(text[num])
	if text[num] == '28':
		next_24_28words.append(text[num+1])


dict_next_24 = {}
for num in Keys:
	dict_next_24[num] = 0
for num in next_24words:
	count = int(dict_next_24[num])
	count = count + 1
	dict_next_24[num] = count

dict_next24_28 = {}
for num in Keys:
	dict_next24_28[num] = 0
for num in next_24_28words:
	count = int(dict_next24_28[num])
	count = count + 1
	dict_next24_28[num] = count


#trigram
count = 0
sum_Pwab = 0.0
dict_trigram = {}
for key in Keys:
	count = count + 1
	Cabw = dict_next24_28[key] - 0.5 #absolute discount
	if Cabw < 0:
		Cabw = 0
	Cab  = dict_next_24['28']
	Pwab = float(Cabw) / float(Cab)
	dict_trigram[key] = Pwab
	sum_Pwab = float(sum_Pwab) + float(Pwab)
	#print OKGREEN + 'Pwab=' +str(Pwab) + ENDC
diff_trigram = abs(1 - float(sum_Pwab))


# Sort by word number and Save
c = open('trigram.model','w')
count_keys =  len(Keys)
# equally distribute diff_trigram to all words
add_trigram = diff_trigram / count_keys
sum_after_added_tri = 0.0
for i in range(1,count_keys+1):
	trigram_added = float(dict_trigram[str(i)]) + float(add_trigram)
	#print "{0:20.17e}".format(float(trigram_added))
	c.write("{0:20.17e}".format(float(trigram_added)) + '\n')
	sum_after_added_tri = sum_after_added_tri + trigram_added
c.close()

