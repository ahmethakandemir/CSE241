#include <iostream>
#include <list>
#include <string>

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
    virtual void printToFile() const = 0;

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
    string content;
    virtual void display() const override
    {
        cout << "File: " << name << endl;
    }
    void changeContent(const string &newContent)
    {
        content = newContent;
    }
    void displayContent() const
    {
        cout << content << endl;
    }
    int fileSize() const
    {
        return content.size();
    }
    virtual void printToFile() const override
    {
        cout << "[~[" << name << "~~";
        cout << "~~" << content << "]~]";
    }

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
    void display() const override
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
    virtual void printToFile() const override
    {

        for (const auto &directory : directories)
        {
            directory->printToFile();
        }
        for (const auto &file : files)
        {
            file->printToFile();
        }

    }
};

void MyShell::printToFile() const
{
    root->display();
    cout << endl;
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
            directories.erase(iterator);
            return;
        }
    }
    cout << "rmdir: failed to remove '"<< name << "': No such file or directory" << endl;
}

void Directory::ls() const
{
    for (const auto &directory : directories)
    {
        cout << directory->name << endl;
    }
    for (const auto &file : files)
    {
        cout << file->name;
    }
}

string Directory::pwd() const
{
    string path;
    if (parent == nullptr)
    {
        cout << name;
    }
    else
    {
        parent->pwd();
        cout << '/' << name;
        path = path + '/' + name;
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
    for (const auto &directory : currentDirectory->directories)
    {
        if (directory->name == name)
        {
            currentDirectory = directory;
            return;
        }
    }
    cout << "cd: " << name << " : No such file or directory" << endl;
}

void Directory::start()
{
    currentDirectory = nullptr;
    size = 0;
    root = new Directory(nullptr, "root");
    currentDirectory = root;
    string command;
    while (true)
    {
        cout << "> ";
        currentDirectory->pwd();
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
            currentDirectory->pwd();
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
        else if (command == "print")
        {
            printToFile();
        }
    }
}

int main()
{
    Directory *root = new Directory();
    root->start();

    return 0;
}
