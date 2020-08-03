/**
 * This file contains implementations for methods in the Process class.
 *
 * You'll need to add code here to make the corresponding tests pass.
 */

#include "process/process.h"
#include "page/page.h"
#include <iostream>

using namespace std;


Process* Process::read_from_input(std::istream& in) {
  // TODO: implement me
  const int PAGE_SIZE = 64;
  string str;
  size_t num_bytes = 0;
  vector<Page*> p;
  if (getline(in, str)) {
    while ((str.length() - num_bytes) / PAGE_SIZE > 0) {
      istringstream str2(str.substr(num_bytes, PAGE_SIZE));
      num_bytes += PAGE_SIZE;
      Page* page = Page::read_from_input(str2);
      p.push_back(page);
    }
    if(str.length() - num_bytes % PAGE_SIZE > 0) {            //End if its 0           //There is one more line to read.
      istringstream str2(str.substr(num_bytes));
      num_bytes += str.substr(num_bytes).size();
      Page* page = Page::read_from_input(str2);
      p.push_back(page);
    }
    return new Process(num_bytes, p);
  }

  return nullptr;
}


size_t Process::size() const {
  // TODO: implement me
  return this->num_bytes;
}


bool Process::is_valid_page(size_t index) const {
  // TODO: implement me
  if(index >= 0 && index < this->pages.size()) {
    return true;
  }
  return false;
}


size_t Process::get_rss() const {
  // TODO: implement me
  return this->page_table.get_present_page_count();
}


double Process::get_fault_percent() const {
  // TODO: implement me
  if(this->memory_accesses > 0) {
    double percent = ((double)page_faults/(double)memory_accesses) * 100;
    return percent;
  }
  return 0.0;
}
