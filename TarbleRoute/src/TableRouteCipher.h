#pragma once
#include <string>
#include <vector>
#include <locale>
#include <codecvt>

class TableRouteCipher
{
private:
    int key;                    // количество столбцов
    wchar_t emptyChar = L'_';   // символ для заполнения пустых ячеек
    std::wstring russianAlphabet = L"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";
    
    int calculateRows(int textLength) const;
    std::vector<std::vector<wchar_t>> createTable(const std::wstring& text, bool forEncryption) const;
    bool isRussianLetter(wchar_t c) const;
    
public:
    TableRouteCipher() = delete;
    TableRouteCipher(int k);
    
    std::wstring encrypt(const std::wstring& text) const;
    std::wstring decrypt(const std::wstring& text) const;
    
    void setKey(int k);
    int getKey() const;
};
