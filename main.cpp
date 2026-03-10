#include <iostream>
#include <fstream>
#include <string>

const int MAX_MOKINIAI = 100;

struct Mokinys {
    std::string VardasPavarde;
    int Amzius;
    double Pazymys;
};

// Reads student records from a semicolon-delimited file.
// Each line has the format: Vardas Pavardė;Amžius;Pažymys
// Example: Jonas Jonaitis;16;9.5
int SkaitytiMokinius(const std::string& failoPavadinimas, Mokinys MokiniuInfo[], int maxDydis) {
    std::ifstream input(failoPavadinimas);
    if (!input.is_open()) {
        std::cerr << "Klaida: nepavyko atidaryti failo \"" << failoPavadinimas << "\".\n";
        return 0;
    }

    int i = 0;
    while (i < maxDydis) {
        // Read name and surname up to the ';' delimiter
        if (!getline(input, MokiniuInfo[i].VardasPavarde, ';')) {
            break;
        }

        std::string amziusStr, pazymysStr;
        if (!getline(input, amziusStr, ';')) break;
        if (!getline(input, pazymysStr)) break;

        MokiniuInfo[i].Amzius  = std::stoi(amziusStr);
        MokiniuInfo[i].Pazymys = std::stod(pazymysStr);
        ++i;
    }

    input.close();
    return i;
}

int main() {
    Mokinys MokiniuInfo[MAX_MOKINIAI];
    int kiekis = SkaitytiMokinius("mokiniai.txt", MokiniuInfo, MAX_MOKINIAI);

    std::cout << "Nuskaityti " << kiekis << " mokiniai:\n";
    for (int i = 0; i < kiekis; ++i) {
        std::cout << (i + 1) << ". " << MokiniuInfo[i].VardasPavarde
                  << " | Amžius: " << MokiniuInfo[i].Amzius
                  << " | Pažymys: " << MokiniuInfo[i].Pazymys << "\n";
    }

    return 0;
}
