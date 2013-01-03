/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */

#ifndef scriptengine_DataObject_h
#define scriptengine_DataObject_h

#include <v8.h>
#include <string>


namespace bit
{
	class ScriptManager;
	
	class JSONValue
	{
	public:
		~JSONValue();
		
		/**	Checks if the object contains a value with the given key
		*/
		bool has(const std::string &key);
		
		/**	Accesses a value specified by the key
			
			This operation is only valid for objects.
		*/
		JSONValue operator[](const std::string &key);
		
		/**	Accesses a value specified by an integer index
			
			This operation is only valid for arrays.
		*/
		JSONValue operator[](int index);
		
		bool isArray();
		bool isBoolean();
		bool isNumber();
		bool isObject();
		bool isString();
		
		uint32_t arrayLength();
		
		std::string toString();
		int64_t toInteger();
		double toDouble();
		bool toBoolean();
		
	private:
		friend class ScriptManager;
		JSONValue(v8::Local<v8::Value> rootValue, v8::Isolate *isolate);
		
		v8::Persistent<v8::Value> value;
		v8::Isolate *isolate;
	};
}

#endif
