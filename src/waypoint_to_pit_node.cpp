#include "ros/ros.h"
#include "helper.cpp"
#include <vector>
#include <iostream>
#include <string>
#include "geometry_msgs/PolygonStamped.h"
#include <waypoint_pit_planner/waypoints.h>

using namespace std;

/* The way point genenerator works as a service

*/

#define RESOLUTION = 0.5;
#define OFFSET = 0.25

		static int robot_x;
		static int robot_y;
		string MAP_FILE2 = "";

void getODOM(const geometry_msgs::PolygonStamped::ConstPtr& msg){
			robot_x = (msg->polygon.points[0].x - .25)/.5; //check
			robot_y	= (msg->polygon.points[0].y - .25)/.5 ; //check
}


bool g_wp(waypoint_pit_planner::waypoints::Request &req, waypoint_pit_planner::waypoints::Response &res){
			
			
			//ros::param::get("map_location", MAP_FILE);	
		
			helper test;

			test.set_location(-1*robot_y,robot_x);
			cout<<"No. of Waypoint Generated"<<test.list_wp.size() <<endl;
		    res.wp_received = test.func();
		    res.mission_flag = test.get_reached_edge_status();
			if (res.wp_received ){
				res.y = (-1 * (.5*test.list_wp[test.list_wp.size() -1 ].x))+.25;
				res.x = (.5*test.list_wp[test.list_wp.size() -1 ].y)+.25;
				cout<<"Way Point to edge Generated"<<  res.x << " " << res.y <<endl;
				return true;
			}
			else if (res.mission_flag){
				return true;
			}
			return false;


}


int main(int argc, char **argv){

	ros::init(argc,argv, "waypoint_pit_planner_server");
		ros::Subscriber sub;
		ros::ServiceServer service;
		ros::NodeHandle n;

	//ros::param::get("map_location", MAP_FILE);
		//n.getParam("map_location", MAP_FILE2);
	//cout<< MAP_FILE2 <<"bidu"<<endl;
					service = n.advertiseService("gen_wp2pit", g_wp);
			sub = n.subscribe("/move_base/local_costmap/footprint", 10, getODOM);
	ros::spin();

	return 0;
}


// class WPGEN{
// 	public:
// 		static int robot_x;
// 		static int robot_y;
// 		ros::Subscriber sub;
// 		ros::ServiceServer service;
// 		ros::NodeHandle n;

// 		WPGEN(){
// 			// service = n.advertiseService("gen_wp2pit", this->g_wp);
// 			sub = n.subscribe("/move_base/local_costmap/footprint", 10, this->getODOM);
// 			//this->n = nh;
// 		}

// 		void getODOM(geometry_msgs::PoseStamped::ConstPtr& msg){
// 			// robot_x = (msg->pose.position.x - 2.5)/5; //check
// 			// robot_y	= (msg->pose.position.y - 2.5)/5; //check
// 		}


// 		static bool g_wp(waypoint_pit_planner::waypoints::Request &req, waypoint_pit_planner::waypoints::Response &res){
// 			// ros::NodeHandle n;

// 			helper test;

// 			// test.set_location(0,0);//robot_x,robot_y);

// 		 //    res.wp_received = test.func();
// 		 //    res.mission_flag = test.get_reached_edge_status();
// 			// res.wp_received = true;
// 			// if (res.wp_received ){
// 			// 	res.x = test.list_wp[test.list_wp.size() -1 ].x;
// 			// 	res.y = test.list_wp[test.list_wp.size() -1 ].y;
// 			// 	return false;
// 			// }
// 			// else if (res.mission_flag){
// 			// 	return true;
// 			// }
// 			return false;

// 		}

// 		void run(){
// 			// ros::NodeHandle n;

// 		ros::spin();
// 		}

// };





// #include <iostream>
// #include "helper.h"

// using namespace std;
// int main() {
//     helper test;
//     bool reply = test.func();
//     for(auto elem:test.list_wp){
//         cout<<elem.x<< " " <<elem.y<<endl;
//     }
//     vector<vector<char>> map_char;// = vector<>(20, );

//     vector<char> seg = vector<char>(20,'1');
//     map_char = vector<vector<char>>(20,seg );

//     for(int i = 0; i<map_char.size();i++){
//         for(int j = 0; j<map_char[0].size();j++){
//             map_char[i][j] =  (test.map[i][j]) == 0?'0':'1';
//         }
//     }

//     for(auto elem:test.list_wp){

//             map_char[elem.x][elem.y] = '@';
//     }

//     for(int i = 0; i<map_char.size();i++){
//         for(int j = 0; j<map_char[0].size();j++){
//             cout<<" "<<map_char[i][j] << " ";
//         }
//         cout<<endl;
//     }

// }
