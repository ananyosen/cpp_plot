#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>


namespace plot{
    
    class Plot{
        public:
            // Window width and height, multiplied by 100
            float width, height;
            // Plot title
            std::string title;
            float xmin, xmax, ymin, ymax;

            template <typename T>            
            Plot & plot(std::vector<T>& y_list, format_string="b-", legend="")
            {   
                std::vector<int> x_list(y_list.length());
                for(int iii = 0; iii < x_list.length(); iii++)
                {
                    x_list.at(iii) = iii;
                }
                this->plot_finally(x_list, y_list, format_string, legend);
            }
            
            template <typename T>            
            Plot & plot(std::vector<T>& x_list, std::vector<T>& y_list, format_string="b-", legend="")
            {
                this->plot_finally(x_list, y_list, format_string, legend);                
            }

            template <typename T>
            void plot_finally(std::vector<T>& x_list, std::vector<T>& y_list, format_string, legend)
            {

            }

        private:
            sf::RenderWindow window;
            sf::Event event;
    };
}