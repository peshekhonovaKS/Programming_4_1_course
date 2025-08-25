#include <fstream> 
#include <iostream>
#include <time.h>
#include <iomanip>//для вывода красивого в файлики
using namespace std;
double func1(double x) {
	return  cos(x);
}
double func2(double x) {
	return  -sin(x);
}
int main(){
	double a = -5.0;
	double b = 5.0;
	int M = 20.0;
	double h = (b - a) / (M - 1);
	double* arrxM = new double[M];
	double* arryM = new double[M];
	double* arrx05M = new double[2*M-1];
	double* arry05M = new double[2 * M - 1];
	double* pribl = new double[M];
	double* pribl05 = new double[2 * M - 1];
	for (int i = 0; i < M; i++) {//равномерная сетка с шагом h
		arrxM[i] = a + i * h;
	}
	for (int i = 0; i < M; i++) {//значения в этой сетке
		arryM[i] = func1(arrxM[i]);
	}
	for (int i = 0; i < 2*M-1; i++) {//сетка h/2
		arrx05M[i] = a + i * h/2;
	}
	for (int i = 0; i < 2 * M - 1; i++) {//значения в ней
		arry05M[i] = func1(arrx05M[i]);
	}
	//формулы численного дифференцирования второго порядка точности
	pribl[0] = (-3 * arryM[0] + 4 * arryM[1] - arryM[2]) / (2 * h); //для крайней
	for (int i = 1; i < M - 1; i++){
		pribl[i] = (-arryM[i - 1] + arryM[i + 1]) / (2 * h);
		}
	pribl[M - 1] = (arryM[M - 3] - 4 * arryM[M - 2] + 3 * arryM[M - 1]) / (2 * h);//для крайней


	//формулы для измельчённой сетки
	pribl05[0] = (-3 * arry05M[0] + 4 * arry05M[1] - arry05M[2]) / h; // в знаменателе (2 * h/2)=h
	for (int i = 1; i < 2*M-2; i++) {//2M-1-1=2M-2
		pribl05[i] = (-arry05M[i - 1] + arry05M[i + 1]) /h;
		}
	pribl05[2 * M - 2] = (arry05M[2 * M - 1 - 3] - 4 * arry05M[2 * M - 1- 2] + 3 * arry05M[2 * M - 1 - 1]) /h;



	double* glav = new double[M];//главная часть
	for (int i = 0; i < M; i++)
	{
		glav[i] =4 * (pribl05[2 * i] - pribl[i]) / 3;
	}
	double* runge = new double[M];//уточняем по правилу Рунге
	for (int i = 0; i < M; i++)
	{
		runge[i] = pribl[i] + glav[i];
	}


	double abs1 = 0.0, abs2 = 0.0, absf=0.0;//погрешности для сетки h
	double abs051 = 0.0, abs052 = 0.0, abs05f = 0.0;//погрешности для сетки h/2
	double absr1 = 0.0, absr2 = 0.0, absrinf = 0.0;//погрешности для Рунге

	double otn1 = 0.0, otn2 = 0.0, otnf = 0.0;
	double otn051 = 0.0, otn052 = 0.0, otn05f = 0.0;
	double otnr1 = 0.0, otnr2 = 0.0, otninf = 0.0;

	for (int i = 0; i < M; i++) {
		abs1 += fabs(func2(arrxM[i])-pribl[i]);
		absr1 += fabs(func2(arrxM[i]) - runge[i]);
		otn1 += fabs(func2(arrxM[i])); //или pribl
		otnr1 += fabs(func2(arrxM[i]));//или runge
		abs2 += pow(fabs(func2(arrxM[i]) - pribl[i]),2);
		absr2 += pow(fabs(func2(arrxM[i]) - runge[i]),2);
		otn2 += pow(fabs(func2(arrxM[i])), 2);
		otnr2 +=pow(fabs(func2(arrxM[i])), 2);
		absf=max(absf, fabs(func2(arrxM[i]) - pribl[i]));
		absrinf = max(absrinf, fabs(func2(arrxM[i]) - runge[i]));
		otnf= max(otnf, fabs(func2(arrxM[i])));
		otninf= max(otninf, fabs(func2(arrxM[i])));

	}
	abs2 = sqrt(abs2);
	otn2 = sqrt(otn2);
	otn2 = abs2 / otn2;
	absr2 = sqrt(absr2);
	otnr2 = sqrt(otnr2);
	otnr2 = absr2 / otnr2;
	otn1=abs1 / otn1;
	otnr1= absr1 / otnr1;
	otnf = absf / otnf;
	otninf = absrinf / otninf;


	for (int i = 0; i < 2 * M - 1; i++) {
		abs051 += fabs(func2(arrx05M[i]) - pribl05[i]);
		otn051 += fabs(func2(arrx05M[i]));
		abs052 += pow(fabs(func2(arrx05M[i]) - pribl05[i]), 2);
		otn052 += pow(fabs(func2(arrx05M[i])), 2);
		abs05f = max(abs05f, fabs(func2(arrx05M[i]) - pribl05[i]));
		otn05f = max(otn05f, fabs(func2(arrx05M[i])));
	}
	otn051 = abs051 / otn051;
	abs052 = sqrt(abs052);
	otn052 = sqrt(otn052);
	otn052 = abs052 / otn052;
	otn05f = abs05f / otn05f;


	//погрешность для главной части
	double abs1gl = 0.0, abs2gl = 0.0, absinfgl = 0.0;
	double otn1gl = 0.0, otn2gl = 0.0, otninfgl = 0.0;
	for (int i = 0; i < M; i++) {
		abs1gl += fabs(glav[i]);
		otn1gl += fabs(func2(arrxM[i]));
		abs2gl += pow(fabs(glav[i]), 2);
		otn2gl += pow(fabs(func2(arrxM[i])), 2);
		absinfgl = max(absinfgl, fabs(glav[i]));
		otninfgl = max(otninfgl, fabs(func2(arrxM[i])));
	}
	otn1gl = abs1gl / otn1gl;
	abs2gl = sqrt(abs2gl);
	otn2gl = abs2gl / otn2gl;
	otninfgl = absinfgl / otninfgl;

	ofstream fout8;
	fout8.open("file8.txt");

	fout8 << "tabl #1" << endl;
	fout8.setf(ios::scientific);
	
	fout8 << setw(30) << left << "pribl znach h"<< setw(30) << left << "||.||1" << setw(30) << left << "||.||2" << setw(30) << left << "||.||inf"<<endl;
	fout8 << setw(30) << left <<"absolut"<<setw(30) << left <<abs1 << setw(30) << left <<abs2 << left <<setw(30)<<absf<< endl;
	fout8 << setw(30) << left << "otnos" << setw(30) << left << otn1 << setw(30) << left << otn2 << left << setw(30) << otnf << endl;
	fout8 <<"----------------------------------------------------------------------------------------------------------------" << endl;
	fout8 << setw(30) << left << "pribl znach h/2" << setw(30) << left << "||.||1" << setw(30) << left << "||.||2" << setw(30) << left << "||.||inf" << endl;
	fout8 << setw(30) << left << "absolut" << setw(30) << left << abs051 << setw(30) << left << abs052 << left << setw(30) << abs05f << endl;
	fout8 << setw(30) << left << "otnos" << setw(30) << left << otn051 << setw(30) << left << otn052 << left << setw(30) << otn05f << endl;
	fout8 << "----------------------------------------------------------------------------------------------------------------" << endl;
	fout8 << setw(30) << left << "runge" << setw(30) << left << "||.||1" << setw(30) << left << "||.||2" << setw(30) << left << "||.||inf" << endl;
	fout8 << setw(30) << left << "absolut" << setw(30) << left << absr1 << setw(30) << left << absr2 << left << setw(30) << absrinf << endl;
	fout8 << setw(30) << left << "otnos" << setw(30) << left << otnr1 << setw(30) << left << otnr2 << left << setw(30) << otninf << endl;
	fout8 << "----------------------------------------------------------------------------------------------------------------" << endl;
	fout8 << "tabl #2" << endl;
	fout8 << setw(30) << left << " " << setw(30) << left << "||.||1" << setw(30) << left << "||.||2" << setw(30) << left << "||.||inf" << endl;
	fout8 << setw(30) << left << "absolut setka h" << setw(30) << left << abs1 << setw(30) << left << abs2 << left << setw(30) << absf << endl;
	//fout8 << setw(30) << left << "absolut setka h/2" << setw(30) << left << abs051 << setw(30) << left << abs052 << left << setw(30) << abs05f << endl;
	fout8 << setw(30) << left << "glav setka h" << setw(30) << left << abs1gl << setw(30) << left << abs2gl << left << setw(30) << absinfgl << endl;
	fout8.close();









	//!!!для рисунка!!!
	double Mviz=1000.0;
	double* arrxMviz = new double[Mviz];
	double* arryMviz = new double[Mviz];
	double h1 = (b - a) / (Mviz - 1);
	for (int i = 0; i < Mviz; i++) {
		arrxMviz[i] = a + i * h1;
	}
	for (int i = 0; i < Mviz; i++) {
		arryMviz[i] = func2(arrxMviz[i]);
	}





	//!!!работа с файлами!!!
	ofstream fout0;
	fout0.open("file0.txt");
	fout0 << a << "\t" << b;
	fout0.close();

	ofstream fout1;
	fout1.open("file1.txt");
	for (int i = 0; i < Mviz; i++) {
		fout1 << fixed;
		fout1.precision(5);
		fout1.setf(ios::right);
		fout1.width(10);
		fout1 << arrxMviz[i] << "\n";
	}
	fout1.close();
	ofstream fout2;
	fout2.open("file2.txt");
	for (int i = 0; i < Mviz; i++) {
		fout2 << fixed;
		fout2.precision(5);
		fout2.setf(ios::right);
		fout2.width(10);
		fout2 << arryMviz[i] << "\n";
	}
	fout2.close();


	ofstream fout3;
	fout3.open("file3.txt");
	for (int i = 0; i < M; i++) {
		fout3 << fixed;
		fout3.precision(5);
		fout3.setf(ios::right);
		fout3.width(10);
		fout3 << pribl[i] << "\n";
	}
	fout3.close();

	ofstream fout4;
	fout4.open("file4.txt");
	for (int i = 0; i < 2*M-1; i++) {
		fout4 << fixed;
		fout4.precision(5);
		fout4.setf(ios::right);
		fout4.width(10);
		fout4 << pribl05[i] << "\n";
	}
	fout4.close();

	ofstream fout5;
	fout5.open("file5.txt");
	for (int i = 0; i < M; i++) {
		fout5 << fixed;
		fout5.precision(5);
		fout5.setf(ios::right);
		fout5.width(10);
		fout5 << arrxM[i] << "\n";
	}
	fout5.close();

	ofstream fout6;
	fout6.open("file6.txt");
	for (int i = 0; i < 2*M-1; i++) {
		fout6 << fixed;
		fout6.precision(5);
		fout6.setf(ios::right);
		fout6.width(10);
		fout6 << arrx05M[i] << "\n";
	}
	fout6.close();

	ofstream fout7;
	fout7.open("file7.txt");
	for (int i = 0; i <  M ; i++) {
		fout7 << fixed;
		fout7.precision(5);
		fout7.setf(ios::right);
		fout7.width(10);
		fout7 << runge[i] << "\n";
	}
	fout7.close();


	delete[] arrxM;
	delete[] arrxMviz;
	delete[] arryMviz;
	delete[] arryM;
	delete[] arrx05M;
	delete[] arry05M;
	delete[] pribl;
	delete[] pribl05;
	delete[] glav;
	delete[] runge;

	std::system("python PythonApplication1.py");
	return 0;
	}
	