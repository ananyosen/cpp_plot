#ifndef PLOT_HPP
#define PLOT_HPP


#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>


namespace cpl{
    
    std::vector<Plot> active_plots;
    unsigned int current_plot;

    class Plot{
        public:
            /* Window params */
            float window_height, window_width;
            std::string window_title;
            bool window_resizable;

            /* Plot params */
            double xmin, xmax, ymin, ymax;
            
            /* Constructors */
            template <typename T>
            Plot& Plot(std::vector<T>& y_list);
            Plot& Plot(std::vector<T>& x_list, std::vector<T>& y_list);
            Plot& Plot(std::vector<T>& x_list, std::vector<T>& y_list, std::string format_string);
            Plot& Plot(std::vector<T>& x_list, std::vector<T>& y_list, std::string format_string, std::string legend);
            
            /* Window functions */
            void setTitle(std::string window_title);
            void setPlotSize(int window_width, int window_height);
            void setResizable(bool window_resizable);

            /* Plot functions */
            void xmin(double xmin);
            void xmax(double xmax);
            void ymin(double ymin);
            void ymax(double ymax);
            void xrange(double xmin, double xmax);
            void yrange(double ymin, double ymax);

            void show(); /* Setup window and show the plot */

        private:

            /* SFML objects */
            sf::RenderWindow window;
            sf::Event event;

    };

    Plot& plot(std::vector<T>& x_list, std::vector<T>& y_list, std::string format_string, std::string legend);
}

#endif