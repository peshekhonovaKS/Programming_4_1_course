# -*- coding: cp1251 -*- 
#для работы кириллицы
import matplotlib.pyplot as plt  #для графиков переименовываем в plt для удобства
import numpy as np #работа с массивами данных
xn = np.genfromtxt('file1.txt')
xm = np.genfromtxt('file3.txt')
ym = np.genfromtxt('file5.txt')
y = np.genfromtxt('file2.txt')
Ln = np.genfromtxt("file4.txt")
otrezok =np.genfromtxt("file0.txt")
#fig, ax = plt.subplots() #создали пространство и оси
def cm_to_inch(value): #функция для того,чтобы можно было указывать размер графика
    return value/2.54
plt.figure(figsize=(cm_to_inch(21),cm_to_inch(15))) #укажем размер графика
plt.grid(True)#сетка 
plt.title('график функции f(x) и интерполяционного многочлена Лагранжа',fontsize=15,fontweight="bold")
plt.plot(xm,ym,color='red',label="f(x)")
plt.plot(xn,y,'ko') # o - это кружок, k - чёрный цвет
plt.plot(xm,Ln,color='blue',label="Ln(x)")
plt.legend() #подпись f(x) и Ln(x)
plt.xlabel('Ось x',fontweight="bold") #подпишем оси
plt.ylabel('Ось y',fontweight="bold")
plt.xlim(otrezok[0],otrezok[1]) #рисунок именно на нашем отрезке, без нуля на графике, можно убрать
#plt.xlim(xn[0],xn[N-1])  если так то нужно ввести N

plt.show()
