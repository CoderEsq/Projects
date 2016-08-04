/****************************************************************************************
*   Author:                       Alex Samuel
*   Date Created:                 12/26/2015
*   Last Modification Date:       7/22/2016
*   Filename:                     dekryptos.cpp
*
*   Overview:   This program will attempt to solve the 4th panel of the Kryptos sculpture.
*
*   Input:  The input shall consist of a file containing a list of possible keys.
*
*   Output: The output of the program will be a solution.
****************************************************************************************/

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <algorithm>
#include <array>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::streamsize;
using std::stringstream;
using std::vector;
using std::ios;
using std::ifstream;
using std::ofstream;
using std::fstream;
using std::array;
using std::find_if;

void dictionaryProg();
void nVig();
void kVig();
void scytale();

int main()
{
            bool menuAgain = true;
            while (menuAgain == true){  //user will be able to repeatedly return to menu
        cout << "\t KRYPTOS SOLVER \n"    //menu displayed to user
             << "Select which program you would like to execute from the choices below.\n"
             << "Enter the integer corresponding to your choice."
             << endl << endl
             << "   1:     Dictionary Attack" << endl
             << "   2:     Normal Vigenere" << endl
             << "   3:     Kryptos Vigenere" << endl
             << "   4:     Scytale Method" << endl
             << "   5:     EXIT TERMINAL" << endl << endl;



             cout << "Your Selection: ";
             int gameChoice;
             cin >> gameChoice;
             cout << endl;

             switch(gameChoice)     //the user's input is what the switch checks to execute the respective branch
             {
             case 1:
                 dictionaryProg();
                 break;

             case 2:
                 nVig();
                 break;

             case 3:
                 kVig();
                 break;

             case 4:
                 scytale();
                 break;

             case 5:            //exits program
                 exit(1);
                 break;
             }

        }




return 0;

}

void dictionaryProg()
{

    string filename1 = "bigalpha.txt";
    string filename2 = "badkeys.txt";
    string filename3 = "goodkeys.txt";
    ifstream inputFile(filename1);
    ofstream outputFile1(filename2);
    ofstream outputFile2(filename3);

    //checks if input and output files opened correctly.
    if(inputFile) {
            cout << filename1 << " has been opened successfully." << endl;}
    else{
            cout << "Can't open input file, " << filename1 << endl;
            }

    if(outputFile1) {
            cout << filename2 << " has been opened successfully." << endl;}
    else{
            cout << "Can't open output file, " << filename2 << endl;
        }

    if(outputFile2) {
            cout << filename3 << " has been opened successfully." << endl << endl;}
    else{
            cout << "Can't open output file, " << filename3 << endl;
            }


    string key;
    int attempts = 0;
    //Kryptos Panels 1-4
    string part1 = "EMUFPHZLRFAXYUSDJKZLDKRNSHGNFIVJYQTQUXQBQVYUVLLTREVJYQTMKYRDMFD";
    string part2 = "VFPJUDEEHZWETZYVGWHKKQETGFQJNCEGGWHKKDQMCPFQZDQMMIAGPFXHQRLGTIMVMZJANQLVKQEDAGDVFRPJUNGEUNAQZGZLECGYUXUEENJTBJLBQCRTBJDFHRRYIZETKZEMVDUFKSJHKFWHKUWQLSZFTIHHDDDUVHDWKBFUFPWNTDFIYCUQZEREEVLDKFEZMOQQJLTTUGSYQPFEUNLAVIDXFLGGTEZFKZBSFDQVGOGIPUFXHHDRKFFHQNTGPUAECNUVPDJMQCLQUMUNEDFQELZZVRRGKFFVOEEXBDMVPNFQXEZLGREDNQFMPNZGLFLPMRJQYALMGNUVPDXVKPDQUMEBEDMHDAFMJGZNUPLGEWJLLAETG";
    string part3 = "ENDYAHROHNLSRHEOCPTEOIBIDYSHNAIACHTNREYULDSLLSLLNOHSNOSMRWXMNETPRNGATIHNRARPESLNNELEBLPIIACAEWMTWNDITEENRAHCTENEUDRETNHAEOETFOLSEDTIWENHAEIOYTEYQHEENCTAYCREIFTBRSPAMHHEWENATAMATEGYEERLBTEEFOASFIOTUETUAEOTOARMAEERTNRTIBSEDDNIAAHTTMSTEWPIEROAGRIEWFEBAECTDDHILCEIHSITEGOEAOSDDRYDLORITRKLMLEHAGTDHARDPNEOHMGFMFEUHEECDMRIPFEIMEHNLSSTTRTVDOHW";
    string part4 = "OBKRUOXOGHULBSOLIFBBWFLRVQQPRNGKSSOTWTQSJQSSEKZZWATJKLUDIAWINFBNYPVTTMZFPKWGDKZXTJCDIGKUHUAUEKCAR";


    string c0 = "KRYPTOSABCDEFGHIJLMNQUVWXZ";
    int keylength;
    int success = 0;

    while(getline(inputFile, key)) {
        string solution;
        vector<string> cipher;
        keylength = key.size();

        if(keylength > 25) {
            continue;
        }

        //cout << "The length of the key is : " << keylength << endl;

        //cout << "The first letter is: " << key.front() << endl;

        for (int ii=0; ii < keylength; ii++) {
            string temp;
            temp = key.at(ii);

            int ltrLoc = c0.find(temp);
            temp.append(c0, ltrLoc+1, c0.length());
            temp.append(c0, 0, ltrLoc);

            cipher.push_back(temp);

        }



    //for (unsigned jj=0; jj<cipher.size(); jj++) {
    //    cout << cipher.at(jj) << endl;
    //}

    for (int ii=0; ii < part4.size(); ii++) {
        string encMsg;
        string decMsg;
        int encLoc;

        encMsg = part4.at(ii);

        encLoc = cipher.at(ii % keylength).find(encMsg);

        if(encLoc > 25) {
            continue;
        }

        decMsg = c0.at(encLoc);

        solution.append(decMsg);
    }

    //cout << solution << endl;

    //std::size_t found = solution.find("BERLINCLOCK");

    array<string, 27> targets{"BERLINCLOCK", "ADQKHMBKNBJ", "ZCPJGLAJMAI",
"YBOIFKZILZH",
"XANHEJYHKYG",
"WZMGDIXGJXF",
"VYLFCHWFIWE",
"UXKEBGVEHVD",
"TWJDAFUDGUC",
"SVICZETCFTB",
"RUHBYDSBESA",
"QTGAXCRADRZ",
"PSFZWBQZCQY",
"OREYVAPYBPX",
"NQDXUZOXAOW",
"MPCWTYNWZNV",
"LOBVSXMVYMU",
"KNAURWLUXLT",
"JMZTQVKTWKS",
"ILYSPUJSVJR",
"HKXROTIRUIQ",
"GJWQNSHQTHP",
"FIVPMRGPSGO",
"EHUOLQFORFN",
"DGTNKPENQEM",
"CFSMJODMPDL",
"BETWEENSUBTLE"};

    auto it = find_if(begin(targets), end(targets),
                           [&](const std::string& s)
                           {return solution.find(s) != std::string::npos; });

    //if (found!=std::string::npos) {
        if (it != end(targets)) {
        success++;
        outputFile2 << key << endl << endl;
        outputFile2 << *it << endl << endl;
        outputFile2 << solution << endl << endl;

        for (unsigned jj=0; jj<cipher.size(); jj++) {
            outputFile2 << cipher.at(jj) << endl;
        }

        outputFile2 << endl;


        cout << "POSSIBLE SOLUTION FOUND! KEY = " << key << endl;
        cout << solution << endl;
    }
    else {
        outputFile1 << key << endl;
    }

    attempts++;

    if (attempts % 10000 == 0) {
        cout << attempts << endl;
    }

    }

    if (success < 1) {
        cout << "NO SOLUTIONS FOUND" << endl;
    }
    //closes input and output files
    inputFile.close();
    outputFile1.close();
    outputFile2.close();

}

void nVig()
{
    vector<string> cipher;
    string alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string enc = "NYPVTTMZFPK";
    string sol = "BERLINCLOCK";

    for (int ii = 0; ii < alpha.size(); ii++) {
        string temp2;
        temp2.append(alpha, ii, alpha.size()-ii);
        temp2.append(alpha, 0, ii);
        //cout << temp2 << endl;
        cipher.push_back(temp2);
    }

    cout << endl << endl;

    //cout << cipher.at(0).substr(1,1) << endl;
    //cout << cipher.at(1).substr(1,1) << endl;
    //cout << cipher.at(2).substr(1,1) << endl;
    cout << alpha << endl;
    for (int kk = 0; kk < sol.size(); kk++) {
        string solLet = sol.substr(kk, 1);

        int alphaPos;
        alphaPos = alpha.find(solLet);

        for (int jj = 0; jj < cipher.size(); jj++) {




            string encLet = enc.substr(kk, 1);
            string vigLet;
            string temp3;

            cout << alpha.at(cipher.at(jj).find(encLet));
            if(jj == alphaPos) {

            }



        }

        cout << endl;

    }

}

void kVig()
{
    vector<string> cipher;
    string alpha = "KRYPTOSABCDEFGHIJLMNQUVWXZ";
    string enc = "NYPVTTMZFPK";
    string sol = "BERLINCLOCK";

    for (int ii = 0; ii < alpha.size(); ii++) {
        string temp2;
        temp2.append(alpha, ii, alpha.size()-ii);
        temp2.append(alpha, 0, ii);
        //cout << temp2 << endl;
        cipher.push_back(temp2);
    }

    cout << endl << endl;

    //cout << cipher.at(0).substr(1,1) << endl;
    //cout << cipher.at(1).substr(1,1) << endl;
    //cout << cipher.at(2).substr(1,1) << endl;
    cout << alpha << endl;
    for (int kk = 0; kk < sol.size(); kk++) {
        string solLet = sol.substr(kk, 1);

        int alphaPos;
        alphaPos = alpha.find(solLet);

        for (int jj = 0; jj < cipher.size(); jj++) {




            string encLet = enc.substr(kk, 1);
            string vigLet;
            string temp3;

            cout << alpha.at(cipher.at(jj).find(encLet));
            if(jj == alphaPos) {

            }



        }

        cout << endl;

    }
}

void scytale()
{
    string filename = "skipSolution.txt";
    ofstream outputFile1(filename);

    if(outputFile1) {
            cout << filename << " has been opened successfully." << endl;
    }
    else{
            cout << "Can't open output file, " << filename << endl;
    }

    int attempt = 0;
    int offset = 0;
    int startIndex = 0;
    int msgLength = 0;
    int success = 0;

    //Kryptos Panels 1-4
    string part1 = "EMUFPHZLRFAXYUSDJKZLDKRNSHGNFIVJYQTQUXQBQVYUVLLTREVJYQTMKYRDMFD";
    string part2 = "VFPJUDEEHZWETZYVGWHKKQETGFQJNCEGGWHKKDQMCPFQZDQMMIAGPFXHQRLGTIMVMZJANQLVKQEDAGDVFRPJUNGEUNAQZGZLECGYUXUEENJTBJLBQCRTBJDFHRRYIZETKZEMVDUFKSJHKFWHKUWQLSZFTIHHDDDUVHDWKBFUFPWNTDFIYCUQZEREEVLDKFEZMOQQJLTTUGSYQPFEUNLAVIDXFLGGTEZFKZBSFDQVGOGIPUFXHHDRKFFHQNTGPUAECNUVPDJMQCLQUMUNEDFQELZZVRRGKFFVOEEXBDMVPNFQXEZLGREDNQFMPNZGLFLPMRJQYALMGNUVPDXVKPDQUMEBEDMHDAFMJGZNUPLGEWJLLAETG";
    string part3 = "ENDYAHROHNLSRHEOCPTEOIBIDYSHNAIACHTNREYULDSLLSLLNOHSNOSMRWXMNETPRNGATIHNRARPESLNNELEBLPIIACAEWMTWNDITEENRAHCTENEUDRETNHAEOETFOLSEDTIWENHAEIOYTEYQHEENCTAYCREIFTBRSPAMHHEWENATAMATEGYEERLBTEEFOASFIOTUETUAEOTOARMAEERTNRTIBSEDDNIAAHTTMSTEWPIEROAGRIEWFEBAECTDDHILCEIHSITEGOEAOSDDRYDLORITRKLMLEHAGTDHARDPNEOHMGFMFEUHEECDMRIPFEIMEHNLSSTTRTVDOHW?";
    string part4 = "?OBKRUOXOGHULBSOLIFBBWFLRVQQPRNGKSSOTWTQSJQSSEKZZWATJKLUDIAWINFBNYPVTTMZFPKWGDKZXTJCDIGKUHUAUEKCAR";

    string test = "ABCDEFGHI";


    string encMsg = part4;
    string key = "BERLINCLOCK";
    int maxStartIndex = 100000;
    int maxOffset = 100000;

    msgLength = encMsg.length();

    //msgLength = 1;

    //cout << "length of string is: " << msgLength << endl;

    //cout << encMsg << endl << endl;



        for (startIndex = 0; startIndex < msgLength; startIndex++) {

            for (offset = 1; offset < msgLength; offset++) {
                string decMsg;
                int location = 0;

                //cout << location << endl;
                //cout << startIndex << endl << offset << endl;

                    for (int ii = 0; ii < msgLength; ii++) {

                        if(ii == 0) {
                                location = startIndex % msgLength;
                        }

                        decMsg.push_back(encMsg.at(location));
                        location = (location + offset) % msgLength;
                    }

                //cout << decMsg << endl;

                std::size_t found = decMsg.find(key);

                if (found != std::string::npos) {

                    cout << "POTENTIAL SOLUTION FOUND" << endl;
                    success++;

                    outputFile1 << decMsg << endl;
                    outputFile1 << "Start Index = " << startIndex << endl;
                    outputFile1 << "Offset = " << offset << endl << endl;
                }
                else if (attempt % 1000000 == 0 && attempt > 1) {
                    cout << attempt << endl;
                }
                else if (attempt % 10000000 == 0 && attempt > 1) {
                    outputFile1 << "Start Index = " << startIndex << endl;
                    outputFile1 << "Offset = " << offset << endl << endl;
                }
                attempt++;

            }

    }

    if (success < 1) {
        cout << "NO SOLUTIONS FOUND" << endl;
    }

    outputFile1.close();
}
