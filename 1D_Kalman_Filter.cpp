#include <iostream>
#include <tuple>
#include <math.h>
// #include <corecrt_math_defines.h>

using namespace std;

double f(double mu, double sigma2, double x)
{
    double prob = (1 / (sqrt(sigma2 * 2 * M_PI))) * exp(-pow(x - mu, 2.0) / (2 * sigma2));
    return prob;
}

tuple<double, double> measurement_update(double mean1, double var1, double mean2, double var2) {
    double new_mean = (mean1 * var2 + mean2 * var1) / (var1 + var2);
    double new_var = 1 / (1 / var1 + 1 / var2);

    return make_tuple(new_mean, new_var);
}

int main()
{
    cout << "PDF value: " << f(10.0, 4.0, 8.0) << endl;

    double new_mean{}, new_var{};

    tie(new_mean, new_var) = measurement_update(10, 8, 13, 2);
    printf("[%f, %f]\n", new_mean, new_var);
    
    return 0;
}