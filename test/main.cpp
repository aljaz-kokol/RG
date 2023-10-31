
#include <iostream>
#include <random>
#include <vector>
#include <chrono>
#include <cmath>

// Constants
const double EPSILON = 0.01;
const double X_L = -6.0;
const double X_U = 6.0;
const double F_INITIAL = 0.5;
const double CR_INITIAL = 0.9;

// Function to compute the Lennard Jones Potential energy
double lennardJonesPotential(const std::vector<double>& positions) {
    double energy = 0.0;
    int numAtoms = positions.size() / 3;

    for (int i = 0; i < numAtoms; ++i) {
        for (int j = i + 1; j < numAtoms; ++j) {
            double dx = positions[i * 3] - positions[j * 3];
            double dy = positions[i * 3 + 1] - positions[j * 3 + 1];
            double dz = positions[i * 3 + 2] - positions[j * 3 + 2];
            double r = sqrt(dx * dx + dy * dy + dz * dz);

            double term = pow(1.0 / r, 12) - 2.0 * pow(1.0 / r, 6);
            energy += term;
        }
    }
    return 4.0 * energy;
}

// Mutation operation
void mutation(double F, const std::vector<std::vector<double>>& population, int currentIdx, std::vector<double>& trial) {
    int numPop = population.size();
    int r1, r2, r3;

    do {
        r1 = rand() % numPop;
    } while (r1 == currentIdx);
    do {
        r2 = rand() % numPop;
    } while (r2 == currentIdx || r2 == r1);
    do {
        r3 = rand() % numPop;
    } while (r3 == currentIdx || r3 == r1 || r3 == r2);

    int dimension = population[currentIdx].size();
    for (int j = 0; j < dimension; ++j) {
        trial[j] = population[r1][j] + F * (population[r2][j] - population[r3][j]);
    }
}

// Crossover operation
void crossover(double CR, const std::vector<std::vector<double>>& population, int currentIdx, std::vector<double>& trial) {
    int dimension = population[currentIdx].size();
    int j_rand = rand() % dimension;

    for (int j = 0; j < dimension; ++j) {
        if (j == j_rand || (rand() / static_cast<double>(RAND_MAX) < CR)) {
            trial[j] = population[currentIdx][j];
        }
    }
}

int main(int argc, char* argv[]) {
//    if (argc != 12) {
//        std::cerr << "Usage: " << argv[0] << " N -seed <seed> -target <target> [-nfesLmt | -runtimeLmt] <Limit> -Np"
//                  << std::endl;
//        return 1;
//    }
//
//    int N = std::atoi(argv[1]);
//    int seed, nfesLmt, runtimeLmt, Np;
//    double target;
//
//    for (int i = 2; i < argc; i += 2) {
//        if (std::string(argv[i]) == "-seed") {
//            seed = std::atoi(argv[i + 1]);
//            std::cout << "seed = " << seed << std::endl;
//        } else if (std::string(argv[i]) == "-target") {
//            target = std::atof(argv[i + 1]);
//        } else if (std::string(argv[i]) == "-nfesLmt") {
//            nfesLmt = std::atoi(argv[i + 1]);
//        } else if (std::string(argv[i]) == "-runtimeLmt") {
//            runtimeLmt = std::atoi(argv[i + 1]);
//        } else if (std::string(argv[i]) == "-Np") {
//            Np = std::atoi(argv[i + 1]);
//        }
//    }
    int N= 10;
    int seed = 50;
    int Np= 100;
    int nfesLmt=10000000;
    int runtimeLmt = 1000000;
    int target=-28.422532;

    std::default_random_engine generator(seed);
    std::uniform_real_distribution<double> distribution(0.0, 1.0);

    int dimension = 3 * N;
    std::vector<std::vector<double>> population(Np, std::vector<double>(dimension));
    std::vector<double> fitness(Np, 0.0);

    // Initialize population
    for (int i = 0; i < Np; ++i) {
        for (int j = 0; j < dimension; ++j) {
            population[i][j] = X_L + distribution(generator) * (X_U - X_L);
        }
        fitness[i] = lennardJonesPotential(population[i]);
    }

    // Main Loop
    int nfes = 0;
    double F = F_INITIAL;
    double CR = CR_INITIAL;
    std::cout << "nfesLmt " << nfesLmt << std::endl;

    // Start Time
    auto start_time = std::chrono::high_resolution_clock::now();
    while (nfes < nfesLmt) {
        for (int i = 0; i < Np; ++i) {
            std::vector<double> trial(dimension);
            mutation(F, population, i, trial);
            crossover(CR, population, i, trial);

            // Repair Operation
            for (int j = 0; j < dimension; ++j) {
                if (trial[j] < X_L) trial[j] = X_L;
                if (trial[j] > X_U) trial[j] = X_U;
            }

            double trialFitness = lennardJonesPotential(trial);
            if (trialFitness < fitness[i] || trialFitness < target + EPSILON) {
                for (int j = 0; j < dimension; ++j) {
                    population[i][j] = trial[j];
                }
                fitness[i] = trialFitness;
            }
            ++nfes;
            if (nfes >= nfesLmt) break;
        }
        for (int i = 0; i < Np; ++i) {
            if (fabs(fitness[i] - target) < EPSILON) {
                std::cout << "START" << std::endl;
                std::cout << "FITNESS IS " << fitness[i] << " END " << std::endl;
                std::cout << "N: " << N << " seed " << seed << " nfes " << nfes << " solution ";

                for (int j = 0; j < dimension; ++j) {
                    std::cout << population[i][j] << " ";
                }
                auto end_time = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> elapsed_time = end_time - start_time;

                std::cout << "Elapsed time " << elapsed_time.count() << " seconds" << std::endl;
                return 0;
            }
        }
    }

    return 0;
}
