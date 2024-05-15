#include <TMatrixD.h>
#include <TVectorD.h>
#include <TDecompSVD.h>
#include <iostream>
#include <cmath>

int equations() {
    // Constants and updated fractions and weights
    double epsilon_ctag_cs = 0.70353953, epsilon_ctag_ud = 0.15467099; // ctagged sample 
    double epsilon_udtag_cs = 0.05377518, epsilon_udtag_ud = 0.49913117; // udtagged sample
    double f_cs = 0.30, f_ud = 0.38, f_x = 0.32;  // sum(f_i) = 1 // cd + us + cb + ub lisätty x:ään
    //f_cs = 0.299479, f_ud = 0.38070246, f_x = 0.27349525
    double w_ctag = 3.71098, w_udtag = 4.85142;  // sum(w_j * epsilon_j_i * f_i) = 1
    double mW = 93.39; // Known mW

    // Background vector b
    TVectorD b(3);
    b(0) = 0;  // Background for cs-tagged
    b(1) = 0;  // Background for ud-tagged
    b(2) = 0;  // Background for x, adjust as necessary

    // Observed values
    double observed_mw_cs_tagged = 90.86;
    double observed_mw_ud_tagged = 93.95;
    double observed_mw_x = 93.54;

    // matrix A
    TMatrixD A(3, 2);
    A(0, 0) = w_ctag * epsilon_ctag_cs * f_cs;
    A(0, 1) = w_udtag * epsilon_ctag_ud * f_ud;
    A(1, 0) = w_ctag * epsilon_udtag_cs * f_cs;
    A(1, 1) = w_udtag * epsilon_udtag_ud * f_ud;
    A(2, 0) = w_ctag * (1 - epsilon_ctag_cs - epsilon_udtag_cs) * f_cs;
    A(2, 1) = w_udtag * (1 - epsilon_ctag_ud - epsilon_udtag_ud) * f_ud;

    // y_meas
    TVectorD y_meas(3);
    y_meas(0) = (observed_mw_cs_tagged / mW) + b(0);
    y_meas(1) = (observed_mw_ud_tagged / mW) + b(1);
    y_meas(2) = (observed_mw_x / mW) + b(2);

    // Solve the system using SVD decomposition to find sqrt(Rcs) and sqrt(Rud)
    TDecompSVD svd(A);
    Bool_t ok;
    TVectorD x_gen = svd.Solve(y_meas, ok);

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