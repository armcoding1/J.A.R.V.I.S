//#include <string>
//#include <iostream>
//#include "command_parser.h"
//#include "executor.h"
//
//int main() {
//    std::string input;
//
//    while (true) {
//        std::cout << ">> ";
//        std::getline(std::cin, input);
//        std::string parsed_command = command_parser::parse_command(input);
//        executor::execute(parsed_command);
//    }
//
//    return 0;
//}

#include <iostream>
#include <include/vosk_api.h>
#include <fstream>
#include <string>

int main() {
    // Инициализация модели
    const char* model_path = "models/vosk-model-small-en-us-0.15";  // Путь к модели
    VoskModel* model = vosk_model_new(model_path);
    if (!model) {
        std::cerr << "Model not loaded!" << std::endl;
        return 1;
    }

    // Инициализация распознавателя
    VoskRecognizer* recognizer = vosk_recognizer_new(model, 16000.0);
    if (!recognizer) {
        std::cerr << "Recognizer not created!" << std::endl;
        vosk_model_free(model);
        return 1;
    }

    // Открытие аудиофайла (например, WAV)
    std::ifstream audio_file("audio.wav", std::ios::binary);
    if (!audio_file.is_open()) {
        std::cerr << "Failed to open audio file!" << std::endl;
        vosk_recognizer_free(recognizer);
        vosk_model_free(model);
        return 1;
    }

    // Чтение аудиофайла
    char buffer[4096];
    while (!audio_file.eof()) {
        audio_file.read(buffer, sizeof(buffer));
        if (audio_file.gcount() > 0) {
            // Подача данных на распознавание
            int result = vosk_recognizer_accept_waveform(recognizer, buffer, audio_file.gcount());
            if (result != 0) {
                std::cerr << "Error during recognition!" << std::endl;
                break;
            }
        }
    }

    // Вывод результата
    const char* result_text = vosk_recognizer_result(recognizer);
    std::cout << "Recognized: " << result_text << std::endl;

    // Очистка
    vosk_recognizer_free(recognizer);
    vosk_model_free(model);

    return 0;
}
