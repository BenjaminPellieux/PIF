<<<<<<< HEAD
cmake_minimum_required(VERSION 3.0)
project(video2.cpp)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

find_package(OpenCV 4 REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(video2 video2.cpp)
target_link_libraries(video2 ${OpenCV_LIBS})
=======
cmake_minimum_required(VERSION 3.10) # Spécifiez la version minimale de CMake

project(vision_pixel_par_pixel) # Nom de votre projet

set(CMAKE_CXX_STANDARD 11) # Définissez le standard C++ à utiliser
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall") # Activez les avertissements

# Trouvez OpenCV sur le système
find_package(OpenCV 4 REQUIRED)

# Incluez les dossiers d'en-tête d'OpenCV
include_directories(${OpenCV_INCLUDE_DIRS})

# Définissez la cible de compilation pour votre exécutable
add_executable(${PROJECT_NAME} vision.cpp)

# Liez votre exécutable avec les bibliothèques d'OpenCV
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
>>>>>>> e334bc49a73df82dd44ddb906a733f9a4f677566
