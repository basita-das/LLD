#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

// Forward declarations for all file types
class TextFile;
class ImageFile;
class VideoFile;

// Visitor Interface //functionality to be performed on each type of file
class FileSystemVisitor
{
public:
    virtual ~FileSystemVisitor() = default;

    // how to visit/treat each type of file based on the function
    // 3 diff types of constructors for 3 diff types of files
    virtual void visit(TextFile *file) = 0;
    virtual void visit(ImageFile *file) = 0;
    virtual void visit(VideoFile *file) = 0;
};

class FileType
{
protected:
    string name; // name of the file type

public:
    FileType(const string &itemName)
    {
        name = itemName;
    }
    virtual ~FileType() = default;

    string getName() const { return name; }

    virtual void accept(FileSystemVisitor *visitor) = 0;
    // it is used to accept a visitor object and
    // call the appropriate visit method based on the type of file
};

class TextFile : public FileType
{
private:
    string content;

public:
    TextFile(const string &fileName, const string &fileContent) : FileType(fileName)
    {
        content = fileContent;
    }

    string getContent() const
    {
        return content;
    }

    void accept(FileSystemVisitor *visitor) override
    {
        visitor->visit(this);
        //  this === *TextFile
        // give the visitor text type file to perform the corresponding operation of the visitor
    }
};

class ImageFile : public FileType
{

public:
    ImageFile(string fileName) : FileType(fileName) {}
    // assign the file name to the base class constructor

    // getters and setters for image-specific attributes can be added here
    void accept(FileSystemVisitor *visitor) override
    {
        visitor->visit(this);
    }
};

class VideoFile : public FileType
{
public:
    VideoFile(const string &fileName) : FileType(fileName) {}
    // getters and setters for video-specific attributes can be added here

    void accept(FileSystemVisitor *visitor) override
    {
        visitor->visit(this);
    }
};

// 1. Size calculation visitor
class SizeCalculationVisitor : public FileSystemVisitor
{
public:
    void visit(TextFile *file) override
    {
        cout << "Calculating size for TEXT file: " << file->getName() << endl;
    }

    void visit(ImageFile *file) override
    {
        cout << "Calculating size for IMAGE file: " << file->getName() << endl;
    }

    void visit(VideoFile *file) override
    {
        cout << "Calculating size for VIDEO file: " << file->getName() << endl;
    }
};

// 2. Compression Visitor
class CompressionVisitor : public FileSystemVisitor
{
public:
    void visit(TextFile *file) override
    {
        cout << "Compressing TEXT file: " << file->getName() << endl;
    }

    void visit(ImageFile *file) override
    {
        cout << "Compressing IMAGE file: " << file->getName() << endl;
    }

    void visit(VideoFile *file) override
    {
        cout << "Compressing VIDEO file: " << file->getName() << endl;
    }
};

// 3. Virus Scanning Visitor
class VirusScanningVisitor : public FileSystemVisitor
{
public:
    void visit(TextFile *file) override
    {
        cout << "Scanning TEXT file: " << file->getName() << endl;
    }

    void visit(ImageFile *file) override
    {
        cout << "Scanning IMAGE file: " << file->getName() << endl;
    }

    void visit(VideoFile *file) override
    {
        cout << "Scanning VIDEO file: " << file->getName() << endl;
    }
};

int main()
{

    FileType *img1 = new ImageFile("sample.jpg"); // file type is image and file name is sample.jpg

    img1->accept(new SizeCalculationVisitor()); // perform size calculation on the image file
    img1->accept(new CompressionVisitor());     // perform compression on the image file
    img1->accept(new VirusScanningVisitor());   // perform virus scanning on the image file

    FileType *vid1 = new VideoFile("test.mp4"); // file type is video and file name is test.mp4
    vid1->accept(new CompressionVisitor());     // perform compression on the video file

    return 0;
}