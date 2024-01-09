#ifndef HAKANOS_H
#define HAKANOS_H

#include <iostream>
#include <list>
#include <string>
#include <cstring>
#include <fstream>
#include <vector>

namespace HakanOS {

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

}

#endif // HAKANOS_H