#include <vector>
#include <string>
#include <stdexcept>
#include <sstream>

#include <SFML/Graphics/Color.hpp>


namespace cpl
{
    PlotData::PlotData(std::vector<double>& x, std::vector<double>& y, std::string format_string, std::string legend, sf::Color& plt_color)
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

    void PlotData::setColor(int red, int green, int blue)
    {
        this->plot_color = sf::Color(red, green, blue);
        this->has_custom_color = true;
    }

    void PlotData::setColor(std::string color_name)
    {
        unsigned int color_uint32 = parse_colors(color_name);
        this->plot_color = sf::Color(color_uint32);
        this->has_custom_color = true;
    }

    void PlotData::parse_format_string()
    {
        /* Placeholder code */ // TODO
    }

    void PlotData::setLegend(std::string legend)
    {
        this->lgend = legend;
    }

    void PlotData::setMarker(std::string marker)
    {
        this->mrker = marker;
        this->parse_format_string();
    }

    void PlotData::setMarkerSize(unsigned short marker_sz)
    {
        this->marker_size = marker_sz;
    }

    unsigned int parse_colors(std::string color_name)
    {
        /* Placeholder code*/ // TODO
        return 255; // Should be black, alpha=255;
    }

    const std::vector<double>& PlotData::getX()
    {
        return this->x_data;
    }
    
    const std::vector<double>& PlotData::getY()
    {
        return this->y_data;
    }
}