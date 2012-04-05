/**********************************************************\

  Auto-generated VadimoniumAPI.h

\**********************************************************/

#include <map>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>

#include "JSAPIAuto.h"
#include "variant_map.h"
#include "BrowserHost.h"
#include "Vadimonium.h"

#include <rapidxml/rapidxml.hpp>

#include <openssl/bio.h>
#include <openssl/pem.h>
#include <openssl/rsa.h>
#include <openssl/err.h>

// This is used to find the current user's application data directory on Windows
#ifdef _WIN32
#include <Shlobj.h>
#endif

#include <boost/weak_ptr.hpp>
#include <boost/filesystem.hpp>
using namespace boost::filesystem;

#ifndef H_VadimoniumAPI
#define H_VadimoniumAPI

class VadimoniumAPI : public FB::JSAPIAuto
{
public:
    ////////////////////////////////////////////////////////////////////////////
    /// @fn VadimoniumAPI::VadimoniumAPI(const VadimoniumPtr& plugin, const FB::BrowserHostPtr host)
    ///
    /// @brief  Constructor for your JSAPI object.
    ///         You should register your methods, properties, and events
    ///         that should be accessible to Javascript from here.
    ///
    /// @see FB::JSAPIAuto::registerMethod
    /// @see FB::JSAPIAuto::registerProperty
    /// @see FB::JSAPIAuto::registerEvent
    ////////////////////////////////////////////////////////////////////////////
    VadimoniumAPI(const VadimoniumPtr& plugin, const FB::BrowserHostPtr& host) :
        m_plugin(plugin), m_host(host)
    {
        registerMethod("getProfiles",         make_method(this, &VadimoniumAPI::getProfiles));
		registerMethod("registerProfile",     make_method(this, &VadimoniumAPI::registerProfile));
        registerMethod("authenticateProfile", make_method(this, &VadimoniumAPI::authenticateProfile));

		// Initialise the application data folder
#ifdef _WIN32
		CHAR szPath[MAX_PATH];
		HRESULT res = SHGetFolderPathA(NULL, CSIDL_APPDATA | CSIDL_FLAG_CREATE, 0, 0, szPath);

		// Load in the XML configuration
		std::string path = std::string(szPath) + "/Vadimonium/config.xml";
		profileDataDirectory_ = std::string(szPath) + "\\Vadimonium\\Profiles\\";
		privateKeyDirectory_ = "F:\\Keys\\";
#else
		std::string path = "~/.vadimonium/config.xml";
		profileDataDirectory_ = "~/.vadimonium/Profiles/";
#endif
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @fn VadimoniumAPI::~VadimoniumAPI()
    ///
    /// @brief  Destructor.  Remember that this object will not be released until
    ///         the browser is done with it; this will almost definitely be after
    ///         the plugin is released.
    ///////////////////////////////////////////////////////////////////////////////
    virtual ~VadimoniumAPI() {};

    VadimoniumPtr getPlugin();

    // Returns a list of all the profiles available on the system
	FB::VariantMap getProfiles();

	// Returns the public-key for the selected profile
	std::string registerProfile(const std::string profileID);

	// Attempts to authenticate a profile by decrypting the base64-encoded message passed to it
	std::string authenticateProfile(const std::string& profileID, const std::string& digest);
    
private:
    VadimoniumWeakPtr m_plugin;
    FB::BrowserHostPtr m_host;

	std::string profileDataDirectory_, privateKeyDirectory_;
};

#endif // H_VadimoniumAPI
