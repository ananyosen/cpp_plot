#include<vector>
#include<subplot.hpp>

using namespace std;

int main()
{
    vector<int> x = {1};
    vector<float> y = {1.39};
    cpl::Subplot<int, float> plt(1.0);
    plt.addPlotdata(x, y, "", "");
}