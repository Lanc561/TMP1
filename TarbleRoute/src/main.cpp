#include <iostream>
#include <string>
#include <vector>
#include <locale>
#include <codecvt>
#include <iomanip>
#include "TableRouteCipher.h"

using namespace std;

// Функция для отображения заголовка
void printHeader(const wstring& title) {
    wcout << L"\n╔══════════════════════════════════════════════════════════════╗" << endl;
    wcout << L"║ " << setw(58) << left << title << L"║" << endl;
    wcout << L"╚══════════════════════════════════════════════════════════════╝" << endl;
}

// Функция для отображения таблицы (для демонстрации)
void displayTable(const vector<vector<wchar_t>>& table, const wstring& title) {
    wcout << L"\n" << title << L":" << endl;
    wcout << L"┌";
    for (int j = 0; j < table[0].size(); j++) {
        wcout << L"───";
        if (j < table[0].size() - 1) wcout << L"┬";
    }
    wcout << L"┐" << endl;
    
    for (int i = 0; i < table.size(); i++) {
        wcout << L"│";
        for (int j = 0; j < table[i].size(); j++) {
            wcout << L" " << table[i][j] << L" │";
        }
        wcout << endl;
        
        if (i < table.size() - 1) {
            wcout << L"├";
            for (int j = 0; j < table[i].size(); j++) {
                wcout << L"───";
                if (j < table[i].size() - 1) wcout << L"┼";
            }
            wcout << L"┤" << endl;
        }
    }
    
    wcout << L"└";
    for (int j = 0; j < table[0].size(); j++) {
        wcout << L"───";
        if (j < table[0].size() - 1) wcout << L"┴";
    }
    wcout << L"┘" << endl;
}

// Подробная демонстрация с визуализацией таблицы
void detailedDemonstration() {
    printHeader(L"ПОДРОБНАЯ ДЕМОНСТРАЦИЯ РАБОТЫ ШИФРА");
    
    // Используем vector с парами вместо tuple
    vector<pair<wstring, int>> testCases = {
        {L"ПРИВЕТМИР", 3},
        {L"ПРОГРАММИРОВАНИЕ", 4},
        {L"КОД", 2}
    };
    
    vector<wstring> descriptions = {
        L"Пример 1: Простой текст",
        L"Пример 2: Длинный текст", 
        L"Пример 3: Короткий текст"
    };
    
    for (size_t i = 0; i < testCases.size(); i++) {
        wstring text = testCases[i].first;
        int key = testCases[i].second;
        wstring description = descriptions[i];
        
        wcout << L"\n" << description << endl;
        wcout << L"─────────────────────────────────────" << endl;
        
        TableRouteCipher cipher(key);
        
        wcout << L"Ключ (столбцы): " << key << endl;
        wcout << L"Исходный текст: " << text << endl;
        
        // Визуализация процесса шифрования
        wstring encrypted = cipher.encrypt(text);
        wcout << L"Зашифрованный текст: " << encrypted << endl;
        
        // Визуализация процесса расшифрования
        wstring decrypted = cipher.decrypt(encrypted);
        wcout << L"Расшифрованный текст: " << decrypted << endl;
        
        // Проверка
        wstring status = (text == decrypted) ? L"✓ УСПЕХ" : L"✗ ОШИБКА";
        wcout << L"Статус: " << status << endl;
    }
}

// Интерактивный режим шифрования
void interactiveEncryption() {
    printHeader(L"РЕЖИМ ШИФРОВАНИЯ");
    
    int key;
    wcout << L"Введите ключ (количество столбцов): ";
    wcin >> key;
    
    if (key <= 0) {
        wcout << L"❌ Ошибка: ключ должен быть положительным числом!" << endl;
        return;
    }
    
    TableRouteCipher cipher(key);
    wcin.ignore(); // Очистка буфера
    
    wstring text;
    wcout << L"Введите текст для шифрования: ";
    getline(wcin, text);
    
    if (text.empty()) {
        wcout << L"❌ Ошибка: текст не может быть пустым!" << endl;
        return;
    }
    
    try {
        wstring encrypted = cipher.encrypt(text);
        wstring decrypted = cipher.decrypt(encrypted);
        
        wcout << L"\n📊 РЕЗУЛЬТАТЫ:" << endl;
        wcout << L"├─ Ключ: " << key << L" столбцов" << endl;
        wcout << L"├─ Исходный текст: " << text << endl;
        wcout << L"├─ Зашифрованный текст: " << encrypted << endl;
        wcout << L"├─ Расшифрованный текст: " << decrypted << endl;
        wcout << L"└─ Проверка: " << (text == decrypted ? L"✅ тексты совпадают" : L"❌ тексты не совпадают!") << endl;
        
    } catch (const exception& e) {
        wcout << L"❌ Ошибка при обработке: " << e.what() << endl;
    }
}

// Режим пакетной обработки
void batchProcessing() {
    printHeader(L"ПАКЕТНАЯ ОБРАБОТКА");
    
    vector<pair<wstring, int>> batchData = {
        {L"ПРИВЕТ", 2},
        {L"ЗДРАВСТВУЙТЕ", 3},
        {L"ШИФРОВАНИЕ", 4},
        {L"ИНФОРМАЦИЯ", 2}
    };
    
    wcout << L"Обработка " << batchData.size() << L" тестовых случаев..." << endl;
    wcout << L"┌───────────────┬──────────┬──────────────────┬────────┐" << endl;
    wcout << L"│     Текст     │  Ключ    │  Шифртекст       │ Статус │" << endl;
    wcout << L"├───────────────┼──────────┼──────────────────┼────────┤" << endl;
    
    int successCount = 0;
    for (const auto& data : batchData) {
        wstring text = data.first;
        int key = data.second;
        
        TableRouteCipher cipher(key);
        wstring encrypted = cipher.encrypt(text);
        wstring decrypted = cipher.decrypt(encrypted);
        bool success = (text == decrypted);
        
        if (success) successCount++;
        
        wcout << L"│ " << setw(13) << text << L" │ " << setw(8) << key 
              << L" │ " << setw(16) << encrypted << L" │ " 
              << (success ? L"  ✅   │" : L"  ❌   │") << endl;
    }
    
    wcout << L"└───────────────┴──────────┴──────────────────┴────────┘" << endl;
    wcout << L"Успешно обработано: " << successCount << L" из " << batchData.size() << L" тестов" << endl;
}

// Режим обучения с примерами
void learningMode() {
    printHeader(L"РЕЖИМ ОБУЧЕНИЯ");
    
    wcout << L"📖 Принцип работы шифра табличной маршрутной перестановки:" << endl;
    wcout << L"─────────────────────────────────────────────────────────" << endl;
    wcout << L"1. Текст записывается в таблицу по строкам слева направо" << endl;
    wcout << L"2. Шифртекст считывается из таблицы по столбцам справа налево" << endl;
    wcout << L"3. Ключ - количество столбцов в таблице" << endl;
    wcout << L"4. Поддерживаются только русские буквы" << endl;
    wcout << L"\n";
    
    // Пример с визуализацией
    wstring exampleText = L"ПРИВЕТ";
    int exampleKey = 3;
    
    wcout << L"🔍 Пример для текста: \"" << exampleText << L"\" с ключом " << exampleKey << endl;
    wcout << L"\nШаг 1: Запись в таблицу (→↓):" << endl;
    wcout << L"   ┌───┬───┬───┐" << endl;
    wcout << L"   │ П │ Р │ И │" << endl;
    wcout << L"   ├───┼───┼───┤" << endl;
    wcout << L"   │ В │ Е │ Т │" << endl;
    wcout << L"   └───┴───┴───┘" << endl;
    
    wcout << L"\nШаг 2: Чтение из таблицы (↓←):" << endl;
    wcout << L"   Столбец 2: И → Т" << endl;
    wcout << L"   Столбец 1: Р → Е" << endl;
    wcout << L"   Столбец 0: П → В" << endl;
    wcout << L"   Результат: \"ИТРЕПВ\"" << endl;
    
    TableRouteCipher cipher(exampleKey);
    wstring result = cipher.encrypt(exampleText);
    wcout << L"\n✅ Фактический результат программы: \"" << result << L"\"" << endl;
}

// Настройки программы
void settingsMenu() {
    printHeader(L"НАСТРОЙКИ ПРОГРАММЫ");
    
    wcout << L"Текущие настройки системы:" << endl;
    wcout << L"├─ Поддерживаемый алфавит: русские буквы (А-Я, Ё)" << endl;
    wcout << L"├─ Режим работы: табличная маршрутная перестановка" << endl;
    wcout << L"├─ Маршрут записи: слева направо, сверху вниз" << endl;
    wcout << L"└─ Маршрут чтения: сверху вниз, справа налево" << endl;
    
    wcout << L"\n📝 Описание алгоритма:" << endl;
    wcout << L"Алгоритм преобразует текст, записывая его в таблицу указанной" << endl;
    wcout << L"ширины (ключ), а затем считывая по заданному маршруту." << endl;
    wcout << L"Это обеспечивает перестановку символов исходного текста." << endl;
}

// Главное меню
void showMainMenu() {
    printHeader(L"ШИФР ТАБЛИЧНОЙ МАРШРУТНОЙ ПЕРЕСТАНОВКИ");
    
    wcout << L"┌───┬─────────────────────────────────────────────┐" << endl;
    wcout << L"│ 1 │ 🔍 Подробная демонстрация                   │" << endl;
    wcout << L"│ 2 │ ⌨️  Интерактивное шифрование                 │" << endl;
    wcout << L"│ 3 │ 📦 Пакетная обработка тестов               │" << endl;
    wcout << L"│ 4 │ 📚 Режим обучения                         │" << endl;
    wcout << L"│ 5 │ ⚙️  Настройки и информация                 │" << endl;
    wcout << L"│ 6 │ 🚪 Выход из программы                      │" << endl;
    wcout << L"└───┴─────────────────────────────────────────────┘" << endl;
    wcout << L"Выберите опцию (1-6): ";
}

int main() {
    // Установка локали для поддержки русского языка
    setlocale(LC_ALL, "ru_RU.UTF-8");
    locale::global(locale("ru_RU.UTF-8"));
    wcout.imbue(locale("ru_RU.UTF-8"));
    wcin.imbue(locale("ru_RU.UTF-8"));
    
    int choice;
    bool running = true;
    
    wcout << L"🎯 Добро пожаловать в программу шифрования!" << endl;
    wcout << L"   Табличная маршрутная перестановка" << endl;
    
    while (running) {
        showMainMenu();
        wcin >> choice;
        
        switch (choice) {
            case 1:
                detailedDemonstration();
                break;
            case 2:
                interactiveEncryption();
                break;
            case 3:
                batchProcessing();
                break;
            case 4:
                learningMode();
                break;
            case 5:
                settingsMenu();
                break;
            case 6:
                wcout << L"\n👋 Спасибо за использование программы! До свидания!" << endl;
                running = false;
                break;
            default:
                wcout << L"❌ Неверный выбор! Пожалуйста, выберите опцию от 1 до 6." << endl;
        }
        
        if (running && choice != 6) {
            wcout << L"\nНажмите Enter для продолжения...";
            wcin.ignore();
            wcin.get();
        }
    }
    
    return 0;
}
