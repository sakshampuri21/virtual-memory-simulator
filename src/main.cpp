#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include "generators.hpp"
#include "policy_factory.hpp"
#include "simulator.hpp"
#include "working_set.hpp"

static const std::size_t kLength = 1000;
static const int kPages = 20;
static const int kMinFrames = 1, kMaxFrames = 8;

static std::vector<std::pair<std::string, ReferenceString>> patterns() {
    return {
        {"Random",         generateRandom(kLength, kPages)},
        {"Sequential",     generateSequential(kLength, kPages)},
        {"Locality-heavy", generateLocality(kLength, kPages)},
    };
}

static void runCompare() {
    std::cout << "\n=== Policy comparison (" << kLength << " refs, " << kPages << " pages) ===\n";
    for (auto& [pname, refs] : patterns()) {
        std::cout << "\nPattern: " << pname << "\n";
        std::cout << std::left << std::setw(8) << "Frames";
        for (auto t : allPolicies()) std::cout << std::setw(24) << makePolicy(t, 1, refs)->name();
        std::cout << "\n" << std::setw(8) << "";
        for (size_t i = 0; i < allPolicies().size(); ++i) std::cout << std::setw(24) << "faults / hit%";
        std::cout << "\n";

        for (int f = kMinFrames; f <= kMaxFrames; ++f) {
            std::cout << std::setw(8) << f;
            for (auto t : allPolicies()) {
                auto policy = makePolicy(t, f, refs);
                SimResult r = simulate(*policy, refs);
                std::ostringstream cell;
                cell << r.faults << " / " << std::fixed << std::setprecision(1) << r.hitRatio() * 100 << "%";
                std::cout << std::setw(24) << cell.str();
            }
            std::cout << "\n";
        }
    }
}

static void runBelady() {
    ReferenceString refs = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5};  // classic example
    std::cout << "\n=== Belady's anomaly (FIFO) ===\nReference string: ";
    for (int p : refs) std::cout << p << ' ';
    std::cout << "\n\nFrames  Faults\n";

    std::size_t prev = 0;
    for (int f = 1; f <= 5; ++f) {
        auto policy = makePolicy(PolicyType::FIFO, f, refs);
        SimResult r = simulate(*policy, refs);
        std::cout << std::left << std::setw(8) << f << std::setw(8) << r.faults;
        if (f > 1 && r.faults > prev) std::cout << "<-- anomaly: more frames, more faults";
        std::cout << "\n";
        prev = r.faults;
    }
}

static void runWorkingSet() {
    const std::size_t window = 20;
    std::cout << "\n=== Sliding-window working set (window = " << window << ") ===\n";
    std::cout << std::left << std::setw(18) << "Pattern" << std::setw(12) << "Avg WSS" << "Max WSS\n";
    for (auto& [pname, refs] : patterns()) {
        WorkingSetStats s = analyzeWorkingSet(refs, window);
        std::cout << std::setw(18) << pname << std::setw(12) << std::fixed << std::setprecision(2)
                  << s.average << s.maximum << "\n";
    }
    std::cout << "\nSmaller WSS = stronger temporal locality = fewer frames needed.\n";
}

int main(int argc, char** argv) {
    std::string mode = argc > 1 ? argv[1] : "all";
    if (mode == "compare")         runCompare();
    else if (mode == "belady")     runBelady();
    else if (mode == "workingset") runWorkingSet();
    else if (mode == "all")        { runCompare(); runBelady(); runWorkingSet(); }
    else {
        std::cerr << "Usage: " << argv[0] << " [compare|belady|workingset|all]\n";
        return 1;
    }
    return 0;
}