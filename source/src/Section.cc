  /// \file Section.cc
/*
 *
 * Section.cc source template generated by fclass
 * Creation date : mar. juin 4 2013
 *
 * This file is part of CfgParser libraries.
 *
 * CfgParser is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * CfgParser is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with CfgParser.  If not, see <http://www.gnu.org/licenses/>.
 * 
 * @author : Eté Rémi
 * @version 0.1.0 13/08/2013
 * @copyright 2013 Eté Rémi
 *
 */


#include "Section.hh"

using namespace std;

namespace cfgparser {

//---------------------------------------------------------------------------------------------------------------

	/****************************
	 * Public member functions
	 ****************************/

	Section::Section( const string &n )
	{
		_name = n;
		_optionValueMap.clear();
	}


	Section::Section( Section const &section )
	{
		_name = section._name;
		_optionValueMap = section._optionValueMap;
	}

	Section::Section( Section &&section )
	{
		_name = section._name;
		_optionValueMap = section._optionValueMap;
	}

	Section::~Section()
	{
		_optionValueMap.clear();
	}


	bool Section::hasOption( const string &option ) const
	{
		return ( _optionValueMap.find( option ) != _optionValueMap.end() );
	}


	template<>
	string Section::getValue( const std::string &key ) const
	{
		if( key.empty() )
			throw CfgParserException("Invalid section key : Asked option is empty");

		if( _optionValueMap.empty() )
			throw CfgParserException(string("Invalid section key : Section is empty. Couldn't find option ") + key + string("in section ") + _name  );

		string k = key;
		normalizeName(&k);

		auto it = _optionValueMap.find( k );
		if( it == _optionValueMap.end() )
			return "";
		else
			return it->second;
	}


//	template<typename T>
//	T Section::getValue( const std::string &key ) const
//	{
//
//	}


	bool Section::isEmpty() const
	{
		return _optionValueMap.empty();
	}


	void Section::print() const
	{
		if( this->isEmpty() )
			return;

		cout << "[" << _name << "]" << endl;

		for( auto it=_optionValueMap.begin() ; it!=_optionValueMap.end() ; it++ )
			cout << "  " << it->first << " = " << it->second << endl;
	}


	void Section::clear()
	{
		_optionValueMap.clear();
	}


	Section& Section::operator +=( const Section& section )
	{
//		for ( auto it = section.getOptionValueMap().begin() ; it != section.getOptionValueMap().end() ; it++)
//			this->SetValue( it->first , it->second );
		return *this;
	}


	Section operator+ ( const Section &section1 , const Section &section2 )
	{
		Section section( section1.getName() );
		section += section1;
		section += section2;
		return section;
	}


	void Section::removeOption( const std::string &option )
	{
		if( _optionValueMap.find( option ) != _optionValueMap.end() )
			_optionValueMap.erase(option);
	}



	template<>
	void Section::setValue( const std::string &key , const string &value )
	{
		if( key.empty() )
			return;
		_optionValueMap[ key ] = value;
	}


}  // namespace 

