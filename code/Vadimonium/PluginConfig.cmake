#/**********************************************************\ 
#
# Auto-Generated Plugin Configuration file
# for Vadimonium
#
#\**********************************************************/

set(PLUGIN_NAME "Vadimonium")
set(PLUGIN_PREFIX "VAD")
set(COMPANY_NAME "IsEpic")

# ActiveX constants:
set(FBTYPELIB_NAME VadimoniumLib)
set(FBTYPELIB_DESC "Vadimonium 1.0 Type Library")
set(IFBControl_DESC "Vadimonium Control Interface")
set(FBControl_DESC "Vadimonium Control Class")
set(IFBComJavascriptObject_DESC "Vadimonium IComJavascriptObject Interface")
set(FBComJavascriptObject_DESC "Vadimonium ComJavascriptObject Class")
set(IFBComEventSource_DESC "Vadimonium IFBComEventSource Interface")
set(AXVERSION_NUM "1")

# NOTE: THESE GUIDS *MUST* BE UNIQUE TO YOUR PLUGIN/ACTIVEX CONTROL!  YES, ALL OF THEM!
set(FBTYPELIB_GUID 125ff609-bac7-5a0d-8298-6ce21289b6ca)
set(IFBControl_GUID f8eb7722-8889-55f9-b53e-943cb17c6f70)
set(FBControl_GUID 3cee866e-5350-58eb-b550-1cc8c6e43f6b)
set(IFBComJavascriptObject_GUID 8e9c387f-d808-5ba0-9582-0deceb57b172)
set(FBComJavascriptObject_GUID aecdad35-a56b-5880-833c-b4adc14b4cf4)
set(IFBComEventSource_GUID f95898aa-72f5-5828-873e-d8170f895bef)

# these are the pieces that are relevant to using it from Javascript
set(ACTIVEX_PROGID "IsEpic.Vadimonium")
set(MOZILLA_PLUGINID "is-epic.co.uk/Vadimonium")

# strings
set(FBSTRING_CompanyName "Is-Epic")
set(FBSTRING_FileDescription "Modern two-factor authentication for the web")
set(FBSTRING_PLUGIN_VERSION "1.0.0.0")
set(FBSTRING_LegalCopyright "Copyright 2012 Is-Epic")
set(FBSTRING_PluginFileName "np${PLUGIN_NAME}.dll")
set(FBSTRING_ProductName "Vadimonium")
set(FBSTRING_FileExtents "")
set(FBSTRING_PluginName "Vadimonium")
set(FBSTRING_MIMEType "application/x-vadimonium")

# Uncomment this next line if you're not planning on your plugin doing
# any drawing:

set (FB_GUI_DISABLED 1)

# Mac plugin settings. If your plugin does not draw, set these all to 0
set(FBMAC_USE_QUICKDRAW 0)
set(FBMAC_USE_CARBON 0)
set(FBMAC_USE_COCOA 0)
set(FBMAC_USE_COREGRAPHICS 0)
set(FBMAC_USE_COREANIMATION 0)
set(FBMAC_USE_INVALIDATINGCOREANIMATION 0)

# If you want to register per-machine on Windows, uncomment this line
#set (FB_ATLREG_MACHINEWIDE 1)

add_boost_library(filesystem)
add_firebreath_library(openssl)