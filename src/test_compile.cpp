#include<vector>
#include <cmath>

#include <SFML/Graphics.hpp>

#include<subplot.hpp>
// #include <plot.hpp>

using namespace std;

int main()
{
    vector<double> x;
    vector<double> y;
    vector<double> y2;
    for (int iii = 0; iii < 200; iii++)
    {
        double v = (static_cast<double>(iii)/100.0)*3.14;
        double s = sin(v);
        double s2 = cos(v);
        x.push_back(v);
        y.push_back(s);
        y2.push_back(s2);
    }
    cpl::Subplot plt(1.0);
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8; // 8xMSAA
    plt.addPlotdata(x, y, "", "");
    plt.addPlotdata(x, y2, "", "");
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window", sf::Style::Default, settings);
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);
    sf::View view;
    // copied code form sfml-dev
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
            if(event.type == sf::Event::Resized)
            {
                // Resize the view 
                window.setView(view = sf::View(sf::FloatRect(0.0, 0.0, static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y))));
            }
        }

        // clear the window with black color
        window.clear(sf::Color::White);

        // draw everything here...
        // window.draw(...);
        plt.draw(&window);

        // end the current frame
        window.display();
    }
}