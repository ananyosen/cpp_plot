#include <string>
#include <vector>
#include <algorithm>
#include <limits>
#include <stdexcept>
#include <sstream>
#include <cmath>

#include <SFML/Window.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>

#include <plotdata.hpp>

namespace cpl
{
    template<typename T, typename U>
    Subplot<T, U>::Subplot(double view_frctn)
    {
        /* 
        ** Initialize a Subplot, with optional view fraction
        ** init draw parameters, xrange and yrange
        ** Supports packing, both horizontally and vertically
        */
        this->view_fraction = view_frctn;
        this->x_view_start = this->y_view_start = 0.0;
        this->x_view_end = this->y_view_end = 1.0;
        this->subplot_title = "";
        this->x_range_scale = this->y_range_scale = 0.1; // plot buffer region over and below max and min points
        this->is_log_x = false;
        this->is_log_y = false;
        this->common_colors = {
            sf::Color::Blue,
            sf::Color::Red,
            sf::Color::Green,
            sf::Color::Yellow,
            sf::Color::Cyan,
            sf::Color::Magenta,
            sf::Color::Black
        };
        this->initialize_plots();
    }

    template<typename T, typename U>
    void Subplot<T, U>::initialize_plots()
    {
        this->x_min = this->y_min = std::numeric_limits<double>::max();
        this->x_max = this->y_max = std::numeric_limits<double>::min();
        this->has_data = false;
    }

    template<typename T, typename U>
    void Subplot<T, U>::addPlotdata(std::vector<T>& x, std::vector<U>& y, std::string format_string, std::string legend)
    {
        /*
        ** init a PlotData, store it to plot_datasets
        ** and change current_dataset to point to the
        ** newly added PlotData. Optionally set xrange
        ** and yrange from dataset
        */
        unsigned int color_id = this->plot_datasets.size() % this->common_colors.size();
        this->plot_datasets.push_back(cpl::PlotData<T, U>(x, y, format_string, legend, this->common_colors.at(color_id)));
        this->current_dataset = this->plot_datasets.size() - 1;
        double min_x = *std::min_element(x.begin(), x.end());
        double min_y= *std::min_element(y.begin(), y.end());
        double max_x = *std::max_element(x.begin(), x.end());
        double max_y = *std::max_element(y.begin(), y.end());
        min_x = (min_x < this->x_min)?min_x:this->x_min;
        min_y = (min_y < this->y_min)?min_y:this->y_min;
        max_x = (max_x > this->x_max)?max_x:this->x_max;
        max_y = (max_y > this->y_max)?max_y:this->y_max;
        this->x_min = min_x - (max_x - min_x)*this->x_range_scale;
        this->y_min = min_y - (max_y - min_y)*this->y_range_scale;
        this->x_max = max_x + (max_x - min_x)*this->x_range_scale;
        this->y_max = max_y + (max_y - min_y)*this->y_range_scale;
    }

    template<typename T, typename U>
    void Subplot<T, U>::removePlotdata(unsigned int position)
    {
        /*
        ** Remove a PlotData from the Subplot
        ** not sure if it'll ever be needed, just in case
        ** sets `has_data` to false if `plot_datasets` is empty
        */
        if(position >= this->plot_datasets.size())
        {
            std::stringstream ss;
            ss << "Invalid position " << position << " to remove with size " << this->plot_datasets.size();
            throw std::out_of_range(ss.str());
        }
        this->plot_datasets.erase(this->plot_datasets.begin() + position);
        if(this->current_dataset >= position)
        {
            this->current_dataset--;
        }
        if(this->plot_datasets.size()==0)
        {
            this->initialize_plots();
        }
    }

    template<typename T, typename U>
    void Subplot<T, U>::draw(sf::RenderWindow* render_wndw)
    {
        /* Oh boy, this is a big one */
        this->parent_window = render_wndw;
        const sf::Vector2u window_size = this->parent_window->getSize();
        unsigned int width = window_size.x;
        unsigned int height = window_size.y;
        sf::Vector2<float> draw_top_left(this->x_view_start*width, this->y_view_start*height);
        sf::Vector2<float> draw_size((this->x_view_end - this->x_view_start)*width, (this->y_view_end - this->y_view_start)*height);
        for(unsigned int iii = 0; iii < this->plot_datasets.size(); iii++)
        {
            const std::vector<T> x = this->plot_datasets.at(iii).getX();
            const std::vector<U> y = this->plot_datasets.at(iii).getY();
            if(x.size()==0 || y.size()==0)
            {
                throw std::invalid_argument("can't plot with 0 datapoints");
            }
            std::vector<sf::Vertex> vertices;
            // TODO: cleanup
            double x_pt = this->mapValue(this->x_min, this->x_max, x.at(0), draw_size.x, this->is_log_x) + draw_top_left.x;
            double y_pt = (draw_size.y - this->mapValue(this->y_min, this->y_max, y.at(0), draw_size.y, this->is_log_y)) + draw_top_left.y;
            vertices.push_back(sf::Vertex(sf::Vector2f(x_pt, y_pt), this->plot_datasets.at(iii).plot_color));
            for(int jjj = 0; jjj < x.size(); jjj++)
            {
                x_pt = this->mapValue(this->x_min, this->x_max, x.at(jjj), draw_size.x, this->is_log_x) + draw_top_left.x;
                y_pt = (draw_size.y - this->mapValue(this->y_min, this->y_max, y.at(jjj), draw_size.y, this->is_log_y)) + draw_top_left.y;
                vertices.push_back(sf::Vertex(sf::Vector2f(x_pt, y_pt), this->plot_datasets.at(iii).plot_color));
            }
            this->parent_window->draw(&vertices[0], vertices.size(), sf::LineStrip);
        }
    }

    template<typename T, typename U>
    double Subplot<T, U>::mapValue(double min, double max, double value, double length, bool is_log10)
    {
        /*
        ** Map a value within min and max to the plot area
        */
        if(is_log10)
        {
            return (log10(value/min)/log10(max/min))*length;
        }
        else
        {
            return ((value - min)/(max - min))*length;
        }
    }

}