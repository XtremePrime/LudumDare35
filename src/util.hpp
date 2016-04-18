#ifndef UTIL_HPP
#define UTIL_HPP

namespace util
{
	template<typename T>
	void clear_vector(std::vector<T*>& v)
 	{
 		for(int i = 0; i < v.size(); ++i)
 			delete (v[i]);
 		v.clear();
 	}

 	/*std::string toup(std::string str)
 	{
 		std::string result = str;
 		for(int i = 0; i < result.length(); ++i)
 		{
 			if(result[i] >= 'a' && result[i] <= 'z')
 				result[i] -= ' ';
 		}
 		return result;
 	}

 	std::string tolow(std::string str)
 	{
 		std::string result = str;
 		for(int i = 0; i < result.length(); ++i)
 		{
 			if(result[i] >= 'A' && result[i] <= 'Z')
 				result[i] += ' ';
 		}
 		return result;
 	}*/
}

#endif // UTIL_HPP
