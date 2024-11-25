#include <vector>
#include <string>

struct EngineParams
{
    double I;
    std::vector<double> M_values;
    std::vector<double> V_values;
    double T_overheat;
    double HM;
    double HV;
    double C;
};

EngineParams read_params(const std::string &filename);
double get_torque(const std::vector<double> &M_values, const std::vector<double> &V_values, double V);
void simulate_engine(const EngineParams &params, double T_env, double &time_to_overheat, double &max_power, double &max_power_V);