#include <iostream>
#include <vector>
#include <string>

class FileSystemElement {
public:
    virtual void display() const = 0;
};

class Folder : public FileSystemElement {
private:
    std::string name;
    std::vector<FileSystemElement*> elements;

public:
    Folder(const std::string& name) : name(name) {}

    void addElement(FileSystemElement* element) {
        elements.push_back(element);
    }

    const std::vector<FileSystemElement*>& getElements() const {
        return elements;
    }

    void display() const override {
        std::cout << "Folder: " << name << std::endl;
        for (const auto& element : elements) {
            element->display();
        }
    }

};

class File : public FileSystemElement {
private:
    std::string name;

public:
    File(const std::string& name) : name(name) {}

    void display() const override {
        std::cout << "File: " << name << std::endl;
    }
};

int main() {
    Folder root("Root");

    Folder folder1("Folder1");
    folder1.addElement(new File("File1"));
    folder1.addElement(new File("File2"));

    Folder folder2("Folder2");
    folder2.addElement(new File("File3"));

    root.addElement(&folder1);
    root.addElement(&folder2);

    root.display();

    return 0;
}