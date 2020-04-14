
#include "incident_logger.hpp"
#include "singleton.hpp"
#include <iostream>


using LogRotation = Singleton<IncidentLogger<16>>;

int main() {

  auto & cb = LogRotation::get();

  cb.push(1, "01");
  cb.push(1, "02");
  cb.push(1, "03");
  cb.push(1, "04");

  cb.flush();

  cb.push(1, "05");
  cb.push(1, "06");
  cb.push(1, "07");
  cb.push(1, "08");
  cb.push(1, "09");
  cb.push(1, "10");
  cb.push(1, "11");
  cb.push(1, "12");
  cb.push(1, "13");
  cb.push(1, "14");
  cb.push(1, "15");
  cb.push(1, "17");
  cb.push(1, "18");
  cb.push(1, "19");
  cb.push(1, "20");
  cb.push(1, "21");
  cb.push(1, "22");
  cb.push(1, "23");
  cb.push(1, "24");
  cb.push(1, "25");
  cb.push(1, "26");
  cb.push(1, "27");
  cb.push(1, "28");

  cb.flush();

  std::cout << NOW << "\n";
  return 0;
}
