#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include "mdns.h"

#define ADDRESS_KEY ""

using namespace std;

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
    
    DNSServiceRef browse_svc;
    DNSServiceErrorType err;
    
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