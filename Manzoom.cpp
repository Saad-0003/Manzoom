#include <iostream>
#include <conio.h>
#include <fstream>
#include <string>
#include <limits>
#include <sstream>
#include <list>
#include <unordered_map>
#include <windows.h>
#include <cstdlib>
#include <vector>
#include <iomanip>
using namespace std;

namespace UI {
    // Color Constants
    const int COLOR_DEFAULT = 15; // White
    const int COLOR_BRAND = 11;   // Light Cyan
    const int COLOR_ERROR = 12;   // Red
    const int COLOR_SUCCESS = 10; // Green
    const int COLOR_INPUT = 14;   // Yellow
    const int COLOR_MUTED = 8;    // Gray

    // Screen Dimensions for "Centering" simulation
    const int CONSOLE_WIDTH = 80;
    const string PADDING_L = "      "; 

    void setColor(int color) {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, color);
    }

    void resetColor() {
        setColor(COLOR_DEFAULT);
    }

    // Draw a horizontal line
    void drawLine(int width = 60) {
        setColor(COLOR_BRAND);
        cout << PADDING_L;
        for (int i = 0; i < width; i++) cout << "\xCD"; // Double horizontal line
        cout << endl;
        resetColor();
    }

    // Print text centered relative to a fixed width
    void printCentered(string text, int width = 60) {
        int padding = (width - text.length()) / 2;
        if (padding < 0) padding = 0;
        cout << PADDING_L;
        setColor(COLOR_BRAND); cout << "\xBA"; // Vertical bar
        resetColor();
        cout << string(padding, ' ') << text << string(width - padding - text.length(), ' ');
        setColor(COLOR_BRAND); cout << "\xBA";
        resetColor();
        cout << endl;
    }

    // Header Art
    void printHeader() {
        setColor(COLOR_BRAND);
        cout << endl;
        cout << PADDING_L << "  __  __                                              " << endl;
        cout << PADDING_L << " |  \\/  | __ _ _ __  _______  ___  _ __ ___          " << endl;
        cout << PADDING_L << " | |\\/| |/ _` | '_ \\|_  / _ \\/ _ \\| '_ ` _ \\   " << endl;
        cout << PADDING_L << " | |  | | (_| | | | |/ / (_) | (_) | | | | | |        " << endl;
        cout << PADDING_L << " |_|  |_|\\__,_|_| |_/___\\___/ \\___/|_| |_| |_|     " << endl;
        cout << endl;
        setColor(COLOR_MUTED);
        cout << PADDING_L << "     -- Abhi Kuch log baki hain jo urdu bol sakta hain -- " << endl;
        cout << endl;
        resetColor();
    }

    void cls() {
        system("CLS");
        printHeader();
    }

    // Fancy box for menus
    void drawMenuBox(string title, const vector<string>& options) {
        int width = 50;
        
        // Top Border
        cout << PADDING_L; setColor(COLOR_BRAND); 
        cout << "\xC9"; for(int i=0; i<width; i++) cout << "\xCD"; cout << "\xBB" << endl;

        string centeredTitle = string((width - title.length())/2, ' ') + title;
        cout << PADDING_L << "\xBA" << " " << left << setw(width-1) << centeredTitle << "\xBA" << endl;
        cout << PADDING_L << "\xCC"; for(int i=0; i<width; i++) cout << "\xCD"; cout << "\xB9" << endl;

        // Options
        resetColor();
        for (const string& opt : options) {
            cout << PADDING_L; setColor(COLOR_BRAND); cout << "\xBA"; resetColor();
            cout << "  " << left << setw(width-2) << opt;
            setColor(COLOR_BRAND); cout << "\xBA" << endl;
        }

        // Bottom Border
        cout << PADDING_L << "\xC8"; for(int i=0; i<width; i++) cout << "\xCD"; cout << "\xBC" << endl;
        resetColor();
    }

    void printError(string msg) {
        cout << PADDING_L; setColor(COLOR_ERROR); cout << "[!] " << msg << endl; resetColor();
    }

    void printSuccess(string msg) {
        cout << PADDING_L; setColor(COLOR_SUCCESS); cout << "[OK] " << msg << endl; resetColor();
    }

    void printPrompt(string msg) {
        cout << PADDING_L; setColor(COLOR_INPUT); cout << ">> " << msg; resetColor();
    }
}


// Main LOGIC
string getPassword() {
    string password;
    char ch;
    while (true) {
        ch = _getch();
        if (ch == '\r') {
            cout << endl;
            break;
        }
        else if (ch == '\b') {
            if (!password.empty()) {
                cout << "\b \b";
                password.pop_back();
            }
        }
        else {
            cout << '*';
            password += ch;
        }
    }
    return password;
}

void emptyFile(const char* filename) {
    ofstream file(filename, ios::out | ios::trunc);
    if (file.is_open()) {
        file.close();
    }
    else {
        UI::printError("Error opening file.");
    }
}

class PoetryNode {
public:
    string title;
    string content;
    string genre;
    string mood;
    PoetryNode* left;
    PoetryNode* right;

    PoetryNode(string t, string c, string g, string m) : title(t), content(c), genre(g), mood(m), left(NULL), right(NULL) {}
};

string toLower(const string& str) {
    string result;
    for (char c : str) {
        result += tolower(c);
    }
    return result;
}

class PoetTree {
private:
    PoetryNode* root;

    void insertPoetryNode(PoetryNode*& node, string title, string content, string genre, string mood) {
        if (!node) {
            node = new PoetryNode(title, content, genre, mood);
        }
        else if (title < node->title) {
            insertPoetryNode(node->left, title, content, genre, mood);
        }
        else {
            insertPoetryNode(node->right, title, content, genre, mood);
        }
    }

    void displayPoemWithPadding(const string& title, const string& genre, const string& mood, const string& content) {
        UI::setColor(UI::COLOR_BRAND);
        cout << "\n" << UI::PADDING_L << "\xDA"; for(int i=0; i<50; i++) cout << "\xC4"; cout << "\xBF\n"; // Thin top border
        
        UI::resetColor();
        cout << UI::PADDING_L << " Title : " << title << endl;
        cout << UI::PADDING_L << " Genre : " << genre << endl;
        cout << UI::PADDING_L << " Mood  : " << mood << endl;
        
        UI::setColor(UI::COLOR_MUTED);
        cout << UI::PADDING_L << " --------------------------------------------------" << endl;
        
        UI::setColor(UI::COLOR_DEFAULT);
        stringstream contentStream(content);
        string line;
        while (getline(contentStream, line)) {
            cout << UI::PADDING_L << "   " << line << endl;
        }

        UI::setColor(UI::COLOR_BRAND);
        cout << UI::PADDING_L << "\xC0"; for(int i=0; i<50; i++) cout << "\xC4"; cout << "\xD9\n"; // Thin bottom border
        UI::resetColor();
    }

    void displayPoems(PoetryNode* node) {
        if (node) {
            displayPoems(node->left);
            displayPoemWithPadding(node->title, node->genre, node->mood, node->content);
            displayPoems(node->right);
        }
    }

    void saveToFile(PoetryNode* node, ofstream& file) {
        if (node) {
            saveToFile(node->left, file);
            file << node->title << "\n"
                << node->genre << "\n"
                << node->mood << "\n"
                << node->content << "\n" << "<<END_CONTENT>>\n";
            saveToFile(node->right, file);
        }
    }

    void loadFromFile(PoetryNode*& node, ifstream& file) {
        string line, title, genre, mood, content;

        while (getline(file, title)) {
            if (!getline(file, genre) || !getline(file, mood)) break;

            content.clear();
            while (getline(file, line)) {
                if (line == "<<END_CONTENT>>") break;
                if (!content.empty()) content += "\n";
                content += line;
            }

            insertPoetryNode(node, title, content, genre, mood);
        }
    }

    void clearTree(PoetryNode*& node) {
        if (node) {
            clearTree(node->left);
            clearTree(node->right);
            delete node;
        }
        node = NULL;
    }

public:
    PoetTree() : root(NULL) {}

    void addPoem(string title, string content, string genre, string mood) {
        insertPoetryNode(root, title, content, genre, mood);
    }

    void displayPoems() {
        if (!root) {
            cout << "\n";
            UI::printError("No poems available in this collection.");
        }
        else {
            displayPoems(root);
        }
    }

    void displayPoemsMatching(const string& keyword) {
        if (!root) {
             cout << "\n";
            UI::printError("No poems to search.");
            return;
        }
        searchAndDisplay(root, keyword);
    }

    void searchAndDisplay(PoetryNode* node, const string& keyword) {
        if (!node) return;

        searchAndDisplay(node->left, keyword);

        string lowerTitle = toLower(node->title);
        string lowerGenre = toLower(node->genre);
        string lowerMood = toLower(node->mood);
        string lowerKeyword = toLower(keyword);

        if (lowerTitle.find(lowerKeyword) != string::npos ||
            lowerGenre.find(lowerKeyword) != string::npos ||
            lowerMood.find(lowerKeyword) != string::npos) {
            displayPoemWithPadding(node->title, node->genre, node->mood, node->content);
        }

        searchAndDisplay(node->right, keyword);
    }

    void savePoems(string filename) {
        ofstream file(filename, ios::trunc);
        if (file.is_open()) {
            saveToFile(root, file);
            file.close();
            if (filename != "AllReader_poetry.txt") {
                UI::printSuccess("Poems saved successfully!");
            }
        }
        else {
            UI::printError("Unable to open file for saving.");
        }
    }

    void savePoems_admin(string filename) {
        ofstream file(filename, ios::app);
        if (file.is_open()) {
            saveToFile(root, file);
            file.close();
            if (filename != "AllReader_poetry.txt") {
                UI::printSuccess("Poems saved successfully!");
            }
        }
        else {
            UI::printError("Unable to open file for saving.");
        }
    }

    void loadPoems(string filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            UI::printError("No existing poems to load.");
        }
        clearTree(root);
        loadFromFile(root, file);
        file.close();
        UI::printSuccess("Poems loaded successfully!"); 
    }
};

class SearchNode {
public:
    string keyword;
    SearchNode* next;

    SearchNode(string kw) : keyword(kw), next(NULL) {}
};

class SearchHistory {
private:
    SearchNode* head;

public:
    SearchHistory() : head(NULL) {}

    void addKeyword(string keyword, const string& username) {
        SearchNode* newNode = new SearchNode(keyword);
        newNode->next = head;
        head = newNode;

        ofstream file(username + "_history.txt", ios::app);
        if (file.is_open()) {
            file << keyword << endl;
            file.close();
        }
    }

    void displayHistory(const string& username) {
        while (head) {
            SearchNode* temp = head;
            head = head->next;
            delete temp;
        }

        ifstream file(username + "_history.txt");
        string keyword;
        while (getline(file, keyword)) {
            SearchNode* newNode = new SearchNode(keyword);
            newNode->next = head;
            head = newNode;
        }
        file.close();

        cout << "\n";
        UI::drawMenuBox("Search History", {}); // Just for header look
        
        SearchNode* current = head;
        while (current) {
            cout << UI::PADDING_L << " > " << current->keyword << endl;
            current = current->next;
        }
        cout << endl;
    }
};

class PoetUser {
private:
    string username;
    string password;
    PoetTree poetryTree;
    SearchHistory searchHistory;

public:
    PoetUser(string u, string p) : username(u), password(p) {
        UI::cls();
        cout << UI::PADDING_L << "Loading poetry collection for " << username << "...\n";
        poetryTree.loadPoems(username + "_poetry.txt");
    }

    void submitPoetry() {
        string title, content, genre, mood;
        cout << endl;
        UI::printPrompt("Enter Poetry Title: ");
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, title);
        
        UI::printPrompt("Enter Poetry Genre: ");
        getline(cin, genre);
        
        UI::printPrompt("Enter Mood (happy, sad, etc): ");
        getline(cin, mood);
        
        UI::printPrompt("Enter Content (end with '.' on new line): \n");
        UI::setColor(UI::COLOR_DEFAULT); // White text for poem input
        
        string line;
        ostringstream poemContent;
        while (true) {
            cout << UI::PADDING_L << "   "; // Indent input
            getline(cin, line);
            if (line == ".") break;
            poemContent << line << "\n";
        }
        poetryTree.addPoem(title, poemContent.str(), genre, mood);
    }

    void displayMyPoems() {
        UI::cls();
        UI::drawLine();
        cout << UI::PADDING_L << "         YOUR POETRY COLLECTION\n";
        UI::drawLine();
        poetryTree.displayPoems();
    }

    void savePoetry() {
        poetryTree.savePoems(username + "_poetry.txt");
        poetryTree.savePoems("AllReader_poetry.txt");
    }
};

class LoginManager {
private:
    string filename = "usersP.txt";
    unordered_map<string, string> users;

    void loadUsers() {
        ifstream file(filename);
        if (file.is_open()) {
            string line, username, password;
            while (getline(file, line)) {
                stringstream ss(line);
                getline(ss, username, '|');
                getline(ss, password, '|');
                users[username] = password;
            }
            file.close();
        }
    }

    void saveUsers() {
        ofstream file(filename);
        if (file.is_open()) {
            for (auto& pair : users) {
                file << pair.first << "|" << pair.second << endl;
            }
            file.close();
        }
    }

public:
    LoginManager() {
        loadUsers();
    }

    bool signUp(string username, string password) {
        if (users.find(username) != users.end()) {
            UI::printError("Username already exists. Try a different one.");
            return false;
        }
        users[username] = password;
        saveUsers();
        return true;
    }

    bool login(string username, string password) {
        if (users.find(username) != users.end() && users[username] == password) {
            return true;
        }
        UI::printError("Invalid credentials.");
        return false;
    }

    bool changePassword(string username, string oldPassword, string newPassword) {
        if (users.find(username) != users.end() && users[username] == oldPassword) {
            users[username] = newPassword;
            saveUsers();
            return true;
        }
        UI::printError("Incorrect old password.");
        return false;
    }
};

class LoginManager_R {
private:
    string filename = "usersR.txt";
    unordered_map<string, string> users;

    void loadUsers() {
        ifstream file(filename);
        if (file.is_open()) {
            string line, username, password;
            while (getline(file, line)) {
                stringstream ss(line);
                getline(ss, username, '|');
                getline(ss, password, '|');
                users[username] = password;
            }
            file.close();
        }
    }

    void saveUsers() {
        ofstream file(filename);
        if (file.is_open()) {
            for (auto& pair : users) {
                file << pair.first << "|" << pair.second << endl;
            }
            file.close();
        }
    }

public:
    LoginManager_R() {
        loadUsers();
    }

    bool signUp(string username, string password) {
        if (users.find(username) != users.end()) {
            UI::printError("Username already exists. Try a different one.");
            return false;
        }
        users[username] = password;
        saveUsers();
        return true;
    }

    bool login(string username, string password) {
        if (users.find(username) != users.end() && users[username] == password) {
            return true;
        }
        UI::printError("Invalid credentials.");
        return false;
    }

    bool changePassword(string username, string oldPassword, string newPassword) {
        if (users.find(username) != users.end() && users[username] == oldPassword) {
            users[username] = newPassword;
            saveUsers();
            return true;
        }
        UI::printError("Incorrect old password.");
        return false;
    }
};

class ReaderUser {
private:
    string username;
    string password;
    PoetTree poetryTree1;
    SearchHistory searchHistory;

public:
    ReaderUser(string u, string p) : username(u), password(p) {
        UI::cls();
        cout << UI::PADDING_L << "Loading poetry collection for you!\n";
        poetryTree1.loadPoems("AllReader(approved)_poetry.txt");
    }

    void browsePoetry() {
        UI::cls();
        UI::drawLine();
        cout << UI::PADDING_L << "            BROWSE POETRY\n";
        UI::drawLine();
        poetryTree1.displayPoems();
        cout << endl;
        system("pause");
    }

    void searchPoetry() {
        UI::cls();
        UI::drawLine();
        cout << UI::PADDING_L << "            SEARCH POETRY\n";
        UI::drawLine();
        
        string keyword;
        UI::printPrompt("Enter keyword (title, genre, mood): ");
        cin.ignore();
        getline(cin, keyword);

        searchHistory.addKeyword(keyword, username);
        
        UI::cls();
        cout << UI::PADDING_L << "Results for: " << keyword << "\n";
        UI::drawLine();

        poetryTree1.displayPoemsMatching(keyword);
        cout << endl;
        system("pause");
    }

    void viewSearchHistory() {
        UI::cls();
        searchHistory.displayHistory(username);
        system("pause");
    }
};


// MAIN Function

int main() {
    SetConsoleOutputCP(437);
    system("color 0B"); // Background Black (0), Text Aqua (B) as base

    UI::cls();
    
    LoginManager loginManager;
    LoginManager_R loginManager_R;
    PoetUser* currentPoet = nullptr;
    ReaderUser* currentReader = nullptr;
    int choice;

    while (true) {
        UI::cls();
        
        vector<string> menuOptions;
        menuOptions.push_back("1. Sign Up as Poet");
        menuOptions.push_back("2. Sign Up as Reader");
        menuOptions.push_back("3. Login as Poet");
        menuOptions.push_back("4. Login as Reader");
        menuOptions.push_back("5. Exit");

        UI::drawMenuBox("USER MENU", menuOptions);
        cout << endl;
        UI::printPrompt("Enter your choice: ");
        cin >> choice;

        if ((cin.fail() || choice < 1 || choice > 5) && choice != 10) {
            cin.clear();
            string invalidInput;
            getline(cin, invalidInput);
            UI::printError("Invalid input. Valid options (1-5).");
            Sleep(1500);
            continue;
        }
        else if (choice == 10) {
            UI::cls();
            string c, admin = "AbdulRehman";
            UI::printPrompt("Enter Password to Login as Admin: ");
            c = getPassword();
            if (c != admin) {
                UI::printError("Wrong Password! Access Denied.");
                Sleep(1500);
            }
            else {
                PoetTree poetryTree2;
                poetryTree2.loadPoems("AllReader_poetry.txt");
                int c_opt = 0;
                while (true) {
                    UI::cls();
                    vector<string> adminOpts;
                    adminOpts.push_back("1. Display Unapproved Poetry");
                    adminOpts.push_back("2. Approve All Pending");
                    adminOpts.push_back("3. Delete All Pending");
                    adminOpts.push_back("4. Exit Admin");
                    UI::drawMenuBox("ADMIN DASHBOARD", adminOpts);
                    
                    cout << endl;
                    UI::printPrompt("Choice: ");
                    cin >> c_opt;
                    
                    if (c_opt == 1) {
                        poetryTree2.displayPoems();
                        system("pause");
                    }
                    else if (c_opt == 2) {
                        poetryTree2.savePoems_admin("AllReader(approved)_poetry.txt");
                        emptyFile("AllReader_poetry.txt");
                        UI::printSuccess("All pending poetry approved.");
                        Sleep(1500);
                    }
                    else if (c_opt == 3) {
                        emptyFile("AllReader_poetry.txt");
                        UI::printError("All pending poetry rejected/deleted.");
                        Sleep(1500);
                    }
                    else if (c_opt == 4) {
                        break;
                    }
                    else {
                        UI::printError("Invalid Choice!");
                        Sleep(1500);
                    }
                }
            }
            continue;
        }
        else if (choice == 1) { // Sign Up Poet
            UI::cls();
            string username, password;
            UI::drawMenuBox("POET REGISTRATION", {});
            cout << endl;
            UI::printPrompt("Enter username: ");
            cin >> username;
            UI::printPrompt("Enter password: ");
            password = getPassword();
            if (loginManager.signUp(username, password)) {
                UI::printSuccess("Sign-up successful! Please log in.");
            }
            Sleep(1500);
        }
        else if (choice == 3) { // Login Poet
            UI::cls();
            string username, password;
            UI::drawMenuBox("POET LOGIN", {});
            cout << endl;
            UI::printPrompt("Enter username: ");
            cin >> username;
            UI::printPrompt("Enter password: ");
            password = getPassword();

            if (loginManager.login(username, password)) {
                currentPoet = new PoetUser(username, password);
                while (true) {
                    UI::cls();
                    vector<string> poetOpts;
                    poetOpts.push_back("1. Submit New Poetry");
                    poetOpts.push_back("2. View My Collection");
                    poetOpts.push_back("3. Save Poetry");
                    poetOpts.push_back("4. Change Password");
                    poetOpts.push_back("5. Logout");
                    
                    UI::drawMenuBox("POET DASHBOARD", poetOpts);
                    cout << endl;
                    UI::printPrompt("Choice: ");
                    cin >> choice;

                    if (cin.fail() || choice < 1 || choice > 5) {
                        cin.clear();
                        string invalidInput;
                        getline(cin, invalidInput);
                        UI::printError("Invalid input.");
                        Sleep(1500);
                        continue;
                    }

                    if (choice == 1) {
                        UI::cls();
                        currentPoet->submitPoetry();
                    }
                    else if (choice == 2) {
                        currentPoet->displayMyPoems();
                        system("pause");
                    }
                    else if (choice == 3) {
                        UI::cls();
                        currentPoet->savePoetry();
                        Sleep(1500);
                    }
                    else if (choice == 4) {
                        UI::cls();
                        string oldPassword, newPassword;
                        UI::drawMenuBox("CHANGE PASSWORD", {});
                        cout << endl;
                        UI::printPrompt("Old password: ");
                        oldPassword = getPassword();
                        UI::printPrompt("New password: ");
                        newPassword = getPassword();

                        if (loginManager.changePassword(username, oldPassword, newPassword)) {
                            UI::printSuccess("Password changed successfully.");
                        }
                        Sleep(1500);
                    }
                    else if (choice == 5) {
                        UI::cls();
                        cout << UI::PADDING_L << "Logging out...\n";
                        delete currentPoet;
                        currentPoet = nullptr;
                        Sleep(1000);
                        break;
                    }
                }
            }
            else {
                Sleep(1500);
            }
        }
        else if (choice == 2) { // Sign up Reader
            UI::cls();
            string username, password;
            UI::drawMenuBox("READER REGISTRATION", {});
            cout << endl;
            UI::printPrompt("Enter username: ");
            cin >> username;
            UI::printPrompt("Enter password: ");
            password = getPassword();
            if (loginManager_R.signUp(username, password)) {
                UI::printSuccess("Sign-up successful! Please log in.");
            }
            Sleep(1500);
        }
        else if (choice == 4) { // Login Reader
            UI::cls();
            string username, password;
            UI::drawMenuBox("READER LOGIN", {});
            cout << endl;
            UI::printPrompt("Enter username: ");
            cin >> username;
            UI::printPrompt("Enter password: ");
            password = getPassword();

            if (loginManager_R.login(username, password)) {
                currentReader = new ReaderUser(username, password);
                while (true) {
                    UI::cls();
                    vector<string> readerOpts;
                    readerOpts.push_back("1. Browse Poetry");
                    readerOpts.push_back("2. Search Poetry");
                    readerOpts.push_back("3. View Search History");
                    readerOpts.push_back("4. Change Password");
                    readerOpts.push_back("5. Exit");
                    
                    UI::drawMenuBox("READER DASHBOARD", readerOpts);
                    cout << endl;
                    UI::printPrompt("Choice: ");
                    cin >> choice;

                    if (cin.fail() || choice < 1 || choice > 5) {
                        cin.clear();
                        string invalidInput;
                        getline(cin, invalidInput);
                        UI::printError("Invalid input.");
                        Sleep(1500);
                        continue;
                    }

                    if (choice == 1) {
                        currentReader->browsePoetry();
                    }
                    else if (choice == 2) {
                        currentReader->searchPoetry();
                    }
                    else if (choice == 3) {
                        currentReader->viewSearchHistory();
                    }
                    else if (choice == 4) {
                        UI::cls();
                        string oldPassword, newPassword;
                        UI::drawMenuBox("CHANGE PASSWORD", {});
                        cout << endl;
                        UI::printPrompt("Old password: ");
                        oldPassword = getPassword();
                        UI::printPrompt("New password: ");
                        newPassword = getPassword();

                        if (loginManager_R.changePassword(username, oldPassword, newPassword)) {
                             UI::printSuccess("Password changed successfully.");
                        }
                        Sleep(1500);
                    }
                    else if (choice == 5) {
                        UI::cls();
                        cout << UI::PADDING_L << "Exiting Reader Mode...\n";
                        delete currentReader;
                        currentReader = nullptr;
                        Sleep(1000);
                        break;
                    }
                }
            }
            else {
                Sleep(1500);
            }
        }
        else if (choice == 5) {
            UI::cls();
            cout << "\n\n";
            UI::printCentered("Thank you for using Manzoom.");
            UI::printCentered("Goodbye!");
            cout << "\n\n";
            break;
        }
    }

    return 0;
}

