#include <TMatrixD.h>
#include <TVectorD.h>
#include <TDecompSVD.h>
#include <iostream>
#include <cmath>

int equations() {
    // Constants and updated fractions and weights
    double epsilon_MC_ctag_cs = 0.70353953, epsilon_MC_ctag_ud = 0.15467099; // ctagged sample 
    double epsilon_MC_udtag_cs = 0.05377518, epsilon_MC_udtag_ud = 0.49913117; // udtagged sample
    double f_cs = 0.30, f_ud = 0.38, f_x = 0.32;  // sum(f_i) = 1 // cd + us + cb + ub lisätty x:ään
    double w_ctag = 3.71098, w_udtag = 4.85142;  // sum(w_j * epsilon_j_i * f_i) = 1

    // Define the N values
    double N_MC_cs = 460 080;
    double N_MC_ud = 584 861;
    double N_MC_x = 491 327;
    double N_MC_total = 1 536 268;

    double N_MC_cstag = 135 591;
    double N_MC_udtag = 249 354;
    double N_MC_xtag = 1 152 202;
    double N_MC_totaltag = 1 537 147;

    double N_DATA_cstag = 4 350;
    double N_DATA_udtag = 7 471;
    double N_DATA_xtag = 44 094;
    double N_DATA_alltag = 55 915;

    // matrix A
    TMatrixD A(3, 2);
    A(0, 0) = w_ctag * epsilon_MC_ctag_cs * f_cs;
    A(0, 1) = w_udtag * epsilon_MC_ctag_ud * f_ud;
    A(1, 0) = w_ctag * epsilon_MC_udtag_cs * f_cs;
    A(1, 1) = w_udtag * epsilon_MC_udtag_ud * f_ud;
    A(2, 0) = w_ctag * (1 - epsilon_MC_ctag_cs - epsilon_MC_udtag_cs) * f_cs;
    A(2, 1) = w_udtag * (1 - epsilon_MC_ctag_ud - epsilon_MC_udtag_ud) * f_ud;

    // y_meas
    TVectorD y_meas(3);
    y_meas(0) = N_MC_cstag/N_MC_totaltag;
    y_meas(1) = N_MC_udtag/N_MC_totaltag;
    y_meas(2) = N_MC_xtag/N_MC_totaltag;

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