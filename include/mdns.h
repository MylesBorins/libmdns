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

#ifndef _MDNS_H_
#define _MDNS_H_

// #include <stdlib.h>
#include <iostream>
#include <vector>
#include <dns_sd.h>

class mdns
{
public:
    mdns(){};
    ~mdns(){};
public:    
    void run();
private:
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
        ((mdns*)context)->
            handle_register_reply(sdRef, flags, errorCode, name,
                                  regtype, domain);
    }

    /// Registration reply handler
    void handle_register_reply(DNSServiceRef sdRef,
                               DNSServiceFlags flags,
                               DNSServiceErrorType errorCode,
                               const char *name,
                               const char *regtype,
                               const char *domain);

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
        ((mdns*)context)->
            handle_browse(sdRef, flags, interfaceIndex, errorCode, 
                          serviceName, regtype, replyDomain);
    }

    /// Browse handler
    void handle_browse(DNSServiceRef sdRef,
                       DNSServiceFlags flags, 
                       uint32_t interfaceIndex, 
                       DNSServiceErrorType errorCode, 
                       const char *serviceName, 
                       const char *regtype, 
                       const char *replyDomain);

    ///< Callback for resolve
    static void resolve_callback(DNSServiceRef sdRef, 
                                 DNSServiceFlags flags, 
                                 uint32_t interfaceIndex, 
                                 DNSServiceErrorType errorCode, 
                                 const char *fullname, 
                                 const char *hosttarget,
                                 uint16_t port,
                                 uint16_t txtlen,
                                 const char* txtRecord,
                                 void *context)
    {
        ((mdns*)context)->
            handle_resolve(sdRef, flags, interfaceIndex, errorCode, 
                           fullname, hosttarget, port, txtlen, txtRecord);
    }

    /// Resolve handler
    void handle_resolve(DNSServiceRef sdRef, 
                        DNSServiceFlags flags, 
                        uint32_t interfaceIndex, 
                        DNSServiceErrorType errorCode, 
                        const char *fullname, 
                        const char *hosttarget,
                        uint16_t port,
                        uint16_t txtlen,
                        const char* txtRecord);

    /**
     * For some lame reason, the dns service doesn't define a strerror
     * analog
     */
    // static const char* dns_service_strerror(DNSServiceErrorType err);

    /**
     * Remove the given DNSServiceRef from the vector.
     */
    void remove_svc(DNSServiceRef sdRef);
};

const char* dns_service_strerror(DNSServiceErrorType err);

void sayHelloWorld( );

#endif