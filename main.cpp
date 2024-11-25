#include "engine.h"
#include <iostream>

using namespace std;

int main()
{
    EngineParams params = read_params("input.txt");

    double T_env;
    cout << "Enter the ambient temperature (C): ";
    cin >> T_env;

    double time_to_overheat, max_power, max_power_V;
    simulate_engine(params, T_env, time_to_overheat, max_power, max_power_V);

    cout << "Time to overheat: " << time_to_overheat << " sec" << endl;
    cout << "Maximum power: " << max_power << " kW" << endl;
    cout << "Rotational speed at maximum power: " << max_power_V << " rad/sec" << endl;

    return 0;
}