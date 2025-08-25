#include <fstream> 
#include <iostream>
#include <time.h>
#include <iomanip>//для вывода красивого в файлики
using namespace std;
double f(double x) {//функция
	return  pow(x, 3);
}
double F(double x) {//первообразная
	return  pow(x, 4)/4;
}
double FF(double a, double b) {//первообразная
	return  F(b)-F(a);
}
double x(double a, double b, double t) // a,b  в -1,1
{
	return (a + b) / 2 + (b - a) * t / 2;
}

int main() {
	double a = 0.0;
	double b = 1.0;
	int K = 30;
	double h = (b - a) / K;
	double I = FF(a, b);
	double I1 = 0.0, I2 = 0.0, I3 = 0.0, I4 = 0.0, I5 = 0.0;
	for (int i = 0; i < K; i++) {
		I1 += h * f(x(a + i * h, a + (i + 1) * h, 0.0));
		I2 += h * (f(x(a + i * h, a + (i + 1) * h, -1.0))+ f(x(a + i * h, a + (i + 1) * h, 1.0)) )/ 2.0;
		I3 += h * (f(x(a + i * h, a + (i + 1) * h, -1.0)) + 4.0*f(x(a + i * h, a + (i + 1) * h, 0.0))
			+f(x(a + i * h, a + (i + 1) * h, 1.0)))/6.0;
		I4 += h * (14*f(x(a + i * h, a + (i + 1) * h, -1.0)) + 64.0 * f(x(a + i * h, a + (i + 1) * h, -0.5))
			+ 24.0*f(x(a + i * h, a + (i + 1) * h, 0.0))+ 64.0 * f(x(a + i * h, a + (i + 1) * h, 0.5))+
			14.0 * f(x(a + i * h, a + (i + 1) * h, 1.0))) /(45.0* 4.0);
		I5 += h * (5*f(x(a + i * h, a + (i + 1) * h, -sqrt(3.0/5.0))) + 8.0 * f(x(a + i * h, a + (i + 1) * h, 0.0)) 
			+ 5.0*f(x(a + i * h, a + (i + 1) * h, sqrt(3.0 / 5.0)))) / 18.0;
	}
	double h2 = (b - a) /(2*K);
	double I12 = 0.0, I22 = 0.0, I32 = 0.0, I42 = 0.0, I52 = 0.0;
	for (int i = 0; i <2*K; i++) {
		I12 += h2 * f(x(a + i * h2, a + (i + 1) * h2, 0.0));
		I22 += h2 * (f(x(a + i * h2, a + (i + 1) * h2, -1.0)) + f(x(a + i * h2, a + (i + 1) * h2, 1.0))) / 2;
		I32 += h2 * (f(x(a + i * h2, a + (i + 1) * h2, -1.0)) + 4.0 * f(x(a + i * h2, a + (i + 1) * h2, 0.0))
			+ f(x(a + i * h2, a + (i + 1) * h2, 1.0)))/6.0;
		I42 += h2 * (14 * f(x(a + i * h2, a + (i + 1) * h2, -1.0)) + 64.0 * f(x(a + i * h2, a + (i + 1) * h2, -0.5))
			+ 24.0* f(x(a + i * h2, a + (i + 1) * h2, 0.0)) + 64.0 * f(x(a + i * h2, a + (i + 1) * h2, 0.5)) +
			14.0 * f(x(a + i * h2, a + (i + 1) * h2, 1.0))) / (45.0*4.0);
		I52 += h2 * (5.0 * f(x(a + i * h2, a + (i + 1) * h2, -sqrt(3.0 / 5.0))) + 8.0 * f(x(a + i * h2, a + (i + 1) * h2, 0.0)) 
			+ 5.0 * f(x(a + i * h2, a + (i + 1) * h2, sqrt(3.0 / 5.0)))) / 18.0;
	}
	//cout << I1 << "  " << I2 << "  " << I3 << "  " << I4 << "  " << I5 << "  " << endl;
	//cout << I12 << "  " << I22 << "  " << I32 << "  " << I42 << "  " << I52 << "  " <<I<<endl;
	double otn1 = 0, otn2 = 0, otn3 = 0, otn4 = 0, otn5 = 0;
	double otn12 = 0, otn22 = 0, otn32 = 0, otn42 = 0, otn52 = 0;
	otn1 = fabs(I - I1) / fabs(I);
	otn2 = fabs(I - I2) / fabs(I);
	otn3 = fabs(I - I3) / fabs(I);
	otn4 = fabs(I - I4) / fabs(I);
	otn5= fabs(I - I5) / fabs(I);
	otn12 = fabs(I - I12) / fabs(I);
	otn22= fabs(I - I22) / fabs(I);
	otn32= fabs(I - I32) / fabs(I);
	otn42= fabs(I - I42) / fabs(I);
	otn52= fabs(I - I52) / fabs(I);
	//cout << otn1 << "  " << otn2 << "  " << otn3 << "  " << otn4 << "  " << otn5 << "  " << endl;
	//cout << otn12 << "  " << otn22 << "  " << otn32 << "  " << otn42 << "  " << otn52 << "  " <<endl;

	ofstream fout8;
	fout8.open("file8.txt");
	fout8.setf(ios::scientific);
	fout8 << setw(30) << left << " " << setw(30) << left << "h" << setw(30) << left << "h/2"<<endl;
	fout8 << setw(30) << left << "I1" << setw(30) << left << otn1 << setw(30) << left << otn12<<endl;
	fout8 << setw(30) << left << "I2" << setw(30) << left << otn2 << setw(30) << left << otn22 << endl;
	fout8 << setw(30) << left << "I3" << setw(30) << left << otn3 << setw(30) << left << otn32 << endl;
	fout8 << setw(30) << left << "I4" << setw(30) << left << otn4 << setw(30) << left << otn42 << endl;
	fout8 << setw(30) << left << "I5" << setw(30) << left << otn5 << setw(30) << left << otn52 << endl;

	fout8.close();


	return 0;
}