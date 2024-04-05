# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "path_finding: 5 messages, 0 services")

set(MSG_I_FLAGS "-Ipath_finding:/home/ros/PIF/catkin_ws/src/path_finding/msg;-Istd_msgs:/opt/ros/noetic/share/std_msgs/cmake/../msg;-Igeometry_msgs:/opt/ros/noetic/share/geometry_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(path_finding_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/ros/PIF/catkin_ws/src/path_finding/msg/Grid.msg" NAME_WE)
add_custom_target(_path_finding_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "path_finding" "/home/ros/PIF/catkin_ws/src/path_finding/msg/Grid.msg" "geometry_msgs/Point"
)

get_filename_component(_filename "/home/ros/PIF/catkin_ws/src/path_finding/msg/GridArray.msg" NAME_WE)
add_custom_target(_path_finding_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "path_finding" "/home/ros/PIF/catkin_ws/src/path_finding/msg/GridArray.msg" "geometry_msgs/Point:path_finding/Grid"
)

get_filename_component(_filename "/home/ros/PIF/catkin_ws/src/path_finding/msg/GridStamped.msg" NAME_WE)
add_custom_target(_path_finding_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "path_finding" "/home/ros/PIF/catkin_ws/src/path_finding/msg/GridStamped.msg" "geometry_msgs/Point:std_msgs/Header:path_finding/GridArray:path_finding/Grid"
)

get_filename_component(_filename "/home/ros/PIF/catkin_ws/src/path_finding/msg/PoseWaste.msg" NAME_WE)
add_custom_target(_path_finding_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "path_finding" "/home/ros/PIF/catkin_ws/src/path_finding/msg/PoseWaste.msg" "geometry_msgs/Point"
)

get_filename_component(_filename "/home/ros/PIF/catkin_ws/src/path_finding/msg/PoseWasteStamped.msg" NAME_WE)
add_custom_target(_path_finding_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "path_finding" "/home/ros/PIF/catkin_ws/src/path_finding/msg/PoseWasteStamped.msg" "std_msgs/Header:path_finding/PoseWaste:geometry_msgs/Point"
)

#
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(path_finding
  "/home/ros/PIF/catkin_ws/src/path_finding/msg/Grid.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/path_finding
)
_generate_msg_cpp(path_finding
  "/home/ros/PIF/catkin_ws/src/path_finding/msg/GridArray.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/home/ros/PIF/catkin_ws/src/path_finding/msg/Grid.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/path_finding
)
_generate_msg_cpp(path_finding
  "/home/ros/PIF/catkin_ws/src/path_finding/msg/GridStamped.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/home/ros/PIF/catkin_ws/src/path_finding/msg/GridArray.msg;/home/ros/PIF/catkin_ws/src/path_finding/msg/Grid.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/path_finding
)
_generate_msg_cpp(path_finding
  "/home/ros/PIF/catkin_ws/src/path_finding/msg/PoseWaste.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/path_finding
)
_generate_msg_cpp(path_finding
  "/home/ros/PIF/catkin_ws/src/path_finding/msg/PoseWasteStamped.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/home/ros/PIF/catkin_ws/src/path_finding/msg/PoseWaste.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/path_finding
)

### Generating Services

### Generating Module File
_generate_module_cpp(path_finding
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/path_finding
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(path_finding_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(path_finding_generate_messages path_finding_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/ros/PIF/catkin_ws/src/path_finding/msg/Grid.msg" NAME_WE)
add_dependencies(path_finding_generate_messages_cpp _path_finding_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ros/PIF/catkin_ws/src/path_finding/msg/GridArray.msg" NAME_WE)
add_dependencies(path_finding_generate_messages_cpp _path_finding_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ros/PIF/catkin_ws/src/path_finding/msg/GridStamped.msg" NAME_WE)
add_dependencies(path_finding_generate_messages_cpp _path_finding_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ros/PIF/catkin_ws/src/path_finding/msg/PoseWaste.msg" NAME_WE)
add_dependencies(path_finding_generate_messages_cpp _path_finding_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ros/PIF/catkin_ws/src/path_finding/msg/PoseWasteStamped.msg" NAME_WE)
add_dependencies(path_finding_generate_messages_cpp _path_finding_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(path_finding_gencpp)
add_dependencies(path_finding_gencpp path_finding_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS path_finding_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages
_generate_msg_eus(path_finding
  "/home/ros/PIF/catkin_ws/src/path_finding/msg/Grid.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/path_finding
)
_generate_msg_eus(path_finding
  "/home/ros/PIF/catkin_ws/src/path_finding/msg/GridArray.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/home/ros/PIF/catkin_ws/src/path_finding/msg/Grid.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/path_finding
)
_generate_msg_eus(path_finding
  "/home/ros/PIF/catkin_ws/src/path_finding/msg/GridStamped.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/home/ros/PIF/catkin_ws/src/path_finding/msg/GridArray.msg;/home/ros/PIF/catkin_ws/src/path_finding/msg/Grid.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/path_finding
)
_generate_msg_eus(path_finding
  "/home/ros/PIF/catkin_ws/src/path_finding/msg/PoseWaste.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/path_finding
)
_generate_msg_eus(path_finding
  "/home/ros/PIF/catkin_ws/src/path_finding/msg/PoseWasteStamped.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/home/ros/PIF/catkin_ws/src/path_finding/msg/PoseWaste.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/path_finding
)

### Generating Services

### Generating Module File
_generate_module_eus(path_finding
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/path_finding
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(path_finding_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(path_finding_generate_messages path_finding_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/ros/PIF/catkin_ws/src/path_finding/msg/Grid.msg" NAME_WE)
add_dependencies(path_finding_generate_messages_eus _path_finding_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ros/PIF/catkin_ws/src/path_finding/msg/GridArray.msg" NAME_WE)
add_dependencies(path_finding_generate_messages_eus _path_finding_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ros/PIF/catkin_ws/src/path_finding/msg/GridStamped.msg" NAME_WE)
add_dependencies(path_finding_generate_messages_eus _path_finding_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ros/PIF/catkin_ws/src/path_finding/msg/PoseWaste.msg" NAME_WE)
add_dependencies(path_finding_generate_messages_eus _path_finding_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ros/PIF/catkin_ws/src/path_finding/msg/PoseWasteStamped.msg" NAME_WE)
add_dependencies(path_finding_generate_messages_eus _path_finding_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(path_finding_geneus)
add_dependencies(path_finding_geneus path_finding_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS path_finding_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(path_finding
  "/home/ros/PIF/catkin_ws/src/path_finding/msg/Grid.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/path_finding
)
_generate_msg_lisp(path_finding
  "/home/ros/PIF/catkin_ws/src/path_finding/msg/GridArray.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/home/ros/PIF/catkin_ws/src/path_finding/msg/Grid.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/path_finding
)
_generate_msg_lisp(path_finding
  "/home/ros/PIF/catkin_ws/src/path_finding/msg/GridStamped.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/home/ros/PIF/catkin_ws/src/path_finding/msg/GridArray.msg;/home/ros/PIF/catkin_ws/src/path_finding/msg/Grid.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/path_finding
)
_generate_msg_lisp(path_finding
  "/home/ros/PIF/catkin_ws/src/path_finding/msg/PoseWaste.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/path_finding
)
_generate_msg_lisp(path_finding
  "/home/ros/PIF/catkin_ws/src/path_finding/msg/PoseWasteStamped.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/home/ros/PIF/catkin_ws/src/path_finding/msg/PoseWaste.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/path_finding
)

### Generating Services

### Generating Module File
_generate_module_lisp(path_finding
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/path_finding
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(path_finding_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(path_finding_generate_messages path_finding_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/ros/PIF/catkin_ws/src/path_finding/msg/Grid.msg" NAME_WE)
add_dependencies(path_finding_generate_messages_lisp _path_finding_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ros/PIF/catkin_ws/src/path_finding/msg/GridArray.msg" NAME_WE)
add_dependencies(path_finding_generate_messages_lisp _path_finding_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ros/PIF/catkin_ws/src/path_finding/msg/GridStamped.msg" NAME_WE)
add_dependencies(path_finding_generate_messages_lisp _path_finding_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ros/PIF/catkin_ws/src/path_finding/msg/PoseWaste.msg" NAME_WE)
add_dependencies(path_finding_generate_messages_lisp _path_finding_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ros/PIF/catkin_ws/src/path_finding/msg/PoseWasteStamped.msg" NAME_WE)
add_dependencies(path_finding_generate_messages_lisp _path_finding_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(path_finding_genlisp)
add_dependencies(path_finding_genlisp path_finding_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS path_finding_generate_messages_lisp)

### Section generating for lang: gennodejs
### Generating Messages
_generate_msg_nodejs(path_finding
  "/home/ros/PIF/catkin_ws/src/path_finding/msg/Grid.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/path_finding
)
_generate_msg_nodejs(path_finding
  "/home/ros/PIF/catkin_ws/src/path_finding/msg/GridArray.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/home/ros/PIF/catkin_ws/src/path_finding/msg/Grid.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/path_finding
)
_generate_msg_nodejs(path_finding
  "/home/ros/PIF/catkin_ws/src/path_finding/msg/GridStamped.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/home/ros/PIF/catkin_ws/src/path_finding/msg/GridArray.msg;/home/ros/PIF/catkin_ws/src/path_finding/msg/Grid.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/path_finding
)
_generate_msg_nodejs(path_finding
  "/home/ros/PIF/catkin_ws/src/path_finding/msg/PoseWaste.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/path_finding
)
_generate_msg_nodejs(path_finding
  "/home/ros/PIF/catkin_ws/src/path_finding/msg/PoseWasteStamped.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/home/ros/PIF/catkin_ws/src/path_finding/msg/PoseWaste.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/path_finding
)

### Generating Services

### Generating Module File
_generate_module_nodejs(path_finding
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/path_finding
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(path_finding_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(path_finding_generate_messages path_finding_generate_messages_nodejs)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/ros/PIF/catkin_ws/src/path_finding/msg/Grid.msg" NAME_WE)
add_dependencies(path_finding_generate_messages_nodejs _path_finding_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ros/PIF/catkin_ws/src/path_finding/msg/GridArray.msg" NAME_WE)
add_dependencies(path_finding_generate_messages_nodejs _path_finding_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ros/PIF/catkin_ws/src/path_finding/msg/GridStamped.msg" NAME_WE)
add_dependencies(path_finding_generate_messages_nodejs _path_finding_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ros/PIF/catkin_ws/src/path_finding/msg/PoseWaste.msg" NAME_WE)
add_dependencies(path_finding_generate_messages_nodejs _path_finding_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ros/PIF/catkin_ws/src/path_finding/msg/PoseWasteStamped.msg" NAME_WE)
add_dependencies(path_finding_generate_messages_nodejs _path_finding_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(path_finding_gennodejs)
add_dependencies(path_finding_gennodejs path_finding_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS path_finding_generate_messages_nodejs)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(path_finding
  "/home/ros/PIF/catkin_ws/src/path_finding/msg/Grid.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/path_finding
)
_generate_msg_py(path_finding
  "/home/ros/PIF/catkin_ws/src/path_finding/msg/GridArray.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/home/ros/PIF/catkin_ws/src/path_finding/msg/Grid.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/path_finding
)
_generate_msg_py(path_finding
  "/home/ros/PIF/catkin_ws/src/path_finding/msg/GridStamped.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/home/ros/PIF/catkin_ws/src/path_finding/msg/GridArray.msg;/home/ros/PIF/catkin_ws/src/path_finding/msg/Grid.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/path_finding
)
_generate_msg_py(path_finding
  "/home/ros/PIF/catkin_ws/src/path_finding/msg/PoseWaste.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/path_finding
)
_generate_msg_py(path_finding
  "/home/ros/PIF/catkin_ws/src/path_finding/msg/PoseWasteStamped.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/home/ros/PIF/catkin_ws/src/path_finding/msg/PoseWaste.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/path_finding
)

### Generating Services

### Generating Module File
_generate_module_py(path_finding
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/path_finding
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(path_finding_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(path_finding_generate_messages path_finding_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/ros/PIF/catkin_ws/src/path_finding/msg/Grid.msg" NAME_WE)
add_dependencies(path_finding_generate_messages_py _path_finding_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ros/PIF/catkin_ws/src/path_finding/msg/GridArray.msg" NAME_WE)
add_dependencies(path_finding_generate_messages_py _path_finding_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ros/PIF/catkin_ws/src/path_finding/msg/GridStamped.msg" NAME_WE)
add_dependencies(path_finding_generate_messages_py _path_finding_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ros/PIF/catkin_ws/src/path_finding/msg/PoseWaste.msg" NAME_WE)
add_dependencies(path_finding_generate_messages_py _path_finding_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ros/PIF/catkin_ws/src/path_finding/msg/PoseWasteStamped.msg" NAME_WE)
add_dependencies(path_finding_generate_messages_py _path_finding_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(path_finding_genpy)
add_dependencies(path_finding_genpy path_finding_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS path_finding_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/path_finding)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/path_finding
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(path_finding_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()
if(TARGET geometry_msgs_generate_messages_cpp)
  add_dependencies(path_finding_generate_messages_cpp geometry_msgs_generate_messages_cpp)
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/path_finding)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/path_finding
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_eus)
  add_dependencies(path_finding_generate_messages_eus std_msgs_generate_messages_eus)
endif()
if(TARGET geometry_msgs_generate_messages_eus)
  add_dependencies(path_finding_generate_messages_eus geometry_msgs_generate_messages_eus)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/path_finding)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/path_finding
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(path_finding_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()
if(TARGET geometry_msgs_generate_messages_lisp)
  add_dependencies(path_finding_generate_messages_lisp geometry_msgs_generate_messages_lisp)
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/path_finding)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/path_finding
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_nodejs)
  add_dependencies(path_finding_generate_messages_nodejs std_msgs_generate_messages_nodejs)
endif()
if(TARGET geometry_msgs_generate_messages_nodejs)
  add_dependencies(path_finding_generate_messages_nodejs geometry_msgs_generate_messages_nodejs)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/path_finding)
  install(CODE "execute_process(COMMAND \"/usr/bin/python3\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/path_finding\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/path_finding
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(path_finding_generate_messages_py std_msgs_generate_messages_py)
endif()
if(TARGET geometry_msgs_generate_messages_py)
  add_dependencies(path_finding_generate_messages_py geometry_msgs_generate_messages_py)
endif()
