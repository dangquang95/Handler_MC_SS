#ifndef NEPTUNE_XMLDESCRIPTION_H
#define NEPTUNE_XMLDESCRIPTION_H

#include "NeptuneClassLib.h"

namespace NeptuneClassLib
{
	////////////////////////////////////////////////////////////////////////////////////////
	//				
	//								XML Control
	//
	////////////////////////////////////////////////////////////////////////////////////////
	class NEPTUNE_CLASS_API CXMLDescription
	{
	public:
		
/*
			Description :
					Get child tree of a given XML node.
			Parameters :
					[IN] strNode : XML node.
					[OUT] pList : Child node tree.
			Return Values :
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of CXMLDescription class is not created.
					NEPTUNE_ERR_DeviceXML
							Object of NodeMaps is not created.
					NEPTUNE_ERR_GC
							XML node list get failed.
					NEPTUNE_ERR_Fail
						    XML node is not existed.
*/	
		ENeptuneError API_CALLTYPE GetNodeList(const _char_t* strNode, NEPTUNE_XML_NODE_LIST* pList);
	
/*
			Description :
					Get information of a XML node.
			Parameters :
					[IN] strNode : XML node.
					[OUT] pInfo : Information of a XML node.
			Return Values :
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of CXMLDescription class is not created.
					NEPTUNE_ERR_DeviceXML
							Object of NodeMaps is not created.
					NEPTUNE_ERR_GC
							XML node information get failed.
*/
		ENeptuneError API_CALLTYPE GetNodeInfo(const _char_t* strNode, NEPTUNE_XML_NODE_INFO* pInfo);
			
/*
			Description :
					Get node value of enum type of a XML node.
			Parameters :
					[IN] strNode : XML node.
					[OUT] pList : Information of enumeration node.
			Return Values :
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of CXMLDescription class is not created.
					NEPTUNE_ERR_DeviceXML
							Object of NodeMaps is not created.
					NEPTUNE_ERR_GC
							Node values of enum type get failed. 
					NEPTUNE_ERR_Fail
							Node's entry get failed.
*/
		ENeptuneError API_CALLTYPE GetNodeEnum(const _char_t* strNode, NEPTUNE_XML_ENUM_LIST* pList);

/*
			Description :
					Set node value of enum type of a XML node.
			Parameters :
					[IN] strNode : XML node.
					[IN] strVal : Enumeration string to write.
			Return Values :
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of CXMLDescription class is not created.
					NEPTUNE_ERR_DeviceXML
							Object of NodeMaps is not created.
					NEPTUNE_ERR_GC
							Node value of enum type set failed.
					NEPTUNE_ERR_Fail
							Node is not existed.
*/
		ENeptuneError API_CALLTYPE SetNodeEnum(const _char_t* strNode, _char_t* strVal);
		
/*
			Description :
					Set visibility for XML tree.
			Parameters :
					[IN] eVisibility : Visibility.
			Return Values :
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of CXMLDescription class is not created.
					NEPTUNE_ERR_DeviceXML
							Object of NodeMaps is not created.
*/
		ENeptuneError API_CALLTYPE SetVisibility(ENeptuneNodeVisibility eVisibility);
		
/*
			Description : 
					Get visibility for XML tree.
			Parameters :
					[OUT] peVisibility : Visibility.
			Return Values :
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of CXMLDescription class is not created.
					NEPTUNE_ERR_DeivceXML
							Object of NodeMpas is not created.
*/
		ENeptuneError API_CALLTYPE GetVisibility(ENeptuneNodeVisibility* peVisibility);
		
/*	
			Description :
					Set value of boolean type XML node.
			Parameters :
					[IN] strNode : XML node.
					[IN] bVal : Boolean value.
			Return Values :
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of CXMLDescription class is not created.
					NEPTUNE_ERR_DeivceXML
							Object of NodeMpas is not created.
					NEPTUNE_ERR_GC
							Node value of boolean type set failed.
*/
		ENeptuneError API_CALLTYPE SetNodeBool(const _char_t* strNode, ENeptuneBoolean bVal);
		
/*
			Description :
					Get value of boolean type XML node.
			Parameters :
					[IN] strNode : XML node.
					[OUT] pbVal : Boolean value.
			Return Values :
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of CXMLDescription class is not created.
					NEPTUNE_ERR_DeviceXML
							Object of NodeMpas is not created.
					NEPTUNE_ERR_GC
							Node value of boolean type get failed.
*/
		ENeptuneError API_CALLTYPE GetNodeBool(const _char_t* strNode, ENeptuneBoolean* pbVal);
		
/*
			Description :
					Set value of float type XML node.
			Parameters :
					[IN] strNode : XML node.
					[OUT] fVal : Float value.
			Return Values :
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of CXMLDescription class is not created.
					NEPTUNE_ERR_DeviceXML
							Object of NodeMpas is not created.
					NEPTUNE_ERR_GC
							Node value of float type set failed.
*/
		ENeptuneError API_CALLTYPE SetNodeFloat(const _char_t* strNode, _float32_t fVal);
		
/*
			Description :
					Get value of float type XML node.
			Parameters : 
					[IN] strNode : XML node.
					[OUT] pValueInfo : Float value information.
			Return Values :
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of CXMLDescription class is not created.
					NEPTUNE_ERR_DeviceXML
							Object of NodeMpas is not created.
					NEPTUNE_ERR_GC
							Node value of float type get failed.
*/
		ENeptuneError API_CALLTYPE GetNodeFloat(const _char_t* strNode, NEPTUNE_XML_FLOAT_VALUE_INFO* pValueInfo);
		
/*
			Description :
					Set value of integer type XML node.
			Parameters : 
					[IN] strNode : XML node.
					[IN] nVal : Integer value.
			Return Values :
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of CXMLDescription class is not created.
					NEPTUNE_ERR_DeviceXML
							Object of NodeMpas is not created.
					NEPTUNE_ERR_GC
							Node value of integer type set failed.
*/
		ENeptuneError API_CALLTYPE SetNodeInt(const _char_t* strNode, _int64_t nVal);
		
/*
			Description :
					Get value of integer type XML node.
			Parameters :
					[IN] strNode : XML node.
					[OUT] pValueInfo : Integer value information.
			Return Values : 
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of CXMLDescription class is not created.
					NEPTUNE_ERR_DeviceXML
							Object of NodeMpas is not created.
					NEPTUNE_ERR_GC
							Node value of integer type get failed.
*/
		ENeptuneError API_CALLTYPE GetNodeInt(const _char_t* strNode, NEPTUNE_XML_INT_VALUE_INFO* pValueInfo);
		
/*
			Description :
					Set value of string type XML node.
			Parameters : 
					[IN] strNode : XML node.
					[IN] strVal : String value.
			Return Values :
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of CXMLDsecription class is not created.
					NEPTUNE_ERR_DeviceXML
							Object of NodeMpas is not created.
					NEPTUNE_ERR_GC
							Node value of string type set failed.
*/
		ENeptuneError API_CALLTYPE SetNodeString(const _char_t* strNode, _char_t* strVal);
		
/*
			Description :
					Get value of string type XML node.
			Parameters :
					[IN] strNode : XML node.
					[OUT] pstrVal : String value information.
					[OUT] peAccessMode : Access mode of XML node.
			Return Values :
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of CXMLDescription class is not created.
					NEPTUNE_ERR_DeviceXML
							Object of NodeMpas is not created.
					NEPTUNE_ERR_GC
							Node value of string type get failed.
*/
		ENeptuneError API_CALLTYPE GetNodeString(const _char_t* strNode, _char_t* pstrVal, _uint32_t* pnSize, ENeptuneNodeAccessMode* peAccessMode);

/*
			Description :
					Set value of command type XML node.
			Parameters :
					[IN] strNode : XML node.
			Return Values :
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of CXMLDescription class is not created.
					NEPTUNE_ERR_DeviceXML
							Object of NodeMpas is not created.
*/
		ENeptuneError API_CALLTYPE SetNodeCommand(const _char_t* strNode);

		ENeptuneError API_CALLTYPE GetNodeList(_char_t* strNode, vector<string>& List);
		ENeptuneError API_CALLTYPE GetNodeEnum(_char_t* strNode, vector<string>& List, _uint32_t* pnIndex);	

	protected:
		CXMLDescription();
		~CXMLDescription();

		class CXMLDescriptionImpl;	
		CXMLDescriptionImpl* m_pxmlImpl;

	private:

	};
}

#endif /*NEPTUNE_XMLDESCRIPTION_H*/