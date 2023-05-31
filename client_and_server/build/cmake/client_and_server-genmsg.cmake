# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "client_and_server: 0 messages, 1 services")

set(MSG_I_FLAGS "-Istd_msgs:/opt/ros/noetic/share/std_msgs/cmake/../msg;-Inav_msgs:/opt/ros/noetic/share/nav_msgs/cmake/../msg;-Igeometry_msgs:/opt/ros/noetic/share/geometry_msgs/cmake/../msg;-Iactionlib_msgs:/opt/ros/noetic/share/actionlib_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(client_and_server_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/qimao/catkin_ws/src/navigation/client_and_server/srv/capture_global_path.srv" NAME_WE)
add_custom_target(_client_and_server_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "client_and_server" "/home/qimao/catkin_ws/src/navigation/client_and_server/srv/capture_global_path.srv" "geometry_msgs/Point:geometry_msgs/Quaternion:std_msgs/Header:geometry_msgs/PoseStamped:nav_msgs/Path:geometry_msgs/Pose"
)

#
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
#

### Section generating for lang: gencpp
### Generating Messages

### Generating Services
_generate_srv_cpp(client_and_server
  "/home/qimao/catkin_ws/src/navigation/client_and_server/srv/capture_global_path.srv"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/PoseStamped.msg;/opt/ros/noetic/share/nav_msgs/cmake/../msg/Path.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Pose.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/client_and_server
)

### Generating Module File
_generate_module_cpp(client_and_server
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/client_and_server
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(client_and_server_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(client_and_server_generate_messages client_and_server_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/qimao/catkin_ws/src/navigation/client_and_server/srv/capture_global_path.srv" NAME_WE)
add_dependencies(client_and_server_generate_messages_cpp _client_and_server_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(client_and_server_gencpp)
add_dependencies(client_and_server_gencpp client_and_server_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS client_and_server_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages

### Generating Services
_generate_srv_eus(client_and_server
  "/home/qimao/catkin_ws/src/navigation/client_and_server/srv/capture_global_path.srv"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/PoseStamped.msg;/opt/ros/noetic/share/nav_msgs/cmake/../msg/Path.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Pose.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/client_and_server
)

### Generating Module File
_generate_module_eus(client_and_server
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/client_and_server
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(client_and_server_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(client_and_server_generate_messages client_and_server_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/qimao/catkin_ws/src/navigation/client_and_server/srv/capture_global_path.srv" NAME_WE)
add_dependencies(client_and_server_generate_messages_eus _client_and_server_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(client_and_server_geneus)
add_dependencies(client_and_server_geneus client_and_server_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS client_and_server_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages

### Generating Services
_generate_srv_lisp(client_and_server
  "/home/qimao/catkin_ws/src/navigation/client_and_server/srv/capture_global_path.srv"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/PoseStamped.msg;/opt/ros/noetic/share/nav_msgs/cmake/../msg/Path.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Pose.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/client_and_server
)

### Generating Module File
_generate_module_lisp(client_and_server
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/client_and_server
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(client_and_server_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(client_and_server_generate_messages client_and_server_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/qimao/catkin_ws/src/navigation/client_and_server/srv/capture_global_path.srv" NAME_WE)
add_dependencies(client_and_server_generate_messages_lisp _client_and_server_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(client_and_server_genlisp)
add_dependencies(client_and_server_genlisp client_and_server_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS client_and_server_generate_messages_lisp)

### Section generating for lang: gennodejs
### Generating Messages

### Generating Services
_generate_srv_nodejs(client_and_server
  "/home/qimao/catkin_ws/src/navigation/client_and_server/srv/capture_global_path.srv"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/PoseStamped.msg;/opt/ros/noetic/share/nav_msgs/cmake/../msg/Path.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Pose.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/client_and_server
)

### Generating Module File
_generate_module_nodejs(client_and_server
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/client_and_server
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(client_and_server_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(client_and_server_generate_messages client_and_server_generate_messages_nodejs)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/qimao/catkin_ws/src/navigation/client_and_server/srv/capture_global_path.srv" NAME_WE)
add_dependencies(client_and_server_generate_messages_nodejs _client_and_server_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(client_and_server_gennodejs)
add_dependencies(client_and_server_gennodejs client_and_server_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS client_and_server_generate_messages_nodejs)

### Section generating for lang: genpy
### Generating Messages

### Generating Services
_generate_srv_py(client_and_server
  "/home/qimao/catkin_ws/src/navigation/client_and_server/srv/capture_global_path.srv"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/PoseStamped.msg;/opt/ros/noetic/share/nav_msgs/cmake/../msg/Path.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Pose.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/client_and_server
)

### Generating Module File
_generate_module_py(client_and_server
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/client_and_server
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(client_and_server_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(client_and_server_generate_messages client_and_server_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/qimao/catkin_ws/src/navigation/client_and_server/srv/capture_global_path.srv" NAME_WE)
add_dependencies(client_and_server_generate_messages_py _client_and_server_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(client_and_server_genpy)
add_dependencies(client_and_server_genpy client_and_server_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS client_and_server_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/client_and_server)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/client_and_server
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(client_and_server_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()
if(TARGET nav_msgs_generate_messages_cpp)
  add_dependencies(client_and_server_generate_messages_cpp nav_msgs_generate_messages_cpp)
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/client_and_server)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/client_and_server
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_eus)
  add_dependencies(client_and_server_generate_messages_eus std_msgs_generate_messages_eus)
endif()
if(TARGET nav_msgs_generate_messages_eus)
  add_dependencies(client_and_server_generate_messages_eus nav_msgs_generate_messages_eus)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/client_and_server)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/client_and_server
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(client_and_server_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()
if(TARGET nav_msgs_generate_messages_lisp)
  add_dependencies(client_and_server_generate_messages_lisp nav_msgs_generate_messages_lisp)
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/client_and_server)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/client_and_server
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_nodejs)
  add_dependencies(client_and_server_generate_messages_nodejs std_msgs_generate_messages_nodejs)
endif()
if(TARGET nav_msgs_generate_messages_nodejs)
  add_dependencies(client_and_server_generate_messages_nodejs nav_msgs_generate_messages_nodejs)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/client_and_server)
  install(CODE "execute_process(COMMAND \"/usr/bin/python3\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/client_and_server\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/client_and_server
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(client_and_server_generate_messages_py std_msgs_generate_messages_py)
endif()
if(TARGET nav_msgs_generate_messages_py)
  add_dependencies(client_and_server_generate_messages_py nav_msgs_generate_messages_py)
endif()
