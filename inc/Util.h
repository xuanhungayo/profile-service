/* 
 * File:   Util.h
 * Author: xuanhungcao
 *
 * Created on July 12, 2017, 3:07 PM
 */

#ifndef UTIL_H
#define UTIL_H

namespace service {

class Util {
public:
	template<class TObject>
	static std::string JSONSerialize(const TObject& thrift_object);
	
	template<class TObject>
	static TObject JSONDeserialize(const std::string& json_string);
};

} // namespace service

#include "Util-imp.h"

#endif /* UTIL_H */

