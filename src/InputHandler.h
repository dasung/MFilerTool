#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip> // For std::hex and std::dec
#include <boost/lexical_cast.hpp>
#include <filesystem>

struct DataRow
{
    int sequenceNumber;
    std::string symbol;
    double price;
    int quntity;
};

class InputHandler
{
public:
    InputHandler() = default;
    ~InputHandler() = default;
    void readCSV(const std::string& filename);

private:

};
