from random import randint
from random import choice

file_name = input("input file name: ")
file_size = int(input("input file size: "))

surname_string = "Ivanov Smirnov Kuznecov Popov Vasilev Petrov \
Sokolov Mihajlov Novikov Fedorov Morozov Volkov Alekseev Lebedev \
Semenov Egorov Pavlov Kozlov Stepanov Nikolaev Orlov Andreev Makarov \
Nikitin  Zaharov  Zajcev  Solovev  Borisov  YAkovlev  Grigorev Romanov \
Vorobev Sergeev Kuzmin  Frolov  Aleksandrov Dmitriev Korolev Gusev Kiselev"
surname_list = surname_string.split()

name_string = "Vadim Valentin Valerij Vasilij Veniamin Vikentij Viktor Vilen \
Vissarion Vitalij Vlad Vladimir Vladislav Vladlen Voldemar Vsevolod Vyacheslav"
name_list = name_string.split()

phone_number_string = "77017333190 77019381234 77027773690 77057163877 77074909644 77077799795 \
77079517777 77714927700 77715740077 77715797822 77770076877 77770076977 77772955554 77787483377 \
77787683377 79021100098 79021100099 79021100147 79032478845 79032478917 79032478979 79032480839"
phone_number_list = phone_number_string.split()

address_string = "Abakan Azov Aleksandrov Aleksin Almetevsk Anapa Angarsk Apatity Arzamas Armavir \
Arhangelsk Asbest Astrahan Achinsk Balakovo Balahna"
address_list = address_string.split()

post_string = "Vrach Uchitel Sanitar Volonter Programmist Santehnik Slesar"
post_list = post_string.split()

service_string = "CRB UFC BMSTU ICPP MIT BOMONKA YANDEX GOOGLE"
service_list = service_string.split()

with open(file_name, 'w') as f:
    for i in range(file_size):
        f.write(choice(surname_list) + ' ')
        f.write(choice(name_list) + ' ')
        f.write(choice(phone_number_list) + ' ')
        f.write(choice(address_list) + ' ')
        status = randint(0, 1)
        f.write(str(status) + ' ')
        if status == 0:
            f.write(str(randint(1, 30)) + ' ')
            f.write(str(randint(1, 12)) + ' ')
            f.write(str(randint(1950, 2020)) + '\n')
        else:
            f.write(choice(post_list) + ' ')
            f.write(choice(service_list) + '\n')
            
    
