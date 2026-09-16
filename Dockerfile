FROM ros:humble-ros-base
ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update && apt-get install -y \
apt-utils \
  ros-humble-rclcpp-components \
  ros-humble-rclcpp-lifecycle \
  && rm -rf /var/lib/apt/lists/*
WORKDIR /ros2_ws
COPY entrypoint.sh /entrypoint.sh
RUN chmod +x /entrypoint.sh
ENTRYPOINT ["/entrypoint.sh"]
CMD ["bash"]
