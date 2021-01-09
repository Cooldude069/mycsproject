/*Simple(but not so simple) ATM system made by Samarth Nasnodkar.*/
#include<bits/stdc++.h>
#include<fstream>
#include<string>
using namespace std;

class Account{
    int id;
    string name;
    float balance;
    public:
        string generateId(string userName , bool raw = false){
            int lines = getDataLength();
            string alphabet = "abcdefghijklmnopqrstuvwxyz";
            string idInString = "";
            if(raw == false){
                idInString = to_string(lines);
            }
            int nameLength = userName.length();
            for(int i=0;i<nameLength;i++){
                for(int j=0;j<26;j++){
                    if(tolower(userName[i]) == alphabet[j]){
                        int temp = j+1;
                        idInString += "." + to_string(temp);
                    }
                }
            }
            return idInString;

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
        void updateBalance(string userId , float amount){
            ifstream dataFile("accounts.txt");
            string temp;
            string userIdInString = userId;
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
        float getBalance(string userId){
            ifstream dataFile("accounts.txt");
            string temp;
            while(getline(dataFile , temp)){
                if(temp.find(userId) == 0){
                    string balance = temp.substr(temp.find(":") + 1);
                    float output = stof(balance);
                    return output;
                }
            }

            return 0;
        }
        bool createAccount(string userId , float amount){
            ifstream dataFile("accounts.txt");
            string temp;
            string content = "";
            while(getline(dataFile , temp)){
                if(temp.find(userId) == 0){
                    return false;
                }
            }

            ifstream newFile("accounts.txt");
            while(getline(newFile , temp)){
                content += temp;
                content += "\n";
            }
            content += userId + " : " + to_string(amount) + "\n";
            ofstream outputFile("accounts.txt");
            outputFile<<content;
            return true;
        }
        void lostId(string userName){
            string tempId = generateId(userName , true);
            ifstream dataFile("accounts.txt");
            string temp;
            string availableIds = "";
            bool found = false;
            int i=0;
            while(getline(dataFile , temp)){
                string tempCounter = to_string(i);
                string tempstarter = tempCounter + tempId;
                if(temp.find(tempstarter) == 0){
                    found = true;
                    availableIds += tempstarter + "\n";
                }
                i+=1;
            }
            cout<<"Here are the ids which match your credentials:\n"<<availableIds;
        }
        void display(string userId){
            float balance = getBalance(userId); 
            cout<<"Your balance : "<<balance<<endl;
        }
        void setup(){
            ifstream dataFile("accounts.txt");
            if(dataFile.good() == false){
                ofstream createFIle("accounts.txt");
                createFIle.close();
            }
        }

};

int main(){
    Account a;
    int choice = 0;
    string someTemp; 
    string theirId;
    float initialBalance;
    string yourname;
    a.setup();
    do
    {
        cout<<"Enter 1 to create an account\n2 to display your balance\n3 to withdraw money\n4 to deposit money\n5 to exit\n";
        cin>>choice;
        switch(choice)
        {
        case 1:
            float amount;
            bool done;
            cout<<"Enter the name\n";
            cin>>someTemp;
            cout<<"Enter the amount to be added\n";
            cin>>amount;
            theirId = a.generateId(someTemp);
            done = a.createAccount(theirId , amount);
            if(done == true){
                cout<<"Your account has successfully been created.\nID:"<<theirId<<"\n";
            }
            else{
                cout<<"your account already exists.\n";
            }
            break;
        
        case 2:
            float amountTwo;
            cout<<"Enter your id(enter lost if you have forgotten your id)\n";
            cin>>theirId;
            if(theirId == "lost"){
                cout<<"Please enter your name\n";
                cin>>yourname;
                a.lostId(yourname);
                cout<<"Enter your id\n";
                cin>>theirId;
            }
            a.display(theirId);
            break;
        case 3:
            float withdrawnAmount; 
            cout<<"Enter your id(enter lost if you have forgotten your ID)\n";
            cin>>theirId;
            if(theirId == "lost"){
                cout<<"Please enter your name\n";
                cin>>yourname;
                a.lostId(yourname);
                cout<<"Enter your id\n";
                cin>>theirId;
            }
            cout<<"Enter the amount to be withdrawn\n";
            cin>>withdrawnAmount;
            initialBalance = a.getBalance(theirId);
            if (withdrawnAmount > initialBalance){
                cout<<"You do no have enough money in your account.\n";
            }
            else{
                a.updateBalance(theirId , withdrawnAmount);
                cout<<"Successfully withdrew Rs."<<withdrawnAmount<<" from your account\nYour current balance : "<<a.getBalance(theirId)<<endl;
            }
            break;
        case 4:
            float depositedAmount; 
            cout<<"Enter your id(enter lost if you have forgotten your ID)\n";
            cin>>theirId;
            if(theirId == "lost"){
                cout<<"Please enter your name\n";
                cin>>yourname;
                a.lostId(yourname);
                cout<<"Enter your id\n";
                cin>>theirId;
            }
            cout<<"Enter the amount to be deposited.\n";
            cin>>depositedAmount;
            a.updateBalance(theirId , -1*depositedAmount);
            cout<<"Successfully withdrew Rs."<<depositedAmount<<" from your account\nYour current balance : "<<a.getBalance(theirId)<<endl;
        }

    } while (choice<5);

    return 0;
    
}