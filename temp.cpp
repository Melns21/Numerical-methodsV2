#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

double exact = 4 * log(2)*log(2) -4*log(4) + 2 ;

double absolute(double a) {
	double abs;
	if (a > exact)
		abs = a - exact;
	else
		abs = exact - a;
	return abs;
}

double relative(double a) {
	double abs = absolute(a);
	double rel = 0;
	if (a > exact)
		rel = abs / exact;
	else
		rel = abs / a;
	return rel * 100.0;
}

double func(const double x) {return x * sqrt(x+1);}
void sympsons(double a, double b, const int n) {
	double x;
	double xnext = 0;
	exact = 0.64379;
	for (int j{ 2 }; j <= n*2; j *= 2){
		vector<double> sums{ 0,0,0 };
		double h{ (b - a) / (2 * j) };

		for (int i{ 1 }; i <= 2 * j - 1; i += 2) {
			sums.at(2) += func(a + h * i); 
			sums.at(1) += func(a + h * (i + 1));
		}

		sums.at(0) = func(a) + 4 * sums.at(2)+ 2 * sums.at(1)- func(b); 
		x = xnext;

		xnext = (h / 3) * sums.at(0);
	}
	cout << "\nМетод Симпона  при n=" << n << " - " << xnext;
	cout << "\nАбсолютная погрешность -  " << absolute(xnext);
	cout << "\nОтносительная погрешность - " << relative(xnext);
}

void rectangle(double a, double b, const int n) {
	const double h = (b - a) / n;
	double s = (func(a) + func(b)) / 2;

	for (int i{ 1 }; i <= n - 1; ++i) {
		s += func(a);
		a+=h;
	}

	double res = h * s;
	cout << "\nМетод прямоугольников  при n=" << n << " - " << res;
	cout << "\nАбсолютная погрешность - " << absolute(res);
	cout << "\nОтносительная погрешность - " << relative(res);
}

double integr(const double &a, const double &b, const int &n, double &y) { return ((b - a) / (2 * n) * y); }
void trapezoid(double a, double b, const int n) {

	const double h{ (b - a) / n };
	double y{ func(a) + func(b) };
	double sum = 0;
	double x = a + h;
	for (int i = 1; i < n; i++) {
		sum += func(x);
		x += h;
	}
	y += sum * 2;
	
	double res = integr(a, b, n, y);
	cout << "\nМетод трапеций при n=" << n << " - " << res;
	cout << "\nАбсолютная погрешность - " << absolute(res);
	cout << "\nОтносительная погрешность - " << relative(res);
}


int main()
{
	setlocale(LC_ALL, "rus");

	sympsons(0,1,4);
	sympsons(0,1,10);
	cout << "\n---------------------------------------";
	rectangle(0,1,4);
	rectangle(0,1,10);
	cout << "\n---------------------------------------";
	trapezoid(0,1,4);
	trapezoid(0,1,10);
	cout << "\n---------------------------------------";

	return 0;

}