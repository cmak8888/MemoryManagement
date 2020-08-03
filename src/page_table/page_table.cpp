/**
 * This file contains implementations for methods in the PageTable class.
 *
 * You'll need to add code here to make the corresponding tests pass.
 */

#include "page_table/page_table.h"

using namespace std;


size_t PageTable::get_present_page_count() const {
  // TODO: implement me
  int counter = 0;
  for (auto i : rows) {
    if (i.present) {
      counter++;
    }
  }
  return counter;
}


size_t PageTable::get_oldest_page() const {                         //Oldest page has the smallest/earliest load time
  // TODO: implement me
  size_t min = 9999999;
  size_t index = 0;
  for (size_t i = 0; i < rows.size(); i++) {
    if(rows[i].present) {
      if(rows[i].loaded_at < min) {
          index = i;
          min = rows[i].loaded_at;
      }
    }
  }
  return index;
}


size_t PageTable::get_least_recently_used_page() const {            //Page accessed at the earliest time that is still present
  // TODO: implement me
  size_t min = 9999999;
  size_t index = 0;
  for (size_t i = 0; i < rows.size(); i++) {
    if(rows[i].present) {
      if(rows[i].last_accessed_at < min) {
          index = i;
          min = rows[i].loaded_at;
      }
    }
  }
  return index;
}
