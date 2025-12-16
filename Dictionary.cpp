    #include<iostream>
    #include "Dictionary.h"
    #include<fstream>
    using namespace std;

    // writing function to read words from the file

    // int loadWords(const char filename[], char words[][MAX_LENGTH]){
    //     ifstream file(filename);
    //     if (!file){
    //         cout<<"Error: cannot open file "<<filename<<endl;
    //         return 0;
    //     }

    //     int count = 0;
        
    //     while (file>>words[count]){
    //         count++;
    //         if (count>= MAX_WORDS){
    //             cout<<"Warning: Maximum words limit reached! "<<endl;
    //             break;
    //         }
    //     }
        
    //     file.close();
    //     return count;
    // }

    // new update 
    // reading function to read words from the file
int loadWords(const char filename[], char words[][MAX_LENGTH]){
    ifstream file(filename);
    if (!file){
        cerr << "Error: cannot open file " << filename << endl;
        return 0;
    }

    int count = 0;
    while (file >> words[count]){
        // normalize to lowercase to keep player checks simple
        for (int i = 0; words[count][i]; ++i) {
            if (words[count][i] >= 'A' && words[count][i] <= 'Z')
                words[count][i] = words[count][i] - 'A' + 'a';
        }
        count++;
        if (count >= MAX_WORDS){
            cout << "Warning: Maximum words limit reached! " << endl;
            break;
        }
    }

    file.close();
    return count;
}

        // writing function to print words on screen

        void printWords(char words[][MAX_LENGTH], int totalWords){
            cout<<"\nLoaded Words: "<<totalWords<<"\n";
            for (int i=0; i<totalWords; i++){
                cout<<i+1<<". "<<words[i]<<endl;
            }
        }