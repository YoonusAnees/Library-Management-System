
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Login
{
    string username;
    string password;
};

struct Books
{
    int bookCount;
    int book_ID[100];
    string bookName[100];
    double bookPrice[100];
};

struct Order
{
    string customerName[100];
    double discount[100];
    double orderTotal[100];
};

Login lg;
Books book;
Order order;


void RegistrationMenu();
void addBooks();
void viewBooks(const Books &book);
void searchBooks();
void orderBooks();
void viewOrder();
void generateQuotation();
void OrderMenu();
void fileWrite(const Login &user);
bool fileRead(const string &username, const string &password);
void registration();
bool Managerlogin();
void CustomerLogin();
void loadBooksFromFile(); 
void saveBooksToFile();   

int main()
{
    char choice;

    cout << "                                            Welcome To Nethra BookShop" << endl;
 
  
    loadBooksFromFile();

    do
    {
        cout << "R to Registration Site " << endl;
        cout << "M for Manager Login" << endl;
        cout << "C for Customer Login " << endl;
        cout << "E to Log out: " << endl;
        cin >> choice;

        switch (choice)
        {
        case 'R':
            RegistrationMenu();
            break;
        case 'M':
            if (Managerlogin())
            {
                cout << "Login Successful!\n";
            }
            break;
        case 'C':
            CustomerLogin();
            break;
        case 'E':
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid Choice. Try Again.\n";
        }
    } while (choice != 'E');

    return 0;
}

void RegistrationMenu()
{
    cout << "                                       Welcome To Nethra BookShop's Registration Site" << endl;

    char choice;

    do
    {
        cout << "R. Manager Registration\n";
        // cout << "S. Save Manager Information to File\n";
        cout << "E to Exit: " << endl;
        cout << "Enter your choice: \n";
        cin >> choice;
        switch (choice)
        {
        case 'R':
            registration();
            cout << "Registered Successfully" << endl;
            break;
        // case 'S':
        //    fileWrite(lg);
        //    cout << "Saved Successfully" << endl;
        //    break;
        case 'E':
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid Choice. Try Again.\n";
        }
    } while (choice != 'E');
}

void addBooks()
{
  
    loadBooksFromFile();

    if (book.bookCount >= 100)
    {
        cout << "Book count exceeded the limit. Cannot add more books." << endl;
        return;
    }

    cout << "How Many Books Do You Need to Add: ";
    int newBooksCount;
    cin >> newBooksCount;

    if (book.bookCount + newBooksCount > 100)
    {
        cout << "Total book count exceeds the limit. Cannot add more books." << endl;
        return;
    }

    for (int i = book.bookCount; i < book.bookCount + newBooksCount; i++)  
    {
        cout << "Enter Book ID: ";
        cin >> book.book_ID[i];
        cout << "Enter Book Name: ";
        cin.ignore(); 
        getline(cin, book.bookName[i]); 
        cout << "Enter Book Price: ";
        cin >> book.bookPrice[i];
    }


    book.bookCount += newBooksCount;


    saveBooksToFile();

    cout << "Book(s) Added Successfully :" << endl;
}

void viewBooks(const Books &book)
{   
    cout << "Books in the Store: " << book.bookCount << endl;
    for (int i = 0; i < book.bookCount; i++)
    {
        cout << "Book ID: " << book.book_ID[i] << " | Book Name: " << book.bookName[i] << " | Book Price: " << book.bookPrice[i] << endl;
    }
}

void searchBooks()
{
    int searchID;
    cout << "Enter the Book ID to search: ";
    cin >> searchID;

    bool found = false;

    for (int i = 0; i < book.bookCount; i++)
    {
        if (book.book_ID[i] == searchID)
        {
            found = true;
            cout << "Book ID " << searchID << " Found!" << endl;
            cout << "Book Name: " << book.bookName[i] << endl;
            cout << "Book Price: " << book.bookPrice[i] << endl;
            break;
        }
    }

    if (!found)
    {
        cout << "Book ID " << searchID << " Not Found" << endl;
    }
}

void orderBooks()
{   int i;
    int bookid;
    cout << "How many Books Do you need to Order: ";
    cin >> book.bookCount;
    cout << "Enter The Customer Name: ";
    cin.ignore(); 
    getline(cin, order.customerName[i]); 

    for (int i = 0; i < book.bookCount; i++)
    {
        if (book.bookCount < 2)
        {
            cout << "Enter The BookId To Order: ";
        }
        else
        {
            cout << "Enter The BookId " << (i + 1) << " To Order: ";
        }
        cin >> bookid;
        int index = -1;

        for (int j = 0; j < book.bookCount; j++)
        {
            if (book.book_ID[j] == bookid)
            {
                index = j;
                break;
            }
        }

        if (index == -1)
        {
            cout << "Book ID " << bookid << " Not Found" << endl;
        }
        else
        {
            order.discount[i] = (book.bookPrice[i] / 100) * 40;
            order.orderTotal[i] = book.bookPrice[i] - order.discount[i];
        }
    }

 
    ofstream orderFile("NethraShopOrder.txt", ios::app);
    if (!orderFile.is_open())
    {
        cout << "Error opening the file!" << endl;
        return;
    }

    orderFile << "Hello " << order.customerName[i] << endl;
    for (int i = 0; i < book.bookCount; i++)
    {
        orderFile << book.bookName[i] << " has been ordered " << endl;
        orderFile << "Discount Price : " << order.orderTotal[i] << endl;
        orderFile << "----------------------------------------------" << endl;
    }

    orderFile.close();

    cout << "Ordered Successfully " << endl;
}

void viewOrder()
{
    int bookid;
    cout << "Enter The BookId To View Order: ";
    cin >> bookid;

    bool found = false;

    for (int i = 0; i < book.bookCount; i++)
    {


        if (book.book_ID[i] == bookid)
        {
            found = true;
            cout << "Hello " << order.customerName[i] << endl;
            cout << "Book Name " << book.bookName[i] << endl;
            cout << "Book ID " << bookid << " Found and It has been ordered " << endl;
            break;
        }
    }

    if (!found)
    {
        cout << "Book ID " << bookid << " Not Found" << endl;
    }
}

void generateQuotation()
{   int i;
    ofstream file("Quotation.txt", ios::app);

    if (!file.is_open())
    {
        cout << "Error opening the file for quotation!" << endl;
        return;
    }

    file << "Customer Name: " << order.customerName[i] << endl;
    file << "Quotation Details:" << endl;

    for (int i = 0; i < book.bookCount; i++)
    {
        file << "Book ID: " << book.book_ID[i] << endl;
        file << "Book Name: " << book.bookName[i] << endl;
        file << "Book Price: " << book.bookPrice[i] << endl;
        file << "Discount: " << order.discount[i] << endl;
        file << "Total Price after Discount: " << order.orderTotal[i] << " Rupees" << endl;
        file << "-----------------------------" << endl;
    }

    file << "Time: " << __TIME__ << endl;
    file << "Date: " << __DATE__ << endl;

    file.close();
    cout << "Quotation Generated" << endl;
}

void OrderMenu()
{
    int countorder;
    do
    {
        cout << "                                   Welcome To Nethra BookShop's Ordering Site : " << endl;
        cout << "Press 1 To Order The Book:" << endl;
        cout << "Press 2 To View Order :" << endl;
        cout << "Press 3 To generate Quotation :" << endl;
        cout << "Press 4 To Exit " << endl;
        cout << "Enter The Choice " << endl;
        cin >> countorder;

        switch (countorder)
        {
        case 1:
            orderBooks();
            break;
        case 2:
            viewOrder();
            break;
        case 3:
            generateQuotation();
            break;
        case 4:
            cout << "Exited To Customer Login Area" << endl;
            break;
        default:
            cout << "Invalid Choice" << endl;
        }
    } while (countorder != 4);
}

void fileWrite(const Login &user)
{
    ofstream registrationFile("registrationFile.txt", ios::app);
    registrationFile << user.username << " " << user.password << endl;
    registrationFile.close();
}

bool fileRead(const string &username, const string &password)
{
    ifstream registrationFile("registrationFile.txt");
    string storedUsername, storedPassword;

    while (registrationFile >> storedUsername >> storedPassword)
    {
        if (storedUsername == username && storedPassword == password)
        {
            registrationFile.close();
            return true; // if  User found
        }
    }

    registrationFile.close();
    return false; // if User not found
}

void registration()
{
    cout << "Enter The Registration: " << endl;
    cout << "Username: ";
    cin >> lg.username;
    cout << "Password: ";
    cin >> lg.password;

    fileWrite(lg);
}

bool Managerlogin()
{
    cout << "Enter Your Login Credentials: " << endl;
    cout << "Username: ";
    cin >> lg.username;
    cout << "Password: ";
    cin >> lg.password;

    if (fileRead(lg.username, lg.password))
    {
        int count;
        cout << "Successfully Logged To Manager Area:" << endl;

        do
        {
            cout << "Press Number 1 To Add BOOKS: " << endl;
            cout << "Press Number 2 To View BOOKS: " << endl;
            cout << "Press Number 3 To Exit " << endl;
            cin >> count;

            switch (count)
            {
            case 1:
                addBooks();
                break;
            case 2:
            	
                viewBooks(book);
                break;
            case 3:
                cout << "Exited To Registration Area:" << endl;
                break;

            default:
                cout << "Invalid Choice" << endl;
            }
        } while (count != 3);
    }
    else
    {
        cout << "Credential Error" << endl;
        cout << "Try Again :)" << endl;
    }
}

void CustomerLogin()
{   cout << "                         Hello There Now You Can Grab 40% Discount For Every Book :)                                                                                             "<<endl;
    int count;
    do
    {   
        cout << "                              Welcome To Nethra BookShop's Customer Site : " << endl;
        cout << "Press Number 1 To View Books: " << endl;
        cout << "Press Number 2 To Search Books: " << endl;
        cout << "Press Number 3 TO View The OrderMenu :" << endl;
        cout << "Press Number 4 To Exit " << endl;
        cin >> count;

        switch (count)
        {
        case 1:
        	
            viewBooks(book);
            break;
        case 2:
            searchBooks();
            break;
        case 3:
            OrderMenu();
            break;
        case 4:
            cout << "Exited To Login Area:" << endl;
            break;
        default:
            cout << "Invalid Choice" << endl;
        }
    } while (count != 4);
}

void loadBooksFromFile()
{
    ifstream readfile("NethraaShop.txt");
    if (!readfile.is_open())
    {
        cout << "Error opening the file!" << endl;
        return;
    }

    readfile >> book.bookCount;
    for (int i = 0; i < book.bookCount; i++)
    {
        readfile >> book.book_ID[i];
        readfile.ignore(); 
        getline(readfile, book.bookName[i]);
        readfile >> book.bookPrice[i];
    }

    readfile.close();
}

void saveBooksToFile()
{
    ofstream file("NethraaShop.txt",ios::app);
    if (!file.is_open())
    {
        cout << "Error opening the file!" << endl;
        return;
    }

    file << book.bookCount << endl;
    for (int i = 0; i < book.bookCount; i++)
    {
        file << book.book_ID[i] << endl;
        file << book.bookName[i] << endl;
        file << book.bookPrice[i] << endl;
    }

    file.close();
}

