#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <string>
#include <iostream>
#include <fstream>
#include <streambuf>
#include <QObject>
#include <QtDebug>


class File_manager
{
public:

    std::string open_file(std::string name)
    {
        std::ifstream fin(name, std::ios_base::app);     //output stream

        std::string file_content((std::istreambuf_iterator<char>(fin)),std::istreambuf_iterator<char>());
        //QString x =  QString::fromUtf8(file_content.c_str());
        fin.close();
        return  file_content;
    }

    void write_file(std::string name, int value=0)
    {
        std::string value_string = std::to_string(value);
        std::ofstream fout(name, std::ios_base::app);    //input stream
        fout<<value_string+"\n";
        fout.close();
    }


    int get_best_score()
    {

        int best_score = 0;
        std::string line;
        std::ifstream myfile("score.txt");
        while (std::getline(myfile, line))
        {
            QString x =  QString::fromUtf8(line.c_str());
            if(std::stoi(line) > best_score)
                best_score = std::stoi(line);
        }
        myfile.close();
        return  best_score;
    }

};



#endif // FILE_MANAGER_H
