#ifndef __CONFIGURABLE_HPP__
#define __CONFIGURABLE_HPP__

#include "tinyxml.h"


/**
 * @brief Skeleton of an XML configurable class
 */
class Configurable {



 public:


	/**
	 * @brief           Construct and initialise configuration DOM
	 */
	Configurable() {

		m_config_doc  = new TiXmlDocument();
		m_config_decl = new TiXmlDeclaration ("1.0", "", "");
		m_config      = new TiXmlElement     ("Config");

		m_config_doc->LinkEndChild( m_config_decl );
		m_config_doc->LinkEndChild( m_config );
		
	}


	/**
	 * @brief           Delete configuration DOM
	 */
	virtual ~Configurable() {
		delete m_config_doc;
	};

	
	/**
	 * @brief           Set a string type attribute
	 *
	 * @param  name     Attribute name 
	 * @param  value    Attribute value
	 */
	inline void
	SetAttribute        (const char* name, const char* value) {
		m_config->SetAttribute (name, value);
	}

	
	/**
	 * @brief           Set a integer type attribute
	 *
	 * @param  name     Attribute name 
	 * @param  value    Attribute value
	 */
	inline void
	SetAttribute        (const char* name, int value) {
		m_config->SetAttribute (name, value);
	}

	
	/**
	 * @brief           Set a float type attribute
	 *
	 * @param  name     Attribute name 
	 * @param  value    Attribute value
	 */
	inline void 
	SetAttribute        (const char* name, double value) {
		m_config->SetDoubleAttribute (name, value);
	}


	/**
	 * @brief           Set a string type attribute
	 *
	 * @param  name     Attribute name 
	 * @return          String representation of value
	 */
	inline const char*
	Attribute           (const char* name) const {
		return m_config->Attribute (name);
	}
	

	/**
	 * @brief           Set a integer type attribute
	 *
	 * @param  name     Attribute name 
	 * @param  value    Attribute value
	 * @return          Status
	 */
	inline const char*
	Attribute           (const char* name, int* value) const {
		return m_config->Attribute (name, value);
	}

	
	/**
	 * @brief           Set a float type attribute
	 *
	 * @param  name     Attribute name 
	 * @param  value    Attribute value
	 * @return          Status
	 */
	inline const char*
	Attribute           (const char* name, double* value) const {
		return m_config->Attribute (name, value);
	}


	/**
	 * @brief           Serialize configuration to string
	 *
	 * @return          String representation of configuration
	 */
	inline const char*
	GetConfig           ()             {

		std::string temp = "";
		temp << *(m_config_doc);
		char* t = new char[temp.length() + 1];
		strcpy (t, temp.c_str());
		return t;

	}


	/**
	 * @brief          Set configuration from string
	 *
	 * @param  cstr    Serialized configuration
	 */
	inline void 
	SetConfig          (const char* cstr) {

		m_config_doc->Clear();
		m_config_doc->Parse(cstr);
		m_config = m_config_doc->RootElement();


	}


	/**
	 * @brief          Get configuration element for more elaborate manipulation. (i.e. Adding children etc)
	 *
	 * @return         Reference to Element "Config"
	 */
	TiXmlElement* 
	Configuration      () {
		
		return m_config;
		
	}


	/**
	 * @brief          Dump XML configuration to file
	 *
	 * @param  fname   Name of output file
	 */
	void 
	DumpConfig        (const char* fname) {
		m_config_doc->SaveFile (fname);
	}
	

	/**
	 * @brief          Read configuration from XML file
	 *
	 * @param  fname   Name of input file
	 */
	void 
	ReadConfig        (const char* fname) {
		m_config_doc->LoadFile (fname);
	}
	

	/**
	 * @brief          Read configuration from XML file
	 *
	 * @param  file    File pointer
	 */
	void 
	ReadConfig        (FILE* file) {
		m_config_doc->LoadFile (file);
	}
	


 protected:
	

	TiXmlElement*       m_config;      /**< Flat Configuration XML element.      */ 
	TiXmlDocument*      m_config_doc;  /**< Containing XML document              */ 
	TiXmlDeclaration*   m_config_decl; /**< Declaration                          */

};



#endif
