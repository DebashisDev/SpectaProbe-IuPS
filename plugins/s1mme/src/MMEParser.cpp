/*
 * MMEParser.cpp
 *
 *  Created on: Aug 1, 2016
 *      Author: Deb
 */

#include "MMEParser.h"
#include <algorithm>

MMEParser::MMEParser() {
	DecodedDataPtr = NULL;
	msgObj = NULL;
	initialize();
}

MMEParser::~MMEParser() {
}

void MMEParser::parseMMEProcedures(int proc_id, std::string xmlin, int length)
{
	//char key[100];
	std::string ret_val;
	std::string xml;
	std::string xml_chunk;
	std::string xml_sub_chunk;

	//Just to ensure we process a full xml
	xml = get_value(xmlin, "RANAP-PDU");
	if(xml.length()<=0) return;

//	msgObj->mmeData->procedure_code = proc_id;
//	msgObj->mmeData->procedure_desc.assign(MMEGlobal::Procedure_Val_String[msgObj->mmeData->procedure_code]);
//
//	switch(proc_id){
//		case 0:	//RAB-Assignment
//			if(xml.find("<RAB-AssignmentRequest>") != -1){
//				msgObj->mmeData->procedure_desc.assign("RAB-AssignmentRequest");
//				msgObj->mmeData->sessionstart = true;
//				if(xml.find("<SEQUENCE>") != -1){
//					xml_chunk = get_value(xml, "SEQUENCE");
//					if(xml.find("<id>") != -1){
//						ret_val = get_value(xml, "id");
//						if(ret_val.length() > 0){
//							int id = atoi(ret_val.c_str());
//							msgObj->mmeData->RABCauseId = id;
//							msgObj->mmeData->RABCauseDesc.assign(IUPSGlobal::Ranap_ID_Val_String[id]);
//						}
//					}
//				}
//				msgObj->mmeData->RABId.assign(get_value(xml, "rAB-ID"));
//				msgObj->mmeData->TEId.assign(get_value(xml, "gTP-TEI"));
//				msgObj->mmeData->PDPType.assign(get_value(xml, "pDP-TypeInformation"));
//
//			}else if(xml.find("<RAB-AssignmentResponse>") != -1){
//				msgObj->mmeData->procedure_desc.assign("RAB-AssignmentResponse");
//				msgObj->mmeData->sessionend = true;
//				xml_chunk = get_value(xml, "RAB-AssignmentResponse");
//				if(xml_chunk.find("<RAB-SetupOrModifiedList>") != -1){
//					if(xml_chunk.find("<RAB-SetupOrModifiedItem>") != -1){
//						msgObj->mmeData->RABCauseDesc.assign("RAB-SetupOrModifiedList");
//						setRABCauseId();		//It takes the Cause Description and feed the Cause Id
//						xml_sub_chunk = get_value(xml_chunk, "RAB-SetupOrModifiedItem");
//						if(xml_sub_chunk.length() > 0){
//							msgObj->mmeData->RABId.assign(get_value(xml_sub_chunk, "rAB-ID"));
//							msgObj->mmeData->TEId.assign(get_value(xml_sub_chunk, "gTP-TEI"));
//						}
//					}
//				}else if(xml_chunk.find("<RAB-ReleasedList>") != -1){
//					if(xml_chunk.find("<RAB-ReleasedItem>") != -1){
//						msgObj->mmeData->RABCauseDesc.assign("RAB-ReleasedList");
//						setRABCauseId();		//It takes the Cause Description and feed the Cause Id
//						xml_sub_chunk = get_value(xml_chunk, "RAB-ReleasedItem");
//						if(xml_sub_chunk.length() > 0){
//							msgObj->mmeData->RABId.assign(get_value(xml_sub_chunk, "rAB-ID"));
//						}
//					}
//				}
//			}
//			break;
//		case 1:	//
//			if(xml.find("<Iu-ReleaseCommand>") != -1){
//				msgObj->mmeData->procedure_desc.assign("Iu-ReleaseCommand");
//				xml_chunk = get_value(xml, "Cause");
//				if(xml_chunk.length() > 0){
//					ret_val = get_value(xml_chunk, "nAS");
//					if(ret_val.length() > 0){
//						break;
//					}
//					ret_val = get_value(xml_chunk, "radioNetwork");
//					if(ret_val.length() > 0){
//						break;
//					}
//				}
//			}else if(xml.find("<Iu-ReleaseComplete>") != -1){
//				msgObj->mmeData->procedure_desc.assign("Iu-ReleaseComplete");
//			}
//			break;
//		case 2:	//
//			break;
//		case 3:	//
//			break;
//		case 4:	//
//			break;
//		case 5:	//
//			break;
//		case 6:	//SecurityModeControl
//			if(xml.find("<SecurityModeCommand>") != -1){
//				msgObj->mmeData->procedure_desc.assign("SecurityModeCommand");
//				xml_chunk = get_value(xml, "SecurityModeCommand");
//				if(xml_chunk.length() > 0){
//					if(xml_chunk.find("<IntegrityProtectionAlgorithm>") != -1){
//						ret_val = get_value(xml_chunk, "IntegrityProtectionAlgorithm");
//					}
//					if(xml_chunk.find("<KeyStatus>") != -1){
//						ret_val = get_value(xml, "KeyStatus");
//					}
//				}
//				break;
//			}
//			if(xml.find("<SecurityModeComplete>") != -1){
//				msgObj->mmeData->procedure_desc.assign("SecurityModeComplete");
//				xml_chunk = get_value(xml, "SecurityModeComplete");
//				if(xml_chunk.length() > 0){
//					if(xml_chunk.find("<ChosenIntegrityProtectionAlgorithm>") != -1){
//						ret_val = get_value(xml_chunk, "ChosenIntegrityProtectionAlgorithm");
//					}
//				}
//				break;
//			}
//			//exit(0);
//			break;
//		case 7:	//
//			break;
//		case 8:	//
//			break;
//		case 9:	//
//			break;
//		case 10:	//
//			break;
//		case 11:	//
//			break;
//		case 12:	//
//			break;
//		case 13:	//
//			break;
//		case 14:	//Paging
//			//msgObj->mmeData->sccp_dir_ms_nw = false;
//			if(xml.find("<CN-DomainIndicator>") != -1){
//				ret_val = get_value(xml, "CN-DomainIndicator");
//			}
//			if(xml.find("<PermanentNAS-UE-ID>") != -1){
//				xml_chunk = get_value(xml, "PermanentNAS-UE-ID");
//				if(xml_chunk.length() > 0){
//					msgObj->mmeData->imsi.assign(processIMSI(get_value(xml_chunk, "iMSI")));
//				}
//			}
//			if(xml.find("<TemporaryUE-ID>") != -1){
//				xml_chunk = get_value(xml, "TemporaryUE-ID");
//				if(xml_chunk.length() > 0){
//					msgObj->mmeData->tmsi.assign(get_value(xml_chunk, "p-TMSI"));
//				}
//			}
//			if(xml.find("<PagingAreaID>") != -1){
//				xml_chunk = get_value(xml, "PagingAreaID");
//				if(xml_chunk.length() > 0){
//					xml_chunk = get_value(xml_chunk, "rAI");
//					if(xml_chunk.length() > 0){
//						xml_sub_chunk = get_value(xml_chunk, "lAI");
//						if(xml_sub_chunk.length() > 0){
//							msgObj->mmeData->PLMNIdHex.assign(get_value(xml_sub_chunk, "pLMNidentity"));
////							PLMNHexDec();
//							msgObj->mmeData->LACIdHex.assign(get_value(xml_sub_chunk, "lAC"));
////							sprintf(msgObj->mmeData->LACIdDec,"%d",(int)strtol(msgObj->mmeData->LACIdHex, NULL, 16));
//							msgObj->mmeData->LACIdDec.assign(std::to_string(strtol((const char *)msgObj->mmeData->LACIdHex.c_str(), NULL, 16)));
//							msgObj->mmeData->RACIdHex.assign(get_value(xml_sub_chunk, "rAC"));
//							msgObj->mmeData->RACIdDec.assign(std::to_string(strtol((const char *)msgObj->mmeData->RACIdHex.c_str(), NULL, 16)));
//						}
//					}
//				}
//				//If both IMSI and TMSI available insert them in tmsi session table
//				/*DEBDEBif(msgObj->mmeData->imsi != NULL && strlen(msgObj->mmeData->imsi) > 5 && msgObj->mmeData->tmsi != NULL && strlen(msgObj->mmeData->tmsi)>4){
//					parser->create_tmsi_session(msgObj->mmeData->tmsi,msgObj->mmeData->imsi);
//				}DEBDEB*/
//			}
//			break;
//		case 15:	//CommonID
//			msgObj->sccpData->sccp_session_id.assign(std::to_string(msgObj->sctpData->dpc))
//											 .append(msgObj->sccpData->sccp_dlr);
//			if(xml.find("<PermanentNAS-UE-ID>") != -1){
//				xml_chunk = get_value(xml, "PermanentNAS-UE-ID");
//				if(xml_chunk.length() > 0){
//					ret_val = get_value(xml_chunk, "iMSI");
//					if(ret_val.length() >= IMSI_LENGTH_MIN){
//						msgObj->mmeData->imsi.assign(processIMSI(ret_val));
//						//Update the IMSI into the session table
//						sm->update_sccp_lookup(SCCPGlobal::COL_IMSI, msgObj->mmeData->imsi, msgObj);
//					}
//				}
//			}
//			break;
//			case 16:	//
//				break;
//			case 17:	//
//				break;
//			case 18:	//
//				break;
//			case 19:	//InitialUE-Message
//				if(xml.find("<CN-DomainIndicator>") != -1){
//					ret_val = get_value(xml, "CN-DomainIndicator");
//				}
//				if(xml.find("<LAI>") != -1){
//					xml_chunk = get_value(xml, "LAI");
//					if(xml_chunk.length() > 0){
//						msgObj->mmeData->PLMNIdHex.assign(get_value(xml_chunk, "pLMNidentity"));
////						PLMNHexDec();
//						msgObj->mmeData->LACIdHex.assign(get_value(xml_chunk, "lAC"));
//						msgObj->mmeData->LACIdDec.assign(std::to_string(strtol((const char *)msgObj->mmeData->LACIdHex.c_str(), NULL, 16)));
//					}
//				}
//				if(xml.find("<RAC>") != -1){
//					msgObj->mmeData->RACIdHex,get_value(xml, "RAC").c_str();
//					msgObj->mmeData->RACIdDec.assign(std::to_string(strtol((const char *)msgObj->mmeData->RACIdHex.c_str(), NULL, 16)));
//
//				}
//				if(xml.find("<SAI>") != -1){
//					xml_chunk = get_value(xml, "SAI");
//					if(xml_chunk.length() > 0){
//						msgObj->mmeData->PLMNIdHex.assign(get_value(xml_chunk, "pLMNidentity"));
////						PLMNHexDec(); //TBD
//						msgObj->mmeData->LACIdHex.assign(get_value(xml_chunk, "lAC"));
//
//						msgObj->mmeData->LACIdDec.assign(std::to_string(strtol((const char *)msgObj->mmeData->LACIdHex.c_str(), NULL, 16)));
//						msgObj->mmeData->SACIdHex.assign(get_value(xml_chunk, "sAC"));
//						msgObj->mmeData->SACIdDec.assign(std::to_string(strtol((const char *)msgObj->mmeData->SACIdHex.c_str(), NULL, 16)));
//
//					}
//				}
//				//Construct the current RAI = PLMN-LAC-RAC as new RAI
////				makeNewRAI();	//TBD
//				if(xml.find("<GlobalRNC-ID>") != -1){
//					xml_chunk = get_value(xml, "GlobalRNC-ID");
//					if(xml_chunk.length() > 0){
//						//ret_val = get_value(xml_chunk, "pLMNidentity");
//						msgObj->mmeData->RNCId.assign(get_value(xml_chunk, "rNC-ID"));
//					}
//				}
//
//				//IMPORTANT....NAS PDU should be always extracted at the end
//				//This is to ensure that all data points captured in Ranap layer also
//				//gets polpulated in the GMM / SM decoding
//				if(xml.find("<NAS-PDU>") != -1){
//					ret_val = get_value(xml, "NAS-PDU");
//					ret_val.erase(std::remove(ret_val.begin(), ret_val.end(), ' '), ret_val.end());
//					//std::replace(ret_val.begin(), ret_val.end(), ' ','');
//					int nas_length = ret_val.length();
//					if(PCons::P_RANAP && PCons::DEBUG) printf("     			: NAS-PDU [%d] - %s\n", nas_length, ret_val.c_str());
////					unsigned char *bytes = (unsigned char*) malloc(nas_length/2);
////					memcpy(bytes, packStringToByteArray(ret_val.c_str(),nas_length), nas_length/2);
//					msgObj->mmeData->packetLengthNAS = nas_length/2;
////					nasParser->parsePacket(bytes, msgObj);
//					nasParser->parsePacket(packStringToByteArray(ret_val), msgObj);
////					free(bytes);
//				}
//				break;
//			case 20:	//DirectTransfer
//				//Message direction is determined in NAS-PDU content
//				if(xml.find("<LAI>") != -1){
//					xml_chunk = get_value(xml, "LAI");
//					if(xml_chunk.length() > 0){
//						msgObj->mmeData->PLMNIdHex.assign(get_value(xml_chunk, "pLMNidentity"));
////						PLMNHexDec();
//						ret_val = get_value(xml_chunk, "lAC");
//						msgObj->mmeData->LACIdHex.assign(get_value(xml_chunk, "lAC"));
//						msgObj->mmeData->LACIdDec.assign(std::to_string(strtol((const char *)msgObj->mmeData->LACIdHex.c_str(), NULL, 16)));
//					}
//				}
//				if(xml.find("<RAC>") != -1){
//					ret_val = get_value(xml, "RAC");
//					msgObj->mmeData->RACIdHex.assign(get_value(xml, "RAC"));
//					msgObj->mmeData->RACIdDec.assign(std::to_string(strtol((const char *)msgObj->mmeData->RACIdHex.c_str(), NULL, 16)));
//				}
//				if(xml.find("<SAI>") != -1){
//					xml_chunk = get_value(xml, "SAI");
//					if(xml_chunk.length() > 0){
//						msgObj->mmeData->PLMNIdHex.assign(get_value(xml_chunk, "pLMNidentity"));
////						PLMNHexDec();
//						msgObj->mmeData->LACIdHex.assign(get_value(xml_chunk, "lAC"));
//						msgObj->mmeData->LACIdDec.assign(std::to_string(strtol((const char *)msgObj->mmeData->LACIdHex.c_str(), NULL, 16)));
//						msgObj->mmeData->SACIdHex.assign(get_value(xml_chunk, "sAC"));
//						msgObj->mmeData->SACIdDec.assign(std::to_string(strtol((const char *)msgObj->mmeData->SACIdHex.c_str(), NULL, 16)));
//					}
//				}
//				//IMPORTANT....NAS PDU should be always extracted at the end
//				//This is to ensure that all data points captured in Ranap layer also
//				//gets polpulated in the GMM / SM decoding
//				if(xml.find("<NAS-PDU>") != -1){
//					ret_val = get_value(xml, "NAS-PDU");
//					//std::replace(ret_val.begin(), ret_val.end(), ' ','');
//					ret_val.erase(std::remove(ret_val.begin(), ret_val.end(), ' '), ret_val.end());
//					int nas_length = ret_val.length();
//					if(PCons::P_RANAP && PCons::DEBUG) printf("     			: NAS-PDU [%d] - %s\n", nas_length, ret_val.c_str());
//					if(nas_length==0) exit(0);
//					//unsigned char *bytes = (unsigned char*) malloc(nas_length/2);
//					//memcpy(bytes, packStringToByteArray(ret_val.c_str(),nas_length), nas_length/2);
//					msgObj->mmeData->packetLengthNAS = nas_length/2;
//					nasParser->parsePacket(packStringToByteArray(ret_val), msgObj);
////					free(bytes);
//				}
//				break;
//			case 21:	//
//				break;
//			case 22:	//
//				break;
//			case 23:	//
//				break;
//			case 24:	//
//				break;
//			case 25:	//
//				break;
//			case 26:	//
//				break;
//			case 27:	//
//				break;
//			case 28:	//
//				break;
//			case 29:	//
//				break;
//			case 30:	//
//				break;
//			case 31:	//
//				break;
//			case 32:	//
//				break;
//			case 33:	//
//				break;
//			case 34:	//
//				break;
//			case 35:	//
//				break;
//			case 36:	//
//				break;
//			case 37:	//
//				break;
//			case 38:	//
//				break;
//			case 39:	//
//				break;
//			case 40:	//
//				break;
//			case 41:	//
//				break;
//			case 42:	//
//				break;
//			case 43:	//
//				break;
//			case 44:	//
//				break;
//			case 45:	//
//				break;
//			case 46:	//
//				break;
//			case 47:	//
//				break;
//			default:
//				break;
//	}
}


void MMEParser::parsePacket(const BYTE packet, TPacket *msgObj)
{
	this->msgObj = msgObj;
	parsePacketToXml(packet,msgObj->mmeData->packetLength);
}

void MMEParser::parsePacketToXml(const BYTE packet, int length)
{
	char* identifier = "MME XML";
	std::string xml;
	xml.clear();

	if(PCons::P_MME && PCons::DEBUG) printf("%s packet\n", identifier);
	if(PCons::P_MME && PCons::DEBUG) printPacketBytes(packet,length);

	//Get the MME XML from file
	//xml = getMMEXML();

	//Get the MME XML from bytes
	xml = decode_mme_packet(packet, length);

	if(xml.empty() || xml.length() <= 0){
		printf("Error while processing MME packet!!! Exiting...");
		exit(0);
	}

//	if(msgObj->sccpData->sccp_session_id.compare("11345ea77c3") == 0){
////	if(PCons::r_pkt_cnt == 5) {
////		printf("PKT CNT %d , LINE CNT %d\n", PCons::r_pkt_cnt, PCons::r_line_cnt);
////		exit(0);
//		traceSessionXml(xml);
//	}

//	if(PCons::P_MME && PCons::DEBUG) printf("MME XML : %s\n", xml.c_str());
    int xmllength = xml.length();
    std::string::size_type sz;
    if(xml.find("<procedureCode>") != -1){
    	unsigned int procedureCode = atoi((get_value(xml, "procedureCode")).c_str());
//    	if(PCons::P_MME && PCons::DEBUG) printf("     MME 		: Procedure Code %d [%s]\n", procedureCode, IUPSGlobal::Procedure_Val_String[procedureCode]);
    	//Process XML content to extract MME PDUS
    	parseMMEProcedures(procedureCode, xml, xmllength);
    	xml="";
    }
}

string MMEParser::decode_mme_packet(const BYTE packet, int length)
{

	OssBuf		perEncodedData;						/* length and address of decoded / encoded data */
	OssBuf		berEncodedData;						/* length and address of decoded / encoded data */
    int			pdu_num;							/* PDU number */
	int			retcode;							/* return code */
	string		xml;								/* final XML output */
	xml.clear();

	DecodedDataPtr = NULL;							/* address of decoded data*/
	pdu_num = mmeS1AP_PDU_PDU; 						/* assign compiler-generated PDU id number */

	unsigned char *bytes = (unsigned char*)malloc(length);
	memcpy(bytes, packet, length);

	perEncodedData.value=bytes;
	perEncodedData.length=length;

	ossSetEncodingRules(world, OSS_PER_ALIGNED); 	/* Set encoding rules */

	/* Decode the encoded data */
	ossPrintHex(world, (char *) perEncodedData.value, perEncodedData.length);
	ossPrint(world, "\nCalling the decoder with the encoding...\n");
	retcode = ossDecode(world, &pdu_num, &perEncodedData, (void**)&DecodedDataPtr);
	if(retcode)
	{
		/* An decoder error occurred. Print error message. */
		ossPrint(world, "%s\n", ossGetErrMsg(world));
		return NULL;
	}
	else /* Decode successful */
	{
		/* Print out the data that was just decoded and free decoded PDU */
		berEncodedData.value = NULL;
		berEncodedData.length = 0; 		/* Initialize encoder output buffer to NULL. */

//		if(msgObj->sccpData->sccp_session_id.compare("11345ea77c3") == 0){
//			printf("XML String before processing ::\n%s\n",xml.c_str());
//			printf("berEncodedData String before processing ::\n%s\n",berEncodedData.value);
//		}

		/* Encoder will allocate needed memory.
		*/
		ossSetEncodingRules(world, OSS_EXER); /* Change encoding rules in use to  XER */
		retcode = ossEncode(world, pdu_num, DecodedDataPtr, &berEncodedData);
		if(retcode)
		{
			/* An error occurred; so, print error message. */
			ossPrint(world, "%s\n", ossGetErrMsg(world));
			return NULL;
		}
		else
		{
			/* Encode was successful. Print out resultant encoding of data. */
			//ossPrint(world, "\nData encoded to:\n\n");
			//ossPrintHex(world, (char *) encodedData.value, encodedData.length);
			xml.assign(std::string((char *)berEncodedData.value));
			xml.erase(std::remove(xml.begin(), xml.end(), ' '), xml.end());
			xml.erase(std::remove(xml.begin(), xml.end(), '\n'), xml.end());


			size_t idxStart = xml.find("<S1AP-PDU>");
			size_t idxEnd = xml.find("</S1AP-PDU>");
			if(idxEnd <= (idxStart+12)){
				printf("Error in parsing MME XML!!! Exiting");
				exit(0);
			}

			xml = xml.substr(idxStart,(idxEnd-idxStart)+12);

//			if(msgObj->sccpData->sccp_session_id.compare("11345ea77c3") == 0){
//				printf("\nEncoded Data Length : %d\n%s\n", length, xml.c_str());
//				//ossPrint(world, (char *) encodedData.value, encodedData.length);
//			}


//			char xml[encodedData.length];
//			sprintf(xml,"%s",encodedData.value);
//			printf("\n-------- XML Encoded Data --------------\n", xml);
			printf("%s\n", xml.c_str());
//			printf("---------------------------------------\n", xml);
//			printf("\n", xml);
//			for(int i=0; i<encodedData.length; i++)
//			{
//				printf("%c",encodedData.value[i]);
//			}
//			printf("\n-------- XML Encoded Data End --------------\n", xml);
		}

		ossFreePDU(world, pdu_num, DecodedDataPtr); /* free up PDU */
	}

	ossFreeBuf(world, perEncodedData.value); /* Free the encoder's output buffer */
	ossFreeBuf(world, berEncodedData.value); /* Free the encoder's output buffer */
	return xml;
}

void MMEParser::setRABCauseId(){
//	std::map<std::string,int>::iterator it1 = MAP_RANAP_ID.find(msgObj->mmeData->RABCauseDesc);
//	if(it1 != MAP_RANAP_ID.end()){
//		msgObj->mmeData->RABCauseId = MAP_RANAP_ID[msgObj->mmeData->RABCauseDesc];
//	}
}

string MMEParser::processIMSI(string imsi){
	//reverse the digits
	string newimsi;
	newimsi.clear();
	//printf("\nIMSI : %s\n",imsi.c_str());
	//IMSI 16 in length
	for(int i=0; i<imsi.length(); i+=2){
		newimsi.append(imsi.substr(i+1,1));
		newimsi.append(imsi.substr(i,1));
		//printf("i : %d %s %s %s\n",i,imsi.substr(i+1,1).c_str(),imsi.substr(i,1).c_str(),newimsi.c_str());
	}
	//Remove the last digit which is F
	//IMSI is 16 in length
	newimsi = newimsi.substr(0,15);
	//printf("Processes IMSI %s\n",newimsi.c_str());
	return newimsi;
}

BYTE MMEParser::packStringToByteArray(string input)
{
	int i = 0, n;
	int l = input.length()/2;
	char data[input.length()+10];
	unsigned char tmpByte[5000];
//	if(msgObj->sccpData->sccp_session_id.compare("11345ea77c3") == 0){
//		printf("ELO :: %s\n",input.c_str());
//	}
	sprintf(data,"%s",input.c_str());

	for(i = 0; i < l; i++) {
		sscanf(data+2*i, "%2X", &n);
		tmpByte[i] = (char)n;
	}
//	if(msgObj->sccpData->sccp_session_id.compare("11345ea77c3") == 0){
//		//printf("%s packet\n", identifier);
//		printPacketBytes(tmpByte, l);
//	}

	return tmpByte;
}

string MMEParser::get_value(std::string inxml, std::string cmptag)
{
	std::size_t start_pos = inxml.find(cmptag);
	if(start_pos != -1){
		//Shift start_pos to end of the tag to fetch the actual content
		start_pos += cmptag.length() + 1;					// increased by by 1 to take care of end >

		std::size_t end_pos = inxml.find(cmptag,start_pos);
		if(end_pos != -1){
			std::string xml_chunk = inxml.substr(start_pos, end_pos-start_pos-2);	//reducing by 2 to take care of </
			return xml_chunk;
		}
	}
	return "";
}

void MMEParser::initialize(){

	//Initialize ASN Decoder
	/*
	* Call ossinit() first to initialize the OSS global structure.
	*/
	if (ossinit(world, s1ap) != 0){
		printf("MMEParser::ASN Decoder Initialization Failed!!! Exiting...\n");
		exit(0);
	}

	/* Turn auto encoding on. */
	ossSetFlags(world, ossGetFlags(world) | DEBUGPDU | AUTOMATIC_ENCDEC);
	printf("MMEParser::ASN Decoder Initialization completed in AUTOMATIC_ENCDEC mode\n");
}

void MMEParser::printPacketBytes(const BYTE packet, int size)
{
		for(int i=0;i<size;i++){
			if((i%16 == 0)) printf("\n	%04x ", i);
			printf("%02x ", packet[i]);
		}
		printf("\n\n");
}
