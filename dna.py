from sys import argv, exit
import csv

if len(argv) != 3:
    print("Usage: python dna.py data.csv sequence.txt")
    exit(1)

file1 = open(argv[1], 'r')
reader = csv.DictReader(file1)

file2 = open(argv[2], 'r')
lst = file2.read()

str = reader.fieldnames
dict = {

}
for i in range(len(str)):
    if i != 0:
        dict[str[i]] = 0

for j in range(1, len(str)):
    max = 0
    for i in range(len(lst)):
        count = 0
        if lst[i: i + len(str[j])] == str[j]:
            count += 1
            while (lst[i + (count * len(str[j])): i + ((count + 1) * len(str[j]))] == str[j]):
                count += 1
        if count > max:
            max = count
    dict[str[j]] = max

for i in reader:
    count = 0
    for j in range(1, len(str)):
        k = i[str[j]]
        if int(k) == dict[str[j]]:
            count += 1
    if count == len(str) - 1:
        print(i['name'])
        exit(0)

print("No match")