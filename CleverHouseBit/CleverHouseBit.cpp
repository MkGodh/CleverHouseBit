#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

enum switches
{
    lights_inside = 1,
    lights_outside = 2,
    heaters = 4,
    water_pipe_heating = 8,
    conditioner = 16
};

int main()
{
    bool totalLight = false;
    double current_time = 14.00;
    int day = 0;
    int colourTemperature = 5000;
    int tempertureIn = 0;
    int temperateOut = 0;
    int switches_state = 0;
    std::string move;
    std::string lights;
    std::string indicators;

    do {
        std::cout << "Temperature inside, temperature outside, movement, lights: " << std::endl;
        std::getline(std::cin, indicators);
        std::stringstream buffer(indicators);
        buffer >> tempertureIn >> temperateOut >> move >> lights;

        if (lights == "on" && !(switches_state & lights_inside))
        {
            if (!totalLight)
            {
                std::cout << "Lights ON!" << std::endl;
                std::cout << "Lights inside ON!" << std::endl;
                totalLight = true;
            }
        }
        else if (lights == "off" && (switches_state & water_pipe_heating)) {
            totalLight = false;
            std::cout << "Lights OFF!" << std::endl;
            std::cout << "Lights inside OFF!" << std::endl;
        }

        if (temperateOut < 0 && !(switches_state & water_pipe_heating))
        {
            switches_state |= water_pipe_heating;
            std::cout << "Water pipe heat ON!" << std::endl;

        }

        else if (temperateOut > 5 && (switches_state & water_pipe_heating))
        {
            switches_state &= ~water_pipe_heating;
            std::cout << "Water pipe heat OFF!" << std::endl;

        }

        if (((current_time >= 16.00 && current_time <= 24.00)
            || (current_time >= 00.00 && current_time <= 05.00)) && move == "yes" &&
            (switches_state & lights_outside))
        {
            switches_state |= lights_outside;
            std::cout << "Lights outside ON!" << std::endl;

        }
        else if (switches_state & lights_outside)
        {
            switches_state &= ~lights_outside;
            std::cout << "Lights outside OFF!" << std::endl;
        }

        if (tempertureIn < 22 && !(switches_state & heaters))
        {
            switches_state |= heaters;
            std::cout << "Heaters ON!" << std::endl;

        }
        else if (tempertureIn > 25 && (switches_state & heaters))
        {
            switches_state &= ~heaters;
            std::cout << "Heaters OFF!" << std::endl;
        }

        if (tempertureIn >= 30 && !(switches_state & conditioner))
        {
            switches_state |= conditioner;
            std::cout << "Conditioner ON!" << std::endl;

        }

        else if (tempertureIn <= 25 && (switches_state & conditioner))
        {
            switches_state &= ~conditioner;
            std::cout << "Conditioner OFF!" << std::endl;

        }

        if (current_time >= 16.00 && current_time <= 20.00 &&
            lights == "on")
        {
            colourTemperature = 2700;
            std::cout << "Colour temperature: " << colourTemperature << 'k' << std::endl;
        }

        else if (current_time >= 00.00 && current_time < 16.00 &&
            lights == "on")
        {
            colourTemperature = 5000;
            std::cout << "Colour temperature: " << colourTemperature << 'k' << std::endl;
        }

        current_time += 1.00;
        if (current_time >= 24.00) {
            day++;
            current_time = 0.00;
        }
        std::cout << std::fixed << std::setprecision(2) << std::setw(5) << std::setfill('0')
            << "Current time: " << current_time << std::endl;

    } while (day <= 2);

    return 0;

}

