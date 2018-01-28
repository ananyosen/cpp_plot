#ifndef PLOT_DATA_HPP
#define PLOT_DATA_HPP

#include <vector>
#include <string>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics.hpp>

namespace cpl
{
    template<typename T, typename U>
    class PlotData{
        public:
            bool show_legend;
            unsigned short marker_size;

            PlotData(std::vector<T>& x, std::vector<U>& y, std::string format_string, std::string legend);
            void setColor(int red, int green, int blue);
            void setColor(std::string color_name);
            void setLegend(std::string legend);
            void setMarker(std::string marker);
            void setMarkerSize(unsigned short m_size);


        private:
            std::vector<T> x_data;
            std::vector<U> y_data;
            std::string fmt_string;
            std::string lgend;
            std::string mrker;
            sf::Color plot_color;

            void parse_format_string();
    };
        
    unsigned int parse_colors(std::string color_name);
}

#include <plotdata.tpp>
#endif