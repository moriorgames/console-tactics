
add_library(
        console_tactics
        MoriorGames/Entity/Map.cpp
        MoriorGames/Entity/Player.cpp
        MoriorGames/Entity/Walls.cpp
        MoriorGames/Observer/Publishable.h
        MoriorGames/Observer/Subscribable.h
        MoriorGames/Services/EventPublisher.cpp
        MoriorGames/Services/Game.cpp
        MoriorGames/Services/Logger.cpp
        MoriorGames/Services/TextureSampler.cpp
        MoriorGames/Utils/TextUtils.h
        MoriorGames/Entity/EventState.cpp MoriorGames/Entity/EventState.h)

target_link_libraries(console_tactics)
