  /// \file ParserStatus.hh
/*
 *
 * ParserStatus.hh header template generated by fclass
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


#ifndef PARSERSTATUS_HH
#define PARSERSTATUS_HH

#include <iostream> 
#include <string> 
#include <cstdlib> 
#include <cmath> 
#include <vector> 


/*!
 *
 * @brief  Helper macro
 * Check a status code and throw a result
 * in case the status code returned from Command
 * is different from Status
 *
 */
#define CFGPARSER_THROW_RESULT_IF( Status , Operator , Command )                                    \
	{ 																								 \
		StatusCode stat = Command;																	 \
		if( Status.fParserStatus Operator stat.fParserStatus ) { 								 \
																									 \
	        std::cerr << #Command << " throw " << stat.ToString() << std::endl;                   \
	        std::cerr << "    in function : " << __FUNCTION__ << std::endl;							 \
	        std::cerr << "    in file :     " << __FILE__ << " line#: " << __LINE__ << std::endl;    \
	        std::cerr << "    message :     " << stat.message << std::endl;                       \
	        throw CfgParserException( stat.message );											 \
		}																							 \
	}

/*!
 *
 * @brief  Helper macro
 * Print some info and throw the given Status
 *
 */
#define CFGPARSER_THROW_RESULT( Status )                                    \
	{ 																								 \
	        std::cerr << "Status thrown : " << Status.ToString() << std::endl;                   \
	        std::cerr << "    in function : " << __FUNCTION__ << std::endl;							 \
	        std::cerr << "    in file :     " << __FILE__ << " line#: " << __LINE__ << std::endl;    \
	        std::cerr << "    message :     " << Status.message << std::endl;                       \
	        throw CfgParserException( Status.message );											 \
	}

/*!
 *
 * @brief  Helper macro
 * Check if the specific pointer is null
 * and return an status code error
 *
 */
#define CFGPARSER_CHECK_POINTER_AND_RETURN( Pointer )                       \
		{                                                                    \
			if( Pointer == 0 || Pointer == NULL )                            \
				return CFGPARSER_ERROR("Assertion pointer != 0 failed!");   \
		}

/*!
 *
 * @brief  Helper macro
 * Check if the specific pointer is null
 * and throw a CfgParserException
 */
#define CFGPARSER_CHECK_POINTER_AND_THROW( Pointer )                                           \
		{                                                                                       \
			if( Pointer == 0 || Pointer == NULL ) {                                             \
				CFGPARSER_THROW_RESULT( CFGPARSER_ERROR("Assertion pointer != 0 failed!") );    \
			}                                                                                   \
		}



namespace cfgparser {


	/*!
	 *
	 * @brief  ParserStatus enum,
	 * list the different states that can be used
	 * in CfgParser libraries
	 *
	 */
	enum ParserStatus {

		fParserSuccess,
		fParserError,
		fParserNoSectionError,
		fParserDuplicateSectionError,
		fParserNoOptionError,
		fParserInterpolationError,
		fParserInterpolationDepthError,
		fParserInterpolationMissingOptionError,
		fParserInterpolationSyntaxError,
		fParserMissingSectionNameError,
		fParserInvalidSectionKey,
		fParserValueError,
		fParserParsingError
	};



	/*!
	 *
	 * @brief  StatusCode class,
	 * helper class that identify a state which is returned from a functions.
	 * Allows to catch exception in an easier way
	 * and is better for future code maintenance
	 *
	 */
	class StatusCode {

		public:
			/*!
			 *
			 * @brief  Constructor
			 *
			 */
			StatusCode() : fParserStatus(fParserSuccess) , message("") {}

			/*!
			 *
			 * @brief
			 *
			 */
			std::string ToString() const;

		// public members
		public:

			ParserStatus fParserStatus;     ///< The parser status
			std::string message;            ///< The returned message

			/*!
			 *
			 * @brief  Assignment operator
			 *
			 */
			StatusCode& operator =(const StatusCode& statusCode);

	};

	/*!
	 *
	 * @brief  "Not equal to" operator to compare two StatusCode object
	 *
	 */
	bool operator != ( const StatusCode &sc1 , const StatusCode &sc2 );

	/*!
	 *
	 * @brief  "Equal to" operator to compare two StatusCode object
	 *
	 */
	bool operator == ( const StatusCode &sc1 , const StatusCode &sc2 );


	/*!
	 *
	 * @brief  Status code which is returned for successful operation
	 *
	 */
	StatusCode CFGPARSER_SUCCESS( const std::string &message = "" );

	/*!
	 *
	 * @brief  Status code which is returned for generic errors
	 *
	 */
	StatusCode CFGPARSER_ERROR( const std::string &message = "" );

	/*!
	 *
	 * @brief  Status code which is returned while looking for
	 * a missing section in a parser instance.
	 *
	 */
	StatusCode CFGPARSER_NO_SECTION_ERROR( const std::string &message = "" );

	/*!
	 *
	 * @brief  Status code which is returned when creating a
	 * section that already exists in the parser
	 *
	 */
	StatusCode CFGPARSER_DUPLICATE_SECTION_ERROR( const std::string &message = "" );

	/*!
	 *
	 * @brief  Status code which is returned while looking for
	 * a missing option in a parser instance or a given section
	 *
	 */
	StatusCode CFGPARSER_NO_OPTION_ERROR( const std::string &message = "" );

	/*!
	 *
	 * @brief  Status code which is returned while parsing
	 * and building a bad value.
	 *
	 */
	StatusCode CFGPARSER_VALUE_ERROR( const std::string &message = "" );

	/*!
	 *
	 * @brief  Status code which is returned while interpolating
	 * a value with an other option that doesn't exists.
	 *
	 */
	StatusCode CFGPARSER_INTERPOLATION_MISSING_OPTION_ERROR( const std::string &message = "" );

	/*!
	 *
	 * @brief  Status code which is returned while interpolating
	 * and a syntax error is found.
	 *
	 */
	StatusCode CFGPARSER_INTERPOLATION_SYNTAX_ERROR( const std::string &message = "" );

	/*!
	 *
	 * @brief  Status code which is returned if a non
	 * existing option is used
	 *
	 */
	StatusCode CFGPARSER_INVALID_SECTION_KEY( const std::string &message = "" );

	/*!
	 *
	 * @brief  Status code which is returned if bad
	 * section name is asked
	 *
	 */
	StatusCode CFGPARSER_MISSING_SECTION_NAME_ERROR( const std::string &message = "" );

	/*!
	 *
	 * @brief  Status code returned for all generic parsing errors
	 *
	 */
	StatusCode CFGPARSER_PARSING_ERROR( const std::string &message = "" );




	/*!
	 *
	 * @brief CfgParserException class,
	 * responsible to throw exception while using the CfgParser library classes
	 *
	 */
	class CfgParserException : public std::exception {

		protected :
			std::string error;        ///< The error message

		public :
			/*!
			 *
			 * @brief Thrown constructor
			 *
			 */
			CfgParserException( const std::string &er ) throw()
				: error(er)  {};

			/*!
			 *
			 * @brief Default destructor
			 *
			 */
			virtual ~CfgParserException() throw() {};

			/*!
			 *
			 * @brief Return the exception message.
			 *
			 */
			virtual const char* what() const throw()
					{ return error.c_str(); }
	};


}  // namespace 

#endif  //  PARSERSTATUS_HH
