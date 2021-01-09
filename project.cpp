#include<bits/stdc++.h>
#include<fstream>
#include<string>
using namespace std;

class Account{
    int id;
    string name;
    float balance;
    public:
        int generateId(string userName){
            int lines = getDataLength();
            string alphabet = "abcdefghijklmnopqrstuvwxyz";
            string idInString = to_string(lines);
            for(int i=0;i<5;i++){
                for(int j=0;j<26;j++){
                    if(tolower(userName[i]) == alphabet[j]){
                        int temp = j+1;
                        if(j>9){
                            temp = (j+1)%10;
                        }
                        idInString += to_string(temp);
                    }
                }
            }
            cout<<idInString<<endl;
            int numericalId = stoi(idInString);
            cout<<"Numerical : "<<numericalId<<endl;

            return numericalId;

        }
        int getDataLength(){
            ifstream dataFile("accounts.txt");
            string temp;
            int lines = 0;
            while(getline(dataFile , temp)){
                lines += 1;
            }
            return lines;
        }
        void updateBalance(int userId , float amount){
            ifstream dataFile("accounts.txt");
            string temp;
            string userIdInString = to_string(userId);
            string outputBalance;
            float outputNumericalbalance;
            bool found = false;
            while (getline(dataFile , temp))
            {
                if(temp.find(userIdInString) == 0){
                    outputBalance = temp.substr(temp.find(":") + 1);
                    outputNumericalbalance = stoi(outputBalance);
                    outputNumericalbalance += amount;
                    found = true;
                } 
            }
            if(found == true){
                string secondTemp;
                string content;
                ifstream dataFile("accounts.txt");
                while(getline(dataFile , secondTemp)){
                    if(secondTemp.find(userIdInString) != 0){
                        content += secondTemp;
                        content += "\n";
                    }
                    else{
                        string edited;
                        edited = userIdInString + " : " + to_string(outputNumericalbalance) + "\n";
                        content += edited;
                    }
                }
                ofstream outputFile("accounts.txt");
                outputFile<<content;
                outputFile.close();
            }
            
        }
        bool createAccount(int userId , float amount){
            ifstream dataFile("accounts.txt");
            string temp;
            string content = "";
            while(getline(dataFile , temp)){
                if(temp.find(to_string(userId)) == 0){
                    return false;
                }
            }

            ifstream newFile("accounts.txt");
            while(getline(newFile , temp)){
                content += temp;
                content += "\n";
            }
            content += to_string(userId) + " : " + to_string(amount) + "\n";
            ofstream outputFile("accounts.txt");
            outputFile<<content;
            return true;
        }
        void openAccount(string userName , float amount){

        }

};

main(){
    Account a;
    int choice = 0;
    string someTemp; 
    do
    {
        cout<<"Enter 1 to create an account\n2 to update balance\n";
        cin>>choice;
        switch(choice)
        {
        case 1:
            float amount;
            bool done;
            int theirId;
            cout<<"Enter the name\n";
            cin>>someTemp;
            cout<<"Enter the amount to be added\n";
            cin>>amount;
            theirId = a.generateId(someTemp);
            cout<<theirId<<endl;
            done = a.createAccount(theirId , amount);
            if(done == true){
                cout<<"Your account has successfully been created.\nID:"<<theirId<<"\n";
            }
            else{
                cout<<"your account already exists.\n";
            }
            break;
        
        case 2:
            int hisId;
            float amountTwo;
            cout<<"Enter your id\n";
            cin>>hisId;
            cout<<"Enter the amount\n";
            cin>>amountTwo;
            a.updateBalance(hisId , amountTwo);
            cout<<"Your balance has successfully been updated.\n";
            break;
        }
    } while (choice<3);
    
}