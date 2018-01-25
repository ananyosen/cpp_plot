#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

#include "plot.hpp"

namespace cpl{

    template <typename T, typename U>            
    Plot::Plot(std::vector<T>& x_list, std::vector<U>& y_list, std::string format_string, std::string legend)
    {
        // this->plot_finally(x_list, y_list, format_string, legend);                
    }

}