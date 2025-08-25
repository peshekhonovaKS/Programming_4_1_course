#include <fstream>
#include <iostream>
#include <time.h>
#include <iomanip>//для вывода красивого в файлики
using namespace std;
double func(double x) {
	return  - x + 2 * cos(x);
}
int main() {
	double a = 10.0;
	double b = 20.0;
	int N = 3;//степень каждого полинома лагранжа, он 
	int K = 6;//число интервалов
	int M = (N - 1) * K + 1;//число точек интерполяции=(N-2)*K +(K+1) число точек между отрезками + на концах
	double* arrxM = new double[M];//массив x-ов  разбиения M
	int S = 2000; //кол-во точек по которым будем строить Ln ( S это Mviz)
	if (S-1 % K != 0) {
		S = S - (S-1) % K;//если у нас нецелое число на подотрезочках то меняем значение S на такое чтобы SS было целым числом
	}
	int SS = (S - 1) / K;//кол-во точек попадающих в интервал
	double* arrxS = new double[S];//массив x-ов  разбиения S
	double* resz = new double[N];//массиив знаменателей
	double* Ln = new double[S]; //массив интерполяционного многочлена
	double* arryM = new double[M]; //массив значения функции
	double* G = new double[S];//у для построения по x-aм разбиения S
	double* arrxMsto = new double[(M-1)*100+1];//массив x-ов разбиения с шагом h/100(по сути мы разбиваем каждый из М-1 (узлов на [ab]
	                                           //М штук,отрезков M-1)отрезков на 100 отрезочков  поэтому точек будет (M-1)*100+1
											  //+1 так как добавили последнюю точку отрезка [ab]

	//зададим равномерную сетку всё как в прошлой программе
	double h=(b - a) / (M - 1); //равномерный шаг
	for (int i = 0; i < M; i++) {
		arrxM[i] = a + i * (b - a) / (M - 1);//(b - a) / (M - 1)=h-равномерный шаг
	}
	for (int i = 0; i < S; i++) {
		arrxS[i] = a + i * (b - a) / (S - 1);//сетка разбиения S
	}
	for (int i = 0; i < M; i++) {  //значения функции в иксах - узлах интерполяци
		arryM[i] = func(arrxM[i]);
		
	}
	for (int i = 0; i < S; i++) {//значения  функций в точках Mviz для рисунка
		G[i] = func(arrxS[i]);
		
	}

	for (int i = 0; i < N; i++) { //вычисляем массив знаменателей на интервальчике
		resz[i] = 1; //нам нужно будет домножать на него, поэому возьмём единицу
		for (int j = 0; j < N; j++) {
			if (j != i) {
				resz[i] = resz[i] * (arrxM[i] - arrxM[j]); // то есть домножим то что получилось на новую скобку
			}
		}
	}
	
	int i = 0;
	for (int k = 0; k < K; k++) { //идём по интервлам
			                                      /*i не зануляюздесь мы берём новый отрезок и нам нужно сохранить, на какой точке мы остановились(мы же не хотим перехожить каждый раз в первый отрезок,
		                                              (k-номер интервала начало отрезочка; (k+1)-начало следующего интервала, конец отрезка. Чтобы был номер ТОЧКИ домножаем на SS (на к-ом интервале у нас SS точек)*/
		for (; i<=(k+1)*SS; i++) {//идем по подинтервалам до номер конца инервала*кол-во точек в интервале т е на первом интервале от 0 до SS, потом от SS+1 до 2SS
			Ln[i] = 0;										
			for (int j = 0; j < N; j++) { //по сумме
				double proizv = 1.0;
				for (int m = 0; m < N; m++) { //по произведению 
					if (j != m)
						proizv *= (arrxS[i] - arrxM[k*(N-1)+m]); //точка внутри интервала:первая точка нужного интервала(k-ый интервал)*кол-во точек+m(номер точки внутри интервала)
				}
				Ln[i] += arryM[k*(N-1)+j] * proizv / resz[j];
				//cout << Ln[i] << proizv << endl;
			}
			//cout << Ln[i] << endl;
		}
	}
	double abs1 = 0, abs2 = 0, absinf = 0;//абсолютные погрешности в L1 L2 Lбеск
	double otn1 = 0, otn2 = 0, otninf = 0;//относительные пограшности=абсолютным/норму func

	for (int i = 0; i < (M-1)*100+1; i++) {
		arrxMsto[i] = a + i * h/100;//    cетка с шагом h/100
	}

	int p = 0;
	for (int k = 0; k < K; k++) {//по итервалам теперь вместо рабиения S у нас сетка h/100
		for (;  p <=(k+1)*((N - 1) * 100); p++) {//на подинтервале уже N узлов и (N-1)подотрезочков разделяем на 100 и домножаем на конец интервала
			double L= 0.0;										
			for (int j = 0; j < N; j++) { //по сумме
				double proizv = 1.0;
				for (int m = 0; m < N; m++) { //по произведению 
					if (j != m)
						proizv *= (arrxMsto[p] - arrxM[k * (N - 1) + m]); // точка внутри интервала представляется как: первая точка нужного интервала(k-ый интервал)+m(номер точки внутри интервала)
				}
				L += arryM[k * (N - 1) + j] * proizv / resz[j];//посчитали интерполяц многочлен в iой точке
				//cout<<"p= " << proizv << endl;
			}
			//cout << L << endl;
			abs1 += fabs(L - func(arrxMsto[p])); //сумма модулей разности
			abs2 += pow(fabs(L - func(arrxMsto[p])),2);//сумма квадратов
			absinf = max(absinf, fabs(L - func(arrxMsto[p])));//максимум модуля разности
			otn1 += fabs(func(arrxMsto[p]));//пока эти переменные обозначают норму в знаменателе
			otn2 += pow(fabs(func(arrxMsto[p])), 2);
			otninf = max(otninf, fabs(func(arrxMsto[p])));//ошибка максимум из относительно1
		}

	}
	abs2 = sqrt(abs2);
	otn2= sqrt(otn2);//пока для знаменателя
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

	//РАБОТА С ФАЙЛАМИ
	ofstream fout0;
	fout0.open("file0.txt");
	fout0 << a << "\t" << b;
	fout0.close();

	ofstream fout; //иксы рабиения N
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
	massy.open("file2.txt"); //функции у
	for (int i = 0; i < M; i++) {
		massy << fixed;
		massy.precision(5);
		massy.setf(ios::right);
		massy.width(10);
		massy << arryM[i] << endl;
	}
	massy.close();

	ofstream fout3;
	fout3.open("file3.txt"); //иксы разбиения M
	for (int i = 0; i < S; i++) {
		fout3 << fixed;
		fout3.precision(5);
		fout3.setf(ios::right);
		fout3.width(10);
		fout3 << arrxS[i] << "\n";
	}
	fout3.close();

	ofstream foutLn; //интерполяционный многочлен
	foutLn.open("file4.txt");
	for (int i = 0; i < S; i++) {
		foutLn << fixed; //Одна цифра после запятой две строчки
		foutLn.precision(5);
		foutLn.setf(ios::right);//выравнивание по правой стороне две строчки
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