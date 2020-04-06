#include <stdio.h>
#include <stdlib.h>
#include <math.h> 

double PI = atan(1.0) * 4;
double g = 9.81, m = 1, l = 1.8, a = 1.35, k = 9;// constants needed for the project

double fun1(double t, double y1, double y2)
{
	return y2;
}

double fun2(double t, double y1, double y2)
{
	return -1.0 * ((sin(y1) / l) + (2.0 * k * pow(a, 2.0) * sin(y1) * cos(y1)) / (m * pow(l, 2.0))); //Basic equation
}


void RK4(double(*funa)(double, double, double), double(*funb)(double, double, double), double* t, double* y1, double* y2, double h)
{
	double k1a, k1b, k2a, k2b, k3a, k3b, k4a, k4b;

	k1a = h * funa(*t, *y1, *y2);
	k1b = h * funb(*t, *y1, *y2);

	k2a = h * funa(*t + h / 2.0, *y1 + (1.0 / 2.0) * k1a, *y2 + (1.0 / 2.0) * k1b);
	k2b = h * funb(*t + h / 2.0, *y1 + (1.0 / 2.0) * k1a, *y2 + (1.0 / 2.0) * k1b);

	k3a = h * funa(*t + h / 2.0, *y1 + (1.0 / 2.0) * k2a, *y2 + (1.0 / 2.0) * k2b);
	k3b = h * funb(*t + h / 2.0, *y1 + (1.0 / 2.0) * k2a, *y2 + (1.0 / 2.0) * k2b);

	k4a = h * funa(*t + h, *y1 + k3a, *y2 + k3b);
	k4b = h * funb(*t + h, *y1 + k3a, *y2 + k3b);


	*y1 += (1.0 / 6.0) * (k1a + 2 * k2a + 2 * k3a + k4a);
	*y2 += (1.0 / 6.0) * (k1b + 2 * k2b + 2 * k3b + k4b);
}

int main()
{
	double y1 = (PI / 6.0) * 1, y2 = 0; //Initial conditions
	double T = 0.796;
	double h = 0.0001;

	FILE* r;
	r = fopen("results.txt", "wt"); //If there is no such file, it should be automatically cretated. Answers are written there
	int i = 0;
	for (double t = 0; t < T; t += h)
	{
		i = i + 1;
		printf("%d.\n", i);
		RK4(fun1, fun2, &t, &y1, &y2, h);
		fprintf(r, "%lf\n", y1 * 360 / (PI * 2));

	}
	printf("final aswers:\n");
	printf("%lfrad\n", y1); // Radians
	printf("%lfdec", y1 * 360 / (PI * 2)); //Degrees
	fclose(r);
	getchar();
	return 0;
}
