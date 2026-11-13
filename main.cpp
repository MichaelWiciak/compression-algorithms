#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

struct SparseEntry
{
  long long row;
  long long col;
  double value;
};

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

  std::vector<SparseEntry> matrix_entries;

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
      matrix_entries.reserve(nonzeros);
      dimensions_read = true;
      continue;
    }

    long long row, col;
    double value;
    std::stringstream ss(line);
    if (ss >> row >> col >> value)
    {
      matrix_entries.push_back({row, col, value});
    }
  }

  std::cout << "Successfully stored " << matrix_entries.size() << " entries in memory." << std::endl;

  if (!matrix_entries.empty())
  {
    std::cout << "First entry -> Row: " << matrix_entries[0].row
              << ", Col: " << matrix_entries[0].col
              << ", Val: " << matrix_entries[0].value << "\n";
  }

  return 0;
}