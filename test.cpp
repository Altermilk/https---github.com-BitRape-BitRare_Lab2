#include <gtest/gtest.h>
#include <project_code.h>  // The header file for your project
#include <functional>
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;
using namespace project;

// Helper function to check if the function executes without throwing exceptions
std::pair<bool, string> isOk(function<void()> f) {
    try {
        f();
    } catch (const std::exception& e) {
        return {false, e.what()};
    }
    return {true, ""};
}

// Define a few mathematical functions for the tests
vector<pair<string, function<double(double)>>> functions = {
    {"x^2", [](double x) { return x * x; }},
    {"sin(x)", [](double x) { return sin(x); }},
    {"exp(x)", [](double x) { return exp(x); }},
    {"log(x+1)", [](double x) { return log(x + 1); }},
    {"sqrt(x+1)", [](double x) { return sqrt(x + 1); }},
    {"cos(x)", [](double x) { return cos(x); }},
    {"tan(x)", [](double x) { return tan(x); }},
    {"1/(1+x^2)", [](double x) { return 1 / (1 + x * x); }},
    {"x^3", [](double x) { return x * x * x; }},
    {"x^4", [](double x) { return x * x * x * x; }}
};

// Define input data
inputData input(0, 1, 10000, "x^2");

// Test case for measurePerformance
TEST(MeasurePerformanceTest, FunctionExecutionTest) {
    // Test that the measurePerformance function works without exceptions
    auto result = isOk([&]() {
        measurePerformance(input, functions);
    });
    EXPECT_TRUE(result.first) << "Error: " << result.second;
}

// Test case for integration with x^2 function
TEST(MeasurePerformanceTest, IntegrationTestXSquare) {
    double result = integrate(input.a, input.b, input.n, functions[0].second);  // Use "x^2"
    EXPECT_NEAR(result, 1.0 / 3.0, 1e-6) << "Integration of x^2 failed";
}

// Test case for integration with sin(x) function
TEST(MeasurePerformanceTest, IntegrationTestSin) {
    double result = integrate(input.a, input.b, input.n, functions[1].second);  // Use "sin(x)"
    EXPECT_NEAR(result, -cos(1) + cos(0), 1e-6) << "Integration of sin(x) failed";
}

// Test case for integration with exp(x) function
TEST(MeasurePerformanceTest, IntegrationTestExp) {
    double result = integrate(input.a, input.b, input.n, functions[2].second);  // Use "exp(x)"
    EXPECT_NEAR(result, exp(1) - 1, 1e-6) << "Integration of exp(x) failed";
}

// Test case for integration with log(x+1) function
TEST(MeasurePerformanceTest, IntegrationTestLog) {
    double result = integrate(input.a, input.b, input.n, functions[3].second);  // Use "log(x+1)"
    EXPECT_NEAR(result, log(2), 1e-6) << "Integration of log(x+1) failed";
}

// Test case for integration with sqrt(x+1) function
TEST(MeasurePerformanceTest, IntegrationTestSqrt) {
    double result = integrate(input.a, input.b, input.n, functions[4].second);  // Use "sqrt(x+1)"
    EXPECT_NEAR(result, 2.0 / 3.0, 1e-6) << "Integration of sqrt(x+1) failed";
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
