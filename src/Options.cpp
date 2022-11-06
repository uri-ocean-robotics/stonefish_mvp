
#include "stonefish_mvp/Options.h"
#include "iostream"


namespace sf {

void ArgParser::parse(int argc, char* argv[]) {

    std::string quality;

    int opt;
    while((opt = getopt(argc, argv, "d:s:r:n:h:w:")) != -1) {
        switch (opt) {
            case 'd':
                argOptions.dataDir = std::string(optarg) + "/";
                break;
            case 's':
                argOptions.scenarioPath = std::string(optarg);
                break;
            case 'n':
                quality = std::string(optarg);
                break;
            case 'r':
                argOptions.simulationRate = std::stod(optarg);
                break;
            case 'h':
                argOptions.renderSettings.windowH = std::stod(optarg);
                break;
            case 'w':
                argOptions.renderSettings.windowW = std::stod(optarg);
                break;
            case '?':
                std::cerr <<"Error in option -" << optopt << std::endl;
            default:
                // todo: abort()?
                break;

        }
    }

    if(quality == "low")
    {
        argOptions.renderSettings.shadows = sf::RenderQuality::LOW;
        argOptions.renderSettings.ao = sf::RenderQuality::DISABLED;
        argOptions.renderSettings.atmosphere = sf::RenderQuality::LOW;
        argOptions.renderSettings.ocean = sf::RenderQuality::LOW;
        argOptions.renderSettings.aa = sf::RenderQuality::LOW;
        argOptions.renderSettings.ssr = sf::RenderQuality::DISABLED;
    }
    else if(quality == "high")
    {
        argOptions.renderSettings.shadows = sf::RenderQuality::HIGH;
        argOptions.renderSettings.ao = sf::RenderQuality::HIGH;
        argOptions.renderSettings.atmosphere = sf::RenderQuality::HIGH;
        argOptions.renderSettings.ocean = sf::RenderQuality::HIGH;
        argOptions.renderSettings.aa = sf::RenderQuality::HIGH;
        argOptions.renderSettings.ssr = sf::RenderQuality::HIGH;
    }
    else // "medium"
    {
        argOptions.renderSettings.shadows = sf::RenderQuality::MEDIUM;
        argOptions.renderSettings.ao = sf::RenderQuality::MEDIUM;
        argOptions.renderSettings.atmosphere = sf::RenderQuality::MEDIUM;
        argOptions.renderSettings.ocean = sf::RenderQuality::MEDIUM;
        argOptions.renderSettings.aa = sf::RenderQuality::MEDIUM;
        argOptions.renderSettings.ssr = sf::RenderQuality::MEDIUM;
    }

    argOptions.helperSettings.showFluidDynamics = false;
    argOptions.helperSettings.showCoordSys = false;
    argOptions.helperSettings.showBulletDebugInfo = false;
    argOptions.helperSettings.showSensors = false;
    argOptions.helperSettings.showActuators = false;
    argOptions.helperSettings.showForces = false;


}

ArgOptions ArgParser::getOptions() {
    return argOptions;
}



}