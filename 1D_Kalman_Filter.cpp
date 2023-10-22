#include <iostream>
#include <vector>
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

tuple<double, double> state_prediction(double mean1, double var1, double mean2, double var2)
{
    double new_mean = mean1 + mean2;
    double new_var = var1 + var2;
    return make_tuple(new_mean, new_var);
}

int main()
{
    cout << "PDF value: " << f(10.0, 4.0, 8.0) << endl;

    double new_mean{}, new_var{};

    tie(new_mean, new_var) = measurement_update(10, 8, 13, 2);
    printf("[%f, %f]\n", new_mean, new_var);

    tie(new_mean, new_var) = state_prediction(10, 4, 12, 4);
    printf("[%f, %f]\n", new_mean, new_var);

    vector<double> measurements{ 5, 6, 7, 9, 10 };
    double measurement_sig = 4;

    vector<double> motion{ 1,1,2,1,1 };
    double motion_sig = 2;

    //Initial state
    double mu = 0;
    double sig = 1000;

    double estimated_mu = mu;
    double estimated_var = pow(sig, 2.0);

    for (size_t i = 0; i < measurements.size(); i++) {
        tie(estimated_mu, estimated_var) = measurement_update(estimated_mu, estimated_var, measurements[i], pow(measurement_sig, 2));
        printf("update:  [%f, %f]\n", estimated_mu, estimated_var);
        
        tie(estimated_mu, estimated_var) = state_prediction(estimated_mu, estimated_var, motion[i], pow(motion_sig, 2));
        printf("predict: [%f, %f]\n", estimated_mu, estimated_var);
    }
    
    return 0;
}