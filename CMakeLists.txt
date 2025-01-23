cmake_minimum_required(VERSION 3.16)
project(PointAndClickSFML)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

#---- Fetch SFML, only works if you have git installed on your machine ----#

include(FetchContent)   # Allows fetching content remotely at configure time
FetchContent_Declare(   # Fetches SFML from github and puts it in the build directory
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 69ea0cd863aed1d4092b970b676924a716ff718b    # Makes sure to fetch SFML version 2.6.1
)

FetchContent_MakeAvailable(SFML)    # Makes sure SFML and its dependencies are avaiable for the project

#---- File management & .exe creation ----#

set(SOURCE_DIR src/)
include_directories(src/)

set(SOURCE_FILES src/main.cpp src/Game.cpp src/Game.h src/BaseClasses/GameObject.cpp src/BaseClasses/GameObject.h src/Common/Player.h src/Common/Player.cpp src/BaseClasses/Vector2.h src/BaseClasses/Vector2.cpp "src/BaseClasses/Room.h" "src/BaseClasses/Room.cpp" "src/Common/RoomSwitch.h" "src/Common/RoomSwitch.cpp"  "src/Level/Key.h" "src/Level/Key.cpp" "src/Level/Vase.h" "src/Level/Vase.cpp" "src/Level/Rooms/RoomEntrance.h" "src/Level/Rooms/RoomEntrance.cpp" "src/Level/Rooms/RoomPuzzle1.h" "src/Level/Rooms/RoomPuzzle1.cpp" "src/BaseClasses/GimmickWindow.h" "src/BaseClasses/GimmickWindow.cpp" "src/Level/Gimmicks/GWCrank.h" "src/Level/Gimmicks/GWCrank.cpp" "src/Level/Rooms/RoomFinal.h" "src/Level/Rooms/RoomFinal.cpp" "src/Level/Rooms/RoomPuzzle2.h" "src/Level/Rooms/RoomPuzzle2.cpp" "src/Level/Crank.h" "src/Level/Crank.cpp" "src/Level/KeyContainer.h" "src/Level/KeyContainer.cpp" "src/Level/Rooms/RoomPuzzle3.h" "src/Level/Rooms/RoomPuzzle3.cpp" "src/Level/Coffin.h" "src/Level/Coffin.cpp" "src/Level/Rooms/RoomEnd.h" "src/Level/Rooms/RoomEnd.cpp" "src/Common/FadeManager.h" "src/Common/FadeManager.cpp")  # Sets variable SOURCE_FILES to hold names & locations of files that need to be compiled into the application
add_executable(PointAndClickSFML ${SOURCE_FILES})  # Names the application and tells compiler which source files to use

target_link_libraries(PointAndClickSFML PRIVATE sfml-graphics sfml-window sfml-system sfml-network sfml-audio) # Links the SFML libraries we need to our application
target_compile_features(PointAndClickSFML PRIVATE cxx_std_20)  # Defines which standard of C++ the compiler should use

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Data/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Bin/Data/)  # Copies data from source directory to build directory (so the executable can access it)

if(WIN32)
    add_custom_command(
        TARGET PointAndClickSFML
        COMMENT "Copy OpenAL DLL to build directory so app can have sound"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:PointAndClickSFML>
        VERBATIM)
endif()