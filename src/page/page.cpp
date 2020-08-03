/**
 * This file contains implementations for methods in the Page class.
 *
 * You'll need to add code here to make the corresponding tests pass.
 */

#include "page/page.h"
#include <iostream>

using namespace std;


// Ensure PAGE_SIZE is initialized.
const size_t Page::PAGE_SIZE;


Page* Page::read_from_input(std::istream& in) {
  // TODO: implement me
  vector<char> pages;
  string str;
  if (getline(in, str)) {
    for(size_t i = 0; i < str.length(); i++) {
       pages.push_back(str[i]);
    }
    while(getline(in, str)) {
     pages.push_back('\n');
     for(size_t i = 0; i < str.length(); i++) {
        pages.push_back(str[i]);
     }
    }
    //pages.resize(length);
    return new Page(pages);
  }
  return nullptr;
}


size_t Page::size() const {
  // TODO: implement me
  if(Page::bytes.size() > PAGE_SIZE) {
    return PAGE_SIZE;
  }
  return bytes.size();
}


bool Page::is_valid_offset(size_t offset) const {
  // TODO: implement me
  size_t size = Page::size();
  if (!bytes.empty()) {
    if (offset < size && offset >= 0) {
      return true;
    }
  }
  return false;
}


char Page::get_byte_at_offset(size_t offset) {       //Run verifier prior to calling
  // TODO: implement me
  return bytes.at(offset);
}
