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
//  ROSSimulationManager.h
//  stonefish_mvp
//
//  Created by Patryk Cieslak on 17/09/19.
//  Copyright (c) 2019-2021 Patryk Cieslak. All rights reserved.
//

#ifndef __Stonefish_ROSSimulationManager__
#define __Stonefish_ROSSimulationManager__

//Stonefish
#include <Stonefish/core/SimulationManager.h>
#include <Stonefish/actuators/VariableBuoyancy.h>
#include <Stonefish/actuators/Servo.h>
#include <Stonefish/actuators/Thruster.h>
#include <Stonefish/actuators/Propeller.h>
#include <Stonefish/actuators/Rudder.h>
#include <Stonefish/actuators/Light.h>

//ROS
#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <std_msgs/Bool.h>
#include <std_msgs/Float64.h>
#include <std_msgs/Float64MultiArray.h>
#include <geometry_msgs/Vector3.h>
#include <geometry_msgs/Transform.h>
#include <sensor_msgs/JointState.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/CameraInfo.h>
#include <nav_msgs/Odometry.h>
// #include <cola2_msgs/Setpoints.h>
#include <std_srvs/Trigger.h>
#include <std_srvs/SetBool.h>
#include <stonefish_mvp/SonarSettings.h>
#include <stonefish_mvp/SonarSettings2.h>
#include <image_transport/image_transport.h>
#include <rosgraph_msgs/Clock.h>
#include "stonefish_mvp/ROSControlInterface.h"

namespace sf
{

    struct ROSActuator
    {


        Scalar setPoint;

        Actuator* actuator;

        std::string rosSubTopicName;

        ROSActuator(Actuator* actuator) :
            actuator(actuator), setPoint(Scalar(0))
        {
            rosSubTopicName = std::string("control/" + actuator->getName());
        }

        void applySetPoint()
        {
            switch(actuator->getType()) {
                case ActuatorType::THRUSTER:
                    ((Thruster*)actuator)->setSetpoint(setPoint);
                    break;
                case ActuatorType::PROPELLER:
                    ((Propeller*)actuator)->setSetpoint(setPoint);
                    break;
                case ActuatorType::RUDDER:
                    ((Rudder*)actuator)->setSetpoint(setPoint);
                    break;
                    // TODO: how should I control the VBS?
                case ActuatorType::VBS:
                    break;
                default:
                    break;
            }
        }

        void callback(const std_msgs::Float64ConstPtr& msg)
        {
            setPoint = msg->data;
        }

    };

    class ColorCamera;
    class DepthCamera;
    class Multibeam2;
    class FLS;
    class SSS;
    class MSIS;
    class SuctionCup;
    class ManualTrajectory;
    class Uniform;
    class Jet;

    struct ROSRobot
    {
        Robot* robot;
        bool publishBaseLinkTransform;
        std::vector<Scalar> thrusterSetpoints;
        std::vector<Scalar> propellerSetpoints;
        std::vector<Scalar> rudderSetpoints;
        std::map<std::string, std::pair<ServoControlMode, Scalar>> servoSetpoints;

        std::vector<ROSActuator> rosActuators;

        ROSRobot(Robot* robot) : robot(robot), publishBaseLinkTransform(false)
        {

            unsigned int aID = 0;
            Actuator* actuator;
            while((actuator = robot->getActuator(aID++)) != nullptr)
            {
                rosActuators.emplace_back(ROSActuator(actuator));
            }
        }
    };

    // A class....
    class ROSSimulationManager : public SimulationManager
    {
    public:
        ROSSimulationManager(Scalar stepsPerSecond, std::string scenarioFilePath);
        virtual ~ROSSimulationManager();

        virtual void BuildScenario();
        virtual void DestroyScenario();

        void AddROSRobot(ROSRobot* robot);

        virtual void SimulationStepCompleted(Scalar timeStep);
        virtual void ColorCameraImageReady(ColorCamera* cam);
        virtual void DepthCameraImageReady(DepthCamera* cam);
        virtual void Multibeam2ScanReady(Multibeam2* mb);
        virtual void FLSScanReady(FLS* fls);
        virtual void SSSScanReady(SSS* sss);
        virtual void MSISScanReady(MSIS* sss);

        bool EnableCurrents(std_srvs::Trigger::Request &req, std_srvs::Trigger::Response &res);
        bool DisableCurrents(std_srvs::Trigger::Request &req, std_srvs::Trigger::Response &res);

        virtual uint64_t getSimulationClock();
        virtual void SimulationClockSleep(uint64_t us);
        ros::NodeHandle& getNodeHandle();
        image_transport::ImageTransport& getImageTransportHandle();
        std::map<std::string, ros::ServiceServer>& getServiceServers();
        std::map<std::string, ros::Publisher>& getPublishers();
        std::map<std::string, image_transport::Publisher>& getImagePublishers();
        std::map<std::string, ros::Subscriber>& getSubscribers();
        std::map<std::string, std::pair<sensor_msgs::ImagePtr, sensor_msgs::CameraInfoPtr>>& getCameraMsgPrototypes();
        std::map<std::string, std::pair<sensor_msgs::ImagePtr, sensor_msgs::ImagePtr>>& getSonarMsgPrototypes();
        std::vector<ROSControlInterface*>& getControlInterfaces();

    protected:
        std::string scnFilePath;
        ros::NodeHandle nh;
        ros::AsyncSpinner spinner;
        image_transport::ImageTransport it;
        tf::TransformBroadcaster br;
        ros::ServiceServer srvECurrents, srvDCurrents;
        std::map<std::string, ros::ServiceServer> srvs;
        std::map<std::string, ros::Publisher> pubs;
        std::map<std::string, image_transport::Publisher> imgPubs;
        std::map<std::string, ros::Subscriber> subs;
        std::map<std::string, std::pair<sensor_msgs::ImagePtr, sensor_msgs::CameraInfoPtr>> cameraMsgPrototypes;
        std::map<std::string, std::pair<sensor_msgs::ImagePtr, sensor_msgs::ImagePtr>> sonarMsgPrototypes;
        std::vector<ROSRobot*> rosRobots;
        std::vector<ROSControlInterface*> controlIfs;
        std::string scenarioDescrption;

        ros::Publisher clockPub;

        uint64_t simTime;
    };

    //Callback functors
    class UniformVFCallback
    {
    public:
        UniformVFCallback(Uniform* vf);
        void operator()(const geometry_msgs::Vector3ConstPtr& msg);

    private:
        Uniform* vf;
    };

    class JetVFCallback
    {
    public:
        JetVFCallback(Jet* vf);
        void operator()(const std_msgs::Float64ConstPtr& msg);

    private:
        Jet* vf;
    };

    class ServosCallback
    {
    public:
        ServosCallback(ROSSimulationManager* sm, ROSRobot* robot);
        void operator()(const sensor_msgs::JointStateConstPtr& msg);

    private:
        ROSSimulationManager* sm;
        ROSRobot* robot;
    };

    class JointGroupCallback
    {
    public:
        JointGroupCallback(ROSSimulationManager* sm, ROSRobot* robot,
                           ServoControlMode mode, const std::vector<std::string>& jointNames);
        void operator()(const std_msgs::Float64MultiArrayConstPtr& msg);

    private:
        ROSSimulationManager* sm;
        ROSRobot* robot;
        ServoControlMode mode;
        std::vector<std::string> jointNames;
    };

    class JointCallback
    {
    public:
        JointCallback(ROSSimulationManager* sm, ROSRobot* robot,
                      ServoControlMode mode, const std::string& jointName);
        void operator()(const std_msgs::Float64ConstPtr& msg);

    private:
        ROSSimulationManager* sm;
        ROSRobot* robot;
        ServoControlMode mode;
        std::string jointName;
    };

    class VBSCallback
    {
    public:
        VBSCallback(VariableBuoyancy* act);
        void operator()(const std_msgs::Float64ConstPtr& msg);

    private:
        VariableBuoyancy* act;
    };

    class TrajectoryCallback
    {
    public:
        TrajectoryCallback(ManualTrajectory* tr);
        void operator()(const nav_msgs::OdometryConstPtr& msg);

    private:
        ManualTrajectory* tr;
    };

    class ActuatorOriginCallback
    {
    public:
        ActuatorOriginCallback(Actuator* act);
        void operator()(const geometry_msgs::TransformConstPtr& msg);

    private:
        Actuator* act;
    };

    class SensorOriginCallback
    {
    public:
        SensorOriginCallback(Sensor* sens);
        void operator()(const geometry_msgs::TransformConstPtr& msg);

    private:
        Sensor* sens;
    };

    class FLSService
    {
    public:
        FLSService(FLS* fls);
        bool operator()(stonefish_mvp::SonarSettings::Request& req, stonefish_mvp::SonarSettings::Response& res);

    private:
        FLS* fls;
    };

    class SSSService
    {
    public:
        SSSService(SSS* sss);
        bool operator()(stonefish_mvp::SonarSettings::Request& req, stonefish_mvp::SonarSettings::Response& res);

    private:
        SSS* sss;
    };

    class MSISService
    {
    public:
        MSISService(MSIS* msis);
        bool operator()(stonefish_mvp::SonarSettings2::Request& req, stonefish_mvp::SonarSettings2::Response& res);

    private:
        MSIS* msis;
    };


	class SuctionCupService
	{
	public:
		SuctionCupService(SuctionCup* suction);
		bool operator()(std_srvs::SetBool::Request& req, std_srvs::SetBool::Response& res);

	private:
		SuctionCup* suction;
	};
}

#endif
