#include <iostream>
#include <vector>
#include <random>
using namespace std;

// Define the particle class
class Particle {
public:
    double x, y;
    int state;
    Particle(double x, double y, int state) : x(x), y(y), state(state) {}
};

// Define the transition class
class Transition {
public:
    int initial_state, final_state;
    double rate;
    Transition(int initial_state, int final_state, double rate) : initial_state(initial_state), final_state(final_state), rate(rate) {}
};

void simulate(double tmax, vector<Particle> particles, vector<Transition> transitions, uniform_real_distribution<double> dis, mt19937 gen) {
    double t = 0.0;

    while (t < tmax) {
        // Calculate the rates
        vector<double> rates(transitions.size());
        double rate_sum = 0.0;
        for (int i = 0; i < transitions.size(); i++) {
            int initial_state = transitions[i].initial_state;
            int final_state = transitions[i].final_state;
            rates[i] = transitions[i].rate;
            rate_sum += rates[i];
        }

        // Choose a transition
        double r = dis(gen) * rate_sum;
        int i = 0;
        double cum_rate = rates[i];
        while (r > cum_rate) {
            i++;
            cum_rate += rates[i];
        }
        Transition chosen_transition = transitions[i];

        // Update the system
        particles[chosen_transition.initial_state].state = chosen_transition.final_state;

        // Print the current state of the system
        cout << "t = " << t << ", State = ";
        for (auto &particle : particles) {
            cout << particle.state << " ";
        }
        cout << endl;

        // Increment the time
        t += -log(dis(gen)) / rate_sum;
    }
}

int main() {
    // Set up the system
    const vector<Particle> particles = { Particle(0, 0, 0), Particle(1, 0, 0) };
    const vector<Transition> transitions = { Transition(0, 1, 1.0), Transition(1, 0, 0.5) };
    const double tmax = 10.0;

    // Set up the random number generator
    random_device rd;
    const mt19937 gen(rd());
    const uniform_real_distribution<double> dis(0.0, 1.0);

    // Run the simulation
    simulate(tmax, particles, transitions, dis, gen);

    return 0;
}
