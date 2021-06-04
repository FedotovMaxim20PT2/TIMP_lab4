/** @file
 *  @author ������� �.�.
 *  @version 1.0
 *  @date 04.06.2021
 *  @brief ���� � ����������� ������ modAlphaCipher
 */
 
#include <vector>
#include <string>
#include <map>
#include <iostream>

#include "modAlphaCipher.h"

using namespace std;

std::wstring numAlpha = L"��������������������������������";
std::map <wchar_t, int> alphaNum; 
	/**
     * @brief �����������
     * @param [in] skey ����, �� �������� ����������� ������������� �������.
     * @throw cipher_error, ����������,���� ���� �� ������
     */
modAlphaCipher::modAlphaCipher(const std::wstring& skey) {
	for (int i = 0; i<numAlpha.size(); i++) {
		alphaNum[numAlpha[i]]=i;
	}
	key = convert(getValidKey(skey));

}
	/**
     * @brief ��������������
     * @param [in] open_text �������� �����. �� ������ ���� ������ �������.
     *                       �������� ������� ������������� ������������� � ���������.
     *                       ��� �������, �� ���������� �������  ���������
     * @return ������������� ������
     * @throw cipher_error, ���� ����� ������
     */
std::wstring modAlphaCipher::encrypt(const std::wstring& open_text) {
	std::vector<int> work = convert(getValidOpenText(open_text));
	for(unsigned i=0; i < work.size(); i++) {
		work[i] = (work[i] + key[i % key.size()]) % alphaNum.size();
	}
	return convert(work);
}
	/**
     * @brief �������������
     * @param [in] cipher_text ������������� �����. �� ������ ���� ������ �������.
     *                       �������� ������� ������������� ������������� � ���������.
     *                       ��� �������, �� ���������� �������  ���������
     * @return �������������� ������ 
     * @throw cipher_error, ���� ����� ������
     */
std::wstring modAlphaCipher::decrypt(const std::wstring& cipher_text) {
	std::vector<int> work = convert(getValidCipherText(cipher_text));
	for(unsigned i=0; i < work.size(); i++) {
		work[i] = (work[i] + alphaNum.size() - key[i % key.size()]) % alphaNum.size();
	}
	return convert(work);
}
	/**
     * @brief ��������������
     * @param [in] str �������� �����. 
     * @return ������,��������� �� ����� �������� � ��������� ��������.
     */
inline std::vector<int> modAlphaCipher::convert(const std::wstring& str) {
	std::vector<int> result;
	for(auto c:str) {
		result.push_back(alphaNum[c]);
	}
	return result;
}
 	/**
     * @brief ��������������
     * @param [in] str ������ ����� �������� � ��������� ��������. 
     * @return ������ �� ������ ��������.
     */
inline std::wstring modAlphaCipher::convert(const std::vector<int>& v) {
	std::wstring result;
	for(auto i:v) {
		result.push_back(numAlpha[i]);
	}
	return result;
}
	/**
     * @brief �������� ����� ������
     * @param [in] in ���� ���������� ������.
     * @return ������ � ������
     * @throw cipher_error, ���� ���� ������� ���������, ������ ��� ����� ������������ �������. 
     */
inline std::wstring modAlphaCipher::getValidKey(const std::wstring & in) {
	if (in.empty()) throw cipher_error("Empty key");
	
	wstring output;
	std::locale loc("ru_RU.UTF-8");
	
	for (wchar_t c : in) {
		if (c >= L'�' && c <= L'�') {
			output += c;
		} else if (c >= L'�' && c <= L'�') {
			output += toupper(c, loc);
		} else {
			throw cipher_error("Invalid key");
		}
	}
	
	return output;
}
	/**
     * @brief �������� ��������� ������
     * @param [in] in �������� �����.
     * @return ������ ��������� ������
     * @throw cipher_error, ���� ������ ������ ��� ����� ������������ �������. 
     */
inline std::wstring modAlphaCipher::getValidOpenText(const std::wstring & in) {
	if (in.empty()) throw cipher_error("Empty Open Text");
	
	wstring output;
	std::locale loc("ru_RU.UTF-8");
	
	for (wchar_t c : in) {
		if (c >= L'�' && c <= L'�') {
			output += c;
		} else if (c >= L'�' && c <= L'�') {
			output += toupper(c, loc);
		} else {
			throw cipher_error("Invalid Open Text");
		}
	}
	
	return output;
}
	/**
     * @brief �������� �������������� ������
     * @param [in] in ������������� �����
     * @return ������������� ������
     * @throw cipher_error, ���� ����� ������ ��� � ������ ���������� ������ �������, ����� ���� ��������
     */
inline std::wstring modAlphaCipher::getValidCipherText(const std::wstring & in){
	if (in.empty()) throw cipher_error("Empty Cipher Text");
	
	wstring output;
	std::locale loc("ru_RU.UTF-8");
	
	for (wchar_t c : in) {
		if (c > L'�' && c < L'�') {
			output += c;
		} else {
			throw cipher_error("Invalid Open Text");
		}
	}
	
	return output;
}