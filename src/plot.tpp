#include <vector>
#include <string>

#ifdef DEBUG_BUILD
#include <iostream>
#include <SFML/System/Vector2.hpp>
#endif

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Image.hpp>

#include <subplot.hpp>

namespace cpl{

    Plot::Plot(float window_width, float window_height)
    {
        /* Create an empty Plot instance */
        this->has_data = false;
        this->window_width = window_width*this->view_scale_multiplier;
        this->window_height = window_height*this->view_scale_multiplier;
    }

    template <typename T>
    Plot::Plot(std::vector<T>& y_list, std::string format_string, std::string legend)
    {
        /* Create a default Plot instance with given data, x axis will be datapoint indices */
        std::vector<double> x_list;
        for(int iii = 0; iii < y_list.size(); iii++)
        {
            x_list.push_back(iii);
        }
        this->initialize_plot(x_list, y_list, format_string, legend);
    }

    template <typename T, typename U>            
    Plot::Plot(std::vector<T>& x_list, std::vector<U>& y_list, std::string format_string, std::string legend)
    {
        /* Create a default Plot instance with given data */
        this->initialize_plot(x_list, y_list, format_string, legend);        
    }

    template <typename T>
    void Plot::plot(std::vector<T>& y_list, std::string format_string, std::string legend)
    {
        /* Create a default Plot instance with given data, x axis will be datapoint indices */
        std::vector<double> x_list;
        for(int iii = 0; iii < y_list.size(); iii++)
        {
            x_list.push_back(iii);
        }
        this->initialize_plot(x_list, y_list, format_string, legend);
    }

    template <typename T, typename U>            
    void Plot::plot(std::vector<T>& x_list, std::vector<U>& y_list, std::string format_string, std::string legend)
    {
        /* Create a default Plot instance with given data */
        this->initialize_plot(x_list, y_list, format_string, legend);        
    }

    template <typename T, typename U>            
    void Plot::initialize_plot(std::vector<T>& x_list, std::vector<U>& y_list, std::string format_string, std::string legend)
    {
        this->window_width = 5*this->view_scale_multiplier;
        this->window_height = 5*this->view_scale_multiplier;
        if(!this->has_data)
        {
            this->subplots.push_back(cpl::Subplot(1.0));
            this->has_data = true;
            this->active_subplot = this->subplots.size() - 1;
        }
        this->subplots.at(this->active_subplot).addPlotdata(x_list, y_list, format_string, legend);
    }

    void Plot::xmin(double x_min)
    {
        this->subplots.at(this->active_subplot).x_min = x_min;
    }

    void Plot::ymin(double y_min)
    {
        this->subplots.at(this->active_subplot).y_min = y_min;
    }

    void Plot::xmax(double x_max)
    {
        this->subplots.at(this->active_subplot).x_max = x_max;
    }

    void Plot::ymax(double y_max)
    {
        this->subplots.at(this->active_subplot).y_max = y_max;
    }

    void Plot::xrange(double x_min, double x_max)
    {
        this->xmin(x_min);
        this->xmax(x_max);
    }

    void Plot::yrange(double y_min, double y_max)
    {
        this->ymin(y_min);
        this->ymax(y_max);
    }

    void Plot::subplotTitle(std::string subplot_title)
    {
        this->subplots.at(this->active_subplot).subplot_title = subplot_title;        
    }

    void Plot::save(std::string file_name)
    {
        this->show(true, file_name);
    }

    void Plot::show(bool save_img, std::string file_name)
    {
        sf::ContextSettings settings;
        settings.antialiasingLevel = 8; // 8xMSAA
        sf::RenderWindow window(sf::VideoMode(this->window_width, this->window_height), "CPP Plot", sf::Style::Default, settings);
        window.setVerticalSyncEnabled(true);
        sf::View view;
        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
                if (event.type == sf::Event::KeyReleased)
                {
                    /* Close window on `escape` or `q` */
                    if(event.key.code == sf::Keyboard::Key::Escape || event.key.code == sf::Keyboard::Key::Q)
                    {
                        window.close();
                    }
                }
                if(event.type == sf::Event::Resized)
                {
                    /* get current window width, height and resize the View to avoid stretching */
                    window.setView(view = sf::View(sf::FloatRect(0.0, 0.0, static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y))));
                }
            }

            window.clear(sf::Color::White);

            /* Draw the subplots */       
            for(int jjj = 0; jjj < this->subplots.size(); jjj++)
            {
                this->subplots.at(jjj).draw(&window);
            }

            if(save_img)
            {
                sf::Texture tmp_texture = sf::Texture();
                tmp_texture.create(window.getSize().x, window.getSize().y); 
                tmp_texture.update(window);
                sf::Image tmp_img =  tmp_texture.copyToImage();
                tmp_img.saveToFile(file_name);
                window.close();
            }
            else
            {
                window.display();                
            }
        }

    }

    template <typename T, typename U>       
    Plot& plot(std::vector<T>& x_list, std::vector<U>& y_list, std::string format_string, std::string legend)
    {
        if(current_plots.size() == 0)
        {
            current_plots.push_back(cpl::Plot(x_list, y_list, format_string, legend));
            active_plot = current_plots.size() - 1;
        }
        else
        {
            current_plots.at(active_plot).plot(x_list, y_list, format_string, legend);
        }
        return current_plots.at(active_plot);
    }

    template <typename T>       
    Plot& plot(std::vector<T>& y_list, std::string format_string, std::string legend)
    {
        if(current_plots.size() == 0)
        {
            current_plots.push_back(cpl::Plot(y_list, format_string, legend));
            active_plot = current_plots.size() - 1;
        }
        else
        {
            current_plots.at(active_plot).plot(y_list, format_string, legend);
        }
        return current_plots.at(active_plot);
    }

    void figure(float window_width, float window_height)
    {
        current_plots.push_back(cpl::Plot(window_width, window_height));
        active_plot = current_plots.size() - 1;
    }

    void show()
    {
        for(int iii = 0; iii < current_plots.size(); iii++)
        {
            current_plots.at(iii).show();
        }
    }

    void save(std::string file_name)
    {
        current_plots.at(active_plot).save(file_name);
    }
}
