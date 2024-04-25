#include <TFile.h>
#include <TH1.h>
#include <map>
#include <vector>
#include <algorithm>
#include <iostream>

void sortHistograms() {
    // Open the ROOT file
    TFile *file = new TFile("output_stag.root", "READ");
    if (!file || file->IsZombie()) {
        std::cerr << "Error opening file!" << std::endl;
        return;
    }

    // List of histogram names, adjust as necessary
    const char* histNames[] = {
        "h_ud", "h_x_ug", "h_x_dg", "h_x_uc", "h_x_ds", "h_x_db",
        "h_x_ud", "h_x_us", "h_x_dc", "h_x_ub",
        "h_x_antiud", "h_x_antiuantid", "h_x_antius", "h_x_antiuantis", "h_x_antids", "h_x_antidantis",
        "h_x_antiuc", "h_x_antiuantic", "h_x_antidc", "h_x_antidantic",
        "h_x_antiub", "h_x_antiuantib", "h_x_antidb", "h_x_antidantib", "h_x_antiug", "h_x_antidg"
    };
    int numHist = sizeof(histNames) / sizeof(histNames[0]);

    // Map to store histograms and their integrals
    std::vector<std::pair<double, TH1*>> histList;

    // Loop over histogram names and retrieve them from the file
    for (int i = 0; i < numHist; i++) {
        TH1* hist = dynamic_cast<TH1*>(file->Get(histNames[i]));
        if (hist) {
            // Store the histogram and its integral (number of entries) in the vector
            histList.push_back(std::make_pair(hist->GetEntries(), hist));
        } else {
            std::cerr << "Histogram " << histNames[i] << " not found!" << std::endl;
        }
    }

    // Sort the vector by the integral, from largest to smallest
    std::sort(histList.begin(), histList.end(), [](const std::pair<double, TH1*>& a, const std::pair<double, TH1*>& b) {
        return a.first > b.first; // Descending order
    });

    // Print the sorted histograms
    std::cout << "Histograms sorted by number of entries:" << std::endl;
    for (const auto& item : histList) {
        std::cout << item.second->GetName() << " has " << item.first << " entries." << std::endl;
    }

    // Close the file
    file->Close();
    delete file;
}
