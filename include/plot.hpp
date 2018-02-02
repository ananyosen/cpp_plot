#ifndef PLOT_HPP
#define PLOT_HPP

#include <vector>
#include <string>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <subplot.hpp>

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
            /* add new plot */
            template <typename T>
            void plot(std::vector<T>& y_list, std::string format_string="b-", std::string legend="");
            template <typename T, typename U>
            void plot(std::vector<T>& x_list, std::vector<U>& y_list, std::string format_string="b-", std::string legend="");
            Plot(float window_width=5, float window_height=5);
            
            /* Window functions */
            void subplotTitle(std::string subplot_title);
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
            float view_scale_multiplier = 100.0;
            std::vector<cpl::Subplot> subplots;
            unsigned int active_subplot;
            bool has_data;
            template <typename T, typename U>            
            void initialize_plot(std::vector<T>& x_list, std::vector<U>& y_list, std::string format_string, std::string legend);


            /* Helper functions */



    };
    
    std::vector<cpl::Plot> current_plots;
    unsigned int active_plot;
    template <typename T, typename U>       
    Plot& plot(std::vector<T>& x_list, std::vector<U>& y_list, std::string format_string="", std::string legend="");
    template <typename T>       
    Plot& plot(std::vector<T>& y_list, std::string format_string="", std::string legend="");
    void figure(float window_width=5, float window_height=5);
    void show();
}

#include <plot.tpp>

#endif