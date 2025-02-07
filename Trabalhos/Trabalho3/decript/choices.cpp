//#include "Encript.hpp"
#include "Decript.hpp"
#include <stdlib.h>

void abrirArq(stringstream &dataStr, vector<pair<size_t, size_t>> &listaFreq, vector<char> &alfabeto, vector<char> &frequenciaOrig, vector<char> &shiftedAlpha, int &shift)
{
    system("clear");
    if (NDEBUG)
        cout
            << "Enter a text file to decode" << endl;
    string pathData;
    cin >> pathData;
    if (!loadMessage(pathData, dataStr))
        cout << "Não foi possivel abrir o arquivo criptografado" << endl;

    loadFrequency(dataStr, listaFreq);
}
void takeAlphabet(stringstream &dataStr, vector<pair<size_t, size_t>> &listaFreq, vector<char> &alfabeto, vector<char> &frequenciaOrig, vector<char> &shiftedAlpha, int &shift)
{
    system("clear");
    if (NDEBUG)
        cout << "Digite o nome do arquivo com as dicas" << endl;
    string pathFreqOrig;
    cin >> pathFreqOrig;

    if (!loadFreqOrig(pathFreqOrig, frequenciaOrig))
        cout << "Falha ao abrir o arquivo com as dicas";

    getAlphabetFromMessage(dataStr, alfabeto, listaFreq);
}
void showShifts(stringstream &dataStr, vector<pair<size_t, size_t>> &listaFreq, vector<char> &alfabeto, vector<char> &frequenciaOrig, vector<char> &shiftedAlpha, int &shift)
{
    system("clear");
    if(frequenciaOrig.size() == 0){
        cout << "Impossivel printar, alfabeto vazio" << endl;
        return ;
    }
    // descobrir o shift na mão
    for (int shif = 0; shif < 51; shif++)
    {
        cout << endl
             << "shift = " << shif << endl
             << endl;
        shiftedAlpha.clear();
        for (size_t i = 0; i < frequenciaOrig.size(); i++)
        {
            char ch = ((size_t)frequenciaOrig[i]) - shif;
            //cout << ch << " -> " << (char)alfabeto[i] << endl;
            shiftedAlpha.push_back(ch);
        }

        printEncription(dataStr, listaFreq, shiftedAlpha);
        cout << endl;
    }
    string a;
    cout << "Digite o shift que quer utilizar: " << endl;
    cin >> a;
    shift = atoi(a.c_str());
    shiftedAlpha.clear();
    for (size_t i = 0; i < frequenciaOrig.size(); i++)
    {
        char ch = ((size_t)frequenciaOrig[i]) - shift;
        cout << i << " -> " << ch << endl;
        shiftedAlpha.push_back(ch);
    }
    system("clear");
}
void decrypt(stringstream &dataStr, vector<pair<size_t, size_t>> &listaFreq, vector<char> &alfabeto, vector<char> &frequenciaOrig, vector<char> &shiftedAlpha, int &shift)
{
    if((shiftedAlpha.size() == 0) || (listaFreq.size() == 0 )|| (dataStr.str().length() == 0)){
        cout << "Impossivel executar, informacoes insuficiente" << endl;
        return ;
    }

    printDecription(dataStr, listaFreq, shiftedAlpha);
    cout << endl;
}

void printShiftedALph(stringstream &dataStr, vector<pair<size_t, size_t>> &listaFreq, vector<char> &alfabeto, vector<char> &frequenciaOrig, vector<char> &shiftedAlpha, int &shift)
{
    system("clear");

    if(shiftedAlpha.size() == 0){
        cout << "Impossivel printar, alfabeto vazio" << endl;
        return ;
    }

    for (size_t i = 0; i < listaFreq.size(); i++)
    {
        cout << i << ": " << (char)listaFreq[i].first << " - " << (char)shiftedAlpha[i] << endl;
    }
}
void changeShiftedAlpha(stringstream &dataStr, vector<pair<size_t, size_t>> &listaFreq, vector<char> &alfabeto, vector<char> &frequenciaOrig, vector<char> &shiftedAlpha, int &shift)
{
    system("clear");
    while (1)
    {
        system("clear");
        printShiftedALph(dataStr, listaFreq, alfabeto, frequenciaOrig, shiftedAlpha, shift);
        decrypt(dataStr, listaFreq, alfabeto, frequenciaOrig, shiftedAlpha, shift);
        string choice;
        cout << endl
             << "Digite o indice do item que deseja alterar(deixe vazio para sair)" << endl;
        getline(cin, choice);
        if (choice.size() == 0)
            break;
        int i = atoi(choice.c_str());
        cout << "Digite o caractere a ser colocado no lugar" << endl;
        getline(cin, choice);
        shiftedAlpha[i] = choice[0];
    }
}

void loadShiftedAlpha(stringstream &dataStr, vector<pair<size_t, size_t>> &listaFreq, vector<char> &alfabeto, vector<char> &frequenciaOrig, vector<char> &shiftedAlpha, int &shift){
    system("clear");
    cout << "Digite o nome do arquivo de alfabeto: " << endl;
    string path;
    cin >> path;

    shiftedAlpha.clear();

    loadAlphabet(path, shiftedAlpha);
}