
add_library(
        console_tactics
        MoriorGames/Entity/Player.cpp
        MoriorGames/Services/InputEvents.cpp
        MoriorGames/Services/MapFactory.cpp
)

target_link_libraries(console_tactics)
