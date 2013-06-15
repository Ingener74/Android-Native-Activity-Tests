/*
 * SmallSettingsFile.h
 *
 *  Created on: 15.08.2012
 *      Author: pavel
 */

#ifndef SMALLSETTINGSFILE_H_
#define SMALLSETTINGSFILE_H_

#include <fstream>
#include <string>

using namespace std;

const string smallSettingsFileDefaultFileName		= "settings";

const string smallSettingsFileErrorStateSuccess		= "success";
const string smallSettingsFileErrorStateNoNameError	= "empty file name";
const string smallSettingsFileErrorStateCantRead	= "can't read file";
const string smallSettingsFileErrorStateCantWrite	= "can't write file";

template <typename T>
class SmallSettingsFile {
	string	_fileName;
	string	_errorState;

	T		_default_value;
public:
	SmallSettingsFile( string name  = smallSettingsFileDefaultFileName, T default_value = T(0) ):_fileName(name), _errorState(), _default_value(default_value){
		_errorState = _fileName.empty() ? smallSettingsFileErrorStateNoNameError : smallSettingsFileErrorStateSuccess;
	}
	virtual ~SmallSettingsFile(){}

	// load and return value from file
	T operator--();

	// read value from file, increment and save back into file
	SmallSettingsFile& operator++(int);

	// save value to file
	SmallSettingsFile& operator<<(const T& value);

	// load, adding and save value to file
	SmallSettingsFile& operator<<=(const T& value);
	SmallSettingsFile& operator+=(const T& value);

	// load value from file
	SmallSettingsFile& operator>>(T& value);

	bool isError() const {
		return _errorState != smallSettingsFileErrorStateSuccess;
	}

	// return error string
	const string& getErrorValue() const {
		return _errorState;
	}
};

//////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
T SmallSettingsFile<T>::operator--(){
	T result;
	try{
		result=T(0);
	}catch(...){

	}
	if(_errorState == smallSettingsFileErrorStateSuccess){
		ifstream file;
		file.open(_fileName.c_str());
		if(file.is_open()){
			file >> result;
			file.close();
			_errorState = smallSettingsFileErrorStateSuccess;
		}else{
			result = _default_value;

			*this << result;

			if(isError())
				_errorState = smallSettingsFileErrorStateCantRead;
		}
	}
	return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
SmallSettingsFile<T>& SmallSettingsFile<T>::operator++(int){
	if(!isError()){
		T result = T(0);

		*this >> result;

		result++;

		*this << result;
	}
	return *this;
}

//////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
SmallSettingsFile<T>& SmallSettingsFile<T>::operator<<(const T& value){
	if(!_fileName.empty()){
		ofstream file;
		file.open(_fileName.c_str());
		if(file.is_open()){
			file << value;
			file.flush();
			file.close();
			_errorState = smallSettingsFileErrorStateSuccess;
		}else{
			_errorState = smallSettingsFileErrorStateCantWrite;
		}
	}
	return *this;
}

//////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
SmallSettingsFile<T>& SmallSettingsFile<T>::operator<<=(const T& value){
	if(_errorState==smallSettingsFileErrorStateSuccess){

		T temp = --*this;

		temp = temp + value;

		*this << temp;
	}
	return *this;
}

//////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
SmallSettingsFile<T>& SmallSettingsFile<T>::operator+=(const T& value){
	if(_errorState==smallSettingsFileErrorStateSuccess){

		T temp = --*this;

		temp = temp + value;

		*this << temp;
	}
	return *this;
}

//////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
SmallSettingsFile<T>& SmallSettingsFile<T>::operator>>(T& value){
	if(_errorState == smallSettingsFileErrorStateSuccess){
		ifstream file;
		file.open(_fileName.c_str());
		if(file.is_open()){
			file >> value;
			file.close();
			_errorState = smallSettingsFileErrorStateSuccess;
		}else{
			value = T(0);

			*this << value;

			if(isError())
				_errorState = smallSettingsFileErrorStateCantRead;
		}
	}
	return *this;
}

#endif /* SMALLSETTINGSFILE_H_ */
