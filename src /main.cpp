#include<iostream>
using namespace std;

class skillSwap
{

    private:

public:

      int registerUSer()
    {
    }

    int login()
    {
    }

    int exit()
    {
    }

    
   

    int clearscreen()
    {
        cout << "\033[2J\033[1;1H"; // ANSI escape code to clear the console screen
        return 0;
    }
};

int main ()
{
    skillSwap s;
    int choice;
    cout <<"welcome to SkillSwap\n\n";
    cout <<"main menu\n";
    cout <<"Register User\n";
    cout <<"Login User\n";
    cout <<"Exit\n";
    

    cout << "Enter your choice: ";
    cin >> choice;
    s.clearscreen();

    switch (choice)
    {
        case 1:
        cout<<"Registering user...\n";
            break;
        case 2:
            cout<<"Logging in...\n";
            break;
        case 3:
            cout<<"Exiting...\n";
            break;

        default:
            cout<<"Invalid choice\n";
            break;
    }
    return 0;
}
