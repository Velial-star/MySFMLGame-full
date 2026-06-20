cmake_minimum_required(VERSION 3.14) # SFML требует минимум 3.14 для FetchContent
project(mario)


set(CMAKE_CXX_STANDARD 23)
set(CMAKE_POLICY_VERSION_MINIMUM 3.5)

# --- 1. Настройка зависимостей ---
include(FetchContent)

# Скачиваем и собираем SFML
FetchContent_Declare(
        sfml
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.5.1 # Указываем нужную версию
)
FetchContent_MakeAvailable(sfml)
# --- 2. Сборка вашего проекта ---
add_executable(MySFMLGame
        Capybara.cpp
        Capybara.h
        main.cpp
        obj.cpp
        obj.h
)

# --- 3. Подключение библиотек ---
# Так как мы использовали FetchContent, библиотеки называются просто sfml-*
target_link_libraries(MySFMLGame PRIVATE sfml-network sfml-graphics sfml-window sfml-audio)

# --- 4. Автоматическое копирование DLL в папку с exe (только Windows) ---
if(WIN32)
    add_custom_command(TARGET MySFMLGame POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "$<TARGET_RUNTIME_DLLS:MySFMLGame>"
            $<TARGET_FILE_DIR:MySFMLGame>
            COMMAND_EXPAND_LISTS
    )
endif()

add_custom_target(copy_assets ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        ${CMAKE_BINARY_DIR}/assets
)

add_dependencies(MySFMLGame copy_assets)