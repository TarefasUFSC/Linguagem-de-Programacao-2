#include "dictionary.hpp"

bool loadDictionary(string path, vector<pair<string, vector<string>>> &listaLinhas)
{
    vector<string> a;
    listaLinhas.push_back(make_pair(path, a));
    ifstream freader(path);
    if (!freader.is_open())
    {
        //cout << "Falha ao abrir o arquivo." << endl;
        return false;
    }
    string leitura;

    while (freader >> leitura)
    {
        listaLinhas[listaLinhas.size() - 1].second.push_back(leitura);
    }
    listaLinhas[listaLinhas.size() - 1].second.erase(listaLinhas[listaLinhas.size() - 1].second.begin());
    freader.close();
    return true;
}

bool searchSubstring(string search, const vector<pair<string, vector<string>>> &listaLinhas, vector<string> &substrings)
{
    for (pair<string, vector<string>> item : listaLinhas)
    {

        for (string line : item.second)
        {
            if (line.find(search) <= line.length())
                substrings.push_back(line);
        }
    }
    if (substrings.size() > 0)
        return true;
    return false;
}
bool removeSubstringLine(string search, vector<pair<string, vector<string>>> &listaLinhas)
{
    int i = 0;
    for (pair<string, vector<string>> item : listaLinhas)
    {

        vector<string> temp;

        for (string line : item.second)
        {
            if (line.find(search) > line.length())
            {
                temp.push_back(line);
            }
        }

        listaLinhas[i].second = temp;
        i++;
    }

    return true;
}