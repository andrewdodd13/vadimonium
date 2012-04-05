/**********************************************************\

  Auto-generated VadimoniumAPI.cpp

\**********************************************************/

#include "JSObject.h"
#include "DOM/Document.h"
#include "global/config.h"

#include "VadimoniumAPI.h"

///////////////////////////////////////////////////////////////////////////////
/// @fn VadimoniumPtr VadimoniumAPI::getPlugin()
///
/// @brief  Gets a reference to the plugin that was passed in when the object
///         was created.  If the plugin has already been released then this
///         will throw a FB::script_error that will be translated into a
///         javascript exception in the page.
///////////////////////////////////////////////////////////////////////////////
VadimoniumPtr VadimoniumAPI::getPlugin()
{
    VadimoniumPtr plugin(m_plugin.lock());
    if (!plugin) {
        throw FB::script_error("The plugin is invalid");
    }
    return plugin;
}

FB::VariantMap VadimoniumAPI::getProfiles() {
	FB::VariantMap result;

	path p(profileDataDirectory_);
	directory_iterator end_itr;
	for (directory_iterator itr(p); itr != end_itr; ++itr) {
		if(!is_directory(itr->status()) && itr->path().extension().compare(".xml") == 0) {
			// Read in the entire file
			std::ifstream inputFile(itr->path().string());
			std::stringstream buffer;
			buffer << inputFile.rdbuf();
			std::string inputString = buffer.str();
			inputFile.close();

			// Parse the XML
			std::vector<char> xml_copy(inputString.begin(), inputString.end());
			xml_copy.push_back('\0');

			rapidxml::xml_document<> doc;
			doc.parse<rapidxml::parse_no_data_nodes | rapidxml::parse_declaration_node>(&xml_copy[0]);

			rapidxml::xml_node<>* cur_node = doc.first_node("profile");
			if(strcmp(cur_node->first_attribute("version")->value(), "0.1") != 0) {
				std::cout << "WARN: " << itr->path() << " is wrong version." << std::endl;
				continue;
			}

			std::string profileID = cur_node->first_node("profileID")->value();
			if((profileID + ".xml").compare(itr->path().filename()) != 0) {
				std::cout << "WARN: " << itr->path() << " profileID does not match filename." << std::endl;
				continue;
			}

			std::string email = cur_node->first_node("email")->value();

			result.insert(std::pair<std::string, std::string>(profileID, profileID + " <" + email + ">"));
		}
	}

	return result;
}

std::string VadimoniumAPI::registerProfile(const std::string profileID) {
	std::string path = profileDataDirectory_ + profileID + ".xml";
	std::ifstream inputFile(path);
	std::stringstream buffer;
	buffer << inputFile.rdbuf();
	std::string inputString = buffer.str();
	inputFile.close();

	// Parse the XML
	std::vector<char> xml_copy(inputString.begin(), inputString.end());
	xml_copy.push_back('\0');

	rapidxml::xml_document<> doc;
	doc.parse<rapidxml::parse_no_data_nodes | rapidxml::parse_declaration_node>(&xml_copy[0]);

	rapidxml::xml_node<>* cur_node = doc.first_node("profile");
	if(strcmp(cur_node->first_attribute("version")->value(), "0.1") != 0) {
		std::cout << "WARN: " << path << " is wrong version." << std::endl;
		return NULL;
	}

	std::ifstream keyFile(profileDataDirectory_ + profileID + ".pub");
	std::stringstream keyBuffer;
	keyBuffer << keyFile.rdbuf();
	return keyBuffer.str();
}

std::string VadimoniumAPI::authenticateProfile(const std::string& profileID, const std::string& digest) {
	FILE* targetFile = fopen((privateKeyDirectory_ + profileID).c_str(), "r");
	RSA *privKey = PEM_read_RSAPrivateKey(targetFile, 0, 0, 0);
	fclose(targetFile);

	unsigned char* inbuffer = new unsigned char[RSA_size(privKey)],
		*outbuffer = new unsigned char[RSA_size(privKey)];

	BIO* b64 = BIO_new(BIO_f_base64());
	BIO* bp = BIO_new_mem_buf((void *)digest.c_str(), -1);
	bp = BIO_push(b64, bp); 
	BIO_read(bp, inbuffer, RSA_size(privKey));
	BIO_free_all(bp);

	int len = RSA_private_decrypt(RSA_size(privKey), inbuffer, outbuffer, privKey, RSA_PKCS1_OAEP_PADDING);
	outbuffer[len] = '\0';

	RSA_free(privKey);

	return std::string(reinterpret_cast<const char*>(outbuffer));
}