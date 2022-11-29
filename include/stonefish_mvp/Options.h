/*
    This file is a part of stonefish_mvp.

    stonefish_mvp is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    stonefish_mvp is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

//
//  parsed_simulator.cpp
//  stonefish_mvp
//
//  Created by Emir Cem Gezer on 12/06/19.
//  Copyright (c) 2022 Emir Cem Gezer. All rights reserved.
//

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