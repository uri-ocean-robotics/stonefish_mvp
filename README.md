# Stonefish Wrapper for ROS-MVP

Stonefish simulator provides a versitale, capable, and modern alternative to UUV simulator. It's installation and usage is pretty straight forward. The documentation for the stonefish library resides at https://stonefish.readthedocs.io/.

Stonefish simulator is shipped as a library. It's core functionality doesn't depend on ROS. It requires a wrapper executable to run. This repository contains wrapper for stonefish, forked from original [stonefish_ros](https://github.com/patrykcieslak/stonefish_ros) repository. This repository is maintained by University of Rhode Island Smart Ocean Systems Laboratory.

**Attention**: This package is a modified version of stonefish_ros repository.

This package delivers a ROS interface for the _Stonefish_ library. It also includes a standard simulator node, which loads the simulation scenario from a scenario description file (XML). The included parser extends the standard functionality of the _Stonefish_ library to enable ROS style search for files, resolution of arguments as well as a complete message interface.

The original stonefish_ros package depends on [open-access & proprietary](https://bitbucket.org/iquarobotics/cola2_msgs/src/master/LICENSE.txt) `cola2_msgs` package. Stonefish MVP package offers an alternative stonefish simulator wrapper that doesn't depend on proprietary packages.

## Documentation

Documentation for stonefish_mvp resides at https://uri-ocean-robotics.github.io/stonefish_mvp

## Credits

The source code for `stonefish_ros` package is at https://github.com/patrykcieslak/stonefish_ros.

Stonefish simulator software and stonefish_ros wrapper were written and is continuously developed by **Patryk Cieślak**.

If you find this software useful in your research, please cite:

*Patryk Cieślak, "Stonefish: An Advanced Open-Source Simulation Tool Designed for Marine Robotics, With a ROS Interface", In Proceedings of MTS/IEEE OCEANS 2019, June 2019, Marseille, France*
```
@inproceedings{stonefish,
   author = {Cie{\'s}lak, Patryk},
   booktitle = {OCEANS 2019 - Marseille},
   title = {{Stonefish: An Advanced Open-Source Simulation Tool Designed for Marine Robotics, With a ROS Interface}},
   month = jun,
   year = {2019},
   doi={10.1109/OCEANSE.2019.8867434}}
```
### Funding
This work was part of a project titled ”Force/position control system to enable compliant manipulation from a floating I-AUV”, which received funding from the European Community H2020 Programme, under the Marie Sklodowska-Curie grant agreement no. 750063. The work was continued under a project titled ”EU Marine Robots”, which received funding from the European Community H2020 Programme, grant agreement no. 731103.

### License
This is free software, published under the General Public License v3.0.
