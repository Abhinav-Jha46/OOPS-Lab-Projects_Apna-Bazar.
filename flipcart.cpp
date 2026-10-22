#include <iostream>
#include <fstream>
#include <windows.h>
#include <limits> // This header is necessary for numeric_limits<streamsize>::max(), which tells the program to ignore all characters in the input buffer up to the next newline.cin.clear() and cin.ignore() are used to clear the error flag and ignore the invalid input when the user enters something that is not a number.
#include <string>
#include <vector>
#include <iomanip> // For std::setw and std::setprecision

#ifdef _WIN32
#include <cstdlib> // For system("CLS")
#else
#include <cstdlib> // For system("clear")
#endif

using namespace std;

// Define ANSI color codes
const string RESET = "\033[0m";
const string BOLD = "\033[1m";
const string BLUE = "\033[34m";
const string YELLOW = "\033[33m";
const string CYAN = "\033[36m";
const string WHITE = "\033[97m";

// Function to clear the screen based on the OS
void clearScreen()
{
#ifdef _WIN32
    system("CLS"); // Windows
#else
    system("clear"); // Linux/Mac
#endif
}

// Function to print the welcome message
void printWelcomeMessage()
{
    cout << endl;
    cout << CYAN << "*" << RESET << endl;
    cout << "*                                           *" << endl;
    cout << "*           " << BOLD << BLUE << "WELCOME TO APNA BAZAAR" << RESET << "          *" << endl;
    cout << "*                                           *" << endl;
    cout << CYAN << "*" << RESET << endl;
    cout << endl;
}

class Login
{
private:
    string user_name;
    string pass_word;

public:
    // constructor
    Login()
    {
        user_name = "";
        pass_word = "";
    }

    // setting the name of user in private;
    void set_userName(string user_name)
    {
        this->user_name= user_name;
    }

    // setting the user password in private;
    void set_Password(string pass_word)
    {
        this->pass_word = pass_word;
    }

    // getting user_name from private;
    string get_userName()
    {
        return user_name;
    }

    // getting user password from private;
    string get_Password()
    {
        return pass_word;
    }
};

// Password validation function
bool isValidPassword(const string &password)
{
    if (password.length() < 8)
        return false;

    bool hasUpper = false, hasLower = false, hasDigit = false, hasSpecial = false;

    for (char ch : password)
    {
        if (isupper(ch))
            hasUpper = true;
        else if (islower(ch))
            hasLower = true;
        else if (isdigit(ch))
            hasDigit = true;
        else
            hasSpecial = true;
    }

    return hasUpper && hasLower && hasDigit && hasSpecial;
}

void Register(Login &user_u)
{
    string userName, password;
    cout << "Enter user name: ";
    getline(cin, userName);
    user_u.set_userName(userName);

    while (true)
    {
        cout << "Enter password (at least 8 characters with uppercase, lowercase, digit, and special character): ";
        getline(cin, password);

        if (isValidPassword(password))
        {
            user_u.set_Password(password);
            break;
        }
        else
        {
            cout << "\033[1;31m" << "Invalid password! Please try again." << "\033[0m" << endl;
        }
    }

    ofstream writeFile("loginFile.txt", ios::app);
    if (!writeFile)
    {
        cout << "Error: Unable to open file for writing!" << endl;
        return;
    }

    writeFile << user_u.get_userName() << ":" << user_u.get_Password() << endl;
    writeFile.close();

    cout << "\033[1;32m" << "User Registered Successfully!" << "\033[0m" << endl;
    Sleep(2000);
    system("cls");
}

bool check = false;

void login(Login &user_u)
{
    string verify_userName, verify_password;
    cout << "Enter user name to verify: ";
    getline(cin, verify_userName);

    cout << "Enter user password to verify: ";
    getline(cin, verify_password);

    ifstream readFile("loginFile.txt");
    if (!readFile)
    {
        cout << "Error: Unable to open file for reading!" << endl;
        return;
    }

    string line;
    bool found = false;

    while (getline(readFile, line))
    {
        size_t delimiter_pos = line.find(':');
        if (delimiter_pos == string::npos)
            continue; // Skip invalid lines

        string stored_userName = line.substr(0, delimiter_pos);
        string stored_password = line.substr(delimiter_pos + 1);

        if (verify_userName == stored_userName && verify_password == stored_password)
        {
            check = true;
            found = true;
            break;
        }
    }
    readFile.close();

    if (found)
    {
        cout << CYAN << "Please wait! We are verifying" << RESET;
        for (int i = 0; i < 3; i++)
        {
            cout << CYAN << "." << RESET;
            Sleep(800);
        }
        system("cls");
        cout << "\033[1;32m" << "Welcome back!" << "\033[0m" << endl;
    }
    else
    {
        check = false;
        cout << "\033[1;31m" << "Incorrect Username or Password. Please try again." << "\033[0m";
        for (int i = 0; i < 3; i++)
        {
            cout << ".";
            Sleep(1000);
        }
    }
    system("cls");
}
// Struct for CartItem
struct CartItem
{
    string name;
    double price;
};

// Class for Item management
class Item
{
public:
    string category;
    string name;
    string description;
    double price;
    void addItem()
    {
        cout << "Do you want to add to an existing category or create a new one? (Enter 1 for existing, 2 for new): ";
        int choice;
        cin >> choice;

        // Clear the input buffer to avoid issues with getline after cin
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        bool b = false;
        if (choice == 1)
        {
            cout << "Type the category from: " << CYAN << "Fashion / Electronics / Books / Home & Kitchen: " << RESET;
            getline(cin, category);
            if (category == "Fashion" || category == "Electronics" || category == "Books" || category == "Home & Kitchen")
            {
                b = true;
            }
        }
        else if (choice == 2)
        {
            cout << "Enter new category name: ";
            getline(cin, category);
            // Create a new file for the new category
            ofstream newCategoryFile(category + ".txt");
            if (!newCategoryFile)
            {
                cout << "Error creating new category file!" << endl;
                return;
            }
            newCategoryFile.close();
            cout << CYAN << "New category created: " << category << RESET << endl;
            b = true;
        }
        else
        {
            cout << "\033[31mInvalid choice! Returning to menu\033[0m";
            for (int i = 0; i < 3; i++)
            {
                cout << "\033[31m.\033[0m";
                Sleep(1000);
            }
            clearScreen();
            return;
        }

        if (b) // ie b == true;
        {
            cout << "Enter item name: ";
            getline(cin, name); // Capture full item name

            cout << "Enter item description: ";
            getline(cin, description); // Capture full item description

            // Validate the price input to ensure it's a valid number
            cout << "Enter item price in Rupees: ";
            while (!(cin >> price) || price <= 0)
            {
                cout << "Invalid price. Please enter a valid price in Rupees: ";
                cin.clear();                                         // Clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the incorrect input
            }

            // Save item to the respective category file
            ofstream categoryOutFile(category + ".txt", ios::app);
            if (!categoryOutFile)
            {
                cout << "Error opening category file for writing!" << endl;
                return;
            }
            categoryOutFile << name << " " << description << " " << price << endl;
            categoryOutFile.close();

            cout << CYAN << "Item added successfully" << RESET;
            for (int i = 0; i < 3; i++)
            {
                cout << CYAN << "." << RESET;
                Sleep(1000);
            }
        }
        else
        {
            cout << "\033[31mYou have entered something wrong! Please enter correct choice\033[0m";
            for (int i = 0; i < 3; i++)
            {
                cout << "\033[31m.\033[0m";
                Sleep(2000);
            }
        }
    }

    void updateItem()
    {
        string category;
        cout << "Enter the category of the item to update (e.g., Fashion): ";
        cin >> category;

        string itemName;
        cout << "Enter the name of the item to update: ";
        cin.ignore(); // to ignore the newline character
        getline(cin, itemName);

        string line;
        ifstream categoryFile(category + ".txt"); // Open the appropriate category file
        if (!categoryFile.is_open())
        {
            cout << "Could not open category file.\n";
            return;
        }

        vector<string> lines;
        bool found = false;

        while (getline(categoryFile, line))
        {
            if (line.find(itemName) != string::npos) // Check if the item name exists in the line
            {
                found = true;
                cout << "Current details: " << line << endl;

                // Get updated values
                cout << "Enter new name (leave blank to keep current): ";
                string newName;
                getline(cin, newName);
                if (newName.empty())
                    newName = itemName; // Keep current name if blank

                cout << "Enter new description (leave blank to keep current): ";
                string newDescription;
                getline(cin, newDescription);
                if (newDescription.empty())
                    newDescription = line.substr(newName.length() + 1, line.find(" ", newName.length() + 1) - newName.length() - 1); // Extract current description

                cout << "Enter new price (leave blank to keep current): ";
                string newPriceStr;
                getline(cin, newPriceStr);
                double newPrice = stod(line.substr(line.rfind(" ") + 1)); // Extract current price
                if (!newPriceStr.empty())
                    newPrice = stod(newPriceStr); // Update price if new input is given

                line = newName + " " + newDescription + " " + to_string(newPrice); // Update the line with new values
            }
            lines.push_back(line); // Store the updated or original line
        }

        categoryFile.close();

        // Write back the updated lines to the file
        ofstream outFile(category + ".txt");
        for (const auto &l : lines)
        {
            outFile << l << endl;
        }
        outFile.close();

        if (found)
        {
            cout << "Item updated successfully!\n";
        }
        else
        {
            cout << "Item not found.\n";
        }
    }

    Item parseItem(const string &line, const string &category)
    {
        Item tempItem;

        // Ensure line is not empty
        if (line.empty())
            return tempItem;

        size_t lastSpace = line.find_last_of(' ');
        if (lastSpace == string::npos)
        {
            cout << "Invalid line format: missing price!" << endl;
            return tempItem; // Return an empty item on error
        }

        // Extract price
        try
        {
            tempItem.price = stod(line.substr(lastSpace + 1)); // Convert the price to a double
        }
        catch (const invalid_argument &e)
        {
            cout << "Error parsing price: " << e.what() << endl;
            return tempItem; // Return an empty item if price parsing fails
        }
        catch (const out_of_range &e)
        {
            cout << "Price out of range: " << e.what() << endl;
            return tempItem; // Return an empty item if price is out of range
        }

        // Extract name and description (everything before the last space)
        string itemDetails = line.substr(0, lastSpace);
        size_t firstSpace = itemDetails.find(' '); // Find the first space

        if (firstSpace == string::npos)
        {
            cout << "Invalid line format: missing name or description!" << endl;
            return tempItem; // Return an empty item if no name/description found
        }

        tempItem.name = itemDetails.substr(0, firstSpace);
        tempItem.description = itemDetails.substr(firstSpace + 1);
        tempItem.category = category;

        return tempItem;
    }

    void showItemsInCategory(vector<CartItem> &cart)
    {
        cout << "\nAvailable Categories:\n"
             << CYAN << "1. Fashion\n2. Electronics\n3. Books\n4. Home & Kitchen\n"
             << RESET;
        int categoryChoice;
        cout << "Select a category (1-4): ";
        cin >> categoryChoice;

        string selectedCategory;
        switch (categoryChoice)
        {
        case 1:
            selectedCategory = "Fashion";
            break;
        case 2:
            selectedCategory = "Electronics";
            break;
        case 3:
            selectedCategory = "Books";
            break;
        case 4:
            selectedCategory = "Home & Kitchen";
            break;
        default:
            cout << "Invalid choice!\n";
            return;
        }

        // Attempt to open the file for the selected category
        ifstream categoryFile(selectedCategory + ".txt");
        if (!categoryFile)
        {
            cout << "No items found in this category or file could not be opened.\n";
            return;
        }

        cout << "\nItems in " << CYAN << selectedCategory << RESET << " category:\n";
        string line;
        vector<Item> items; // Temporary storage for items
        int itemIndex = 1;

        // Read items from the file and display them
        while (getline(categoryFile, line))
        {
            if (line.empty() || line.find_first_not_of(' ') == string::npos)
                continue; // Skip empty or whitespace-only lines

            // Attempt to parse the item
            Item tempItem = parseItem(line, selectedCategory);

            // If the item is valid, add it to the list
            if (!tempItem.name.empty())
            {
                cout << itemIndex << ". " << CYAN << "Name: " << RESET << tempItem.name
                     << ", " << CYAN << "Description: " << RESET << tempItem.description
                     << ", " << CYAN << "Price in Rupees: " << RESET << tempItem.price << endl;
                items.push_back(tempItem);
                itemIndex++;
            }
        }
        categoryFile.close();

        // Prompt the user for item selection and action
        int itemChoice;
        cout << "\nEnter the number of the item you want to take action on (0 to cancel): ";
        cin >> itemChoice;

        if (itemChoice > 0 && itemChoice <= items.size())
        {
            int action;
            cout << CYAN << "1. Add to Cart\n2. Buy Now\n"
                 << RESET << "Choose an action (1-2): ";
            cin >> action;

            if (action == 1)
            {
                CartItem cartItem = {items[itemChoice - 1].name, items[itemChoice - 1].price};
                cart.push_back(cartItem); // Add to cart
                cout << CYAN << "Item added to cart" << RESET;
                for (int i = 0; i < 3; i++)
                {
                    cout << CYAN << "." << RESET;
                    Sleep(1000);
                }
            }
            else if (action == 2)
            {
                cout << CYAN << "\nBuying the item" << RESET;
                for (int i = 0; i < 3; i++)
                {
                    cout << CYAN << "." << RESET;
                    Sleep(1000);
                }
                CartItem cartItem = {items[itemChoice - 1].name, items[itemChoice - 1].price};
                cart.push_back(cartItem); // Add to cart and simulate purchase
                cout << CYAN << "Item purchased successfully!\n"
                     << RESET;
                system("cls");

                generateBill(cart); // Automatically generate bill after purchase
            }
            else
            {
                cout << "Invalid action selected.\n";
            }
        }
        else if (itemChoice == 0)
        {
            cout << "Action canceled.\n";
        }
        else
        {
            cout << "Invalid item selection.\n";
        }
    }

    // Function to generate and display the bill
    void generateBill(const vector<CartItem> &cart)
    {
        double total = 0;
        string phoneNumber, address;

        cout << "Please enter your phone number: ";
        cin >> phoneNumber;
        cout << "Please enter your address: ";
        cin.ignore(); // To clear the newline character from the input buffer
        getline(cin, address);

        cout << CYAN << "===============================================" << RESET << endl;
        cout << BOLD << BLUE << "                  AP NA BAZAAR Invoice               " << RESET << endl;
        cout << CYAN << "===============================================" << RESET << endl;

        cout << YELLOW << "Customer Details:" << RESET << endl;
        cout << "Phone Number: " << phoneNumber << endl;
        cout << "Address     : " << address << endl;

        cout << CYAN << "-----------------------------------------------" << RESET << endl;
        cout << BOLD << "Items Purchased:" << RESET << endl;

        cout << left << setw(25) << "Item" << right << setw(10) << "Price (Rupees)" << endl;
        cout << CYAN << "-----------------------------------------------" << RESET << endl;

        // Loop through the cart and display the purchased items
        for (const auto &item : cart)
        {
            cout << left << setw(25) << item.name << right << setw(10) << fixed << setprecision(2) << item.price << endl;
            total += item.price;
        }

        cout << CYAN << "-----------------------------------------------" << RESET << endl;
        cout << BOLD << "Total Amount Due: " << WHITE << "Rupees " << fixed << setprecision(2) << total << RESET << endl;
        cout << CYAN << "===============================================" << RESET << endl;
        cout << BOLD << YELLOW << "          Thank you for shopping with us!       " << RESET << endl;
        cout << CYAN << "===============================================" << RESET << endl;

        cout << "Press Enter to go back to the main menu...";
        cin.ignore(); // To clear any lingering input
        cin.get();    // Wait for user to press Enter
    }
};

void deleteAccount(Login &user_u)
{
    cout << "Are you sure you want to delete your account? (y/n): ";
    char confirm;
    cin >> confirm;

    // Check if the user confirmed the deletion
    if (confirm == 'y' || confirm == 'Y')
    {
        ifstream userFile("loginFile.txt");
        ofstream tempFile("temp.txt");

        // Check if the files opened successfully
        if (!userFile.is_open() || !tempFile.is_open())
        {
            cout << "Error opening files!" << endl;
            return; // Exit the function if file opening fails
        }

        string line;
        bool accountFound = false;

        // Read lines from the user file
        while (getline(userFile, line))
        {
            size_t delimiter_pos = line.find(':');
            if (delimiter_pos == string::npos)
                continue; // Skip invalid lines

            string stored_userName = line.substr(0, delimiter_pos);
            // Write back the line to tempFile if it's not the account to delete
            if (stored_userName != user_u.get_userName())
            {
                tempFile << line << endl; // Write the other users to the temp file
            }
            else
            {
                accountFound = true; // Mark that the account was found and removed
            }
        }

        // Close the files
        userFile.close();
        tempFile.close();

        // If the account was found, delete it
        if (accountFound)
        {
            // Remove the original loginFile.txt file
            if (remove("loginFile.txt") != 0)
            {
                cout << "Error deleting the original file!" << endl;
                return; // Exit if there was an error deleting the file
            }

            // Rename the temp file to loginFile.txt
            if (rename("temp.txt", "loginFile.txt") != 0)
            {
                cout << "Error renaming the temporary file!" << endl;
                return; // Exit if there was an error renaming the file
            }

            cout << "Account deleted successfully! Please register again." << endl;
        }
        else
        {
            cout << "Account not found!" << endl;
        }

        // Wait for user to press Enter before exiting
        cout << "Press Enter to exit the program...";
        cin.ignore(); // To discard any leftover newline character
        cin.get();    // Wait for Enter key to be pressed

        exit(0); // Exit the program after deleting the account
    }
}
class ShoppingCart
{
public:
    vector<CartItem> cart;

    void showCart()
    {
        if (cart.empty())
        {
            cout << "Your cart is empty!\n";
            return;
        }

        cout << "Items in your cart:\n";
        for (const auto &item : cart)
        {
            cout << CYAN << "Item: " << RESET << item.name << ", " << CYAN << "Price in Rupees: " << RESET << item.price << endl;
        }
        cout << "Press Enter to go back to the main menu...";
        cin.ignore();
        cin.get(); // Wait for user to press Enter
    }
};

void manageItems(Item &item, ShoppingCart &shoppingCart, Login user)
{
    int choice;
    do
    {
        clearScreen();         // Clear the screen for the main menu
        printWelcomeMessage(); // Print the welcome message again

        cout << CYAN << "\nMenu:\n"
             << RESET << "1. Manage Account\n2. Show Items\n3. Show Cart\n4. Generate Bill\n5. Logout\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            int manageChoice;
            do
            {
                clearScreen();         // Clear the screen for account management
                printWelcomeMessage(); // Print the welcome message again

                cout << CYAN << "\nMenu:\n"
                     << RESET << "1.Add Item\n2.Update Item\n3.Delete Account\n4.Logout\n5.Back\n";

                cout << "Enter your choice: ";
                cin >> manageChoice;

                switch (manageChoice)
                {
                case 1:
                    item.addItem();
                    break;
                case 2:
                    item.updateItem();
                    break;
                case 3:
                    deleteAccount(user);
                    break;
                case 4:
                    cout << CYAN << "Logging out" << RESET;
                    for (int i = 0; i < 3; i++)
                    {
                        cout << CYAN << '.' << RESET;
                        Sleep(1000);
                    }
                    system("cls");
                    return;
                    break;
                case 5:
                    cout << CYAN << "Returning to main menu" << RESET;
                    for (int i = 0; i < 3; i++)
                    {
                        cout << CYAN << '.' << RESET;
                        Sleep(1000);
                    }
                    break;
                default:
                    cout << "Invalid choice!\n";
                }
            } while (manageChoice != 5);
            break;
        }
        case 2:
            item.showItemsInCategory(shoppingCart.cart); // Show items and allow adding to cart
            break;
        case 3:
            shoppingCart.showCart(); // Show items in cart
            break;
        case 4:
            if (!shoppingCart.cart.empty())
            {
                item.generateBill(shoppingCart.cart); // Generate bill for items in cart
            }
            else
            {
                cout << "Your cart is empty!\n";
            }
            break;
        case 5:
            cout << CYAN << "Logging out" << RESET;
            for (int i = 0; i < 3; i++)
            {
                cout << ".";
                Sleep(1000);
            }
            system("cls");
            return;
            break;
        case 6:
            cout << "Exiting the program. Goodbye!\n";
            break;
        default:
            cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 6);
    return;
}

int main()
{
    clearScreen();
    printWelcomeMessage();

    Item item;
    ShoppingCart shoppingCart;
    Login user;

    bool flag = true;

    while (flag)
    {
        int user_input;

        cout << "\033[1;32m" << "\t********** Register / Login **********" << "\033[0m" << endl;
        cout << "Choose an option:" << endl;
        cout << "1. Register" << endl;
        cout << "2. Login" << endl;
        cout << "3. Exit" << endl;

        try
        {
            cin >> user_input;

            // Check if the input operation failed
            if (cin.fail())
            {
                throw runtime_error("Invalid input! Please enter a number.");
            }

            // Clear the input buffer after valid input
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            switch (user_input)
            {
            case 1:
                Register(user);
                manageItems(item, shoppingCart, user);
                break;
            case 2:
                login(user);
                // Assuming 'check' is defined somewhere in your context
                if (check == true)
                {
                    manageItems(item, shoppingCart, user);
                }
                break;
            case 3:
                cout << "You quit!" << endl;
                flag = false;
                break;
            default:
                cout << "\033[1;31m" << "Invalid input! Please try again" << "\033[0m";
                for (int i = 0; i < 3; i++)
                {
                    cout << "\033[1;31m" << "." << "\033[0m";
                    Sleep(1000);
                }
                clearScreen();
            }
        }
        catch (const exception &e)
        {
            cout << "\033[1;31m" << e.what() << "\033[0m" << endl;
            cout << "Please try again." << endl;
            for (int i = 0; i < 3; i++)
            {
                cout << ".";
                Sleep(1000);
            }
            cin.clear();                                         // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the rest of the input
            clearScreen();
        }
    }

    return 0;
}