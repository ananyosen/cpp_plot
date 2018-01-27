/* Define a subplot class
** A drawing space where plots are made
** from corresponding PlotData class.
** A Plot window can have multiple Subplots
** and a Subplot can have multiple datasets
*/

#ifndef SUBPLOT_HPP
#define SUBPLOT_HPP

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
    class Subplot
    {
        public:
            /* Plot view specific params */
            double x_min, x_max, y_min, y_max, x_range_scale, y_range_scale;
            double view_fraction, x_view_start, x_view_end, y_view_start, y_view_end;
            // bool custom_xrange
            std::string subplot_title;

            Subplot(double view_frctn=1.0);
            void addPlotdata(std::vector<T>& x, std::vector<U>& y, std::string format_string, std::string legend);
            void removePlotdata(unsigned int position);
            void draw(sf::RenderWindow& parent_wndw);

        private:
            sf::RenderWindow parent_window;
            std::vector<cpl::PlotData<T, U>> plot_datasets;
            unsigned int current_dataset;
            bool init_done = false;
    };
}

#endif