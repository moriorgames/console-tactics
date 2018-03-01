
add_library(
        console_tactics
        MoriorGames/Entity/Map.cpp
        MoriorGames/Entity/Player.cpp
        MoriorGames/Entity/Tile.cpp
        MoriorGames/Services/InputEvents.cpp
        MoriorGames/Services/Logger.cpp
        MoriorGames/Utils/TextUtils.h
)

target_link_libraries(console_tactics)
