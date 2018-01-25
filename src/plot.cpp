#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

#include "plot.hpp"

namespace cpl{

    template <typename T>            
    Plot& Plot::Plot(std::vector<T>& y_list, format_string="b-", legend="")
    {   
        std::vector<int> x_list(y_list.length());
        for(int iii = 0; iii < x_list.length(); iii++)
        {
            x_list.at(iii) = iii;
        }
        this->plot_finally(x_list, y_list, format_string, legend);
    }
    
    template <typename T>            
    Plot& Plot::Plot(std::vector<T>& x_list, std::vector<T>& y_list, std::string format_string="b-", std::string legend="")
    {
        this->plot_finally(x_list, y_list, format_string, legend);                
    }

    template <typename T>
    void Plot::plot_finally(std::vector<T>& x_list, std::vector<T>& y_list, std::string format_string, std::string legend)
    {

    }
}