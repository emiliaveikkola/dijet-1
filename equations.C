#include <TMatrixD.h>
#include <TVectorD.h>
#include <TDecompSVD.h>
#include <iostream>
#include <cmath>

int main() {
    // Constants for your model
    double epsilon_ctag_cs = 0.70353953, epsilon_ctag_ud = 0.15467099;
    double epsilon_udtag_cs = 0.05377518, epsilon_udtag_ud = 0.49913117;
    double f_cs = 0.4, f_ud = 0.6;
    double mW = 93.39; // Known mW, used to normalize mw measurements

    // Observed values (set these based on your data)
    double observed_mw_cs_tagged = 90.86;
    double observed_mw_ud_tagged = 93.95;
    double observed_mw_x = 93.54;

    // Setting up matrix A for coefficients
    TMatrixD A(3, 2);
    A(0, 0) = epsilon_ctag_cs * f_cs;
    A(0, 1) = epsilon_ctag_ud * f_ud;
    A(1, 0) = epsilon_udtag_cs * f_cs;
    A(1, 1) = epsilon_udtag_ud * f_ud;
    A(2, 0) = (1 - epsilon_ctag_cs - epsilon_udtag_cs) * f_cs;
    A(2, 1) = (1 - epsilon_ctag_ud - epsilon_udtag_ud) * f_ud;

    // Adjusting y_meas to incorporate division by mW for normalization
    TVectorD y_meas(3);
    y_meas(0) = observed_mw_cs_tagged / mW;
    y_meas(1) = observed_mw_ud_tagged / mW;
    y_meas(2) = observed_mw_x / mW;

    // Solving the system using SVD decomposition to find sqrt(Rcs) and sqrt(Rud)
    TDecompSVD svd(A);
    Bool_t ok;
    TVectorD x_gen = svd.Solve(y_meas, ok); // x_gen contains the sqrt values of Rcs and Rud

    if (ok) {
        // Compute the actual Rcs and Rud by squaring the solved sqrt values
        double Rcs = std::pow(x_gen(0), 2);
        double Rud = std::pow(x_gen(1), 2);
        std::cout << "Solutions found: Rcs = " << Rcs << ", Rud = " << Rud << std::endl;
    } else {
        std::cout << "No solution or unstable solution found." << std::endl;
    }

    return 0;
}