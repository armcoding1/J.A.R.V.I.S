cmake_minimum_required(VERSION 3.10)

project(SpeechRecognition)

# Путь к исходным файлам
set(SOURCES src/main.cpp)

# Указываем путь к заголовочным файлам и библиотекам
include_directories(include)
link_directories(libs)

# Указываем, какие библиотеки линковать
add_executable(speech_recognition ${SOURCES})
target_link_libraries(speech_recognition vosk asound)
