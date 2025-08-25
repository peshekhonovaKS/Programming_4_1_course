# -*- coding: cp1251 -*- 
#��� ������ ���������
import matplotlib.pyplot as plt  #��� �������� ��������������� � plt ��� ��������
import numpy as np #������ � ��������� ������
xn = np.genfromtxt('file1.txt')
xm = np.genfromtxt('file3.txt')
ym = np.genfromtxt('file5.txt')
y = np.genfromtxt('file2.txt')
Ln = np.genfromtxt("file4.txt")
otrezok =np.genfromtxt("file0.txt")
#fig, ax = plt.subplots() #������� ������������ � ���
def cm_to_inch(value): #������� ��� ����,����� ����� ���� ��������� ������ �������
    return value/2.54
plt.figure(figsize=(cm_to_inch(21),cm_to_inch(15))) #������ ������ �������
plt.grid(True)#����� 
plt.title('������ ������� f(x) � ����������������� ���������� ��������',fontsize=15,fontweight="bold")
plt.plot(xm,ym,color='red',label="f(x)")
plt.plot(xn,y,'ko') # o - ��� ������, k - ������ ����
plt.plot(xm,Ln,color='blue',label="Ln(x)")
plt.legend() #������� f(x) � Ln(x)
plt.xlabel('��� x',fontweight="bold") #�������� ���
plt.ylabel('��� y',fontweight="bold")
plt.xlim(otrezok[0],otrezok[1]) #������� ������ �� ����� �������, ��� ���� �� �������, ����� ������
#plt.xlim(xn[0],xn[N-1])  ���� ��� �� ����� ������ N

plt.show()
