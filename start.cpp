#include <iostream>
#include <string>
#include <sqlite3.h>
#include <vector>
using namespace std;

int main(){
    sqlite3* db;
    sqlite3_stmt* stmt;

    // Veritabanına bağlanma
    int rc = sqlite3_open("emails.db", &db);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to open database: " << sqlite3_errmsg(db) << std::endl;
        return 1;
    }

    std::vector<std::string> emails;

    // E-posta adreslerini seçme
    const char* query = "SELECT email FROM emails";
    rc = sqlite3_prepare_v2(db, query, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare query: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return 1;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        const unsigned char* email = sqlite3_column_text(stmt, 0);
        emails.push_back(reinterpret_cast<const char*>(email));
    }

    // Bellekten kaynakları temizleme
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    string message;
    string subject;
    cout << "Please enter your subject:";
    getline(cin,subject);
    cout << "Please enter your message:";
    getline(cin,message);

    // E-posta adreslerini ekrana yazdırma
    for (const auto& email : emails) {
        std::string command = "python3 emailsender.py " + email + " " + message + " " + subject;
        std::system(command.c_str());
    }


    return 0;
}





