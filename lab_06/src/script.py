from random import randint

file_name = input("Введите название файла: ")
file_size = int(input("Введите количество элементов файла: "))

with open(file_name, 'w') as f:
    for i in range(file_size):
        f.write(str(randint(0, file_size)) + '\n')