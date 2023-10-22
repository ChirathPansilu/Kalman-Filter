#include <iostream>
#include <math.h>
#include <corecrt_math_defines.h>

using namespace std;

double f(double mu, double sigma2, double x)
{
    double prob = (1 / (sqrt(sigma2 * 2 * M_PI))) * exp(-pow(x - mu, 2.0) / (2 * sigma2));
    return prob;
}

int main()
{
    cout << "PDF value: " << f(10.0, 4.0, 8.0) << endl;
    return 0;
}