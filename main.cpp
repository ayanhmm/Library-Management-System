#include "inclusions.h"
using namespace std;
#define MAX 200

void checkpoint(){
    cout<<endl;
    for(int i=0; i<30; i++) cout<<"-";
    cout<<endl;
}

// declaring commonly used variables
int i = 0, j = 0, iterator1, iterator2, iterator3, current_pos = 0;
string username[MAX];
string password[MAX];
int student_array[MAX];
string choice;
string line_username, line_password, lines, temp, temp1;

// declaring all file paths
string cppfile_path = "/Users/ayanmahajan/Downloads/Vs Code/Library-Management-System/";
string inside_file_path = "Library-Management-System/Library-Management-system/Library-Management-System/";
string common_path = cppfile_path + inside_file_path;
string userfile_path = common_path + "user_file.txt";
string passwordfile_path = common_path + "password_file.txt";
string student_details_path = common_path + "student_details.txt";
string book_list_path = common_path + "book.txt";


class login
{
private:
    string user;
    string pass;

public:
    int check();
    string registeration();
    void display();
    void change_password();
    void exit();
    // void append();
    int initialize();
};

class book
{
private:
    int number;

public:
    void check_in();
    void check_out();

    // void due_details();
    // void date_enroll();
    // void reset_enroll();
};

class student
{
private:
    string student_name;
    int student_id;

public:
    void add_student();
    int edit_student();
    void view_student_details(int w);
    void list_all_students();
    int initialize();
};

/// Add student to database for able to issue books
void student ::add_student()
{
    checkpoint();
    cout << "Enter the name of student to add: ";
    cin >> student_name;
    cout << "Enter the student ID(only numbers): ";
    cin >> student_id;
    checkpoint();
    fstream studentfile(student_details_path, ios::app);
    studentfile << student_name << " ";
    studentfile << student_id << endl;
    student_array[current_pos] = student_id;
    studentfile.close();
    current_pos = current_pos + 1;
}

/// View the details of particular student
// compares the date of issue with current date
// uses ctime library to get time
//  converts it into readable format


void student ::view_student_details(int w)
{
    time_t tt;
//    The time_t type in C++ is used to represent time in a system-independent way. It's typically used to store the number of seconds since the Unix epoch
    
    struct tm *ti;
    time(&tt);
    ti = localtime(&tt);
//    time_t now = time(0);
//    struct tm *ltm = localtime(&now);

    fstream studentfile(student_details_path, ios::in);

    cout << endl;
    int y = 0;
    while (y < current_pos)
    {
        if (student_array[y] == w)
        {
            break;
        }
        y++;
    }
    y = y + 1;
    if (y == current_pos + 1)
    {
        checkpoint();
        cout << "Not found" << endl;
        checkpoint();
    }
    else
    {
        checkpoint();
        cout << "The entered ID is in line no.: " << y << endl;
        fstream studentfile(student_details_path, ios::in);
        int lineno = 0;
        do
        {
            if (lineno == y)
            {
                cout << "Student name and ID: " << lines << endl;
                checkpoint();
                break;
            }
            lineno++;

        } while (getline(studentfile, lines));
        fstream file(book_list_path, ios::in);
        string str;
        cout << "The list of checked out books under ID: " << w << endl;
        while (getline(file, str))
        {
            smatch matches;
            regex reg2("([0-9]+)");
//            sorta like string matching
            regex_search(str, matches, reg2);
            if (matches.str(1) == to_string(w))
            {
                regex reg("[0-9]+ (.*)");
                sregex_iterator currentmatch(str.begin(), str.end(), reg);
                sregex_iterator lastmatch;

                while (currentmatch != lastmatch)
                {
                    smatch match = *currentmatch;
                    cout << matches.str(1) << ": " << match.str() << endl;
                    currentmatch++;
                }
            }
        }
        checkpoint();
        cout << endl;
        file.close();
    }
}

/// Edit the details of particular student (issue or return)
int student ::edit_student()
{
    cout << '\n';
    int id_temp;
    checkpoint();
    cout << "Enter the student ID: ";
    cin >> id_temp;
    int i = 0;
    while (i < MAX)
    {
        if (id_temp == student_array[i])
        {
            iterator3 = id_temp;
            checkpoint();
            cout << "1:Issue (check out) a book" << endl;
            cout << "2:Return (check in) a book" << endl;
            book b;
            int choice2;
            cin >> choice2;
            switch (choice2)
            {
            case 1:
            {
                b.check_out();
                break;
            }
            case 2:
            {
                b.check_in();
                break;
            }
            default:
            {
                checkpoint();
                cout << "Incorrect entry" << endl;
                checkpoint();
                break;
            }
            }

            break;
        }
        else
        {
            i++;
        }
        if (i == MAX)
        {
            checkpoint();
            cout << "No student found" << endl;
            checkpoint();
        }
    }

    return iterator3;
}

/// Check out of book (issuing the book)
void book ::check_out()
{
    string book;
    fstream booklist(book_list_path, ios::app | ios::out);
    checkpoint();
    cout << "Enter the number books to be issued: ";
    cin >> number;
    int i = 0;
    cin.ignore();
    time_t tt;
    struct tm *ti;
    time(&tt);
    ti = localtime(&tt);
    checkpoint();
    cout << "Issue Day, Date and Time is: " << endl;
    cout << "Day Month Date Time Year" << endl;
    cout << asctime(ti);
    checkpoint();
    time_t now = time(0);
    struct tm *ltm = localtime(&now);
    int upload_temp;
    char upload[50];
    
//    upload_temp = sprintf(upload, "%02d/%02d/%04d", ltm->tm_mday, 1 + ltm->tm_mon, 1900 + ltm->tm_year);
//    'sprintf' is deprecated: This function is provided for compatibility reasons only.  Due to security concerns inherent in the design of sprintf(3), it is highly recommended that you use snprintf(3) instead
    
    upload_temp = snprintf(upload, sizeof(upload), "%02d/%02d/%04d", ltm->tm_mday, 1 + ltm->tm_mon, 1900 + ltm->tm_year);

    while (i < number)
    {
        checkpoint();
        cout << "Enter the name of book: ";
        getline(cin, book);
        booklist << iterator3 << " " << book << " " << upload << endl;
        i++;
    }
    checkpoint();
    cout << "Books issued" << endl;
    checkpoint();
    booklist.close();
}

/// Printing all Students who have took membership
void student ::list_all_students()
{
    checkpoint();
    string alpha("");
    string num("");
    fstream studentfile(student_details_path, ios::in);
    string temp;
    while (getline(studentfile, temp))
    {
        for (int i = 0; i < temp.length(); i++)
        {

            if ((temp[i] >= 'A' && temp[i] <= 'Z') ||
                (temp[i] >= 'a' && temp[i] <= 'z') ||
                (temp[i] == ' '))
            {
                alpha = alpha + temp[i];
            }
            if (isdigit(temp[i]))
            {
                num = num + temp[i];
            }
        }
        cout << "Student name: " << alpha << "---";
        cout << "Student ID: " << num << endl;
        num = "";
        alpha = "";
    }
    checkpoint();
    studentfile.close();
}

/// Check in of book by student (Returning the book)
void book ::check_in()
{
    string stri;
    string str, ee[MAX];
    int h;
    int j = 0;
    fstream file(book_list_path, ios::in);
    while (getline(file, str))
    {
        smatch matches;
        regex reg2("([0-9]+)");
        regex_search(str, matches, reg2);
        if (matches.str(1) == to_string(iterator3))
        {
            regex reg("[0-9]+ (.*)");
            sregex_iterator currentmatch(str.begin(), str.end(), reg);
            sregex_iterator lastmatch;
            while (currentmatch != lastmatch)
            {
                smatch match = *currentmatch;
                ee[j] = match.str();
                currentmatch++;
            }
            j++;
        }
    }
    file.close();
    if (j == 0)
    {
        checkpoint();
        cout << "No entry found in that ID" << endl;
        checkpoint();
    }
    else
    {
        checkpoint();
        cout << "what do u want to remove in: " << endl;
        for (int i = 0; i < j; i++)
        {
            cout << i + 1 << ": " << ee[i] << endl;
        }
        checkpoint();
        cin >> h;
        int i;
        int c = 0;
        for (i = 0; i < j; i++)
        {
            if (ee[i] != ee[h - 1])
            {
                c++;
            }
            else
            {
                fstream f(book_list_path, ios::in);
                fstream temp("temp.txt", ios::out);
                while (getline(f, stri))
                {
                    if (stri != ee[h - 1])
                    {
                        temp << stri << endl;
                    }
                }
                f.close();
                temp.close();
                remove("book.txt");
                rename("temp.txt", "book.txt");
            }
        }

        if (c == j)
        {
            checkpoint();
            cout << "Not found" << '\n';
            checkpoint();
        }
        else
        {
            checkpoint();
            cout << "Removed successfully" << '\n';
            checkpoint();
        }
    }
}

/// Initializing (the code that runs first of all)
///  read student data from student details  file, extract integers from the file's content, and store those integers in an array called student_array. The function returns the final position in the array, which represents the number of valid entries processed.
int student ::initialize()
{
    ifstream studentfile(student_details_path);
    if (studentfile.is_open())
    {
        string lines;
        while (!studentfile.eof())
        {
            getline(studentfile, lines);
            stringstream ss(lines); 
            // When you write stringstream ss(lines);, you are initializing a stringstream object ss with the content of the lines string
//            initializes a stringstream object ss with the content of the lines string. This allows us to treat the line as a stream, making it easy to extract data from it.
            string tem;
            int fou;
            while (ss >> temp)
            {
                if (stringstream(temp) >> fou)
                {
                    student_array[current_pos] = fou;
                }
            }
            current_pos++;
        }
        current_pos = current_pos - 1;
    }
    else
    {
        current_pos = 0;
    }

    studentfile.close();

    return current_pos;
}

/// Initializing (the code that runs first of all)
/// read usernames from user file and passwords from passwords file ->  store them in separate arrays.
int login ::initialize()
{
    fstream passfile(passwordfile_path);
    fstream userfile(userfile_path);

    if (userfile.is_open())
    {
        while (!userfile.eof())
        {
            getline(userfile, line_username);
            username[i] = line_username;
            i++;
        }
        i = i - 1;
    }
    else
    {
        i = 0;
    }
    userfile.close();

    if (passfile.is_open())
    {
        while (!passfile.eof())
        {
            getline(passfile, line_password);
            password[j] = line_password;
            j++;
        }
        j = j - 1;
    }
    else
    {
        j = 0;
    }
    passfile.close();

    return i;
//    return j;
}

/// Registering a user to control the whole system
string login ::registeration()
{
    ifstream userfile(userfile_path);
    checkpoint();
    cout << "Do u have an account? yes or no" << endl;
    cin >> choice;
    if (choice == "yes")
    {
        cin.ignore();
        check();
    }
    else if (choice == "no")
    {
        checkpoint();
        cout << "Type your New Username: " << endl;
        cin.ignore();
        getline(cin, user);
        iterator2 = 0;
        while (getline(userfile, line_username))
        {
            if (line_username == user)
            {
                iterator2++;
            }
        }
        userfile.close();
        fstream passfile(passwordfile_path, ios::app | ios::out);
        fstream userfi(userfile_path, ios::app | ios::out);
        if (iterator2 == 1)
        {
            checkpoint();
            cout << "Same username existing in database\nPlease use another username to register" << endl;
            checkpoint();
            registeration();
        }
        else
        {
            userfi << user << endl;
            username[i] = user;
            checkpoint();
            cout << "Type your New Password: " << endl;
            getline(cin, pass);
            passfile << pass << endl;
            password[j] = pass;
            checkpoint();
            cout << endl
                 << "Registered successfully" << endl;
            checkpoint();
            check();
        }
        passfile.close();
        userfi.close();
    }
    else
    {
        checkpoint();
        cout << "Invalid Entry" << endl
             << endl;
        checkpoint();
        registeration();
    }

    return choice;
}

/// Check for the credentials while logging in
int login ::check()
{
    checkpoint();
    cout << "enter the username: ";
    getline(cin, user);
    iterator1 = 0;
    do
    {
        if (user == username[iterator1])
        {
            checkpoint();
            cout << "enter the password: " << endl;
            cout << "if you have forgot the password, type forget" << endl;
            getline(cin, pass);
            if (pass == password[iterator1])
            {
                cout << endl;
                checkpoint();
                cout << "You are now logged in" << endl;
                checkpoint();
                break;
            }
            else if (pass == "forget")
            {
                checkpoint();
                cout << "enter the same username again" << endl;
                getline(cin, temp1);
                if (temp1 == username[iterator1])
                {
                    cout << endl;
                    checkpoint();
                    cout << "You are now logged in" << endl;
                    checkpoint();
                    cout << endl;
                    pass = password[iterator1];
                    break;
                }
                else
                {
                    checkpoint();
                    cout << "Incorrect entry sorry" << endl;
                    checkpoint();
                    _Exit(0);
                }
//                pass = password[iterator1];
            }
            else
            {
                checkpoint();
                cout << "Incorrect password" << endl;
                checkpoint();
                _Exit(0);
            }
        }
        iterator1++;

    } while (iterator1 < MAX);

    if (iterator1 == MAX)
    {
        checkpoint();
        cout << "User doesnt exist" << endl;
        checkpoint();
        exit();
    }

    return iterator1;
}

/// Change the password if user wants after logging in
void login ::change_password()
{
    string pass1;
    cout << endl;

    cin.ignore();
    if (iterator1 == i)
    {
//        cannot change password if you just created the account
        checkpoint();
        cout << "You cannot change your password at this moment" << '\n';
        cout << "Try to change when you login with same credentials the next time" << endl;
        checkpoint();
    }
    else
    {
        checkpoint();
        cout << "Type your old password here: " << endl;
        getline(cin, temp);
        ofstream fileout("temp_file.txt");
        ifstream filein(passwordfile_path, ios::app);
        if (temp != pass)
        {
            checkpoint();
            cout << "You have typed an incorrect password" << endl;
            checkpoint();
            filein.close();
            fileout.close();
        }
        else
        {
            checkpoint();
            cout << "Type the new password" << endl;
            getline(cin, pass1);
            for (iterator2 = 0; iterator2 < j; iterator2++)
            {
                if (password[iterator2] == pass)
                {
                    // the line is iterator2+1
                    for (int y = 0; y < iterator1; ++y)
                    {
                        getline(filein, line_password);
                        fileout << line_password << endl;
                    }

                    fileout << pass1 << endl;
                    if (choice == "yes")
                    {
                        for (int y = iterator1 + 1; y < j; y++)
                        {
                            fileout << password[y] << endl;
                        }
                    }
                    else if (choice == "no")
                    {
                        for (int y = iterator1 + 1; y < j + 1; y++)
                        {
                            fileout << password[y] << endl;
                        }
                    }

                    password[iterator2] = pass1;
                }
            }
            filein.close();
            fileout.close();

            remove("password_file.txt");
            rename("temp_file.txt", "password_file.txt");
            pass = pass1;
        }
        checkpoint();
        cout << "Password updated successfully" << endl;
        checkpoint();
    }
    display();
}

/// Display the credentials
void login ::display()
{
    checkpoint();
    cout << "Username: " << user << endl;
    cout << "Password: " << pass << endl;
    checkpoint();
}

/// Exit the portal
void login ::exit()
{
    _Exit(0);
}

/// Main function starts
int main()
{
    checkpoint();
    cout << "LIBRARY MANGEMENT SYSTEM" << endl;
    checkpoint();

    int choice, choice1;
    login l;
    student s;

    s.initialize();

    l.initialize();

    l.registeration();

    while (true)
    {
        bool flag = true;
        checkpoint();
        cout << "1:Change password" << endl;
        cout << "2:Display details" << endl;
        cout << "3:Enter into 2nd portal" << endl;
        cout << "4:Exit System" << endl;

        checkpoint();
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            l.change_password();
            break;
        }
        case 2:
        {
            l.display();
            break;
        }
        case 3:
        {
            checkpoint();
            cout << "1:Add a student to database" << endl;
            cout << "2:Edit the details of a student" << endl;
            cout << "3:View the details of a particular student" << endl;
            cout << "4:View all enrolled students for library books" << endl;
            cout << "5:Exit System" << endl;

            checkpoint();
            cin >> choice1;
            switch (choice1)
            {
            case 1:
            {
                s.add_student();
                cout << endl;
                break;
            }
            case 2:
            {
                checkpoint();
                cout << "Processing...." << endl;
                checkpoint();
                s.edit_student();
                break;
            }
            case 3:
            {
                int q;
                checkpoint();
                cout << "Enter the ID of student to view the details" << endl;
                cin >> q;
                s.view_student_details(q);
                break;
            }
            case 4:
            {
                s.list_all_students();
                break;
            }
            case 5:
            {
                flag = false;
                _Exit(0);
                break;
            }
            default:
            {
                checkpoint();
                cout << "Incorrect entry" << endl;
                checkpoint();
                break;
            }
            }

            break;
        }
//            if (flag == false)
//            {
//                break;
//            }

        case 4:
        {
            _Exit(0);
            break;
        }

        default:
        {
            checkpoint();
            cout << "Incorrect entry" << endl;
            checkpoint();
            break;
        }
        }
    }
//    system("cls");
    return 0;
}
