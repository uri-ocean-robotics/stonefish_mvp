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
//  parsed_simulator_nogpu.cpp
//  stonefish_mvp
//
//  Created by Patryk Cieslak on 16/12/20.
//  Copyright (c) 2020 Patryk Cieslak. All rights reserved.
//

#include "ros/ros.h"
#include "Stonefish/core/ConsoleSimulationApp.h"
#include "Stonefish/utils/SystemUtil.hpp"

#include "stonefish_mvp/ROSSimulationManager.h"
#include "stonefish_mvp/Options.h"

int main(int argc, char **argv)
{

    sf::ArgParser argParser;

    argParser.parse(argc, argv);

	ros::init(argc, argv, "parsed_simulator_nogpu", ros::init_options::NoSigintHandler);

	sf::ROSSimulationManager manager(
        argParser.getOptions().simulationRate,
        argParser.getOptions().scenarioPath);
    sf::ConsoleSimulationApp app(
        "Stonefish Simulator",
        argParser.getOptions().dataDir,
        &manager);
	app.Run();

	return 0;
}
