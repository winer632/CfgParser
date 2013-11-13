  /// \file RawCfgParser.hh
/*
 *
 * RawCfgParser.hh header template generated by fclass
 * Creation date : jeu. juin 6 2013
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


#ifndef RAWCFGPARSER_HH
#define RAWCFGPARSER_HH

#include <iostream> 
#include <string> 
#include <cstdlib> 
#include <cmath> 
#include <vector>
#include <algorithm>
#include <fstream>


#include "Section.hh"
#include "ParserStatus.hh"




namespace cfgparser {


	/**
	 * @brief Class RawCfgParser
	 * Parse and write configuration file in an ini format.
	 *
	 * Example:
	 *
	 *     [sectionName]
	 *
	 *     # this is a comment
	 *     anOption : aValue
	 *     aLongOption = this is a
	 *        long value
	 *     anInteger : 158
	 *     aDoubleVector = 145.6:146985.2:.2:965.4:5.5
	 *
	 * Interpolation are not implemented in this class.
	 * For this feature, use the CfgParser class.
	 *
	 * Vector values are separated with a ':' character.
	 * Section can only be created, removed and filled
	 * via this class. A section is got as a constant
	 * object so that it can't be modified without the
	 * parser instance.
	 */

	class RawCfgParser {

	public:

		/**
		 * @brief Default Constructor
		 * Option/value pairs can be passed for the default section
		 * The flag 'allowNoValue' allows to set and read an option
		 * with no value (disabled by default).
		 */
		RawCfgParser( const OptionValueMap *optionValueMap = nullptr , bool allowNoValue = false );

		/**
		 * @brief Copy constructor
		 */
		RawCfgParser( const RawCfgParser &parser );

		/**
		 * @brief
		 */
		RawCfgParser( RawCfgParser &&parser );

		/**
		 * @brief Default Destructor
		 */
		virtual ~RawCfgParser();

		/**
		 * @brief Create a section in the parser
		 */
		void createSection( const std::string &secName );

		/**
		 * @brief Adds a section to current section collection.
		 * Simply do additional checks
		 */
		void addSection( Section *section );

		/**
		 * @brief Get a value with a type T
		 */
		template<typename T>
		T getValue( const std::string& sectionName , const std::string &key ) const
		{
			Section *section = nullptr;
			CFGPARSER_THROW_RESULT_IF( CFGPARSER_SUCCESS() , != , this->getSection( sectionName , section ) );
			std::string value = section->getValue<T>( key );
			T finalVal;
			cfgparser::convert<T>( value , finalVal );
			return std::move( finalVal );
		}

		/**
		 * @brief Returns true if the the given section has the given option.
		 */
		bool hasOption( const std::string &sectionName , const std::string &key ) const;

		/**
		 * @brief Returns true if the parser instance contains the given section
		 */
		bool hasSection( const std::string &secName ) const;

		/**
		 * @brief Returns true if the parser instance contains the given section
		 */
		bool hasSection( const Section *section ) const;

		/**
		 * @brief Returns the given section. Throw if the section doesn't exists.
		 */
		const Section *getSection( const std::string &sectionName ) const;

		/**
		 * @brief Reads the given file in the ini format style.
		 */
		void read( const std::string &fileName );

		/**
		 * @brief Reads the given file in the ini format style.
		 */
		void read( const std::vector< std::string > &fileNames );

		/**
		 * @brief Reads the given file in the ini format style.
		 */
		void read( std::ifstream& stream );

		/**
		 * @brief Reads the given file in the ini format style.
		 */
		void read( std::ifstream* stream );

		/**
		 * @brief Removes an option from a given section
		 */
		void removeOption( const std::string &sectionName , const std::string &opt );

		/**
		 * @brief Removes a section from the parser instance
		 */
		void removeSection( const std::string &sectionName );

		/**
		 * @brief Set a value in the given section and a given option
		 */
		template<typename T>
		void setValue( const std::string& sectionName , const std::string &key, const T &value )
		{
			Section *section = nullptr;
			CFGPARSER_THROW_RESULT_IF( CFGPARSER_SUCCESS() , != , this->getSection( sectionName , section ) );
			section->setValue<T>( key , value );
		}

		/**
		 * @brief Writes all the default section and all the sections in the given file in an ini standard format
		 */
		void write( const std::string &fileName ) const;

		/**
		 * @brief Writes all the default section and all the sections in the given stream file instance in an ini standard format
		 */
		void write( std::ofstream& stream ) const;

		/**
		 * @brief Writes all the default section and all the sections in the given stream file instance in an ini standard format
		 */
		void write( std::ofstream* stream ) const;

		/**
		 * @brief Prints the sections in the console ( default section and all sections )
		 */
		void print() const;

		/**
		 * @brief Returns the option name after a 'ToLower' operation
		 */
		std::string optionXForm( const std::string &optionStr ) const;

		/**
		 * @brief Returns the options of the given section. Throw if the sections doesn't exists.
		 */
		const StringCollection getOptions( const std::string &secName ) const;

		/**
		 * @brief Returns all the values of the given section
		 */
		const StringCollection getValues( const std::string &secName ) const;

		/**
		 * @brief Clears the parser content.
		 */
		void clear();

		/**
		 * @brief Returns the default section
		 */
		const Section *getDefaultSection()
		{
			return _defaultSection;
		}

		/**
		 * @brief Returns the sections
		 */
		const SectionCollection *getSections()
		{
			return _sections;
		}


	// protected member functions
	protected:

		/**
		 * @brief Reads the given file in the ini format style. Private method containing the reading algorithm
		 */
		StatusCode _read( std::ifstream* stream );

		/**
		 * @brief Writes all the default section and all the sections in the given stream file instance in an ini standard format
		 */
		StatusCode _write( std::ofstream* stream ) const;

		/**
		 * @brief Gets a section with a given name
		 */
		StatusCode getSection( const std::string &sectionName , Section *sec ) const;


	// protected members
	protected:

		SectionCollection *_sections;                       ///< The sections in the parser instance.
		Section *_defaultSection;                           ///< The default section.
		static const std::string DEFAULT_SECTION;         ///< The default section name.
		bool _allowNoValue;                                ///< True if allows no value for a given option


	};  // class

}  // namespace 

#endif  //  RAWCFGPARSER_HH
