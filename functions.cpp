#include <iostream>
#include <cmath>
#include <omp.h>
#include <vector>
#include <chrono>
#include <functional>
#include <string>

using namespace std;
namespace project{


struct inputData{
    double a;
    double b;
    int n;
    string title;
    inputData(double _a, double _b, int _n, string &str){
        a = _a;
        b = _b;
        n = _n;
        title = str;
    }
}

double integrate(double a, double b, int n, function<double(double)> func) {
    double h = (b - a) / n;
    double sum = 0.0;

    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < n; ++i) {
        double x = a + (i + 0.5) * h;
        sum += func(x);
    }

    return sum * h;
}

void measurePerformance(inputData input, function<double(double)> functions) {
    double a = input.a;
    double b = input.b;
    int n = input.n;

    vector<int> num_threads = {1, 2, 4, 8};

    for (const auto& func : functions) {
        cout << "Testing function: " << input.title << endl; 

        for (int threads : num_threads) {
            omp_set_num_threads(threads);
            auto start = chrono::high_resolution_clock::now();
            double result = integrate(a, b, n, func.second);
            auto end = chrono::high_resolution_clock::now();
            chrono::duration<double> duration = end - start;

            cout << "Time with " << threads << " threads: " << duration.count() << " seconds" << endl;
        }

        cout << "Integral result: " << result << endl;

        cout << "Speedup:" << endl;
        for (size_t i = 1; i < num_threads.size(); ++i) {
            double speedup = times[0] / times[i];
            cout << "Speedup with " << num_threads[i] << " threads: " << speedup << endl;
        }
        cout << endl;
    }
}
}

// int main() {


//     // vector<pair<string, function<double(double)>>> functions = {
//     //     {"x^2", [](double x) { return x * x; }},
//     //     {"sin(x)", [](double x) { return sin(x); }},
//     //     {"exp(x)", [](double x) { return exp(x); }},
//     //     {"log(x+1)", [](double x) { return log(x + 1); }},
//     //     {"sqrt(x+1)", [](double x) { return sqrt(x + 1); }},
//     //     {"cos(x)", [](double x) { return cos(x); }},
//     //     {"tan(x)", [](double x) { return tan(x); }},
//     //     {"1/(1+x^2)", [](double x) { return 1 / (1 + x * x); }},
//     //     {"x^3", [](double x) { return x * x * x; }},
//     //     {"x^4", [](double x) { return x * x * x * x; }}
//     // };
//     inputData input;
//     input.a << 
//     function func <<
//     measurePerformance(input, func);
//     return 0;
// }