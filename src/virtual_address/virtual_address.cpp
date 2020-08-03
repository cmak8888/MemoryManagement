/**
 * This file contains implementations for methods in the VirtualAddress class.
 *
 * You'll need to add code here to make the corresponding tests pass.
 */

#include "virtual_address/virtual_address.h"

using namespace std;


VirtualAddress VirtualAddress::from_string(int process_id, string address) {
  // TODO: implement me
  return VirtualAddress(process_id, bitset<PAGE_BITS>(address.substr(0, PAGE_BITS)).to_ulong(), bitset<OFFSET_BITS>(address.substr(PAGE_BITS, OFFSET_BITS)).to_ulong());
}


string VirtualAddress::to_string() const {
  // TODO: implement me
  stringstream output;
  bitset<OFFSET_BITS> off(offset);
  bitset<PAGE_BITS> pa(page);
  output << pa.to_string() << off.to_string();
  return output.str();
}


ostream& operator <<(ostream& out, const VirtualAddress& address) {
  // TODO: implement me
  out << "PID " << address.process_id
  << " @ " << address.to_string()
  << " [page: " << address.page
  << "; offset: " << address.offset
  << "]";
  return out;
}
