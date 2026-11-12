#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

int main(int argc, char *argv[])
{
  std::ifstream data("./data/bcsstk01.mtx");
  if (!data.is_open())
  {
    std::cerr << "Error: Could not open file!" << std::endl;
    return 1;
  }

  std::string line;
  long long rows = 0, cols = 0, nonzeros = 0;
  bool dimensions_read = false;

  while (std::getline(data, line))
  {
    if (line.empty() || line[0] == '%')
    {
      continue;
    }

    if (!dimensions_read)
    {
      std::stringstream ss(line);
      ss >> rows >> cols >> nonzeros;
      std::cout << "Matrix size: " << rows << " rows, "
                << cols << " columns, "
                << nonzeros << " non-zeros.\n";
      dimensions_read = true;
      continue;
    }

    long long row, col;
    double value;
    std::stringstream ss(line);
    if (ss >> row >> col >> value)
    {
      std::cout << "Row: " << row << ", Col: " << col << ", Val: " << value << "\n";
    }
  }

  std::cout << "Finished parsing file." << std::endl;
  return 0;
}