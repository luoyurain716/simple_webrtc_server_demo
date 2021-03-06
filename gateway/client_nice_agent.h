#ifndef _WXH_MY_NICE_H_
#define _WXH_MY_NICE_H_


#include <boost/thread/thread.hpp>
#include <iostream>
#include <agent.h>
#include <offer_answer_server.h>
#include <gio/gnetworking.h>

//#pragma comment(lib, "../libnice/nice/nice.lib")

//#pragma comment(lib, "../glib/lib/gio-2.0.lib")
//#pragma comment(lib, "../glib/lib/glib-2.0.lib")
//#pragma comment(lib, "../glib/lib/gmodule-2.0.lib")
//#pragma comment(lib, "../glib/lib/gobject-2.0.lib")
//#pragma comment(lib, "../glib/lib/gthread-2.0.lib")

#include "offer_answer_server.h"
//queue = g_async_queue_new();
class dtls_srtp;
class ClientNiceAgent
{
public:
	ClientNiceAgent(websocket_server* pserver, connection_hdl hdl, gboolean controlling,OfferAnswerServer *offerAnswerServer ,gchar* stun_addr = "stun.l.google.com", guint stun_port = 19302);

    //ClientNiceAgent(websocket_server* pserver, connection_hdl hdl, gboolean controlling, gchar* stun_addr = NULL, guint stun_port= 0);
    ~ClientNiceAgent();

    static void init();
    static void release();
    static void* loop_thread(void *data);

    int32_t add_stream(char* szstreamname, uint32_t componentnum);
    bool start_gather(int32_t streamid);
    void candidate_gathering_done(int32_t stream_id);
    void component_state_changed(int32_t streamid, uint32_t componentid, guint state);
    void new_selected_pair_full(guint stream_id,guint component_id, NiceCandidate *lcandidate, NiceCandidate* rcandidate);
    void nice_recv_data(int32_t streamid, uint32_t componentid, guint len, gchar *buf);

    bool set_remote_sdp(const char* sdp);
    bool set_remote_candidate(const char* szcandidate);
    bool send_data(int32_t streamid, uint32_t componentid, guint len, gchar *buf);
    bool send_data_need_protect(int32_t streamid, uint32_t componentid, guint len, gchar *buf);
    bool pushDataToAgent(RtpQuePacketObj *rtpQuePacketObj);
private:
    NiceAgent *agent;
    std::map < int32_t, uint32_t> mapstream_componet;
    websocket_server* pserver_;
    connection_hdl hdl_;
    std::string remote_sdp;
    dtls_srtp* dtls_;

    boost::thread* thread_audio_;
    OfferAnswerServer *mOfferAnswerServer;
    static GMainLoop *gloop;
    static GThread *gloopthread;
};



#endif
