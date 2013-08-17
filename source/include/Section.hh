  /// \file Section.hh
/*
 *
 * Section.hh header template generated by fclass
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


#ifndef SECTION_HH
#define SECTION_HH

#include <iostream> 
#include <string> 
#include <cstdlib> 
#include <cmath> 
#include <vector>
#include <map>
#include <algorithm>
#include <sstream>

#include "ParserStatus.hh"
#include "StrOp.hh"

namespace cfgparser {


	class Section;
	class RawCfgParser;
	class CfgParser;
	class SafeCfgParser;

	typedef std::map <std::string,std::string> OptionValueMap;
	typedef std::vector<Section*> SectionCollection;
	typedef std::vector<const Section *> ConstSectionCollection;


	/*!
	 *
	 * Section class.
	 *
	 * Represent a config section in cfg file.
	 * A section has a name and a set of option/value
	 * pairs of various types. These values can be
	 * retrieved by using GetValue() methods.
	 * A value can be set only by using a parser
	 * instance so that a section can't exists
	 * without any parser instance.
	 *
	 */

	class Section {

		public:

			/*!
			 *
			 * @brief  Constructor with section name
			 *
			 */
			Section( const std::string &n );

			/*!
			 *
			 * @brief  Default Destructor
			 *
			 */
			virtual ~Section();

			/*!
			 *
			 * @brief Copy constructor
			 *
			 */
			Section( const Section &section );


		// protected members
		protected :

			std::string name;                           ///< The section name
			OptionValueMap optionValueMap;              ///< The option/value pairs


		// public member functions
		public:

			/*!
			 *
			 * @brief  Return the section name
			 *
			 */
			inline const std::string GetName() const
				{ return name; }

			/*!
			 *
			 * @brief  Return a string value
			 *
			 */
			StatusCode GetValue( const std::string &option , std::string *value ) const;

			/*!
			 *
			 * @brief  Return an int value
			 *
			 */
			StatusCode GetValue( const std::string &option , int *value ) const;

			/*!
			 *
			 * @brief  Return a double value
			 *
			 */
			StatusCode GetValue( const std::string &option , double *value ) const;

			/*!
			 *
			 * @brief  Return a bool value
			 *
			 */
			StatusCode GetValue( const std::string &option , bool *value ) const;

			/*!
			 *
			 * @brief  Return a string vector value
			 *
			 */
			StatusCode GetValue( const std::string &option , std::vector<std::string> *value ) const;

			/*!
			 *
			 * @brief  Return a double vector value
			 *
			 */
			StatusCode GetValue( const std::string &option , std::vector<double> *value ) const;

			/*!
			 *
			 * @brief  Return an int vector value
			 *
			 */
			StatusCode GetValue( const std::string &option , std::vector<int> *value ) const;

			/*!
			 *
			 * @brief  Return a bool vector value
			 *
			 */
			StatusCode GetValue( const std::string &option , std::vector<bool> *value ) const;

			/*!
			 *
			 * @brief  Return true if the section contains the given option
			 *
			 */
			bool HasOption( const std::string &opt ) const;

			/*!
			 *
			 * @brief  Return true if the section is empty
			 *
			 */
			bool IsEmpty() const;

			/*!
			 *
			 * @brief  Print the section with all option-value pairs
			 *
			 */
			StatusCode Print() const;


		// inline public member functions
		public:

			/*!
			 *
			 * @brief  Return the Option/Value map containing all option-value pairs.
			 *
			 */
			inline const OptionValueMap GetOptionValueMap() const
				{ return optionValueMap; }


		protected:

			/*!
			 *
			 * @brief  Clear the section
			 *
			 */
			StatusCode Clear();

			/*!
			 *
			 * @brief  Operator to add section
			 *
			 */
			Section& operator +=( const Section& section );

			/*!
			 *
			 * @brief  Delete a a option from the section
			 *
			 */
			StatusCode RemoveOption( const std::string &opt );

			/*!
			 *
			 * @brief  Set the given option with a string value
			 *
			 */
			StatusCode SetValue( const std::string &option , const std::string &value );

			/*!
			 *
			 * @brief  Set the given option with an int value
			 *
			 */
			StatusCode SetValue( const std::string &option, const int &value );

			/*!
			 *
			 * @brief  Set the given option with a double value
			 *
			 */
			StatusCode SetValue( const std::string &option, const double &value );

			/*!
			 *
			 * @brief  Set the given option with a bool value
			 *
			 */
			StatusCode SetValue( const std::string &option, const bool &value );

			/*!
			 *
			 * @brief  Set the given option with a string vector value
			 *
			 */
			StatusCode SetValue( const std::string &option, const std::vector< std::string > &value );

			/*!
			 *
			 * @brief  Set the given option with an int vector value
			 *
			 */
			StatusCode SetValue( const std::string &option, const std::vector< int > &value );

			/*!
			 *
			 * @brief  Set the given option with a double vector value
			 *
			 */
			StatusCode SetValue( const std::string &option, const std::vector< double > &value );

			/*!
			 *
			 * @brief  Set the given option with a bool vector value
			 *
			 */
			StatusCode SetValue( const std::string &option, const std::vector< bool > &value );


		// inline private member functions
		private:

			/*!
			 *
			 * @brief  Set the section name
			 *
			 */
			inline void SetName( const std::string &n )
				{ name = n;}

			// friend classes
			friend class RawCfgParser;
			friend class CfgParser;
			friend class SafeCfgParser;

			/*!
			 *
			 * @brief  'Addition' operator
			 *
			 */
			friend Section operator +( Section const& section1, Section const& section2 );


	};  // class

	/*!
	 *
	 * @brief  Operator to add section. Keep the name of the first section
	 *
	 */
	Section operator+ ( Section const& section1, Section const& section2 );


}  // namespace 

#endif  //  SECTION_HH
