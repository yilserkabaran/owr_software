/*

This service logs the calls from the husky's encoders
Created by Harry J E Day for BlueSat UNSW

Date 22/03/2014
*/

#include "ros/ros.h"
#include "sensor_msgs/JointState.h"
#define FLOAT_BYTES 4
#define logFolder "~/logs/"
#define logName "encoders.txt"

FILE logFile;
void writeLog(const char* message);

void reciveMsg(const sensor_msgs::JointState::ConstPtr& msg) {
    
    assert(msg);
    
    ROS_INFO("recived a message");
    const int arraySize = 4 ;
    
    int count = 0;
    
    std::ostringstream streamHeader;
    streamHeader << "name";
    streamHeader << "\t";
    streamHeader << "positon";
    streamHeader << "\t";
    streamHeader << "velocity";
    streamHeader << "\t";
    streamHeader << "effort";
    std::string messageHeader(streamHeader.str());
    ROS_INFO(messageHeader.c_str());
    bool error = false;
    
    
    while((count < arraySize) && !error) {
        error = false;
        std::ostringstream stream;
        if(msg->name.size() != 0) {
            stream << msg->name[count];
            stream << "\t";
        } else {  
            error = true;
        }
        if(msg->position.size() != 0) {
            stream << msg->position[count];
            stream << "\t";
        } else {  
            error = true;
        }   
        if(msg->velocity.size() != 0) {
            stream << msg->velocity[count];
            stream << "\t";
        } else {  
            error = true;
        }
        if(msg->effort.size() != 0) {
            stream << msg->effort[count];
         
        } else {  
            error = true;
        }
        
        if(!error) {
            std::string message(stream.str());
            ROS_INFO(message.c_str());
        }
        count++;
    }
    ROS_INFO((const char*) msg->name[0].c_str());
}

int main(int argc, char** argv) {
    
    //init log
    
   // logFile = fopen(strcpy(logFolder,logName), "a");
    

    //initialise the ros package
    ros::init(argc, argv, "encoderLogger");

    //a nodehandler is used to communiate with the rest of ros
    ros::NodeHandle n;

    //pass the void that is called when a message is recived
    ros::Subscriber sub = n.subscribe("/joint_states", 1000, reciveMsg);

    //loop with callbacks
    ros::spin();

    return 0;
}

void writeLog(const char* message) {
    //fprintf(logFile, "%s %c",message, '\n');
}
