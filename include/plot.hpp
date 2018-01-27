#ifndef PLOT_HPP
#define PLOT_HPP


#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>


namespace cpl{
    
    unsigned int current_plot;

    class Plot{
        public:
            /* Window params */
            float window_height, window_width;
            std::string window_title;
            bool window_resizable;

            /* Plot params */
            double x_min, x_max, y_min, y_max;
            std::string plot_title;
            double point_size;
            
            /* Constructors */
            template <typename T>
            Plot(std::vector<T>& y_list, std::string format_string="b-", std::string legend="");
            template <typename T, typename U>
            Plot(std::vector<T>& x_list, std::vector<U>& y_list, std::string format_string="b-", std::string legend="");
            Plot(bool create_window=false, float window_width=5, float window_height=5);
            
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
            void title(std::string plot_title);


            void show(); /* Setup window and show the plot */

        private:

            /* SFML objects */
            sf::RenderWindow window;
            sf::Event event;


            /* Helper functions */



    };
    
    std::vector<Plot> active_plots;
    template <typename T>       
    Plot& plot(std::vector<T>& x_list, std::vector<T>& y_list, std::string format_string, std::string legend);
}

#endif