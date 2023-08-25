cmake_minimum_required(VERSION 3.16)

project(SmartCalc VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra")

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

include_directories("Model" "View" "Controller")

find_package(Qt6 CONFIG REQUIRED COMPONENTS Widgets PrintSupport)

set(SOURCES main.cc ./Model/Model.cc ./View/View.cc ./View/qcustomplot.cc ./Controller/Controller.cc)

add_executable(SmartCalc ${SOURCES} "./Model/Model.h" "./View/View.h" "./Controller/Controller.h"
  "./View/qcustomplot.h" "./View/View.ui" "./View/ViewCredit.ui")

target_link_libraries(SmartCalc PRIVATE Qt6::Widgets Qt6::PrintSupport)
