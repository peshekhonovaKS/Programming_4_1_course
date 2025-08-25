# -*- coding: cp1251 -*- 
#��� ������ ���������
import matplotlib.pyplot as plt  #��� �������� ��������������� � plt ��� ��������
import numpy as np #������ � ��������� ������
xmviz = np.genfromtxt('file1.txt')
ymviz = np.genfromtxt('file2.txt')
xm = np.genfromtxt('file4.txt')
ym = np.genfromtxt('file5.txt')
apr = np.genfromtxt('file3.txt')
otrezok =np.genfromtxt("file0.txt")

#fig, ax = plt.subplots() #������� ������������ � ���
def cm_to_inch(value): #������� ��� ����,����� ����� ���� ��������� ������ �������
    return value/2.54
plt.figure(figsize=(cm_to_inch(21),cm_to_inch(15))) #������ ������ �������
plt.grid(True)#����� 
plt.title('������ ������� y � �������������',fontsize=15,fontweight="bold")
#plt.plot(xn,y,color='red',label="f(x)")
plt.plot(xmviz,ymviz,color='red',label="f(x)")
#plt.plot(xm,ym,'ro')
plt.plot(xm,ym,'ko') # o - ��� ������, k - ������ ����
plt.plot(xmviz,apr,color='blue',label="approximazia(x)")
plt.legend() #������� f(x) � Apr(x)
plt.xlabel('��� x',fontweight="bold") #�������� ���
plt.ylabel('��� y',fontweight="bold")
plt.xlim(otrezok[0],otrezok[1]) #������� ������ �� ����� �������, ��� ���� �� �������, ����� ������
#plt.xlim(xn[0],xn[N-1])  ���� ��� �� ����� ������ N

plt.show()
