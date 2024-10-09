#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int main()
{
    int a, i=0;
    string text, oldP, pass1, pass2Conf, username, pass0, age, user, word, word1;
    string creds[2], cp[2];

    cout << "         Security System          " << endl;

    cout <<  "________________________________" << endl << endl;
    cout << "|          1.Register            |" << endl;
    cout << "|          2.Login               |" << endl;
    cout << "|          3.Change password     |" << endl;
    cout << "|__________4.End Program_________|" << endl;

    do {
        cout << endl << endl;
        cout << "Enter your option: ";
        cin >> a;
        switch(a)
        {
            case 1:{
                cout << "_____________________________" << endl << endl;
                cout <<"|----------Register-----------| " << endl;
                cout <<"|_____________________________|" << endl << endl;
                cout <<"Please enter your username: ";
                cin >> username;
                cout <<"Please enter your password: ";
                cin >> pass0;
                cout << "Please enter your age: ";
                cin >> age;

                ofstream of1;
                of1.open("test_file.txt");
                if(of1.is_open()){
                    of1 << username << "\n";
                    of1 << pass0;
                    cout << "Registration successful!" << endl;
                    of1.close();  // Close the file after writing
                }

                break;

            }
        
            case 2: {

                i = 0;

                cout << "_____________________________" << endl << endl;
                cout <<"|-----------Login-------------| " << endl;
                cout <<"|_____________________________|" << endl << endl;

                ifstream of2;
                of2.open("test_file.txt");
                cout << "Please enter your username: ";
                cin >> username;
                cout << "Please enter your password: ";
                cin >> pass1;

                if (of2.is_open()) {
                    // Loop through file until the end of the file
                    while (getline(of2, text)) {
                        istringstream iss(text);
                        iss >> word;

                        // Make sure we only store two credentials (username and password)
                        if (i < 2) {
                            creds[i] = word;
                            i++;
                        }
                    }

                    // Now we can compare the credentials
                    if (username == creds[0] && pass1 == creds[1]) {
                        cout << "---Login successful--- " << endl << endl;

                        cout << "Details: " << endl;
                        cout << "Username: " + username << endl;
                        cout << "Age: " + age << endl;
                    } else {
                        cout << endl << endl;
                        cout << "              Incorrect Credentials                      " << endl;
                        cout << "|             1. Press 2 to Login                        |" << endl;
                        cout << "|             2. Press 3 to change your password         |" << endl;
                    }
                } else {
                    cout << "Error opening file." << endl;
                }
                of2.close();  // Close the file after reading

                break;
            }
       
            case 3: {
                i = 0;
                // Code for password change can be added here.
                cout << "------------------Change Password -------------------" << endl;

                ifstream of0;
                of0.open("test_file.txt");
                cout<< "Enter the old password: ";
                cin >> oldP;
                if(of0.is_open())
                {
                    while(of0.eof())
                    {
                        while(getline(of0, text)){
                            istringstream iss(text);
                            iss>> word1;
                            cp[i] = word1;
                            i++;
                        }
                        if(oldP == cp[1])
                        {
                            of0.close();

                            ofstream of1;
                            if(of1.is_open())
                            {
                                cout << "Enter your new password here: ";
                                cin >> pass1;
                                cout << "Enter your password again: ";
                                cin >> pass2Conf;

                                if(pass1 == pass2Conf)
                                {
                                    of1 <<cp[0] << "\n";
                                    of1 << pass1;
                                    cout << "Password has been changed suvccessfully." << endl;
                                }
                                else{
                                    of1<<cp[0]<<"\n";
                                    of1<<oldP;
                                    cout << "Passwords do not match." << endl;

                                }
                            }
                        }
                        else{
                            cout << "Please enter a valid password: " << endl;
                            break;
                        }
                    }
                }

                break;
            }

            case 4: {
                cout << "Profile Saved. Exiting the program." << endl;
                break;
            }

                default: {
                    cout << "Enter a valid option: " << endl;
                }

        }
    } while(a != 4);

    return 0;
}
