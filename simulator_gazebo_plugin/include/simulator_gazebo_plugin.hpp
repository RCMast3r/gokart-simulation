// Copyright 2022 Tomas Nagy
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef SIMULATOR_GAZEBO_PLUGIN__SIMULATOR_GAZEBO_PLUGIN_HPP_
#define SIMULATOR_GAZEBO_PLUGIN__SIMULATOR_GAZEBO_PLUGIN_HPP_

#include <gazebo/common/PID.hh>
#include <gazebo/common/Plugin.hh>
#include <rclcpp/rclcpp.hpp>

#include <nav_msgs/msg/odometry.hpp>
#include <simulator_msgs/msg/control_command.hpp>

#include <simulator_gazebo_joint.hpp>

namespace gokart_gazebo_plugin
{

class GokartGazeboPlugin : public gazebo::ModelPlugin
{
public:
  GokartGazeboPlugin();

  void Load(gazebo::physics::ModelPtr model, sdf::ElementPtr sdf);

private:
  void LoadParameters(sdf::ElementPtr sdf);

  void Update();

  using ControlCommand = simulator_msgs::msg::ControlCommand;
  using Odometry = nav_msgs::msg::Odometry;

  std::string base_link_name_;
  std::string fl_steering_joint_name_;
  std::string fr_steering_joint_name_;
  std::string rl_motor_joint_name_;
  std::string rr_motor_joint_name_;

  gazebo::physics::WorldPtr world_;
  gazebo::physics::ModelPtr model_;
  gazebo::physics::LinkPtr base_link_;

  gazebo::common::Time last_sim_time_;
  gazebo::common::Time last_update_time_;

  gazebo::event::ConnectionPtr update_connection_;

  gokart_gazebo_plugin::Joint front_left_steering = gokart_gazebo_plugin::Joint{};
  gokart_gazebo_plugin::Joint front_right_steering = gokart_gazebo_plugin::Joint{};
  gokart_gazebo_plugin::Joint rear_left_motor = gokart_gazebo_plugin::Joint{};
  gokart_gazebo_plugin::Joint rear_right_motor = gokart_gazebo_plugin::Joint{};

  double desired_steering_angle_;
  double desired_velocity_;

  rclcpp::Node::SharedPtr ros_node_;
  rclcpp::Subscription<ControlCommand>::SharedPtr control_command_sub_;
  rclcpp::Publisher<Odometry>::SharedPtr ground_truth_pub_;

  Odometry ground_truth_msg_ = Odometry();

};

}  // namespace gokart_gazebo_plugin

#endif  // SIMULATOR_GAZEBO_PLUGIN__GAZEBO_PLUGIN_HPP_
