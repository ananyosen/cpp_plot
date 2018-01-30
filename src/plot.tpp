#include <vector>
#include <string>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <subplot.hpp>

namespace cpl{

    Plot::Plot(float window_width, float window_height)
    {
        /* Create an empty Plot instance, optionally open an empty window to draw to */
        this->window_width = window_width*this->view_scale_multiplier;
        this->window_height = window_height*this->view_scale_multiplier;
    }

    template <typename T>            
    Plot::Plot(std::vector<T>& y_list, std::string format_string, std::string legend)
    {
        /* Create a default Plot instance with given data, x axis will be datapoint indices */

    }

    template <typename T, typename U>            
    Plot::Plot(std::vector<T>& x_list, std::vector<U>& y_list, std::string format_string, std::string legend)
    {
        /* Create a default Plot instance with given data */
    }

    template <typename T, typename U>            
    void Plot::initialize_plot(std::vector<T>& x_list, std::vector<U>& y_list, std::string format_string, std::string legend)
    {

    }

}