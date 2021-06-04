/** @file
 *  @author Федотов М.М.
 *  @version 1.0
 *  @date 04.06.2021
 *  @brief заголовочный файл класса shifr
 */
 
#pragma once
#include <string>
#include <map>

/** @brief Шифрование методом Маршрутной перестановки
 *  Для зашифровывания и расшифровывания предназначены методы encrypt и decrypt.
 *  @warning Реализация  только для английского языка
 */

class shifr {
public:
	std::string encrypt(std::string in, const int key);
	std::string decrypt(std::string in, const int key);
private: 
	void isInvalidKey(std::string in, const int key);
	void isInvalidMsg(std::string in, const int key);

};

class encryptException: public std::invalid_argument {
	
public:
    explicit encryptException (const std::string& what_arg):
        std::invalid_argument(what_arg) {}
    explicit encryptException (const char* what_arg):
        std::invalid_argument(what_arg) {}
};
