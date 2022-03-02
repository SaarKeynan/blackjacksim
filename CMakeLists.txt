cmake_minimum_required(VERSION 3.21)
project(cppbj)

set(CMAKE_CXX_STANDARD 14)

add_executable(cppbj main.cpp Card.h Suit.h Hand.cpp Hand.h List.h Rank.h Move.h Player.cpp Player.h Rules.h Status.h Game.h Game.cpp BSTableCell.h Condition.h ConditionObjType.h ConditionObject.h CmpType.h Condition.cpp)
