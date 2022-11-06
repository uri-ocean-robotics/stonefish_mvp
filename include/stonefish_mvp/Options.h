#pragma once

#include "cstdio"
#include "cstdlib"
#include "unistd.h"
#include "string"
#include "Stonefish/utils/SystemUtil.hpp"

namespace sf {

    struct ArgOptions {

        //! @brief Data Directory
        std::string dataDir;

        //! @brief Scenario file path
        std::string scenarioPath;

        //! @brief Simulation rate
        sf::Scalar simulationRate;

        sf::RenderSettings renderSettings;

        sf::HelperSettings helperSettings;
    };

    class ArgParser {
        private:
            ArgOptions argOptions;

        public:
            ArgParser() = default;

            void parse(int argc, char* argv[]);

            ArgOptions getOptions();

    };
}