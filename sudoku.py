

f = open('logic.txt', 'w')


for i in range(1, 10):
    s = ""
    for j in range(1, 10):
        s += "e" + str(i) + str(j) + ' '
    f.write(s + "\r\n")

f.write("\r\n______________________________\r\n")

for i in range(1, 10):
    s = "\<and> valid "
    for j in range(1, 10):
        s += "e" + str(i) + str(j) + ' '
    f.write(s + "\r\n")    

f.write("\r\n______________________________\r\n")

for i in range(1, 10):
    s = "\<and> valid "
    for j in range(1, 10):
        s += "e" + str(j) + str(i) + ' '
    f.write(s + "\r\n")    

f.write("\r\n______________________________\r\n")

for i in range(1, 10):
    s = ""
    for j in range (i, 10):
        if(i != j):
            s += "(e" + str(i) + " ≠ " + "e" + str(j) + ") \<and> "
    f.write(s + "\r\n")
s = ""
for i in range(1, 10):
    s += "(e" + str(i) + " < 10) \<and> "
f.write(s + "\r\n")

f.write("\r\n______________________________\r\n")
