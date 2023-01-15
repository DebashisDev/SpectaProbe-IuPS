/*
 * RANAPParser.cpp
 *
 *  Created on: 16-Jul-2016
 *      Author: Deb
 */

#include "RANAPParser.h"

//int RANAP_SESSION = 1;
//int GMM_SESSION = 2;

PCons::P_RANAP = true;
PCons::DEBUG = true;

RANAPParser::RANAPParser() {
	//cout << "Calling RANAPParser::RANAPParser() Constructor" << endl;
	nasParser = new NASParser();
//	sm = new SCCPSessionManager();
	initialize();
//	msgObj = NULL;
}

RANAPParser::~RANAPParser() {
	delete (nasParser);
//	delete (sm);
}


void RANAPParser::parseRanapProcedures(int proc_id, std::string xmlin, int length, MPacket *msgObj, SCTP *sctpMsgObj, int chunkNo)
{
	//char key[100];
	std::string ret_val;
	std::string xml;
	std::string xml_chunk;
	std::string xml_sub_chunk;

	//Just to ensure we process a full xml
	xml = get_value(xmlin, "RANAP-PDU");
	if(xml.length()<=0) return;

	sctpMsgObj->iups_procedure_code = proc_id;

	strcpy(sctpMsgObj->iups_procedure_desc, IUPSGlobal::Procedure_Val_String[sctpMsgObj->iups_procedure_code]);

	switch(proc_id){
		case 0:	//RAB-Assignment
			if(xml.find("<RAB-AssignmentRequest>") != -1){
				strcpy(sctpMsgObj->iups_procedure_desc, "RAB-AssignmentRequest");
				strcpy(sctpMsgObj->iups_session_ranap_id, "RAB-AssignmentRequest");
				sctpMsgObj->iups_rsessionstart = true;
				if(xml.find("<SEQUENCE>") != -1){
					xml_chunk = get_value(xml, "SEQUENCE");
					if(xml.find("<id>") != -1){
						ret_val = get_value(xml, "id");
						if(ret_val.length() > 0){
							int id = atoi(ret_val.c_str());
							sctpMsgObj->iups_RABCauseId = id;
							strcpy(sctpMsgObj->iups_RABCauseDesc, IUPSGlobal::Ranap_ID_Val_String[id]);
						}
					}
					if(xml.find("<MaxBitrate>") != -1){
						//printf("<MaxBitrate> Found...\n");
						xml_sub_chunk = get_value(xml, "maxBitrate");
						int idx_1 = xml_sub_chunk.find("<MaxBitrate>");
						//printf("<MaxBitrate> Found...idx_1 %d\n",idx_1);
						if(idx_1 != -1){
							ret_val = get_value(xml_sub_chunk, "MaxBitrate");
							//printf("idx_1 [%d] MaxBitrate :: %s\n",idx_1,ret_val.c_str());
							strcpy(sctpMsgObj->iups_Mbrdnl, ret_val.c_str());
							int endPos = 25 + ret_val.length();
							int idx_2 = xml_sub_chunk.find("<MaxBitrate>",endPos);
							if(idx_2 != -1){
								ret_val = get_value(endPos, xml_sub_chunk, "MaxBitrate");
								//printf("idx_2 [%d] MaxBitrate :: %s\n",idx_2,ret_val.c_str());
								strcpy(sctpMsgObj->iups_Mbrupl, ret_val.c_str());
							}
						}
					}
					if(xml.find("<RAB-Parameter-ExtendedMaxBitrateList>") != -1){
						xml_sub_chunk = get_value(xml, "RAB-Parameter-ExtendedMaxBitrateList");
						if(xml_sub_chunk.find("<ExtendedMaxBitrate>") != -1)
						{
							ret_val = get_value(xml_sub_chunk, "ExtendedMaxBitrate");
							//printf("ExtendedMaxBitrate :: %s\n",ret_val.c_str());
							strcpy(sctpMsgObj->iups_ExtendedMbr, ret_val.c_str());
						}
					}
				}
				strcpy(sctpMsgObj->iups_RABId, get_value(xml, "rAB-ID").c_str());
				strcpy(sctpMsgObj->iups_TEId, get_value(xml, "gTP-TEI").c_str());
				strcpy(sctpMsgObj->iups_PDPType, get_value(xml, "pDP-TypeInformation").c_str());

			}else if(xml.find("<RAB-AssignmentResponse>") != -1){

				if(xml.find("<MaxBitrate>") != -1)
					printf("%s\n",xml.c_str());

				strcpy(sctpMsgObj->iups_procedure_desc, "RAB-AssignmentResponse");
				strcpy(sctpMsgObj->iups_session_ranap_id, "RAB-AssignmentRequest");
				sctpMsgObj->iups_rsessionend = true;
				xml_chunk = get_value(xml, "RAB-AssignmentResponse");
				if(xml_chunk.find("<RAB-SetupOrModifiedList>") != -1){
					if(xml_chunk.find("<RAB-SetupOrModifiedItem>") != -1){
						strcpy(sctpMsgObj->iups_RABCauseDesc, "RAB-SetupOrModifiedList");
						setRABCauseId(msgObj, sctpMsgObj, chunkNo);		//It takes the Cause Description and feed the Cause Id
						xml_sub_chunk = get_value(xml_chunk, "RAB-SetupOrModifiedItem");
						if(xml_sub_chunk.length() > 0){
							strcpy(sctpMsgObj->iups_RABId, get_value(xml_sub_chunk, "rAB-ID").c_str());
							strcpy(sctpMsgObj->iups_TEId, get_value(xml_sub_chunk, "gTP-TEI").c_str());
						}
					}
				}else if(xml_chunk.find("<RAB-ReleasedList>") != -1){
					if(xml_chunk.find("<RAB-ReleasedItem>") != -1){
						strcpy(sctpMsgObj->iups_RABCauseDesc, "RAB-ReleasedList");
						setRABCauseId(msgObj, sctpMsgObj, chunkNo);		//It takes the Cause Description and feed the Cause Id
						xml_sub_chunk = get_value(xml_chunk, "RAB-ReleasedItem");
						if(xml_sub_chunk.length() > 0){
							strcpy(sctpMsgObj->iups_RABId, get_value(xml_sub_chunk, "rAB-ID").c_str());
						}
					}
				}
			}
			break;
		case 1:	//
			if(xml.find("<Iu-ReleaseCommand>") != -1){
				strcpy(sctpMsgObj->iups_procedure_desc, "Iu-ReleaseCommand");
				strcpy(sctpMsgObj->iups_session_ranap_id, "Iu-ReleaseCommand");
				sctpMsgObj->iups_rsessionstart = true;
				xml_chunk = get_value(xml, "Cause");
				if(xml_chunk.length() > 0){
					ret_val = get_value(xml_chunk, "nAS");
					if(ret_val.length() > 0){
						break;
					}
					ret_val = get_value(xml_chunk, "radioNetwork");
					if(ret_val.length() > 0){
						break;
					}
				}
			}else if(xml.find("<Iu-ReleaseComplete>") != -1){
				strcpy(sctpMsgObj->iups_procedure_desc, "Iu-ReleaseComplete");
				strcpy(sctpMsgObj->iups_session_ranap_id, "Iu-ReleaseCommand");
				sctpMsgObj->iups_rsessionend = true;
				sctpMsgObj->iups_EndCauseId = 0;
				strcpy(sctpMsgObj->iups_EndCauseDesc, "ReleaseComplete");
			}
			break;
		case 2:	//
			break;
		case 3:	//
			break;
		case 4:	//
			break;
		case 5:	//
			break;
		case 6:	//SecurityModeControl
			if(xml.find("<SecurityModeCommand>") != -1){
				strcpy(sctpMsgObj->iups_procedure_desc, "SecurityModeCommand");
				strcpy(sctpMsgObj->iups_session_ranap_id, "SecurityModeCommand");
				sctpMsgObj->iups_rsessionstart = true;
				xml_chunk = get_value(xml, "SecurityModeCommand");
				if(xml_chunk.length() > 0){
					if(xml_chunk.find("<IntegrityProtectionAlgorithm>") != -1){
						ret_val = get_value(xml_chunk, "IntegrityProtectionAlgorithm");
					}
					if(xml_chunk.find("<KeyStatus>") != -1){
						ret_val = get_value(xml, "KeyStatus");
					}
				}
				break;
			}
			if(xml.find("<SecurityModeComplete>") != -1){
				strcpy(sctpMsgObj->iups_procedure_desc, "SecurityModeComplete");
				strcpy(sctpMsgObj->iups_session_ranap_id, "SecurityModeCommand");
				sctpMsgObj->iups_rsessionend = true;
				xml_chunk = get_value(xml, "SecurityModeComplete");
				if(xml_chunk.length() > 0){
					if(xml_chunk.find("<ChosenIntegrityProtectionAlgorithm>") != -1){
						ret_val = get_value(xml_chunk, "ChosenIntegrityProtectionAlgorithm");
					}
				}
				break;
			}
			//exit(0);
			break;
		case 7:	//
			break;
		case 8:	//
			break;
		case 9:	//
			break;
		case 10:	//
			break;
		case 11:	//
			break;
		case 12:	//
			break;
		case 13:	//
			break;
		case 14:	//Paging
			//msgObj->iups_sccp_dir_ms_nw = false;
			if(xml.find("<CN-DomainIndicator>") != -1){
				ret_val = get_value(xml, "CN-DomainIndicator");
			}
			if(xml.find("<PermanentNAS-UE-ID>") != -1){
				xml_chunk = get_value(xml, "PermanentNAS-UE-ID");
				if(xml_chunk.length() > 0){
					strcpy(sctpMsgObj->iups_IMSI, processIMSI(get_value(xml_chunk, "iMSI")).c_str());
					//printf("                  PermanentNAS-UE-ID 14 IMSI : %s\n",msgObj->IMSI);
				}
			}
			if(xml.find("<TemporaryUE-ID>") != -1){
				xml_chunk = get_value(xml, "TemporaryUE-ID");
				if(xml_chunk.length() > 0){
					std::string tmsi = get_value(xml_chunk, "p-TMSI");
					std::transform(tmsi.begin(), tmsi.end(), tmsi.begin(), ::tolower);
					strcpy(sctpMsgObj->iups_TMSI, tmsi.c_str());
				}
			}
			if(xml.find("<PagingAreaID>") != -1){
				xml_chunk = get_value(xml, "PagingAreaID");
				if(xml_chunk.length() > 0){
					xml_chunk = get_value(xml_chunk, "rAI");
					if(xml_chunk.length() > 0){
						xml_sub_chunk = get_value(xml_chunk, "lAI");
						if(xml_sub_chunk.length() > 0){
							strcpy(sctpMsgObj->iups_PLMNIdHex, get_value(xml_sub_chunk, "pLMNidentity").c_str());
							strcpy(sctpMsgObj->iups_LACIdHex, get_value(xml_sub_chunk, "lAC").c_str());
							sctpMsgObj->iups_LACIdDec = strtol((const char *)sctpMsgObj->iups_LACIdHex, NULL, 16);
							strcpy(sctpMsgObj->iups_RACIdHex, get_value(xml_sub_chunk, "rAC").c_str());
							sctpMsgObj->iups_RACIdDec = strtol((const char *)sctpMsgObj->iups_RACIdHex, NULL, 16);
						}
					}
				}
				//If both IMSI and TMSI available insert them in tmsi session table
				/*DEBDEBif(msgObj->iups_imsi != NULL && strlen(msgObj->iups_imsi) > 5 && msgObj->iups_tmsi != NULL && strlen(msgObj->iups_tmsi)>4){
					parser->create_tmsi_session(msgObj->iups_tmsi,msgObj->iups_imsi);
				}DEBDEB*/
			}
			//printf("RANAP Parser :: IMSI [%s] TMSI [%s]\n",sctpMsgObj->iups_IMSI, sctpMsgObj->iups_TMSI);
			break;
		case 15:	//CommonID
			sprintf(sctpMsgObj->sccp_session_id, "%d%s", sctpMsgObj->sctp_dpc, sctpMsgObj->sccp_dlr);
			if(xml.find("<PermanentNAS-UE-ID>") != -1){
				xml_chunk = get_value(xml, "PermanentNAS-UE-ID");
				if(xml_chunk.length() > 0){
					ret_val = get_value(xml_chunk, "iMSI");
					if(ret_val.length() >= 15){
						strcpy(sctpMsgObj->iups_IMSI, processIMSI(ret_val).c_str());
//						printf("                  PermanentNAS-UE-ID 15 IMSI : %s\n",sctpMsgObj->iups_IMSI);
						//Update the IMSI into the session table
						//sm->update_sccp_lookup(SCCPGlobal::COL_IMSI, msgObj->IMSI, msgObj);
					}
				}
			}
			break;
			case 16:	//
				break;
			case 17:	//
				break;
			case 18:	//
				break;
			case 19:	//InitialUE-Message
				if(xml.find("<CN-DomainIndicator>") != -1){
					ret_val = get_value(xml, "CN-DomainIndicator");
				}
				if(xml.find("<LAI>") != -1){
					xml_chunk = get_value(xml, "LAI");
					if(xml_chunk.length() > 0){
						strcpy(sctpMsgObj->iups_PLMNIdHex, get_value(xml_chunk, "pLMNidentity").c_str());
//						PLMNHexDec();
						strcpy(sctpMsgObj->iups_LACIdHex, get_value(xml_chunk, "lAC").c_str());
						sctpMsgObj->iups_LACIdDec = strtol((const char *)sctpMsgObj->iups_LACIdHex, NULL, 16);
					}
				}
				if(xml.find("<RAC>") != -1){
					strcpy(sctpMsgObj->iups_RACIdHex, get_value(xml, "RAC").c_str());
					sctpMsgObj->iups_RACIdDec = strtol((const char *)sctpMsgObj->iups_RACIdHex, NULL, 16);

				}
				if(xml.find("<SAI>") != -1){
					xml_chunk = get_value(xml, "SAI");
					if(xml_chunk.length() > 0){
						strcpy(sctpMsgObj->iups_PLMNIdHex, get_value(xml_chunk, "pLMNidentity").c_str());
//						PLMNHexDec(); //TBD
						strcpy(sctpMsgObj->iups_LACIdHex, get_value(xml_chunk, "lAC").c_str());

						sctpMsgObj->iups_LACIdDec = strtol((const char *)sctpMsgObj->iups_LACIdHex, NULL, 16);
						strcpy(sctpMsgObj->iups_SACIdHex, get_value(xml_chunk, "sAC").c_str());
						sctpMsgObj->iups_SACIdDec = strtol((const char *)sctpMsgObj->iups_SACIdHex, NULL, 16);

					}
				}
				//Construct the current RAI = PLMN-LAC-RAC as new RAI
//				makeNewRAI();	//TBD
				if(xml.find("<GlobalRNC-ID>") != -1){
					xml_chunk = get_value(xml, "GlobalRNC-ID");
					if(xml_chunk.length() > 0){
						//ret_val = get_value(xml_chunk, "pLMNidentity");
						strcpy(sctpMsgObj->iups_RNCId, get_value(xml_chunk, "rNC-ID").c_str());
					}
				}

				//IMPORTANT....NAS PDU should be always extracted at the end
				//This is to ensure that all data points captured in Ranap layer also
				//gets polpulated in the GMM / SM decoding
				if(xml.find("<NAS-PDU>") != -1){
					ret_val = get_value(xml, "NAS-PDU");
					ret_val.erase(std::remove(ret_val.begin(), ret_val.end(), ' '), ret_val.end());
					//std::replace(ret_val.begin(), ret_val.end(), ' ','');
					int nas_length = ret_val.length();
					if(PCons::P_RANAP && PCons::DEBUG) printf("     			: NAS-PDU [%d] - %s\n", nas_length, ret_val.c_str());
					sctpMsgObj->iups_packetLengthNAS = nas_length/2;
					nasParser->parsePacket(packStringToByteArray(ret_val), msgObj, sctpMsgObj, chunkNo);
//					free(bytes);
				}
				break;
			case 20:	//DirectTransfer
				//Message direction is determined in NAS-PDU content
				if(xml.find("<LAI>") != -1){
					xml_chunk = get_value(xml, "LAI");
					if(xml_chunk.length() > 0){
						strcpy(sctpMsgObj->iups_PLMNIdHex, get_value(xml_chunk, "pLMNidentity").c_str());
//						PLMNHexDec();
						ret_val = get_value(xml_chunk, "lAC");
						strcpy(sctpMsgObj->iups_LACIdHex, get_value(xml_chunk, "lAC").c_str());
						sctpMsgObj->iups_LACIdDec = strtol((const char *)sctpMsgObj->iups_LACIdHex, NULL, 16);
					}
				}
				if(xml.find("<RAC>") != -1){
					ret_val = get_value(xml, "RAC");
					strcpy(sctpMsgObj->iups_RACIdHex, get_value(xml, "RAC").c_str());
					sctpMsgObj->iups_RACIdDec, strtol((const char *)sctpMsgObj->iups_RACIdHex, NULL, 16);
				}
				if(xml.find("<SAI>") != -1){
					xml_chunk = get_value(xml, "SAI");
					if(xml_chunk.length() > 0){
						strcpy(sctpMsgObj->iups_PLMNIdHex, get_value(xml_chunk, "pLMNidentity").c_str());
//						PLMNHexDec();
						strcpy(sctpMsgObj->iups_LACIdHex, get_value(xml_chunk, "lAC").c_str());
						sctpMsgObj->iups_LACIdDec = strtol((const char *)sctpMsgObj->iups_LACIdHex, NULL, 16);
						strcpy(sctpMsgObj->iups_SACIdHex, get_value(xml_chunk, "sAC").c_str());
						sctpMsgObj->iups_SACIdDec = strtol((const char *)sctpMsgObj->iups_SACIdHex, NULL, 16);
					}
				}
				//IMPORTANT....NAS PDU should be always extracted at the end
				//This is to ensure that all data points captured in Ranap layer also
				//gets polpulated in the GMM / SM decoding
				if(xml.find("<NAS-PDU>") != -1){
					ret_val = get_value(xml, "NAS-PDU");
					//std::replace(ret_val.begin(), ret_val.end(), ' ','');
					ret_val.erase(std::remove(ret_val.begin(), ret_val.end(), ' '), ret_val.end());
					int nas_length = ret_val.length();
					if(PCons::P_RANAP && PCons::DEBUG) printf("     			: NAS-PDU [%d] - %s\n", nas_length, ret_val.c_str());
					if(nas_length==0) exit(0);
					//unsigned char *bytes = (unsigned char*) malloc(nas_length/2);
					//memcpy(bytes, packStringToByteArray(ret_val.c_str(),nas_length), nas_length/2);
					sctpMsgObj->iups_packetLengthNAS = nas_length/2;
					nasParser->parsePacket(packStringToByteArray(ret_val), msgObj, sctpMsgObj, chunkNo);
//					free(bytes);
				}
				break;
			case 21:	//
				break;
			case 22:	//
				break;
			case 23:	//
				break;
			case 24:	//
				break;
			case 25:	//
				break;
			case 26:	//
				break;
			case 27:	//
				break;
			case 28:	//
				break;
			case 29:	//
				break;
			case 30:	//
				break;
			case 31:	//
				break;
			case 32:	//
				break;
			case 33:	//
				break;
			case 34:	//
				break;
			case 35:	//
				break;
			case 36:	//
				break;
			case 37:	//
				break;
			case 38:	//
				break;
			case 39:	//
				break;
			case 40:	//
				break;
			case 41:	//
				break;
			case 42:	//
				break;
			case 43:	//
				break;
			case 44:	//
				break;
			case 45:	//
				break;
			case 46:	//
				break;
			case 47:	//
				break;
			default:
				break;
	}
}

void RANAPParser::parsePacket(const BYTE packet, MPacket *msgObj, SCTP *sctpMsgObj, int chunkNo)
{
//	this->msgObj = msgObj;
	PCons::r_pkt_cnt++;
	//Set session type as RANAP
	//However if NAS PDU processing is done for GMM message, it is set as GMM_SESSION
	sctpMsgObj->iups_sessiontype = RANAP_SESSION;
	//Populate ranap packet length
	sctpMsgObj->iups_ranap_bytes = sctpMsgObj->iups_packetLengthRANAP;

	if(sctpMsgObj->iups_packetLengthRANAP > msgObj->frSize)
	{
		//Something is not right
		ProbeUtility::HEXDUMP((const void *)packet, msgObj->frSize);
		exit(0);
	}

	parsePacketToXml(packet, msgObj, sctpMsgObj, chunkNo);

	sctpMsgObj->sccp_ranap_present = true;
}

void RANAPParser::parsePacketToXml(const BYTE packet, MPacket *msgObj, SCTP *sctpMsgObj, int chunkNo)
{
	char* identifier = "RANAP XML";
	std::string xml = "";
	//Get the RANAP XML from bytes
	xml = decode_ranap_packet(packet, sctpMsgObj->iups_packetLengthRANAP);

	if(xml.empty() || xml.length() <= 0){
		printf("Error while processing RANAP packet!!! %lu\n", msgObj->packetNo); 
//		ProbeUtility::writePcap("RANAP.pcap", packet, msgObj->packetNo, msgObj->frSize, msgObj->frTimeEpochSec);

//		exit(0);
		return;
	}

    int xmllength = xml.length();
    std::string::size_type sz;
    if(xml.find("<procedureCode>") != -1){
    	unsigned int procedureCode = atoi((get_value(xml, "procedureCode")).c_str());
    	if(PCons::P_RANAP && PCons::DEBUG) printf("     RANAP 		: Procedure Code %d [%s]\n", procedureCode, IUPSGlobal::Procedure_Val_String[procedureCode]);
    	//Process XML content to extract RANAP PDUS
    	parseRanapProcedures(procedureCode, xml, xmllength, msgObj, sctpMsgObj, chunkNo);
    	if(PCons::P_RANAP && PCons::DEBUG) printf("     RANAP 		: Procedure Code Desc [%s]\n", sctpMsgObj->iups_procedure_desc);
    	xml="";
    }
}

string RANAPParser::decode_ranap_packet(const BYTE packet, int length)
{

	PDU_TYPEDEF 	*msg = NULL;	/* decoded message */
	PDU_CONTAINER 	pdu;			/* coding container */

	string xml;						/* final XML output */

	unsigned char *perEncodedData;

	//ProbeUtility::HEXDUMP(packet, length);
	try
	{

		perEncodedData = (unsigned char*)malloc(length);
		memcpy(perEncodedData, packet, length);

		EncodedBuffer msgbuf(length, (char *)perEncodedData);	/* encoded data */



		ctl.setEncodingRules(ENCODING_RULES);
		ctl.setDecodingFlags(ctl.getDecodingFlags() | AUTOMATIC_ENCDEC);

		pdu.decode(ctl, msgbuf);
		msg = pdu.get_data();

		//Now Encode into XML
		EncodedBuffer msgbufXml;

		ctl.setEncodingRules(XML_ENCODING_RULES);
		ctl.setEncodingFlags(ctl.getEncodingFlags() | AUTOMATIC_ENCDEC);

		pdu.encode(ctl, msgbufXml);

		//msgbufXml.print_xml(ctl,0);

		//printf("Printing XML\n");

		//printf("XML = %s\n", (char *)msgbufXml.get_data());

		xml.assign((char *)msgbufXml.get_data());

		//printf("XML = %s\n", xml.c_str());

		xml.erase(std::remove(xml.begin(), xml.end(), ' '), xml.end());
		xml.erase(std::remove(xml.begin(), xml.end(), '\n'), xml.end());

		size_t idxStart = xml.find("<RANAP-PDU>");
		size_t idxEnd = xml.find("</RANAP-PDU>");
		if(idxEnd <= (idxStart+12)){
			printf("Error in parsing RANAP XML!!! Exiting");
			//exit(0);
		}
		else
		{
			xml = xml.substr(idxStart,(idxEnd-idxStart)+12);
		}
		//printf("XML = %s\n", xml.c_str());


	} catch (...) {
		printf("An unexpected exception occurred While processing RANAP.\n");
    }

	free(perEncodedData);
	delete msg;
	return xml;
//	return "";
}


std::string RANAPParser::getRanapXML(){
	std::string line;
	PCons::r_line_cnt++;

	std::getline(IPGlobal::ranapxmlfile, line);
	if(line.empty() || line.length() < 10)
	{
		//printf("**** Read line from RANAP XML File : %s\n", line.c_str());
		std::getline(IPGlobal::ranapxmlfile, line);
	}
	return line;
}


void RANAPParser::initialize(){
	printf("RANAPParser::Initializing RANAP ID Map...");
	for(int i=0; i<sizeof(IUPSGlobal::ID_Val_String)/sizeof(IUPSGlobal::ID_Val_String[0]); i++){
//		printf("**** Initializing Ranap ID Map %s :: [%d]\n",IUPSGlobal::ID_Val_String[i],i);
		if(IUPSGlobal::ID_Val_String[i] != NULL){
			MAP_RANAP_ID[IUPSGlobal::ID_Val_String[i]] = i;
		}else{
//			printf("**** Initializing Ranap ID Map %s :: [%d]\n",IUPSGlobal::ID_Val_String[i],i);
		}
	}
	printf(" completed, read %d elements\n",MAP_RANAP_ID.size());
}


std::string RANAPParser::get_value(int startPos, std::string inxml, std::string cmptag)
{
	std::size_t start_pos = inxml.find(cmptag,startPos);
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

std::string RANAPParser::get_value(std::string inxml, std::string cmptag)
{
	return get_value(0,inxml,cmptag);
}

string RANAPParser::processIMSI(string imsi){
	//reverse the digits
//	if(PCons::DEBUG) printf("     			: Before %s\n",XDR::imsi);
	//char *raw;// = imsi;
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
return newimsi;
}

BYTE RANAPParser::packStringToByteArray(string input)
{
	int i = 0, n;
	int l = input.length()/2;
	char data[input.length()+10];
	unsigned char tmpByte[5000];
	sprintf(data,"%s",input.c_str());

	for(i = 0; i < l; i++) {
		sscanf(data+2*i, "%2X", &n);
		tmpByte[i] = (char)n;
	}
	return tmpByte;
}

void RANAPParser::printPacketBytes(const BYTE packet, int size)
{
		for(int i=0;i<size;i++){
			if((i%16 == 0)) printf("\n	%04x ", i);
			printf("%02x ", packet[i]);
		}
		printf("\n\n");
}

void RANAPParser::setRABCauseId(MPacket *msgObj, SCTP *sctpMsgObj, int chunkNo){
	std::map<std::string,int>::iterator it1 = MAP_RANAP_ID.find(sctpMsgObj->iups_RABCauseDesc);
	if(it1 != MAP_RANAP_ID.end()){
		sctpMsgObj->iups_RABCauseId = MAP_RANAP_ID[sctpMsgObj->iups_RABCauseDesc];
	}
}

