#include <vector>
#include <string>
#include <stdexcept>
#include <sstream>

#include <SFML/Graphics/Color.hpp>


namespace cpl
{
    template<typename T, typename U>
    PlotData<T, U>::PlotData(std::vector<T>& x, std::vector<U>& y, std::string format_string, std::string legend, sf::Color& plt_color)
    {
        if(x.size() != y.size())
        {
            std::stringstream ss;
            ss << "x list size=" << x.size() << " and y list size=" << y.size() << ", mismatch";
            throw std::invalid_argument(ss.str());
        }
        this->x_data = x;
        this->y_data = y;
        this->fmt_string = format_string;
        this->lgend = legend;
        this->plot_color = plt_color;
        this->parse_format_string();
    }

    template<typename T, typename U>
    void PlotData<T, U>::setColor(int red, int green, int blue)
    {
        this->plot_color = sf::Color(red, green, blue);
        this->has_custom_color = true;
    }

    template<typename T, typename U>
    void PlotData<T, U>::setColor(std::string color_name)
    {
        unsigned int color_uint32 = parse_colors(color_name);
        this->plot_color = sf::Color(color_uint32);
        this->has_custom_color = true;
    }

    template<typename T, typename U>
    void PlotData<T, U>::parse_format_string()
    {
        /* Placeholder code */ // TODO
    }

    template<typename T, typename U>
    void PlotData<T, U>::setLegend(std::string legend)
    {
        this->lgend = legend;
    }

    template<typename T, typename U>
    void PlotData<T, U>::setMarker(std::string marker)
    {
        this->mrker = marker;
        this->parse_format_string();
    }

    template<typename T, typename U>
    void PlotData<T, U>::setMarkerSize(unsigned short marker_sz)
    {
        this->marker_size = marker_sz;
    }

    unsigned int parse_colors(std::string color_name)
    {
        /* Placeholder code*/ // TODO
        return 255; // Should be black, alpha=255;
    }

    template<typename T, typename U>
    const std::vector<T>& PlotData<T, U>::getX()
    {
        return this->x_data;
    }
    
    template<typename T, typename U>
    const std::vector<U>& PlotData<T, U>::getY()
    {
        return this->y_data;
    }
}