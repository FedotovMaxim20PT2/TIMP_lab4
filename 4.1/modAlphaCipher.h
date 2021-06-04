/** @file 
 *  @author Федотов М.М.
 *  @version 1.0
 *  @date 04.06.2021
 *  @brief файл с реализацией класса modAlphaCipher
 */
 
#pragma once

#include <vector>
#include <string>
#include <map>

/** @brief Шифрование методом Гронсфельда
 *  @details Ключ устанавливается в конструкторе.
 *  Для зашифровывания и расшифровывания предназначены методы encrypt и decrypt.
 *  @warning Реализация  для русского языка
 */
class modAlphaCipher {
	
private:
	std::wstring numAlpha = L"АБВГДЕЖЗИЙКЛМНОПРСТУФХЦЧШЩЬЫЪЭЮЯ";
	std::map <wchar_t,int> alphaNum;
	std::vector <int> key;
	std::vector <int> convert(const std::wstring& s);
	std::wstring convert(const std::vector<int>& v);
	std::wstring getValidKey(const std::wstring & in);
	std::wstring getValidOpenText(const std::wstring & in);
	std::wstring getValidCipherText(const std::wstring & in);

public:
	modAlphaCipher()=delete;
    modAlphaCipher(const std::wstring& skey);
	std::wstring encrypt(const std::wstring& open_text);
	std::wstring decrypt(const std::wstring& cipher_text);
};

class cipher_error: public std::invalid_argument {
	
public:
    explicit cipher_error (const std::string& what_arg):
        std::invalid_argument(what_arg) {}
    explicit cipher_error (const char* what_arg):
        std::invalid_argument(what_arg) {}
};
