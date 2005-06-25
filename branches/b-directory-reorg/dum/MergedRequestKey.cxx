#include "dum/MergedRequestKey.hxx"
#include "resiprocate/SipMessage.hxx"
#include "resiprocate/CSeqCategory.hxx"

using namespace resip;

const MergedRequestKey MergedRequestKey::Empty;

MergedRequestKey::MergedRequestKey()
{
}

MergedRequestKey::MergedRequestKey(const SipMessage& req) : 
   mRequestUri(Data::from(req.header(h_RequestLine).uri())),
   mCSeq(Data::from(req.header(h_CSeq))),
   mTag(req.header(h_From).exists(p_tag) ? req.header(h_From).param(p_tag) : Data::Empty),
   mCallId(req.header(h_CallID).value())
{
}

bool
MergedRequestKey::operator==(const MergedRequestKey& other) const
{
   return (mCallId == other.mCallId  &&
           mTag == other.mTag &&
           mCSeq == other.mCSeq &&
           mRequestUri == other.mRequestUri);
}

bool
MergedRequestKey::operator!=(const MergedRequestKey& other) const
{
   return !(*this == other);
}

bool
MergedRequestKey::operator<(const MergedRequestKey& other) const
{
   if ( mCallId < other.mCallId)
   {
      return true;
   }
   else if (mCallId > other.mCallId)
   {
      return false;
   }
   
   if (mTag < other.mTag)
   {
      return true;
   }
   else if (mTag > other.mTag)
   {
      return false;
   }
   
   if (mCSeq < other.mCSeq)
   {
      return true;
   }
   else if (mCSeq > other.mCSeq)
   {
      return false;
   }
   
   return (mRequestUri < other.mRequestUri);
}

Data& MergedRequestKey::cseq()
{
    return mCSeq;
}

const Data& MergedRequestKey::cseq() const
{
    return mCSeq;
}


/* ====================================================================
 * The Vovida Software License, Version 1.0 
 * 
 * Copyright (c) 2000 Vovida Networks, Inc.  All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 
 * 3. The names "VOCAL", "Vovida Open Communication Application Library",
 *    and "Vovida Open Communication Application Library (VOCAL)" must
 *    not be used to endorse or promote products derived from this
 *    software without prior written permission. For written
 *    permission, please contact vocal@vovida.org.
 *
 * 4. Products derived from this software may not be called "VOCAL", nor
 *    may "VOCAL" appear in their name, without prior written
 *    permission of Vovida Networks, Inc.
 * 
 * THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESSED OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, TITLE AND
 * NON-INFRINGEMENT ARE DISCLAIMED.  IN NO EVENT SHALL VOVIDA
 * NETWORKS, INC. OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT DAMAGES
 * IN EXCESS OF $1,000, NOR FOR ANY INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
 * USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
 * 
 * ====================================================================
 * 
 * This software consists of voluntary contributions made by Vovida
 * Networks, Inc. and many individuals on behalf of Vovida Networks,
 * Inc.  For more information on Vovida Networks, Inc., please see
 * <http://www.vovida.org/>.
 *
 */
