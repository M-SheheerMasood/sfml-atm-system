#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <iomanip>
#include <string>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <cstdio>
using namespace std;
// libraries used

// global variables to use for file names
string usernamesfile = "User_data.txt";
string passwordfile = "User_pass.txt";
string accountfile = "User_account_info.txt";

int delay(int milliseconds) // func to delay code for lockout
{
    clock_t goal = milliseconds + clock();
    while (goal > clock())
        ;
    return 1;
}

bool uppercheck(string pass, int index = 0) // recursive func that checks if there is a uppercase character in the string given
{
    if (index == pass.length())
    {
        return 0;
    }
    if (isupper(pass[index]))
    {
        return 1;
    }
    return uppercheck(pass, index + 1);
}

bool lowercheck(string pass, int index = 0) // recursive func that checks if there is a lowercase character in the string given
{
    if (index == pass.length())
    {
        return 0;
    }
    if (islower(pass[index]))
    {
        return 1;
    }
    return lowercheck(pass, index + 1);
}

bool numbercheck(string pass, int index = 0) // recursive func that checks if there is a numerical character in the string given
{
    if (index == pass.length())
    {
        return 0;
    }
    if (isdigit(pass[index]))
    {
        return 1;
    }
    return numbercheck(pass, index + 1);
}

bool password_check(string pass) // fucntion that checks if a given string is an acceptable password
{
    if (pass.length() >= 8 && uppercheck(pass) && lowercheck(pass) && numbercheck(pass))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

bool file_append(string line, string filename) // func that adds a given line into a file
{
    fstream file;
    file.open(filename, ios::app);
    file << line << endl;
    file.close();
    return 1;
}

int file_read_check(string user_name, string filename) // func that checks a file for a given string
{
    fstream file;
    string line;
    int counter = 0;
    file.open(filename, ios::in);
    for (; getline(file, line);) // iterating through each line
    {
        if (line == user_name)
        {
            file.close();
            return counter; // returns line number if found
        }
        counter++;
    }
    file.close();
    return -1; // returns -1 if not found
}

string file_line_return(int linenumber, string filename) // func that returns the line at a given index
{
    fstream file;
    string line;
    int counter = 0;
    file.open(filename, ios::in);
    for (; getline(file, line);) // iterating through each line of file
    {
        if (counter == linenumber) // stops when line counter is equal to the given line number
        {
            file.close();
            return line; // returns the line stored at that line number
        }
        counter++;
    }
    file.close();
    return "-1"; // else returns -1
}

bool file_remove_line(int linenum, string filename) // func that removes a full line from a file at the given line number
{
    fstream file;
    string line;
    fstream newfile;
    int counter = 0;
    if (linenum >= 0)
    {
        file.open(filename, ios::in);
        newfile.open("temp.txt", ios::out); // temp file to store data in
        for (; getline(file, line);)        // iterating through each line in the file
        {
            if (linenum != counter) // adds a line from the file to the temp file if its not at the given line number
            {
                newfile << line << endl;
            }

            counter++;
        }
        file.close();
        newfile.close();
        remove(filename.c_str());             // removes the old file
        rename("temp.txt", filename.c_str()); // renames the temp file to the old file
        return 1;
    }
    else
    {
        return 0; // returns if line doesnt exist in file
    }
}

bool file_edit_line(string edit, int linenum, string filename) // func that edits the contents of a line at the given line number
{
    fstream file;
    string line;
    fstream newfile;
    int counter = 0;
    if (linenum >= 0)
    {
        file.open(filename, ios::in);
        newfile.open("temp.txt", ios::out); // tenp file to store data in
        for (; getline(file, line);)        // iterating through each line in the file
        {
            if (counter == linenum) // adds the edited line where it was initially
            {
                newfile << edit << endl;
            }
            else // adds a line from the file to the temp file if its not at the given line number
            {
                newfile << line << endl;
            }

            counter++;
        }
        file.close();
        newfile.close();
        remove(filename.c_str());             // removes the old file
        rename("temp.txt", filename.c_str()); // renames the temp file to the old file
        return 1;
    }
    else
    {
        return 0; // return if line dosnt exist in file
    }
}

bool is_digits(string &str) // func to check if given string only contains digits
{
    if (str.empty()) // if string = ""
    {
        return 0;
    }
    for (char ch : str) // iterating through each element of the string as a character
    {
        if (!isdigit(ch))
        {
            return 0;
        }
    }
    return 1; // true if only digits
}

int main() // main func where GUI is running and the objects are declared
{
    // properties for the repeating buttons
    int buttonsizeX = 120;
    int buttonsizeY = 70;
    int fontsize = 25;

    sf::RenderWindow window(sf::VideoMode(700, 500), "ATM SYSTEM"); // making window

    sf::Font font;
    font.loadFromFile("times.ttf"); // choosing font (paste path of font file in your computer)

    sf::RectangleShape start(sf::Vector2f(200, 100)); // button with variable name start (click able area)
    start.setPosition(250, 200);
    start.setFillColor(sf::Color::Cyan);

    sf::Text starttext("Start", font, 50); // text displayed over the start button
    starttext.setPosition(300, 220);
    starttext.setFillColor(sf::Color::Black);

    sf::RectangleShape createbutton(sf::Vector2f(buttonsizeX, buttonsizeY)); // button with variable name create (click able area)
    createbutton.setPosition(10, 100);
    createbutton.setFillColor(sf::Color::Yellow);

    sf::Text createtext("Create\nAccount", font, fontsize); // text displayed over the create button
    createtext.setPosition(20, 105);
    createtext.setFillColor(sf::Color::Black);

    sf::RectangleShape deletebutton(sf::Vector2f(buttonsizeX, buttonsizeY)); // button with variable name delete (click able area)
    deletebutton.setPosition(570, 105);
    deletebutton.setFillColor(sf::Color::Yellow);

    sf::Text deletetext("Delete\nAccount", font, fontsize); // text displayed over the delete button
    deletetext.setPosition(580, 110);
    deletetext.setFillColor(sf::Color::Black);

    sf::RectangleShape loginbutton(sf::Vector2f(buttonsizeX, buttonsizeY)); // button with variable login (click able area)
    loginbutton.setPosition(10, 300);
    loginbutton.setFillColor(sf::Color::Cyan);

    sf::Text logintext("Login", font, 35); // text displayed over the login button
    logintext.setPosition(20, 310);
    logintext.setFillColor(sf::Color::Black);

    sf::RectangleShape logoutbutton(sf::Vector2f(buttonsizeX, buttonsizeY)); // button with variable logout (click able area)
    logoutbutton.setPosition(570, 300);
    logoutbutton.setFillColor(sf::Color::Cyan);

    sf::Text logouttext("Logout", font, 35); // text displayed over the logout button
    logouttext.setPosition(580, 310);
    logouttext.setFillColor(sf::Color::Black);

    sf::RectangleShape depositbutton(sf::Vector2f(buttonsizeX, buttonsizeY)); // button with variable deposit (click able area)
    depositbutton.setPosition(10, 200);
    depositbutton.setFillColor(sf::Color::Green);

    sf::Text deposittext("Deposit\nMoney", font, fontsize); // text displayed over the deposit button
    deposittext.setPosition(20, 205);
    deposittext.setFillColor(sf::Color::Black);

    sf::RectangleShape withdrawbutton(sf::Vector2f(buttonsizeX, buttonsizeY)); // button with variable name withdraw (click able area)
    withdrawbutton.setPosition(570, 200);
    withdrawbutton.setFillColor(sf::Color::Green);

    sf::Text withdrawtext("Withdraw\nMoney", font, fontsize); // text displayed over the withdraw button
    withdrawtext.setPosition(580, 205);
    withdrawtext.setFillColor(sf::Color::Black);

    sf::Text inputprompt1("", font, 30); // displays prompt in location 1
    inputprompt1.setPosition(170, 100);
    inputprompt1.setFillColor(sf::Color::White);

    sf::Text inputtext1("", font, 30); // displays text in location 1
    inputtext1.setPosition(180, 150);
    inputtext1.setFillColor(sf::Color::White);

    sf::Text inputprompt2("", font, 30); // displays prompt in location 2
    inputprompt2.setPosition(170, 250);
    inputprompt2.setFillColor(sf::Color::White);

    sf::Text inputtext2("", font, 30); // displays text in location 2
    inputtext2.setPosition(180, 300);
    inputtext2.setFillColor(sf::Color::White);

    sf::Text outputprompt("", font, 20); // displays output
    outputprompt.setPosition(50, 390);
    outputprompt.setFillColor(sf::Color::White);

    sf::RectangleShape cursor1(sf::Vector2f(2, 28)); // displays text cursor in location 1
    cursor1.setFillColor(sf::Color::White);
    cursor1.setPosition(inputtext1.getPosition().x, inputtext1.getPosition().y + 6.5);

    sf::RectangleShape cursor2(sf::Vector2f(2, 28)); // displays text cursor in location 2
    cursor2.setFillColor(sf::Color::White);
    cursor2.setPosition(inputtext2.getPosition().x, inputtext2.getPosition().y + 6.5);

    sf::Clock clock;
    bool showcursor1 = true;
    bool showcursor2 = true;

    string user_input1, user_input2, user_name, user_password; // declaring checks for button logic
    bool is_typing1 = false, is_typing2 = false, is_start = false, is_logout = true, is_create_acc = false, is_delete_acc = false, is_login = false, is_withdraw = false, is_deposit = false, logged_in = false;
    int numberofline, logincounter = 0, usernumber = -1;
    while (window.isOpen()) // window loop
    {
        sf::Event event;
        while (window.pollEvent(event)) // basically updates when something changes
        {
            if (event.type == sf::Event::Closed) // for closing window
            {
                window.close();
            }
            if (logged_in) // showing balance when logged in
            {
                inputprompt1.setString("Balance:");
                inputtext1.setString(file_line_return(usernumber, accountfile));
                logincounter = 0;
            }
            if (logincounter >= 5) // lockout functionality , pauses/delays the code for given time
            {
                outputprompt.setString("\n\n                          You have been locked out for 10 seconds");
                window.draw(outputprompt);
                window.display();
                delay(10000);
                // setting everything back to start
                logincounter = 0;
                is_logout = true;
                is_start = false;
                user_input1.clear();
                user_input2.clear();
                inputprompt1.setString("");
                inputprompt2.setString("");
                outputprompt.setString("");
                inputtext1.setString("");
                inputtext2.setString("");
                is_typing1 = false;
                is_typing2 = false;
                is_create_acc = false;
                is_delete_acc = false;
                is_login = false;
                is_withdraw = false;
                is_deposit = false;
                logged_in = false;
                sf::FloatRect textBounds1 = inputtext1.getGlobalBounds();
                cursor1.setPosition(textBounds1.left + textBounds1.width, inputtext1.getPosition().y + 6.5);
                sf::FloatRect textBounds2 = inputtext2.getGlobalBounds();
                cursor2.setPosition(textBounds2.left + textBounds2.width, inputtext2.getPosition().y + 6.5);
            }

            if (is_typing1 && event.type == sf::Event::TextEntered) // for displaying entered string location 1
            {
                if (event.text.unicode == '\b') // for backspace
                {
                    if (!user_input1.empty())
                    {
                        user_input1.pop_back();
                    }
                }
                else if (event.text.unicode == '\r') // for enter
                {
                    if (is_create_acc && file_read_check(user_input1, usernamesfile) < 0) // once string is entered it checks for create account
                    {
                        is_typing1 = false;
                        is_typing2 = true;
                        outputprompt.setString("");
                    }
                    else if (is_create_acc && file_read_check(user_input1, usernamesfile) >= 0)
                    {
                        outputprompt.setString("                                         User already exists!");
                    }
                    if (is_delete_acc && file_read_check(user_input1, usernamesfile) >= 0) // once string is entered it checks for delete account
                    {
                        is_typing1 = false;
                        is_typing2 = true;
                        outputprompt.setString("");
                    }
                    else if (is_delete_acc && file_read_check(user_input1, usernamesfile) < 0)
                    {
                        outputprompt.setString("                                           User does not exist!");
                    }
                    if (is_login && file_read_check(user_input1, usernamesfile) >= 0) // once string is entered it checks for login
                    {
                        is_typing1 = false;
                        is_typing2 = true;
                        outputprompt.setString("");
                    }
                    else if (is_login && file_read_check(user_input1, usernamesfile) < 0)
                    {
                        outputprompt.setString("                                           User does not exist!");
                    }
                }
                else if (event.text.unicode < 128) // for characters
                {
                    user_input1 += static_cast<char>(event.text.unicode);
                }
                inputtext1.setString(user_input1);
                sf::FloatRect textBounds1 = inputtext1.getGlobalBounds();
                cursor1.setPosition(textBounds1.left + textBounds1.width, inputtext1.getPosition().y + 6.5);
            }

            else if (is_typing2 && event.type == sf::Event::TextEntered) // for displaying entered string location 2
            {
                if (event.text.unicode == '\b') // for backspace
                {
                    if (!user_input2.empty())
                    {
                        user_input2.pop_back();
                    }
                }
                else if (event.text.unicode == '\r') // for enter
                {
                    if (is_create_acc && password_check(user_input2)) // once string is entered it creates account
                    {
                        is_typing1 = false;
                        is_typing2 = false;
                        file_append(user_input1, usernamesfile); // writing data for new user
                        file_append(user_input2, passwordfile);
                        file_append("0", accountfile);
                        outputprompt.setString("                                   Account Created Successfully!");
                        // to clear screen after account creation
                        user_input1.clear();
                        user_input2.clear();
                        inputtext1.setString("");
                        inputtext2.setString("");
                        inputprompt1.setString("");
                        inputprompt2.setString("");
                        sf::FloatRect textBounds1 = inputtext1.getGlobalBounds();
                        cursor1.setPosition(textBounds1.left + textBounds1.width, inputtext1.getPosition().y + 6.5);
                        sf::FloatRect textBounds2 = inputtext2.getGlobalBounds();
                        cursor2.setPosition(textBounds2.left + textBounds2.width, inputtext2.getPosition().y + 6.5);
                    }
                    else if (is_create_acc && password_check(user_input2) == 0)
                    {
                        outputprompt.setString("   Password must be 8 charaters long!\n   It should also contain a lowercase letter, Uppercase Letter and a digit!");
                    }
                    if (is_delete_acc)
                    {
                        numberofline = file_read_check(user_input1, usernamesfile);
                        if (file_line_return(numberofline, passwordfile) == user_input2) // verifying for account deletion
                        {
                            file_remove_line(numberofline, usernamesfile); // removing the account data
                            file_remove_line(numberofline, passwordfile);
                            file_remove_line(numberofline, accountfile);
                            outputprompt.setString("                                    Account Deleted Successfully!");
                            is_typing1 = false;
                            is_typing2 = false;
                            // to clear screen after account deletion
                            user_input1.clear();
                            user_input2.clear();
                            inputtext1.setString("");
                            inputtext2.setString("");
                            inputprompt1.setString("");
                            inputprompt2.setString("");
                            sf::FloatRect textBounds1 = inputtext1.getGlobalBounds();
                            cursor1.setPosition(textBounds1.left + textBounds1.width, inputtext1.getPosition().y + 6.5);
                            sf::FloatRect textBounds2 = inputtext2.getGlobalBounds();
                            cursor2.setPosition(textBounds2.left + textBounds2.width, inputtext2.getPosition().y + 6.5);
                        }
                        else
                        {
                            outputprompt.setString("                                        Incorrect Password!");
                        }
                    }
                    if (is_login)
                    {
                        numberofline = file_read_check(user_input1, usernamesfile);
                        if (file_line_return(numberofline, passwordfile) == user_input2) // verifying for account login
                        {
                            usernumber = numberofline;
                            logged_in = true;
                            is_typing1 = false;
                            is_typing2 = false;
                            outputprompt.setString("                                       Logged in Successfully!");
                            // clearing screen after login
                            user_input1.clear();
                            user_input2.clear();
                            inputtext1.setString("");
                            inputtext2.setString("");
                            inputprompt1.setString("");
                            inputprompt2.setString("");
                            sf::FloatRect textBounds1 = inputtext1.getGlobalBounds();
                            cursor1.setPosition(textBounds1.left + textBounds1.width, inputtext1.getPosition().y + 6.5);
                            sf::FloatRect textBounds2 = inputtext2.getGlobalBounds();
                            cursor2.setPosition(textBounds2.left + textBounds2.width, inputtext2.getPosition().y + 6.5);
                        }
                        else
                        {
                            outputprompt.setString("                                        Incorrect Password!\n                                              " + to_string(4 - logincounter) + " tries left");
                            logincounter++;
                        }
                    }

                    if (is_withdraw && logged_in && is_digits(user_input2))
                    {
                        if (stoi(user_input2) > stoi(file_line_return(usernumber, accountfile))) // verifies for withdrawing money
                        {
                            outputprompt.setString("                                Invalid! Insufficient balance!");
                        }
                        else if (stoi(user_input2) <= stoi(file_line_return(usernumber, accountfile)))
                        {
                            if (stoi(user_input2) > 0)
                            {
                                string add = to_string(stoi(file_line_return(usernumber, accountfile)) - stoi(user_input2)); // updating balance after withdrawl
                                file_edit_line(add, usernumber, accountfile);
                                outputprompt.setString("                                   Withdrawl of " + user_input2 + " Successful");
                                // clearing screen after login
                                user_input1.clear();
                                user_input2.clear();
                                inputtext2.setString("");
                                sf::FloatRect textBounds1 = inputtext1.getGlobalBounds();
                                cursor1.setPosition(textBounds1.left + textBounds1.width, inputtext1.getPosition().y + 6.5);
                                sf::FloatRect textBounds2 = inputtext2.getGlobalBounds();
                                cursor2.setPosition(textBounds2.left + textBounds2.width, inputtext2.getPosition().y + 6.5);
                            }
                            else
                            {
                                outputprompt.setString("                                      Invalid Amount!");
                            }
                        }
                    }
                    else if (!is_digits(user_input2) && is_withdraw && logged_in)
                    {
                        outputprompt.setString("                                    Enter Positive Digits only!");
                    }
                    if (is_deposit && logged_in && is_digits(user_input2)) // verifies for depositing money
                    {
                        if (stoi(user_input2) <= 0)
                        {
                            outputprompt.setString("                                      Invalid Ammount!");
                        }
                        else if (stoi(user_input2) > 0)
                        {
                            string add = to_string(stoi(file_line_return(usernumber, accountfile)) + stoi(user_input2)); // updating balance
                            file_edit_line(add, usernumber, accountfile);
                            outputprompt.setString("                                   Deposit of " + user_input2 + " Successful");
                            // clearing screen after login
                            user_input1.clear();
                            user_input2.clear();
                            inputtext2.setString("");
                            sf::FloatRect textBounds1 = inputtext1.getGlobalBounds();
                            cursor1.setPosition(textBounds1.left + textBounds1.width, inputtext1.getPosition().y + 6.5);
                            sf::FloatRect textBounds2 = inputtext2.getGlobalBounds();
                            cursor2.setPosition(textBounds2.left + textBounds2.width, inputtext2.getPosition().y + 6.5);
                        }
                    }
                    else if (!is_digits(user_input2) && is_deposit && logged_in)
                    {
                        outputprompt.setString("                                Enter Positive Digits only!");
                    }
                }
                else if (event.text.unicode < 128) // for characters
                {
                    user_input2 += static_cast<char>(event.text.unicode);
                }
                inputtext2.setString(user_input2);
                sf::FloatRect textBounds2 = inputtext2.getGlobalBounds();
                cursor2.setPosition(textBounds2.left + textBounds2.width, inputtext2.getPosition().y + 6.5);
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) // checking if mouse is clicked
            {

                sf::Vector2i mousePos = sf::Mouse::getPosition(window);                                 // getting pos of mouse click
                if (start.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)) && is_logout) // checking is click is on button start
                {
                    // logic for button showing and pressing avalability
                    is_start = true;
                    is_logout = false;
                }
                else if (logoutbutton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)) && is_start) // checking is click is on button logout
                {
                    // logic for button showing and pressing avalability
                    is_logout = true;
                    is_start = false;
                    user_input1.clear();
                    user_input2.clear();
                    inputprompt1.setString("");
                    inputprompt2.setString("");
                    outputprompt.setString("");
                    inputtext1.setString("");
                    inputtext2.setString("");
                    is_typing1 = false;
                    is_typing2 = false;
                    is_create_acc = false;
                    is_delete_acc = false;
                    is_login = false;
                    is_withdraw = false;
                    is_deposit = false;
                    logged_in = false;
                    sf::FloatRect textBounds1 = inputtext1.getGlobalBounds();
                    cursor1.setPosition(textBounds1.left + textBounds1.width, inputtext1.getPosition().y + 6.5);
                    sf::FloatRect textBounds2 = inputtext2.getGlobalBounds();
                    cursor2.setPosition(textBounds2.left + textBounds2.width, inputtext2.getPosition().y + 6.5);
                }
                else if (createbutton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)) && is_start && !is_withdraw && !is_deposit) // checking is click is on button create
                {
                    // logic for button showing and pressing avalability
                    is_create_acc = true;
                    inputprompt1.setString("Enter Username:");
                    inputprompt2.setString("Enter Password:");
                    is_typing1 = true;
                    is_typing2 = false;
                    inputtext1.setString("");
                    inputtext2.setString("");
                    user_input1.clear();
                    user_input2.clear();
                    outputprompt.setString("");
                    is_delete_acc = false;
                    is_login = false;
                    is_withdraw = false;
                    is_deposit = false;
                    logged_in = false;
                    sf::FloatRect textBounds1 = inputtext1.getGlobalBounds();
                    cursor1.setPosition(textBounds1.left + textBounds1.width, inputtext1.getPosition().y + 6.5);
                    sf::FloatRect textBounds2 = inputtext2.getGlobalBounds();
                    cursor2.setPosition(textBounds2.left + textBounds2.width, inputtext2.getPosition().y + 6.5);
                }
                else if (deletebutton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)) && is_start && !is_withdraw && !is_deposit) // checking is click is on button delete
                {
                    // logic for button showing and pressing avalability
                    is_delete_acc = true;
                    inputprompt1.setString("Enter Username:");
                    inputprompt2.setString("Enter Password:");
                    is_typing1 = true;
                    is_typing2 = false;
                    inputtext1.setString("");
                    inputtext2.setString("");
                    user_input1.clear();
                    user_input2.clear();
                    outputprompt.setString("");
                    is_create_acc = false;
                    is_login = false;
                    is_withdraw = false;
                    is_deposit = false;
                    logged_in = false;
                    sf::FloatRect textBounds1 = inputtext1.getGlobalBounds();
                    cursor1.setPosition(textBounds1.left + textBounds1.width, inputtext1.getPosition().y + 6.5);
                    sf::FloatRect textBounds2 = inputtext2.getGlobalBounds();
                    cursor2.setPosition(textBounds2.left + textBounds2.width, inputtext2.getPosition().y + 6.5);
                }
                else if (loginbutton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)) && is_start && !is_withdraw && !is_deposit) // checking is click is on button login
                {
                    // logic for button showing and pressing avalability
                    is_login = true;
                    inputprompt1.setString("Enter Username:");
                    inputprompt2.setString("Enter Password:");
                    is_typing1 = true;
                    is_typing2 = false;
                    inputtext1.setString("");
                    inputtext2.setString("");
                    user_input1.clear();
                    user_input2.clear();
                    outputprompt.setString("");
                    is_create_acc = false;
                    is_delete_acc = false;
                    is_withdraw = false;
                    is_deposit = false;
                    logged_in = false;
                    sf::FloatRect textBounds1 = inputtext1.getGlobalBounds();
                    cursor1.setPosition(textBounds1.left + textBounds1.width, inputtext1.getPosition().y + 6.5);
                    sf::FloatRect textBounds2 = inputtext2.getGlobalBounds();
                    cursor2.setPosition(textBounds2.left + textBounds2.width, inputtext2.getPosition().y + 6.5);
                }
                else if (depositbutton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)) && is_start && logged_in) // checking is click is on button deposit
                {
                    // logic for button showing and pressing avalability
                    is_deposit = true;
                    inputprompt2.setString("Amount to Deposit:");
                    is_typing1 = false;
                    is_typing2 = true;
                    inputtext2.setString("");
                    user_input1.clear();
                    user_input2.clear();
                    outputprompt.setString("");
                    is_create_acc = false;
                    is_delete_acc = false;
                    is_login = false;
                    is_withdraw = false;
                    sf::FloatRect textBounds1 = inputtext1.getGlobalBounds();
                    cursor1.setPosition(textBounds1.left + textBounds1.width, inputtext1.getPosition().y + 6.5);
                    sf::FloatRect textBounds2 = inputtext2.getGlobalBounds();
                    cursor2.setPosition(textBounds2.left + textBounds2.width, inputtext2.getPosition().y + 6.5);
                }
                else if (withdrawbutton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)) && is_start && logged_in) // checking is click is on button withdraw
                {
                    // logic for button showing and pressing avalability
                    is_withdraw = true;
                    inputprompt2.setString("Amount to withdraw:");
                    is_typing1 = false;
                    is_typing2 = true;
                    inputtext2.setString("");
                    user_input1.clear();
                    user_input2.clear();
                    outputprompt.setString("");
                    is_create_acc = false;
                    is_delete_acc = false;
                    is_login = false;
                    is_deposit = false;
                    sf::FloatRect textBounds1 = inputtext1.getGlobalBounds();
                    cursor1.setPosition(textBounds1.left + textBounds1.width, inputtext1.getPosition().y + 6.5);
                    sf::FloatRect textBounds2 = inputtext2.getGlobalBounds();
                    cursor2.setPosition(textBounds2.left + textBounds2.width, inputtext2.getPosition().y + 6.5);
                }
            }
        }

        if (clock.getElapsedTime().asSeconds() > 0.5f) // for cursor toggle
        {
            showcursor1 = !showcursor1;
            showcursor2 = !showcursor2;
            clock.restart();
        }
        // 'drawing' the window
        window.clear(sf::Color::Black);
        // implementing the button showing logic
        if (is_typing1 && showcursor1)
        {
            window.draw(cursor1);
        }
        else if (is_typing2 && showcursor2)
        {
            window.draw(cursor2);
        }
        if (is_logout)
        {
            window.draw(start);
            window.draw(starttext);
        }
        else if (is_start)
        {
            window.draw(logoutbutton);
            window.draw(logouttext);
            if (!logged_in)
            {
                window.draw(createbutton);
                window.draw(createtext);
                window.draw(deletebutton);
                window.draw(deletetext);
                window.draw(loginbutton);
                window.draw(logintext);
                if (is_create_acc || is_delete_acc || is_login)
                {
                    window.draw(inputprompt1);
                    window.draw(inputtext1);
                    window.draw(inputprompt2);
                    window.draw(inputtext2);
                    window.draw(outputprompt);
                }
            }
            else if (logged_in)
            {
                window.draw(depositbutton);
                window.draw(deposittext);
                window.draw(withdrawbutton);
                window.draw(withdrawtext);
                window.draw(inputprompt1);
                window.draw(inputtext1);
                window.draw(inputprompt2);
                window.draw(inputtext2);
                window.draw(outputprompt);
            }
        }
        window.display();
    }
    return 0;
}
