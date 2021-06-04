/** @file
 *  @author Федотов М.М.
 *  @version 1.0
 *  @date 04.06.2021
 *  @brief файл с реализацией класса shifr
 */
 
#include "shifr.h"
#include <iostream>
#include <string>

using namespace std;
/**
 * @brief Зашиврование
 * @param  in открытый текст. Не пустая строка
 *                                            Не-буквы удаляются
 *                                            Строчные буквы преобразуются в прописные
 * @param key целое число
 * @return зашифрованный текст
 * @throw encryptException при вводе в качестве параметра пустого текста
 */

string shifr::encrypt(string in, const int key)
{
    isInvalidMsg(in, key);
    isInvalidKey(in, key);

    int array_size = in.length();
    int array_height = (array_size/key) + ((array_size%key > 0) ? 1 : 0);
    int lower_string_lenght = in.length()%key;
    int zvezdi = (lower_string_lenght > 0) ? key - lower_string_lenght : 0;

    char ** matrix = new char*[array_height];
    for (int i =0; i<array_height; i++) matrix[i] = new char[key];

    std::string output;

    for (int i = 0; i < zvezdi; i++) {
        matrix[array_height-1][(key-1)-i] = '*';
    }

    int charId = 0;
    for (int i = 0; i < array_height; i++) {
        for (int j = 0; j < key; j++) {
            if (matrix[i][j] == '*') continue;

            matrix[i][j] = in.at(charId);
            charId++;
        }
    }


    for (int i = 0; i < key; i++) {
        for (int j = 0; j < array_height; j++) {
            if (matrix[j][(key-1)-i] == '*') continue;
            output+=matrix[j][(key-1)-i];
        }
    }

    for (int i = 0; i < array_height; i++) delete[] matrix[i];
    delete[] matrix;
    return output;
}
/**
 * @brief Расшифрование
 * @param in зашифрованный текст. Не пустая строка
 *                                                    Строчные симводы преобразуются в прописные
 *                                                    Не-буквы удаляются 
 * @param key целое число
 * @return расшифрованная строка
 * @throw encryptException при пустом тексте
 */

string shifr::decrypt(string in, const int key)
{
    isInvalidMsg(in, key);
    isInvalidKey(in, key);


    int array_height = (in.length()/key) + ((in.length()%key > 0) ? 1 : 0);
    int lower_string_lenght = in.length()%key;
    int zvezdi = (lower_string_lenght > 0) ? key - lower_string_lenght : 0;

    char ** matrix = new char*[array_height];
    for (int i =0; i<array_height; i++) matrix[i] = new char[key];

    std::string output;

    for (int i = 0; i < array_height; i++) {
        for (int j = 0; j < key; j++) {
            matrix[i][j] = '\0';
        }
    }

    for (int i = 0; i< zvezdi; i++) {
        matrix[array_height-1][(key-1)-i] = '*';
    }

    int charId = 0;
    for (int i = 0; i < key; i++) {
        for (int j = 0; j < array_height; j++) {
            if (matrix[j][(key-1)-i] == '*') continue;

            matrix[j][(key-1)-i] = in.at(charId);
            charId++;
        }
    }

    for (int i = 0; i < in.length(); i++) {
        int y = i/key;
        int x = (i%key);

        char c = matrix[y][x];

        if (c != '\0') {
            output+=c;
        }

    }

    for (int i = 0; i < array_height; i++) delete[] matrix[i];
    delete[] matrix;
    return output;
}
/**
 * @brief Проверка ключа
 * @param in ключ для шифрования
 * @return строка с ключом
 * @throw encryptException при пустом ключе, при коротком ключе 
 */
void shifr::isInvalidKey(std::string in, const int key)
{
    if (key == 0) throw encryptException("Empty key");

    if (in.length()/2 < key) {
        throw encryptException("Invalid key value");
    }
}
/**
 * @brief Проверка текста
 * @param in строка для шифрования
 * @param key ключ
 * @throw encryptException при пустом тексте,при содержании некорректных символов в сообщении
 */
void shifr::isInvalidMsg(std::string in, const int key)
{
    if (in.empty()) throw encryptException("Empty message");

    for (char c : in) {
        if (!isalpha(c)) throw encryptException("Invalid char in Text");
    }
}
