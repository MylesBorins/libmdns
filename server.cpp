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

int main( int argv, char * argc[] )
{
    
    DNSServiceRef register_svc;
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

    int input;
    
    cout << "                                       " << endl;
    cout << "=======================================" << endl;
    cout << "||| Give me some input to quit brav |||" << endl;
    cout << "=======================================" << endl;
    cout << "                                       " << endl;
    cout << "[mdns]:";
    cin >> input;

    return 0;
}