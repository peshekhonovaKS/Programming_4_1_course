# -*- coding: cp1251 -*- 
#��� ������ ���������
import matplotlib.pyplot as plt  #��� �������� ��������������� � plt ��� ��������
import numpy as np #������ � ��������� ������
xmviz = np.genfromtxt('file1.txt')
ymviz = np.genfromtxt('file2.txt')
xm = np.genfromtxt('file5.txt')
ym = np.genfromtxt('file3.txt')
xm05 = np.genfromtxt('file6.txt')
ym05 = np.genfromtxt('file4.txt')
yrunge=np.genfromtxt('file7.txt')

otrezok =np.genfromtxt("file0.txt")

#fig, ax = plt.subplots() #������� ������������ � ���
def cm_to_inch(value): #������� ��� ����,����� ����� ���� ��������� ������ �������
    return value/2.54
plt.figure(figsize=(cm_to_inch(21),cm_to_inch(15))) #������ ������ �������
plt.grid(True)#����� 
plt.title('��������� �����������������',fontsize=15,fontweight="bold")
plt.plot(xmviz,ymviz,color='red',label="f'(x)")
plt.scatter(xm,ym,color='blue',label="f'(x) ����������� � ������ h")
plt.scatter(xm05,ym05,color='black',label="f'(x) ����������� � ������ h/2")
plt.scatter(xm,yrunge,color='yellow',label="f'(x) �� ������� �����")
plt.legend() #������� f(x) � Apr(x)
plt.xlabel('��� x',fontweight="bold") #�������� ���
plt.ylabel('��� y',fontweight="bold")
plt.xlim(otrezok[0],otrezok[1]) #������� ������ �� ����� �������, ��� ���� �� �������, ����� ������
#plt.xlim(xn[0],xn[N-1])  ���� ��� �� ����� ������ N

plt.show()
