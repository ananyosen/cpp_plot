#include <string>
#include <vector>
#include <algorithm>
#include <limits>
#include <stdexcept>
#include <sstream>

#include <SFML/Window.hpp>
#include <SFML/System/Vector2.hpp>

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
        this->plot_datasets.push_back(cpl::PlotData<T, U>(x, y, format_string, legend));
        this->current_dataset = this->plot_datasets.size() - 1;
        double min_x = *std::min_element(x.begin(), x.end());
        double min_y= *std::min_element(y.begin(), y.end());
        double max_x = *std::max_element(x.begin(), x.end());
        double max_y = *std::max_element(y.begin(), y.end());
        min_x = (min_x < this->x_min)?min_x:this->x_min;
        min_y = (min_y < this->y_min)?min_y:this->y_min;
        max_x = (max_x < this->x_max)?max_x:this->x_max;
        max_y = (max_y < this->y_max)?max_y:this->y_max;
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
        ** sets `init_done` to false if `plot_datasets` is empty
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
    void Subplot<T, U>::draw(sf::RenderWindow& render_wndw)
    {
        /* Oh boy, this is a big one */
        this->parent_window = render_wndw;
        const sf::Vector2u window_size = this->parent_window.getSize();
        unsigned int width = window_size.x;
        unsigned int height = window_size.y;
        sf::Vector2<float> draw_top_left(this->x_view_start*width, this->y_view_start*height);
        sf::Vector2<float> draw_size((this->x_view_end - this->x_view_start)*width, (this->y_view_end - this->y_view_start)*height);
    }

}