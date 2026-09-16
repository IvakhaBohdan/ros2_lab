#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "rclcpp_lifecycle/lifecycle_node.hpp"

using CallbackReturn = rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn;

class ManagedNode : public rclcpp_lifecycle::LifecycleNode {
public:
   explicit ManagedNode(const std::string & node_name)
   : LifecycleNode(node_name) {}

   CallbackReturn on_configure(const rclcpp_lifecycle::State &) override {
     RCLCPP_INFO(get_logger(), "State transition: [Unconfigured] -> [Inactive]");
     return CallbackReturn::SUCCESS;
   }

   CallbackReturn on_activate(const rclcpp_lifecycle::State & state) override {
     LifecycleNode::on_activate(state);
     RCLCPP_INFO(get_logger(), "State transition: [Inactive] -> [Active]");
     return CallbackReturn::SUCCESS;
    }

   CallbackReturn on_deactivate(const rclcpp_lifecycle::State & state) override {
      LifecycleNode::on_deactivate(state);
      RCLCPP_INFO(get_logger(), "State transition: [Active] -> [Inactive]");
      return CallbackReturn::SUCCESS;
    }

    CallbackReturn on_cleanup(const rclcpp_lifecycle::State &) override {
       RCLCPP_INFO(get_logger(), "State transition: [Inactive] -> [Unconfigured]");
       return CallbackReturn::SUCCESS;
    }
  };

int main(int argc, char ** argv) {
   rclcpp::init(argc, argv);
   auto exec = std::make_shared<rclcpp::executors::SingleThreadedExecutor>();

   auto node1 = std::make_shared<ManagedNode>("lifecycle_node_1");
   auto node2 = std::make_shared<ManagedNode>("lifecycle_node_2");

   exec->add_node(node1->get_node_base_interface());
   exec->add_node(node2->get_node_base_interface());

   exec->spin();
   rclcpp::shutdown();

   return 0;
  }
