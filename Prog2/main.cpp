#include <fstream>
#include <iostream>
#include <time.h>
#include <iomanip>//��� ������ ��������� � �������
using namespace std;
double func(double x) {
	return  - x + 2 * cos(x);
}
int main() {
	double a = 10.0;
	double b = 20.0;
	int N = 3;//������� ������� �������� ��������, �� 
	int K = 6;//����� ����������
	int M = (N - 1) * K + 1;//����� ����� ������������=(N-2)*K +(K+1) ����� ����� ����� ��������� + �� ������
	double* arrxM = new double[M];//������ x-��  ��������� M
	int S = 2000; //���-�� ����� �� ������� ����� ������� Ln ( S ��� Mviz)
	if (S-1 % K != 0) {
		S = S - (S-1) % K;//���� � ��� ������� ����� �� ������������� �� ������ �������� S �� ����� ����� SS ���� ����� ������
	}
	int SS = (S - 1) / K;//���-�� ����� ���������� � ��������
	double* arrxS = new double[S];//������ x-��  ��������� S
	double* resz = new double[N];//������� ������������
	double* Ln = new double[S]; //������ ����������������� ����������
	double* arryM = new double[M]; //������ �������� �������
	double* G = new double[S];//� ��� ���������� �� x-a� ��������� S
	double* arrxMsto = new double[(M-1)*100+1];//������ x-�� ��������� � ����� h/100(�� ���� �� ��������� ������ �� �-1 (����� �� [ab]
	                                           //� ����,�������� M-1)�������� �� 100 ����������  ������� ����� ����� (M-1)*100+1
											  //+1 ��� ��� �������� ��������� ����� ������� [ab]

	//������� ����������� ����� �� ��� � ������� ���������
	double h=(b - a) / (M - 1); //����������� ���
	for (int i = 0; i < M; i++) {
		arrxM[i] = a + i * (b - a) / (M - 1);//(b - a) / (M - 1)=h-����������� ���
	}
	for (int i = 0; i < S; i++) {
		arrxS[i] = a + i * (b - a) / (S - 1);//����� ��������� S
	}
	for (int i = 0; i < M; i++) {  //�������� ������� � ����� - ����� �����������
		arryM[i] = func(arrxM[i]);
		
	}
	for (int i = 0; i < S; i++) {//��������  ������� � ������ Mviz ��� �������
		G[i] = func(arrxS[i]);
		
	}

	for (int i = 0; i < N; i++) { //��������� ������ ������������ �� �������������
		resz[i] = 1; //��� ����� ����� ��������� �� ����, ������ ������ �������
		for (int j = 0; j < N; j++) {
			if (j != i) {
				resz[i] = resz[i] * (arrxM[i] - arrxM[j]); // �� ���� �������� �� ��� ���������� �� ����� ������
			}
		}
	}
	
	int i = 0;
	for (int k = 0; k < K; k++) { //��� �� ���������
			                                      /*i �� ������������ �� ���� ����� ������� � ��� ����� ���������, �� ����� ����� �� ������������(�� �� �� ����� ���������� ������ ��� � ������ �������,
		                                              (k-����� ��������� ������ ���������; (k+1)-������ ���������� ���������, ����� �������. ����� ��� ����� ����� ��������� �� SS (�� �-�� ��������� � ��� SS �����)*/
		for (; i<=(k+1)*SS; i++) {//���� �� ������������� �� ����� ����� ��������*���-�� ����� � ��������� � � �� ������ ��������� �� 0 �� SS, ����� �� SS+1 �� 2SS
			Ln[i] = 0;										
			for (int j = 0; j < N; j++) { //�� �����
				double proizv = 1.0;
				for (int m = 0; m < N; m++) { //�� ������������ 
					if (j != m)
						proizv *= (arrxS[i] - arrxM[k*(N-1)+m]); //����� ������ ���������:������ ����� ������� ���������(k-�� ��������)*���-�� �����+m(����� ����� ������ ���������)
				}
				Ln[i] += arryM[k*(N-1)+j] * proizv / resz[j];
				//cout << Ln[i] << proizv << endl;
			}
			//cout << Ln[i] << endl;
		}
	}
	double abs1 = 0, abs2 = 0, absinf = 0;//���������� ����������� � L1 L2 L����
	double otn1 = 0, otn2 = 0, otninf = 0;//������������� �����������=����������/����� func

	for (int i = 0; i < (M-1)*100+1; i++) {
		arrxMsto[i] = a + i * h/100;//    c���� � ����� h/100
	}

	int p = 0;
	for (int k = 0; k < K; k++) {//�� ��������� ������ ������ �������� S � ��� ����� h/100
		for (;  p <=(k+1)*((N - 1) * 100); p++) {//�� ������������ ��� N ����� � (N-1)������������� ��������� �� 100 � ��������� �� ����� ���������
			double L= 0.0;										
			for (int j = 0; j < N; j++) { //�� �����
				double proizv = 1.0;
				for (int m = 0; m < N; m++) { //�� ������������ 
					if (j != m)
						proizv *= (arrxMsto[p] - arrxM[k * (N - 1) + m]); // ����� ������ ��������� �������������� ���: ������ ����� ������� ���������(k-�� ��������)+m(����� ����� ������ ���������)
				}
				L += arryM[k * (N - 1) + j] * proizv / resz[j];//��������� ���������� ��������� � i�� �����
				//cout<<"p= " << proizv << endl;
			}
			//cout << L << endl;
			abs1 += fabs(L - func(arrxMsto[p])); //����� ������� ��������
			abs2 += pow(fabs(L - func(arrxMsto[p])),2);//����� ���������
			absinf = max(absinf, fabs(L - func(arrxMsto[p])));//�������� ������ ��������
			otn1 += fabs(func(arrxMsto[p]));//���� ��� ���������� ���������� ����� � �����������
			otn2 += pow(fabs(func(arrxMsto[p])), 2);
			otninf = max(otninf, fabs(func(arrxMsto[p])));//������ �������� �� ������������1
		}

	}
	abs2 = sqrt(abs2);
	otn2= sqrt(otn2);//���� ��� �����������
	otn1 = abs1 / otn1;
	otn2 = abs2 / otn2;
	otninf = absinf / otninf;
	//cout << "abs1=" << abs1 << endl << "otn1= " << otn1 << endl<< "abs2=" << abs2 << endl << "otn2= " << otn2 << endl << "absinf=" << absinf << endl << "otninf= " << otninf << endl;
	//cout << setw(15) << "abs1 = " <<fixed << setprecision(7) << abs1 << setw(15) << "abs2 = " << abs2 << setw(15) << "absinf = " << absinf << endl;
	//cout << setw(15) << "otn1 = " <<fixed << setprecision(7) << otn1 << setw(15) << "otn2 = "  << otn2 << setw(15) << "otninf = " << otninf << endl;
 
	ofstream fout8;
	fout8.open("file8.txt");
	fout8.setf(ios::scientific);
	fout8 << setw(30) << left << " " << setw(30) << left << "||.||1" << setw(30) << left << "||.||2" << setw(30) << left << "||.||inf" << endl;
	fout8 << setw(30) << left << "absolut" << setw(30) << left << abs1 << setw(30) << left << abs2 << left << setw(30) << absinf << endl;
	fout8 << setw(30) << left << "otnosit" << setw(30) << left << otn1 << setw(30) << left << otn2 << left << setw(30) << otninf << endl;
	fout8.close();

	//������ � �������
	ofstream fout0;
	fout0.open("file0.txt");
	fout0 << a << "\t" << b;
	fout0.close();

	ofstream fout; //���� �������� N
	fout.open("file1.txt");
	for (int i = 0; i < M; i++) {
		fout << fixed;
		fout.precision(5);
		fout.setf(ios::right);
		fout.width(10);
		fout << arrxM[i] << "\n";
	}
	fout.close();

	ofstream massy;
	massy.open("file2.txt"); //������� �
	for (int i = 0; i < M; i++) {
		massy << fixed;
		massy.precision(5);
		massy.setf(ios::right);
		massy.width(10);
		massy << arryM[i] << endl;
	}
	massy.close();

	ofstream fout3;
	fout3.open("file3.txt"); //���� ��������� M
	for (int i = 0; i < S; i++) {
		fout3 << fixed;
		fout3.precision(5);
		fout3.setf(ios::right);
		fout3.width(10);
		fout3 << arrxS[i] << "\n";
	}
	fout3.close();

	ofstream foutLn; //���������������� ���������
	foutLn.open("file4.txt");
	for (int i = 0; i < S; i++) {
		foutLn << fixed; //���� ����� ����� ������� ��� �������
		foutLn.precision(5);
		foutLn.setf(ios::right);//������������ �� ������ ������� ��� �������
		foutLn.width(10);
		foutLn << Ln[i] << "\n";
	}
	foutLn.close();

	ofstream fout4;
	fout4.open("file5.txt"); 
	for (int i = 0; i < S; i++) {
		fout4 << fixed;
		fout4.precision(5);
		fout4.setf(ios::right);
		fout4.width(10);
		fout4 << G[i] << "\n";
	}
	fout4.close();

	delete[] arrxM;
	delete[] arrxS; 
	delete[] resz;
	delete[] Ln;
	delete[] arryM;
	delete[] arrxMsto;
	delete[] G;
	std::system("python PythonApplication1.py");

	return 0;



}