#include <vector>
#include <cmath>

#include <plot.hpp>

using namespace std;

int main()
{
    vector<double> x;
    vector<double> y;
    vector<float> y2;
    for (int iii = 0; iii < 200; iii++)
    {
        double v = (static_cast<double>(iii)/100.0)*3.14;
        double s = sin(v);
        float s2 = cos(v);
        x.push_back(v);
        y.push_back(s);
        y2.push_back(s2);
    }
    // cpl::Plot plt(6, 4);
    // plt.plot(x, y);
    // plt.plot(x, y2);
    // plt.show();
    cpl::plot(x, y);
    cpl::plot(x, y2);
    cpl::show();
    cpl::save("plt.png");
}