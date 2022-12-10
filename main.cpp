#include <iostream>
#include <vector>


#include "PhaseDiagram.h"
#include "Flow.h"

bool split_condition(std::vector<double> x_1, std::vector<double> x_2) {
    return true;
}

void sleep() {
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

int main() {
    auto comp = std::make_shared<PhaseDiagram<phy::Flow>>(0.0, 0.0, 1.1, 0.7);
    comp->compute();
//    double mu = 0.4;
//    double T = 0.4;
//    double initial_box_size = 0.8;
//    double Lambda = 1e5;
//    double t_max = 20.7232658369;
//    double N_flavor = 2;
//    int N_grid = 1000;
//    double sigma_max = 6.0;
////    dp::Leaf<phy::Flow> root(mu, T, initial_box_size, split_condition, Lambda, t_max, N_flavor, N_grid, sigma_max);
//    std::cout << "Hello, World!" << std::endl;
    return 0;
}
