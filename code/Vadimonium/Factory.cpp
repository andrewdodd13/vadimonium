/**********************************************************\ 
 
 Auto-generated Factory.cpp
 
 This file contains the auto-generated factory methods 
 for the Vadimonium project
 
\**********************************************************/

#include "FactoryBase.h"
#include "Vadimonium.h"
#include <boost/make_shared.hpp>

class PluginFactory : public FB::FactoryBase
{
public:
    ///////////////////////////////////////////////////////////////////////////////
    /// @fn FB::PluginCorePtr createPlugin(const std::string& mimetype)
    ///
    /// @brief  Creates a plugin object matching the provided mimetype
    ///         If mimetype is empty, returns the default plugin
    ///////////////////////////////////////////////////////////////////////////////
    FB::PluginCorePtr createPlugin(const std::string& mimetype)
    {
        return boost::make_shared<Vadimonium>();
    }
    
    ///////////////////////////////////////////////////////////////////////////////
    /// @see FB::FactoryBase::globalPluginInitialize
    ///////////////////////////////////////////////////////////////////////////////
    void globalPluginInitialize()
    {
        Vadimonium::StaticInitialize();
    }
    
    ///////////////////////////////////////////////////////////////////////////////
    /// @see FB::FactoryBase::globalPluginDeinitialize
    ///////////////////////////////////////////////////////////////////////////////
    void globalPluginDeinitialize()
    {
        Vadimonium::StaticDeinitialize();
    }
};

///////////////////////////////////////////////////////////////////////////////
/// @fn getFactoryInstance()
///
/// @brief  Returns the factory instance for this plugin module
///////////////////////////////////////////////////////////////////////////////
FB::FactoryBasePtr getFactoryInstance()
{
    static boost::shared_ptr<PluginFactory> factory = boost::make_shared<PluginFactory>();
    return factory;
}

