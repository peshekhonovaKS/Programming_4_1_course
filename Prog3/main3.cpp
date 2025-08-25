#include <fstream> 
#include <iostream>
#include <time.h>
#include <iomanip>//��� ������ ��������� � �������
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;
using Eigen::MatrixXd;
using Eigen::VectorXd;
double func(double x) {
	//return  x+sin(pow(x, 2)) ;
	return sin(x);
}

double fi(int i, double x, double* metr, int N, int k) {//fi_i(x), metr - �����, �� �������� �������, N - ���������� ����� � ���������, k - ��������, � ������� ��������� 
	double znam = 1.0;
	double f = 1.0;
	for (int j = 0; j < N; j++)
		if (i != j + (N - 1) * k) {
			f *= x - metr[j + (N - 1) * k];
			znam *= metr[i] - metr[j + (N - 1) * k];
		}
	f = f / znam;
	return f;
}

int main() {
	srand(time(NULL));
	double a = -3.0;
	double b = 3.0;
	int K = 3; //���-�� �������������
	int N = 5; //���-�� ����� �� �������� ��������
	int L = 20;//���-�� ��������� ����� �� ����� ������������
	int M = (N - 1) * K + 1;//����� ����� ����� �����
	double* arrxM = new double[M];//������ ���� ����� ����� �
	double* arrxL = new double[L * K];//������ ���� ��������� ����� �� ��� ab
	double* arryL = new double[L * K];//y-�� �� ��������� ������

	double h = (b - a) / (M - 1); //����������� ���
	for (int i = 0; i < M; i++)
		arrxM[i] = a + i * (b - a) / (M - 1);//      (b - a) / (M - 1)=h-����������� ���

	int l = 0;
	for (int k = 0; k < K; k++) { //�������� �� �������������
		double k1 = arrxM[k * (N - 1)]; //����,��������������� ������ ������������:����� ���������*���-�� ����� � ���������
		double k2 = arrxM[(k + 1) * (N - 1)];//����� ������������
		//cout << " k1 = " << k1 << " k2 = " << k2 << endl;
		for (; l < L * (k + 1); l++) { //����� �� ����� L c�������� ����� �� ������������, ��������� L*(k+1)=���-�� ����� �� ����� ���������
			//cout << a<<" "<<b<< endl;
			arrxL[l] = k1 + (k2 - k1) * rand() / (float)RAND_MAX; //����� ����� �� ������������ [k1k2]
			//cout << arrxL[l]<<"  ";
		}
	}

	double t;
	for (int i = 1; i < K * L; i++) {
		for (int j = 0; j < K * L - 1; j++)
			if (arrxL[j] > arrxL[j + 1]) {
				t = arrxL[j];
				arrxL[j] = arrxL[j + 1];
				arrxL[j + 1] = t;
			}

	}//��������� ��������� ����� 

	//�-�� ����������� �� ��������� ������ L, ����� �� ������� [ab] �� K*L
	for (int i = 0; i < K * L; i++) {
		arryL[i] = func(arrxL[i]);
	}

	//!!!!!!!!!!!������� ���������!!!!!!!!!!!

	//c����� ������� �
	double** arr = new double* [M];//���-�� �����=����� �� �-��=����� ����� �� �������=M ��� �� ����� ��������� �� ���������
	for (int i = 0; i < M; i++) {
		arr[i] = new double[N];//���-�� �������� �������=����� ����� �� ������������
		for (int j = 0; j < N; j++) {
			arr[i][j] = 0;
		}
	}


	/*for (int p = 0; p < M; p++) {//������ ������� � ����� ������� 
		for (int i = 0; i < N; i++) {//������� ������� �
			cout << arr[p][i] << " ";
		}
		cout << endl;
	}
	cout << endl;*/


	MatrixXd arr1 = MatrixXd::Zero(M, M);//������ �������
	VectorXd arrright = VectorXd::Zero(M);//������ �����
	VectorXd � = VectorXd::Zero(M);//������ �1...�M

	for (int k = 0; k < K; k++) { //�� ����������
		for (int i = k * (N - 1); i <= (k + 1) * (N - 1); i++) {//i ��� ����� ������� ������� ��������� ���������� ��������� ����� ��������� �� ���-�� ����� � ��
			for (int j = i; j <= (k+1)*(N-1); j++) {//j-������� ������� �������
				for (int l = k * L; l < (k + 1) * L; l++) {
					arr[i][j-i] += fi(i, arrxL[l], arrxM, N, k) * fi(j, arrxL[l], arrxM, N, k);
					//cout << fi(i, arrxL[l], arrxM, N, k) << endl;
				}
			}

			for (int l = k * L; l < (k + 1) * L; l++)
				arrright(i) += arryL[l] * fi(i, arrxL[l], arrxM, N, k);
		}
	}

	//!!!!!!!!!!!������� ������!!!!!!!!!!!
	for (int j = 0; j < N; j++) {
		for (int i = 0; i < M - j; i++) {
			arr1(i, i + j) = arr[i][j];
			arr1(i + j, i) = arr[i][j];
		}
	}

	/*cout << endl;
	//������� ������ �������
	for (int p = 0; p < M; p++) {//������ ������� �1
		for (int i = 0; i < M; i++) {//������� ������� �1
			cout << arr1(p, i) << " ";
		}
		cout << endl;
	}
	cout << endl;
	//����� ������ �����
	for (int i = 0; i < M; i++) {
		cout << arrright(i) << " ";
	}
	cout << endl;
	*/
	VectorXd C = arr1.lu().solve(arrright);
	/*//����� ������� �
	for (int i = 0; i < M; i++) {
		cout << C(i) << " ";
	}
	cout << endl;*/
	


	//!!!!!!!��� �������!!!!!!!!
	int Mviz = 1000;
	if (Mviz - 1 % K != 0) {
		Mviz = Mviz - (Mviz - 1) % K;//���� � ��� ������� ����� �� ������������� �� ������ �������� S �� ����� ����� SS ���� ����� ������
	}
	//cout<<S<<endl;
	int SS = (Mviz - 1) / K;//���-�� ����� ���������� � ��������
	double* arrxMviz = new double[Mviz];//����� ������ ����� ��� �������
	double* arryMviz = new double[Mviz];//������� y ��� �������
	for (int i = 0; i < Mviz; i++) {
		arrxMviz[i] = a + i * (b - a) / (Mviz - 1);
	}
	for (int i = 0; i < Mviz; i++) {
		arryMviz[i] = func(arrxMviz[i]);
	}

	double* AprMviz = new double[Mviz];//������� ������������

	//!!!!!!!!������ ������������!!!!!!!!
	for (int i = 0; i < Mviz; i++) {
		AprMviz[i] = 0;
		int k = i / SS;
		if (k == K) {
			k = K - 1; //�������� ����� ��������� ����� �� ������� � �������������� ��������
		}
		for (int j = k * (N - 1); j <= (k + 1) * (N - 1); j++) {
			AprMviz[i] += C(j) * fi(j, arrxMviz[i], arrxM, N, k);
		}
	}

	
	/*double* arryM = new double[M];
	for (int i = 0; i < M; i++) {
		arryM[i] = func(arrxM[i]);
	}*/

	//����������� �� ��������� �����
	double abs1 = 0, abs2 = 0, absinf = 0;
	double otn1 = 0, otn2 = 0, otninf = 0;
	for (int i = 0; i <K*L; i++) {
		double Apr = 0;
		int k = i / L;
		for (int j = k * (N - 1); j <= (k + 1) * (N - 1); j++) {
			Apr += C(j) * fi(j, arrxL[i], arrxM, N, k);
		}
		abs1 += fabs(Apr - arryL[i]); //����� ������� ��������
		abs2 += pow(fabs(Apr - arryL[i]), 2);//����� ���������
		absinf = max(absinf, fabs(Apr - arryL[i]));//�������� ������ ��������
		otn1 += fabs(arryL[i]);
		otn2 += pow(fabs(arryL[i]), 2);
		otninf = max(otninf, fabs(arryL[i]));//������ �������� �� ������������1

	}
	abs2 = sqrt(abs2);
	otn2 = sqrt(otn2);
	otn1 = abs1 / otn1;
	otn2 = abs2 / otn2;
	otninf = absinf / otninf;
	//cout << setw(15) << "abs1 = " << fixed << setprecision(7) << abs1 << setw(15) << "abs2 = " << abs2 << setw(15) << "absinf = " << absinf << endl;
	//cout << setw(15) << "otn1 = " << fixed << setprecision(7) << otn1 << setw(15) << "otn2 = " << otn2 << setw(15) << "otninf = " << otninf << endl;
	//����������� � ����� h/100
	double abs1sto = 0, abs2sto = 0, absinfsto = 0;
	double otn1sto = 0, otn2sto = 0, otninfsto = 0;
	for (int i = 0; i < M; i++) {
		int k = i / (N - 1);
		if (k != K) {
			for (int j = 0; j < 100; j++) {
				double Apr = 0;
				for (int l = k * (N - 1); l <= (k + 1) * (N - 1); l++) {
					Apr += C(l) * fi(l, arrxM[i] + (h * j) / 100, arrxM, N, k);
				}
				//cout << Apr << " " << func(arrxM[i] + (h * j) / 100) << endl;
				abs1sto += fabs(Apr - func(arrxM[i] + (h * j) / 100)); //����� ������� ��������
				abs2sto += pow(fabs(Apr - func(arrxM[i] + (h * j) / 100)), 2);//����� ���������
				absinfsto = max(absinfsto, fabs(Apr - func(arrxM[i] + (h * j) / 100)));//�������� ������ ��������
				otn1sto += fabs(func(arrxM[i] + (h * j) / 100));
				otn2sto += pow(fabs(func(arrxM[i] + (h * j) / 100)), 2);
				otninfsto = max(otninfsto, fabs(func(arrxM[i] + (h * j) / 100)));
			}
		}
		else {
			double Apr = 0;
			k = K - 1;
			for (int j = k * (N - 1); j <= (k + 1) * (N - 1); j++) {
				Apr += C(j) * fi(j, arrxM[M-1], arrxM, N, k);
			}
			abs1sto += fabs(Apr - func(arrxM[M - 1])); //����� ������� ��������
			abs2sto += pow(fabs(Apr - func(arrxM[M - 1])), 2);//����� ���������
			absinfsto = max(absinfsto, fabs(Apr - func(arrxM[M - 1])));//�������� ������ ��������
			otn1sto += fabs(func(arrxM[M - 1]));
			otn2sto += pow(fabs(func(arrxM[M - 1])), 2);
			otninfsto = max(otninfsto, fabs(func(arrxM[M - 1])));//������ �������� �� ������������1

		}
	}
	abs2sto = sqrt(abs2sto);
	otn2sto = sqrt(otn2sto);
	otn1sto = abs1sto / otn1sto;
	otn2sto = abs2sto / otn2sto;
	otninfsto = absinfsto / otninfsto;
	//cout << setw(15) << "abs1 = " << fixed << setprecision(7) << abs1sto << setw(15) << "abs2 = " << abs2sto << setw(15) << "absinf = " << absinfsto << endl;
	//cout << setw(15) << "otn1 = " << fixed << setprecision(7) << otn1sto << setw(15) << "otn2 = " << otn2sto << setw(15) << "otninf = " << otninfsto << endl;
	
	ofstream fout8;
	fout8.open("file8.txt");
	fout8.setf(ios::scientific);
	fout8 << setw(30) << left << "v sluch tochkah" << setw(30) << left << "||.||1" << setw(30) << left << "||.||2" << setw(30) << left << "||.||inf" << endl;
	fout8 << setw(30) << left << "absolut" << setw(30) << left << abs1 << setw(30) << left << abs2 << left << setw(30) << absinf << endl;
	fout8 << setw(30) << left << "otnos" << setw(30) << left << otn1 << setw(30) << left << otn2 << left << setw(30) << otninf << endl;
	fout8 << "----------------------------------------------------------------------------------------------------------------" << endl;
	fout8 << setw(30) << left << "v tochkah h/100" << setw(30) << left << "||.||1" << setw(30) << left << "||.||2" << setw(30) << left << "||.||inf" << endl;
	fout8 << setw(30) << left << "absolut" << setw(30) << left << abs1sto << setw(30) << left << abs2sto << left << setw(30) << absinfsto << endl;
	fout8 << setw(30) << left << "otnos" << setw(30) << left << otn1sto << setw(30) << left << otn2sto << left << setw(30) << otninfsto << endl;
	fout8.close();





	//!!!!!!!�����!!!!!!!!
	ofstream fout0;
	fout0.open("file0.txt");
	fout0 << a << "\t" << b;
	fout0.close();

	ofstream fout; //��������� ����
	fout.open("file1.txt");
	for (int i = 0; i < Mviz; i++) {
		fout << fixed;
		fout.precision(5);
		fout.setf(ios::right);
		fout.width(10);
		fout << arrxMviz[i] << "\n";
	}
	fout.close();

	ofstream massy;
	massy.open("file2.txt");
	for (int i = 0; i < Mviz; i++) {
		massy << fixed;
		massy.precision(5);
		massy.setf(ios::right);
		massy.width(10);
		massy << arryMviz[i] << endl;
	}
	massy.close();
	ofstream fout3;
	fout3.open("file3.txt");
	for (int i = 0; i < Mviz; i++) {
		fout3 << fixed;
		fout3.precision(5);
		fout3.setf(ios::right);
		fout3.width(10);
		fout3 << AprMviz[i] << "\n";
	}
	fout3.close();

	ofstream fout4;
	fout4.open("file4.txt");
	for (int i = 0; i < K*L; i++) {
		fout4 << fixed;
		fout4.precision(5);
		fout4.setf(ios::right);
		fout4.width(10);
		fout4 << arrxL[i] << "\n";
	}
	fout4.close();

	ofstream fout5;
	fout5.open("file5.txt");
	for (int i = 0; i < K*L; i++) {
		fout5 << fixed;
		fout5.precision(5);
		fout5.setf(ios::right);
		fout5.width(10);
		fout5 << arryL[i] << "\n";
	}
	fout5.close();




	//!!!!!!!��������!!!!!!!!
	delete[] AprMviz;
	delete[] arrxMviz;
	delete[] arryMviz;
	delete[] arrxM;
	//delete[] arryM;
	delete[] arrxL;
	delete[] arryL;
	for (int i = 0; i < M; i++) {
		delete[] arr[i];
	}
	delete[] arr;

	std::system("python PythonApplication1.py");

	return 0;

}

			