# -*- coding: cp1251 -*- 
#для работы кириллицы
import matplotlib.pyplot as plt  #для графиков переименовываем в plt для удобства
import numpy as np #работа с массивами данных
xmviz = np.genfromtxt('file1.txt')
ymviz = np.genfromtxt('file2.txt')
xm = np.genfromtxt('file5.txt')
ym = np.genfromtxt('file3.txt')
xm05 = np.genfromtxt('file6.txt')
ym05 = np.genfromtxt('file4.txt')
yrunge=np.genfromtxt('file7.txt')

otrezok =np.genfromtxt("file0.txt")

#fig, ax = plt.subplots() #создали пространство и оси
def cm_to_inch(value): #функция для того,чтобы можно было указывать размер графика
    return value/2.54
plt.figure(figsize=(cm_to_inch(21),cm_to_inch(15))) #укажем размер графика
plt.grid(True)#сетка 
plt.title('численное дифференцировнаие',fontsize=15,fontweight="bold")
plt.plot(xmviz,ymviz,color='red',label="f'(x)")
plt.scatter(xm,ym,color='blue',label="f'(x) приближённое с сеткой h")
plt.scatter(xm05,ym05,color='black',label="f'(x) приближённое с сеткой h/2")
plt.scatter(xm,yrunge,color='yellow',label="f'(x) по правилу Рунге")
plt.legend() #подпись f(x) и Apr(x)
plt.xlabel('Ось x',fontweight="bold") #подпишем оси
plt.ylabel('Ось y',fontweight="bold")
plt.xlim(otrezok[0],otrezok[1]) #рисунок именно на нашем отрезке, без нуля на графике, можно убрать
#plt.xlim(xn[0],xn[N-1])  если так то нужно ввести N

plt.show()
