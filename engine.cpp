#include "engine.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>

using namespace std;

EngineParams read_params(const string &filename)
{
    EngineParams params;
    ifstream file(filename.c_str());
    string line;
    while (getline(file, line))
    {
        istringstream iss(line);
        string key, value;
        getline(iss, key, '=');
        getline(iss, value);
        if (key == "I")
        {
            params.I = stod(value);
        }
        else if (key == "M_values")
        {
            istringstream values(value);
            string val;
            while (getline(values, val, ','))
            {
                params.M_values.push_back(stod(val));
            }
        }
        else if (key == "V_values")
        {
            istringstream values(value);
            string val;
            while (getline(values, val, ','))
            {
                params.V_values.push_back(stod(val));
            }
        }
        else if (key == "T_overheat")
        {
            params.T_overheat = stod(value);
        }
        else if (key == "HM")
        {
            params.HM = stod(value);
        }
        else if (key == "HV")
        {
            params.HV = stod(value);
        }
        else if (key == "C")
        {
            params.C = stod(value);
        }
    }
    return params;
}

double get_torque(const vector<double> &M_values, const vector<double> &V_values, double V)
{
    for (size_t i = 0; i < V_values.size() - 1; ++i)
    {
        if (V_values[i] <= V && V < V_values[i + 1])
        {
            return M_values[i] + (M_values[i + 1] - M_values[i]) * (V - V_values[i]) / (V_values[i + 1] - V_values[i]);
        }
    }
    return 0;
}

void simulate_engine(const EngineParams &params, double T_env, double &time_to_overheat, double &max_power, double &max_power_V)
{
    const double dt = 0.1; // Simulation step (sec)
    double V = 0;          // Initial rotational speed (rad/sec)
    double T = T_env;      // Initial engine temperature (C)
    double time = 0;       // Simulation time (sec)
    max_power = 0;         // Maximum power (kW)
    max_power_V = 0;       // Rotational speed at maximum power (rad/sec)

    while (T < params.T_overheat)
    {
        double M = get_torque(params.M_values, params.V_values, V);
        double a = M / params.I;                       // Acceleration of the crankshaft
        V += a * dt;                                   // Update rotational speed
        double VH = M * params.HM + V * V * params.HV; // Heating rate
        double VC = params.C * (T_env - T);            // Cooling rate
        T += (VH - VC) * dt;                           // Update temperature
        time += dt;                                    // Update time

        double power = M * V / 1000.0; // Power (kW)
        if (power > max_power)
        {
            max_power = power;
            max_power_V = V;
        }
    }

    time_to_overheat = time;
}