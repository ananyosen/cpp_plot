#ifndef PLOT_DATA_HPP
#define PLOT_DATA_HPP

#include <vector>
#include <string>
#include <stdexcept>
#include <sstream>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics.hpp>

namespace cpl
{
    // template<typename T, typename U>
    class PlotData{
        public:
            bool show_legend, has_custom_color;
            unsigned short marker_size;
            sf::Color plot_color;

            PlotData(std::vector<double>& x, std::vector<double>& y, std::string format_string, std::string legend, sf::Color& plt_color);
            void setColor(int red, int green, int blue);
            void setColor(std::string color_name);
            void setLegend(std::string legend);
            void setMarker(std::string marker);
            void setMarkerSize(unsigned short m_size);
            const std::vector<double>& getX();
            const std::vector<double>& getY();
            // const sf::Color

        private:
            std::vector<double> x_data;
            std::vector<double> y_data;
            std::string fmt_string;
            std::string lgend;
            std::string mrker;

            void parse_format_string();
    };
        
    unsigned int parse_colors(std::string color_name);
}

#include <plotdata.tpp>
#endif