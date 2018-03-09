
add_library(
        console_tactics
        MoriorGames/Entity/EventState.cpp
        MoriorGames/Entity/Lamps.cpp
        MoriorGames/Entity/Map.cpp
        MoriorGames/Entity/Player.cpp
        MoriorGames/Entity/Walls.cpp
        MoriorGames/Observer/EventObservable.h
        MoriorGames/Observer/EventPublishable.h
        MoriorGames/Services/EventPublisher.cpp
        MoriorGames/Services/Game.cpp
        MoriorGames/Services/Logger.cpp
        MoriorGames/Services/TextureSampler.cpp
        MoriorGames/Utils/TextUtils.h
        MoriorGames/ValueObject/Coordinate.cpp
        MoriorGames/View/CeilingView.cpp
        MoriorGames/View/GameView.cpp
)

target_link_libraries(console_tactics)
