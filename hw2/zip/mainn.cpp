#include <iostream>
#include <list>
#include <string>
#include <cstring>
#include <fstream>
#include <vector>
using namespace std;

class Directory; // Forward declaration

class MyShell
{
public:
    virtual void display() const = 0;
    virtual string pwd() const = 0;
    virtual void ls() const = 0;
    virtual void rm(const string &name) = 0;
    virtual void rmdir() = 0;
    void mkdir(const string &name);
    void cd(const string &name);
    virtual void printToFile(ofstream &filename) const = 0;
    void getFromFile(ifstream &filename);
    void cp(const string &pathname);
    ~MyShell();

protected:
    Directory *currentDirectory;
    Directory *root;
    int size;
};

class File : public MyShell
{
public:
    File(const string &name) : name(name) {}
    string name;
    
    Directory *parent;
    virtual void display() const override;
    void changeContent(const string &newContent);
    string displayContent() const;
    int fileSize() const;
    void printToFile(ofstream &filename) const override;

private:
    string pwd() const override { return ""; }
    void ls() const override {}
    void rmdir() override {}
    void rm(const string &name) override {}
    string content;
};

class Directory : public MyShell
{
public:
    Directory() : parent(nullptr), name("root") {}
    Directory(Directory *parent, const string &name) : parent(parent), name(name) {}
    void start();
    Directory *parent;
    string name;
    list<Directory *> directories;
    list<File *> files;
    string pwd() const override;
    void ls() const override;
    void rmdir() override;
    void rm(const string &name) override;
    void display() const override;
    void printToFile(ofstream &filename) const override;
    ~Directory();
};

string File::displayContent() const
    {
        cout << content << endl;
        return content;
    }

int File::fileSize() const
    {
        return content.size();
    }

Directory::~Directory()
    {
        for (const auto &directory : directories)
        {
            delete directory;
        }
        for (const auto &file : files)
        {
            delete file;
        }
    }

void File::changeContent(const string &newContent)
    {
        content = newContent;
    }

void File::display() const
    {
        cout << "File: " << name << endl;
    }

MyShell::~MyShell(){
        delete root;
        delete currentDirectory;
}

void MyShell::cp(const string &pathname)
{
    try
    {
        try
        {
            ifstream filename(pathname);
            if (!filename.is_open())
            {
                throw 1;
            }
            string textContent;
            string line;
            while (getline(filename, line))
            {
                textContent += line;
            }
            filename.close();
            File *newfile = new File(pathname);
            newfile->parent = currentDirectory;
            newfile->changeContent(textContent);
            currentDirectory->files.push_back(newfile);
        }
        catch (...)
        {
            Directory *tempdir = new Directory();
            tempdir = currentDirectory;
            currentDirectory = root;
            string path;
            vector<string> paths;
            for (int j = 0; j < pathname.size(); j++)
            {
                if (pathname[j] == '/')
                {
                    paths.push_back(path);
                    path = "";
                }
                else
                {
                    path += pathname[j];
                }
                if(j == pathname.size() - 1){
                    paths.push_back(path);
                }
            }
            for (int j = 0; j < paths.size() - 2; j++)
            {
                cd(paths[j]);
            }
            string name = paths[paths.size() - 1];
            for (const auto &file : currentDirectory->files)
            {
                if (file->name == name)
                {
                    File *newfile = new File(pathname);
                    newfile->parent = tempdir;
                    newfile->changeContent(file->displayContent());
                    tempdir->files.push_back(newfile);
                    currentDirectory = tempdir;
                    return;
                }
            }
        }
    }
    catch (...)
    {
        cout << "cp: cannot stat '" << pathname << "': No such file or directory" << endl;
        return;
    }
}

void MyShell::getFromFile(ifstream &filename)
{
    currentDirectory = nullptr;
    size = 0;
    root = new Directory(nullptr, "root");
    currentDirectory = root;

    string line;
    while (getline(filename, line))
    {
        if (line == "" || line == "\n" || line[0] != '/')
        {
            continue;
        }

        int i = 0;
        while (i < line.size())
        {
            string name;
            while (line[i] != '/' && i < line.size() && line[i] != ' ')
            {
                name += line[i];
                i++;
            }
            if (line == "/root\n")
            {
                continue;
            }
            if (name == "root")
            {
                currentDirectory = root;
            }
            else
            {
                bool isin = false;
                for (const auto &directory : currentDirectory->directories)
                {
                    if (directory->name == name)
                    {
                        currentDirectory = directory;
                        isin = true;
                        break;
                    }
                }
                if (!isin)
                {
                    if (name != "root")
                    {
                        mkdir(name);
                        cd(name);
                    }
                }
            }

            // cout << line << endl;
            // cout << line[i] << int(line[i]) << line[i + 1] << int(line[i + 1]) << endl;
            if (line[i] == ' ')
                i++;
            if (line[i] == '[')
            {
                if (line[i + 1] == '~')
                {
                    // cout << "here" ;
                    if (line[i + 2] == '[')
                    {
                        string filesname;
                        i += 3;
                        while (!((line[i] == '~') && (line[i + 1] == '~') && (line[i + 2] == '~') && (line[i + 3] == '~')))
                        {
                            filesname += line[i];
                            i++;
                        }
                        i += 4;
                        string content;
                        while (!((line[i] == ']') && (line[i + 1] == '~') && (line[i + 2] == ']')))
                        {
                            content += line[i];
                            i++;
                        }
                        i += 3;
                        File *newfile = new File(filesname);
                        newfile->parent = currentDirectory;
                        newfile->changeContent(content);
                        currentDirectory->files.push_back(newfile);
                    }
                }
            }

            if (line[i] == '/')
            {
                i++;
            }
        }

        currentDirectory = root;
    }
}

void MyShell::printToFile(ofstream &filename) const
{
    root->printToFile(filename);
}

void Directory::printToFile(ofstream &filename) const
{
    filename << "\n"
             << pwd();
    for (const auto &directory : directories)
    {
        if (directory->name != "")
            directory->printToFile(filename);
    }
    for (const auto &file : files)
    {
        filename << endl
                 << "/" << name;
        file->printToFile(filename);
    }
}

void File::printToFile(ofstream &filename) const
{
    filename << parent->pwd();
    filename << " [~[" << name << "~~";
    filename << "~~" << content << "]~]" << endl;
}

void Directory::display() const
{
    for (const auto &directory : directories)
    {
        cout << endl;
        directory->pwd();
        directory->display();
    }
    for (const auto &file : files)
    {
        file->display();
        cout << ", ";
    }
}

void Directory::rm(const string &name)
{
    for (auto iterator = files.begin(); iterator != files.end(); iterator++)
    {
        if ((*iterator)->name == name)
        {
            files.erase(iterator);
            return;
        }
    }
    cout << "rm: cannot remove '" << name << "': No such file or directory" << endl;
}

void Directory::rmdir()
{

    string name;
    cin >> name;
    for (auto iterator = directories.begin(); iterator != directories.end(); iterator++)
    {
        if ((*iterator)->name == name)
        {
            if (((*iterator)->directories.size() != 0) || ((*iterator)->files.size() != 0))
            {
                cout << "rmdir: failed to remove '" << name << "': Directory not empty" << endl;
                return;
            }
            directories.erase(iterator);
            return;
        }
    }
    cout << "rmdir: failed to remove '" << name << "': No such file or directory" << endl;
}

void Directory::ls() const
{
    for (const auto &directory : directories)
    {
        if (directory->name != "")
            cout << "D " << directory->name << endl;
    }
    for (const auto &file : files)
    {
        cout << "F " << file->name << endl;
    }
}

string Directory::pwd() const
{
    string path;
    if (parent == nullptr)
    {
        path = path + "/" + name;
    }
    else
    {
        Directory tempdir = *this;
        while (tempdir.parent != nullptr)
        {
            path = "/" + tempdir.name + path;
            tempdir = *tempdir.parent;
        }
        path = "/" + tempdir.name + path;
    }
    return path;
}

void MyShell::mkdir(const string &name)
{
    Directory *newDirectory = new Directory(currentDirectory, name);
    currentDirectory->directories.push_back(newDirectory);
}

void MyShell::cd(const string &name)
{
    if (name == "..")
    {
        if (currentDirectory->parent == nullptr)
        {
            return;
        }
        currentDirectory = currentDirectory->parent;
        return;
    }
    else{
        for (const auto &directory : currentDirectory->directories)
        {
            if (directory->name == name)
            {
                currentDirectory = directory;
                return;
            }
        }
    }

    int i = 0;
    bool isPath = false;
    while (i < name.size())
    {
        if (name[i] == '/')
        {
            isPath = true;
            break;
        }
        i++;
    }
    if (isPath)
    {
        string path;
        vector<string> paths;
        for (int j = 0; j < name.size(); j++)
        {
            if (name[j] == '/')
            {
                paths.push_back(path);
                path = "";
            }
            else
            {
                path += name[j];
            }
            if(j == name.size() - 1){
                paths.push_back(path);
            }
        }
        currentDirectory = root;
        for (int j = 0; j < paths.size(); j++)
        {
            cd(paths[j]);
        }

    }
}

void Directory::start()
{
    currentDirectory = nullptr;
    size = 0;
    root = new Directory(nullptr, "root");
    currentDirectory = root;
    try
    {
        ifstream filename("db.txt");
        getFromFile(filename);
    }
    catch (...)
    {
        cout << "db.txt not found" << endl;
    }

    string command;
    while (true)
    {
        cout << "> ";
        if(currentDirectory->pwd() == "/root/")
            currentDirectory = root;
        cout << currentDirectory->pwd();
        cout << "$ ";
        cin >> command;
        if (command == "mkdir")
        {
            string name;
            cin >> name;
            mkdir(name);
        }
        else if (command == "exit")
        {
            cout << "Terminal exited with code 0" << endl;
            exit(0);
        }
        else if (command == "cd")
        {
            string name;
            cin >> name;
            cd(name);
        }
        else if (command == "pwd")
        {
            cout << currentDirectory->pwd();
            cout << endl;
        }
        else if (command == "ls")
        {
            currentDirectory->ls();
        }
        else if (command == "rmdir")
        {
            currentDirectory->rmdir();
        }
        else if (command == "rm")
        {
            string name;
            cin >> name;
            currentDirectory->rm(name);
        }
        else if (command == "cp")
        {
            string pathname;
            cin >> pathname;
            cp(pathname);
        }
        else if (command == "cat")
        {
            string name;
            cin >> name;
            for (const auto &file : currentDirectory->files)
            {
                if (file->name == name)
                {
                    file->displayContent();
                    break;
                }
            }
        }
        else if (command == "display")
        {
            currentDirectory->display();
        }
        else if (command == "clear")
        {
            system("clear");
        }

        else
        {
            cout << "invalid command" << endl;
        }

        string file = "db.txt";
        ofstream filename(file);
        root->printToFile(filename);
    }
}

int main()
{

    Directory *root = new Directory();
    root->start();

    return 0;
}
