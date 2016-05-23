// read iris dataset
#ifndef _IRIS_READER_H_
#define _IRIS_READER_H_

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <random>
#include <iterator>

namespace iris {

struct DataItem{
 public:
  double data[4];
  std::string cls;
};

std::ostream& operator<<(std::ostream& os, const DataItem& d){
  os << d.data[0] << ", " << d.data[1] << ", " << d.data[2] << \
      ", " << d.data[3] << ", " << d.cls;
  return os;
}

std::istream& operator>>(std::istream& is, DataItem& d) {
  for (int i = 0; i < 4; i++) {
    std::string tmp;
    if (!getline(is, tmp, ',')) {
      std::cout << "end reading data" << std::endl;
      return is;
    }
    d.data[i] = std::stod(tmp);
  }
  std::getline(is, d.cls);
  return is;
}

class IrisData{
 public:
  IrisData() = delete;
  ~IrisData() {}
  explicit IrisData(std::string  filename);
  const std::vector<DataItem> GetTrainData() const {return data_train_;}
  const std::vector<DataItem> GetTestData() const {return data_test_;}
 private:
  std::vector<DataItem> data_train_;
  std::vector<DataItem> data_test_;
};

IrisData::IrisData(std::string filename) {
  std::ifstream ifs(filename);
  DataItem item;
  int cnt = 0;
  std::vector<DataItem> data;
  while (ifs >> item) {
    data.push_back(item);
  }
  // shuffle
  std::random_device rd;
  std::mt19937 g(rd());
  std::shuffle(data.begin(), data.end(), g);
  // print the shuffled result
  std::copy(data.begin(), data.end(), std::ostream_iterator<DataItem>(std::cout, "\n"));
  std::cout << "\n";
  data_train_.assign(data.begin(), data.begin() + 130);
  data_test_.assign(data.begin() + 130, data.end());
}
}



#endif /* _IRIS_READER_H_ */
