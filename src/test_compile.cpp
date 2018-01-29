#include<vector>
#include<subplot.hpp>
#include <cmath>

#include <SFML/Graphics.hpp>

using namespace std;

int main()
{
    vector<double> x;
    vector<double> y;
    for (int iii = 0; iii < 200; iii++)
    {
        double v = (static_cast<double>(iii)/100.0)*3.14;
        double s = sin(v);
        x.push_back(v);
        y.push_back(s);
    }
    cpl::Subplot<double, double> plt(1.0);
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    plt.addPlotdata(x, y, "", "");
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window", sf::Style::Default, settings);
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);
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