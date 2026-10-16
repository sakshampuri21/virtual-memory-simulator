#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "generators.hpp"
#include "policy_factory.hpp"
#include "simulator.hpp"
#include "working_set.hpp"

const std::size_t LENGTH = 1000;
const int PAGES = 20;
const int MIN_FRAMES = 1;
const int MAX_FRAMES = 8;

const std::vector<std::string> POLICY_NAMES = {"FIFO", "LRU", "Optimal"};

struct Pattern {
    std::string name;
    ReferenceString refs;
};

std::vector<Pattern> makePatterns() {
    return {
        {"Random",         generateRandom(LENGTH, PAGES)},
        {"Sequential",     generateSequential(LENGTH, PAGES)},
        {"Locality-heavy", generateLocality(LENGTH, PAGES)},
    };
}

std::string formatResult(const SimResult& r) {
    std::ostringstream out;
    out << r.faults << " / " << std::fixed << std::setprecision(1)
        << r.hitRatio() * 100 << "%";
    return out.str();
}

void runCompare() {
    std::cout << "\n=== Policy comparison (" << LENGTH << " refs, "
              << PAGES << " pages) ===\n";

    for (const Pattern& p : makePatterns()) {
        std::cout << "\nPattern: " << p.name << "\n";

        std::cout << std::left << std::setw(8) << "Frames";
        for (const std::string& name : POLICY_NAMES)
            std::cout << std::setw(24) << name;
        std::cout << "\n" << std::setw(8) << "";
        for (size_t i = 0; i < POLICY_NAMES.size(); ++i)
            std::cout << std::setw(24) << "faults / hit%";
        std::cout << "\n";

        for (int frames = MIN_FRAMES; frames <= MAX_FRAMES; ++frames) {
            std::cout << std::setw(8) << frames;
            for (const std::string& name : POLICY_NAMES) {
                auto policy = makePolicy(name, frames, p.refs);
                SimResult r = simulate(*policy, p.refs);
                std::cout << std::setw(24) << formatResult(r);
            }
            std::cout << "\n";
        }
    }
}

void runBelady() {
    ReferenceString refs = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5};

    std::cout << "\n=== Belady's anomaly (FIFO) ===\nReference string: ";
    for (int page : refs)
        std::cout << page << ' ';
    std::cout << "\n\nFrames  Faults\n";

    std::size_t previousFaults = 0;
    for (int frames = 1; frames <= 5; ++frames) {
        auto policy = makePolicy("FIFO", frames, refs);
        SimResult r = simulate(*policy, refs);

        std::cout << std::left << std::setw(8) << frames << std::setw(8) << r.faults;
        if (frames > 1 && r.faults > previousFaults)
            std::cout << "<-- anomaly: more frames, more faults";
        std::cout << "\n";

        previousFaults = r.faults;
    }
}

void runWorkingSet() {
    const std::size_t WINDOW = 20;

    std::cout << "\n=== Sliding-window working set (window = " << WINDOW << ") ===\n";
    std::cout << std::left << std::setw(18) << "Pattern"
              << std::setw(12) << "Avg WSS" << "Max WSS\n";

    for (const Pattern& p : makePatterns()) {
        WorkingSetStats s = analyzeWorkingSet(p.refs, WINDOW);
        std::cout << std::setw(18) << p.name << std::setw(12) << std::fixed
                  << std::setprecision(2) << s.average << s.maximum << "\n";
    }
    std::cout << "\nSmaller WSS = stronger temporal locality = fewer frames needed.\n";
}

int main(int argc, char** argv) {  
    //argc is the number of words typed on the command line, including the program name.
    // argv holds those words as text. For ./vmsim belady, argc is 2, argv[0] is "./vmsim" and argv[1] is "belady".
    std::string mode = (argc > 1) ? argv[1] : "all";

    if (mode == "compare") {
        runCompare();
    } else if (mode == "belady") {
        runBelady();
    } else if (mode == "workingset") {
        runWorkingSet();
    } else if (mode == "all") {
        runCompare();
        runBelady();
        runWorkingSet();
    } else {
        std::cerr << "Usage: " << argv[0] << " [compare|belady|workingset|all]\n";
        return 1;
    }
    return 0;
}