#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include "mdns.h"

#define ADDRESS_KEY ""

using namespace std;

typedef std::vector<DNSServiceRef> SvcVector;
SvcVector svc_vec_;

///< Callback for registration reply
static void register_reply_callback(DNSServiceRef sdRef,
                                    DNSServiceFlags flags,
                                    DNSServiceErrorType errorCode,
                                    const char *name,
                                    const char *regtype,
                                    const char *domain,
                                    void *context) 
{
    
};

///< Callback for browse
static void browse_callback(DNSServiceRef sdRef, 
                            DNSServiceFlags flags, 
                            uint32_t interfaceIndex, 
                            DNSServiceErrorType errorCode, 
                            const char *serviceName, 
                            const char *regtype, 
                            const char *replyDomain, 
                            void *context)
{
    cerr << serviceName << endl;
};

int main( int argv, char * argc[] )
{
    
    DNSServiceRef register_svc, browse_svc;
    DNSServiceErrorType err;
    
    char txt[255];
    TXTRecordRef record;
    TXTRecordCreate(&record, 255, &txt);
    err = TXTRecordSetValue(&record, ADDRESS_KEY, 0, NULL);
    
    err = DNSServiceRegister(&register_svc,
                             0 /* interface */,
                             0 /* flags */,
                             "Hello World" /* name */,
                             "_hello-world._udp" /* regtype */,
                             NULL /* domain */,
                             NULL /* host */,
                             22,
                             TXTRecordGetLength(&record) /* txtLen */,
                             TXTRecordGetBytesPtr(&record) /* txtRecord */,
                             register_reply_callback /* callback */,
                             NULL /* context */);

    TXTRecordDeallocate(&record);
    
    if (err != kDNSServiceErr_NoError) {
        cerr << "error in DNSServiceRegister: " << dns_service_strerror(err) << endl;
        return -1;
    }

    svc_vec_.push_back(register_svc);
    
    DNSServiceProcessResult(register_svc);

    cerr << "DNSServiceRegister succeeded" << endl;
    
    
    // kick off a browse for other services on the local network
    err = DNSServiceBrowse(&browse_svc,
                           0 /* flags */, 
                           0 /* interface */,
                           "_hello-world._udp" /* regtype */, 
                           NULL /* domain */,
                           browse_callback /* callback */,
                           NULL /* context */);

    if (err != kDNSServiceErr_NoError) {
        cerr << "error in DNSServiceRegister: " << dns_service_strerror(err) << endl;
        return -2;
    }
    
    DNSServiceProcessResult(browse_svc);

    return 0;
}