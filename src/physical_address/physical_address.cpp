/**
 * This file contains implementations for methods in the PhysicalAddress class.
 *
 * You'll need to add code here to make the corresponding tests pass.
 */

#include "physical_address/physical_address.h"

using namespace std;


string PhysicalAddress::to_string() const {
  // TODO: implement me
  stringstream output;
  bitset<OFFSET_BITS> off(offset);          //Converts into a bit array
  bitset<FRAME_BITS> pa(frame);               //Converts into a bit array
  output << pa.to_string() << off.to_string();
  return output.str();
}


ostream& operator <<(ostream& out, const PhysicalAddress& address) {
  // TODO: implement me
  out << address.to_string()
  << " [frame: " << address.frame
  << "; offset: " << address.offset
  << "]";
  return out;
}
