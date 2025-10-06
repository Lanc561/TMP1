#include "TableRouteCipher.h"
#include <stdexcept>
#include <cmath>
#include <algorithm>

using namespace std;

TableRouteCipher::TableRouteCipher(int k)
{
    if (k <= 0) {
        throw invalid_argument("Ключ должен быть положительным числом");
    }
    key = k;
}

// Проверка, является ли символ русской буквой
bool TableRouteCipher::isRussianLetter(wchar_t c) const
{
    return russianAlphabet.find(c) != wstring::npos;
}

int TableRouteCipher::calculateRows(int textLength) const
{
    return (textLength + key - 1) / key;
}

vector<vector<wchar_t>> TableRouteCipher::createTable(const wstring& text, bool forEncryption) const
{
    int rows = calculateRows(text.length());
    vector<vector<wchar_t>> table(rows, vector<wchar_t>(key, emptyChar));
    
    if (forEncryption) {
        int index = 0;
        for (int i = 0; i < rows && index < text.length(); i++) {
            for (int j = 0; j < key && index < text.length(); j++) {
                table[i][j] = text[index++];
            }
        }
    } else {
        int index = 0;
        for (int j = key - 1; j >= 0 && index < text.length(); j--) {
            for (int i = 0; i < rows && index < text.length(); i++) {
                table[i][j] = text[index++];
            }
        }
    }
    
    return table;
}

wstring TableRouteCipher::encrypt(const wstring& text) const
{
    if (text.empty()) return L"";
    
    // Фильтруем только русские буквы
    wstring filteredText;
    for (wchar_t c : text) {
        if (isRussianLetter(c)) {
            filteredText += c;
        }
    }
    
    if (filteredText.empty()) return L"";
    
    auto table = createTable(filteredText, true);
    int rows = table.size();
    wstring result;
    
    for (int j = key - 1; j >= 0; j--) {
        for (int i = 0; i < rows; i++) {
            if (table[i][j] != emptyChar) {
                result += table[i][j];
            }
        }
    }
    
    return result;
}

wstring TableRouteCipher::decrypt(const wstring& text) const
{
    if (text.empty()) return L"";
    
    // Фильтруем только русские буквы
    wstring filteredText;
    for (wchar_t c : text) {
        if (isRussianLetter(c)) {
            filteredText += c;
        }
    }
    
    if (filteredText.empty()) return L"";
    
    auto table = createTable(filteredText, false);
    int rows = table.size();
    wstring result;
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < key; j++) {
            if (table[i][j] != emptyChar) {
                result += table[i][j];
            }
        }
    }
    
    return result;
}

void TableRouteCipher::setKey(int k)
{
    if (k <= 0) {
        throw invalid_argument("Ключ должен быть положительным числом");
    }
    key = k;
}

int TableRouteCipher::getKey() const
{
    return key;
}
