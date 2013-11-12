/*
 *    Copyright 2007 Intel Corporation
 * 
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 * 
 *        http://www.apache.org/licenses/LICENSE-2.0
 * 
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

// Modified from code found at http://www.dtnrg.org/docs/code/DTN2/servlib/discovery/

#include "mdns.h"

using namespace std;

// borrowed from https://github.com/monome/serialosc
static void DNSSD_API mdns_callback(DNSServiceRef sdRef, DNSServiceFlags flags,
                   DNSServiceErrorType errorCode, const char *name,
                   const char *regtype, const char *domain, void *context) {

	/* on OSX, the bonjour library insists on having a callback passed to
	   DNSServiceRegister. */

	return;
}

const char* dns_service_strerror(DNSServiceErrorType err)
{
    switch(err) {
    case kDNSServiceErr_NoError: return "kDNSServiceErr_NoError";
    case kDNSServiceErr_Unknown: return "kDNSServiceErr_Unknown";
    case kDNSServiceErr_NoSuchName: return "kDNSServiceErr_NoSuchName";
    case kDNSServiceErr_NoMemory: return "kDNSServiceErr_NoMemory";
    case kDNSServiceErr_BadParam: return "kDNSServiceErr_BadParam";
    case kDNSServiceErr_BadReference: return "kDNSServiceErr_BadReference";
    case kDNSServiceErr_BadState: return "kDNSServiceErr_BadState";
    case kDNSServiceErr_BadFlags: return "kDNSServiceErr_BadFlags";
    case kDNSServiceErr_Unsupported: return "kDNSServiceErr_Unsupported";
    case kDNSServiceErr_NotInitialized: return "kDNSServiceErr_NotInitialized";
    case kDNSServiceErr_AlreadyRegistered: return "kDNSServiceErr_AlreadyRegistered";
    case kDNSServiceErr_NameConflict: return "kDNSServiceErr_NameConflict";
    case kDNSServiceErr_Invalid: return "kDNSServiceErr_Invalid";
    case kDNSServiceErr_Firewall: return "kDNSServiceErr_Firewall";
    case kDNSServiceErr_Incompatible: return "kDNSServiceErr_Incompatible";
    case kDNSServiceErr_BadInterfaceIndex: return "kDNSServiceErr_BadInterfaceIndex";
    case kDNSServiceErr_Refused: return "kDNSServiceErr_Refused";
    case kDNSServiceErr_NoSuchRecord: return "kDNSServiceErr_NoSuchRecord";
    case kDNSServiceErr_NoAuth: return "kDNSServiceErr_NoAuth";
    case kDNSServiceErr_NoSuchKey: return "kDNSServiceErr_NoSuchKey";
    case kDNSServiceErr_NATTraversal: return "kDNSServiceErr_NATTraversal";
    case kDNSServiceErr_DoubleNAT: return "kDNSServiceErr_DoubleNAT";
    case kDNSServiceErr_BadTime: return "kDNSServiceErr_BadTime";
    default:
        static char buf[32];
        snprintf(buf, sizeof(buf), "%d", err);
        return buf;
    }
}

void sayHelloWorld( )
{
    cerr << "Hello World" << endl;
};