#ifndef SRC_PACKETLISTENER_H_
#define SRC_PACKETLISTENER_H_

#include <string>

#include "SolarGlobal.h"
#include "Log.h"
#include "SpectaTypedef.h"
#include "InterfaceMonitor.h"
#include "BaseConfig.h"

using namespace std;

class PacketListener : public BaseConfig {

	public:
		PacketListener(int perListenerRouters, int intfId);
		~PacketListener();
		VOID start();

	private:

		int ROUTER_TO_PROCESS = 0;
		int END_ROUTER_ID = 0;
		string InterfaceName;
		int InterfaceId = 0;
		uint64_t PKT_COUNTER = 0;
		int MAX_PKT_ALLOWED_PER_TIME_INDEX = 0;

		int cfg_hexdump;
		int cfg_timestamping;
		int cfg_verbose;

//		RawPkt *rawPkt;
		int t_index;

		VOID hexdump(const void* pv, int len);

		VOID consume_packet(interfaceThread* t, ef_packed_stream_packet* ps_pkt);
		VOID handle_rx_ps(interfaceThread* t, const ef_event* pev);
		VOID receivePackets(interfaceThread* t);

		VOID setPktCounter();
		VOID resetPktCounter();

		VOID countDiscardedPkt();

		VOID storepkt_i_0(BYTE pkt, uint16_t len, long tv_sec, uint32_t tv_nsec);
		VOID storepkt_i_1(BYTE pkt, uint16_t len, long tv_sec, uint32_t tv_nsec);
		VOID storepkt_i_2(BYTE pkt, uint16_t len, long tv_sec, uint32_t tv_nsec);
		VOID storepkt_i_3(BYTE pkt, uint16_t len, long tv_sec, uint32_t tv_nsec);

		VOID storepkt_i_0_r_0(BYTE pkt, uint16_t len, long tv_sec, uint32_t tv_nsec);
		VOID storepkt_i_0_r_1(BYTE pkt, uint16_t len, long tv_sec, uint32_t tv_nsec);
//		VOID storepkt_i_0_r_2(BYTE pkt, uint16_t len, long tv_sec, uint32_t tv_nsec);
//		VOID storepkt_i_0_r_3(BYTE pkt, uint16_t len, long tv_sec, uint32_t tv_nsec);

		VOID storepkt_i_1_r_0(BYTE pkt, uint16_t len, long tv_sec, uint32_t tv_nsec);
		VOID storepkt_i_1_r_1(BYTE pkt, uint16_t len, long tv_sec, uint32_t tv_nsec);
//		VOID storepkt_i_1_r_2(BYTE pkt, uint16_t len, long tv_sec, uint32_t tv_nsec);
//		VOID storepkt_i_1_r_3(BYTE pkt, uint16_t len, long tv_sec, uint32_t tv_nsec);

		VOID storepkt_i_2_r_0(BYTE pkt, uint16_t len, long tv_sec, uint32_t tv_nsec);
		VOID storepkt_i_2_r_1(BYTE pkt, uint16_t len, long tv_sec, uint32_t tv_nsec);
//		VOID storepkt_i_2_r_2(BYTE pkt, uint16_t len, long tv_sec, uint32_t tv_nsec);
//		VOID storepkt_i_2_r_3(BYTE pkt, uint16_t len, long tv_sec, uint32_t tv_nsec);

		VOID storepkt_i_3_r_0(BYTE pkt, uint16_t len, long tv_sec, uint32_t tv_nsec);
		VOID storepkt_i_3_r_1(BYTE pkt, uint16_t len, long tv_sec, uint32_t tv_nsec);
//		VOID storepkt_i_3_r_2(BYTE pkt, uint16_t len, long tv_sec, uint32_t tv_nsec);
//		VOID storepkt_i_3_r_3(BYTE pkt, uint16_t len, long tv_sec, uint32_t tv_nsec);

//		VOID storepkt_i_0(int rid);
//		VOID storepkt_i_1(int rid);
//		VOID storepkt_i_2(int rid);
//		VOID storepkt_i_3(int rid);
//
//		VOID storepkt_i_0_r_0();
//		VOID storepkt_i_0_r_1();
//		VOID storepkt_i_0_r_2();
//		VOID storepkt_i_0_r_3();
//
//		VOID storepkt_i_1_r_0();
//		VOID storepkt_i_1_r_1();
//		VOID storepkt_i_1_r_2();
//		VOID storepkt_i_1_r_3();
//
//		VOID storepkt_i_2_r_0();
//		VOID storepkt_i_2_r_1();
//		VOID storepkt_i_2_r_2();
//		VOID storepkt_i_2_r_3();
//
//		VOID storepkt_i_3_r_0();
//		VOID storepkt_i_3_r_1();
//		VOID storepkt_i_3_r_2();
//		VOID storepkt_i_3_r_3();

};

#endif /* SRC_PACKETLISTENER_H_ */
